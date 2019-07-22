#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <mutex>
#include <thread>
#include <stdlib.h>
#include <sstream>
#include <cstdlib>
#include <memory>
#include <future>
#include <functional>
#include <type_traits>
#include <cassert>
#include <fstream>
#include <filesystem>

//using namespace std;

#define DEFAULT_MEMORY 1000000
#define MB_TO_BYTE 1000000 // 1MB = 10^6 bytes
#define TEMP_PATH "./"

/************************************************************************************************
 * 		THREAD POOLING 
 * 
 * REF: https://github.com/progschj/ThreadPool
 * 
 ************************************************************************************************/
class ThreadPool
{
public:
    ThreadPool(size_t);
    template <class F, class... Args>
    auto enqueue(F &&f, Args &&... args)
        -> std::future<typename std::result_of<F(Args...)>::type>;
    ~ThreadPool();

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};

// the constructor just launches some amount of workers
inline ThreadPool::ThreadPool(size_t threads)
    : stop(false)
{
    for (size_t i = 0; i < threads; ++i)
        workers.emplace_back(
            [this] {
                for (;;)
                {
                    std::function<void()> task;

                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        this->condition.wait(lock,
                                             [this] { return this->stop || !this->tasks.empty(); });
                        if (this->stop && this->tasks.empty())
                            return;
                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }

                    task();
                }
            });
}

// add new work item to the pool
template <class F, class... Args>
auto ThreadPool::enqueue(F &&f, Args &&... args)
    -> std::future<typename std::result_of<F(Args...)>::type>
{
    using return_type = typename std::result_of<F(Args...)>::type;

    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...));

    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queue_mutex);

        // don't allow enqueueing after stopping the pool
        if (stop)
            throw std::runtime_error("enqueue on stopped ThreadPool");

        tasks.emplace([task]() { (*task)(); });
    }
    condition.notify_one();
    return res;
}

// the destructor joins all threads
inline ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for (std::thread &worker : workers)
        worker.join();
}

/************************************************************************************************
 * 
 * 	SORT THREAD 
 * 
 ************************************************************************************************/

class SortThread
{
private:
    int m_block_id;
    std::string m_input_path;
    std::string m_output_path;
    std::vector<std::string> m_data;

public:
    SortThread(const std::string output, std::vector<std::string> &data, int blockId)
        : m_output_path(output), m_data(data), m_block_id(blockId) {}

    static void *run(void *obj)
    {
        ((SortThread *)obj)->sortAndWrite();
        delete ((SortThread *)obj);
        return nullptr;
    }

    void sortAndWrite()
    {
        std::stringstream fileName;
        fileName << m_output_path << "." << m_block_id;

        std::ofstream inFile(fileName.str(), std::ios::out | std::ios::in);
        sort(m_data.begin(), m_data.end());
        for (size_t i = 0; i < m_data.size(); i++)
        {
            inFile << m_data[i] << '\n';
        }
        inFile.close();
        m_data.clear();
    }
};

/*************************************************************************************************
 * 
 * 		K-way merge sorted 
 * 
 ************************************************************************************************/
template <class T>
class MinHeapFile
{
public:
    T data;
    std::istream *stream;
    bool (*compFunc)(const T &a, const T &b);

public:
    MinHeapFile(const T &data, std::istream *stream, bool (*compFunc)(const T &a, const T &b))
        : data(data), stream(stream), compFunc(compFunc) {}

    MinHeapFile(const T &data, std::istream *stream)
        : data(data), stream(stream) {}

    bool operator<(const MinHeapFile &a) const
    {
        return !(compFunc(data, a.data));
    }
};

template <class T>
class KwayMerge
{
public:
    // Constructor, using custom comparision function
    KwayMerge(const std::string &inFile,
              const std::string &outFile,
              bool (*compareFunction)(const T &a, const T &b) = NULL,
              int memory = DEFAULT_MEMORY,
              std::string tempPath = TEMP_PATH);

    // Constructor, using T's overloaded < operator. Must be defined.
    KwayMerge(const std::string &inFile,
              const std::string &outFile,
              int memory = DEFAULT_MEMORY,
              std::string tempPath = TEMP_PATH);

    // Destructor
    ~KwayMerge(void);

    void Sort();
    void setMemrorySize(int memory);
    long long int getFileSize();
    void setComparision(bool (*compareFunction)(const T &a, const T &b));

private:
    // Driver the creation of sorted sub-files stored on disk
    void blockSort();

    // Drivers the merging of the sorted temp files.
    // Final, sorted and merged output is written to "out"
    void merge();
    void writeToTempFile(const std::vector<T> &blockData);
    void openTempFiles();
    void closeTempFiles();

private:
    std::string m_input_path;
    std::string m_output_path;
    std::string _temp_path;
    bool (*_compareFunction)(const T &a, const T &b);
    std::vector<std::string> _vTempFileNames;
    std::vector<std::ifstream *> _vTempFiles;
    unsigned int m_memory;
    unsigned int m_file_counter;
    bool _tempFileUsed;

    // For multithreading operation.
private:
    long long int m_file_size;    // Size of the "input.txt" file
    long long int m_memory_block; // Size of block which is processed by each threads
    unsigned int m_num_threads;   // Number of threads
    unsigned int m_num_blocks;    // Number of blocks
    unsigned int m_block_counter;
};

template <class T>
KwayMerge<T>::KwayMerge(const std::string &inFile,
                        const std::string &outFile,
                        bool (*compareFunction)(const T &a, const T &b),
                        int memory,
                        std::string tempPath)
    : m_input_path(inFile), m_output_path(outFile), _compareFunction(compareFunction), _temp_path(tempPath), m_memory(memory), m_file_counter(0)
{
    m_file_size = getFileSize();
    m_num_blocks = 0;
    //m_memory_block = m_memory / m_num_threads;
}

template <class T>
KwayMerge<T>::KwayMerge(const std::string &inFile,
                        const std::string &outFile,
                        int memory,
                        std::string tempPath)
    : m_input_path(inFile), m_output_path(outFile), _compareFunction(NULL), _temp_path(tempPath), m_memory(memory), m_file_counter(0)
{
    m_file_size = getFileSize();
    m_num_blocks = 0;
    //m_memory_block = m_memory / m_num_threads;
}

template <class T>
KwayMerge<T>::~KwayMerge(void)
{
}

template <class T>
long long int KwayMerge<T>::getFileSize()
{
    long long int fileSize = 0;
    std::ifstream inFile(m_input_path);
    inFile.seekg(0, inFile.end);
    fileSize = inFile.tellg();
    std::cout << "+++++ Size of File = " << fileSize << '\n';
    inFile.seekg(0, inFile.beg);
    inFile.close();
    return fileSize;
}

template <class T>
void KwayMerge<T>::Sort()
{
    blockSort();
    merge();
}

template <class T>
void KwayMerge<T>::setMemrorySize(int memory)
{
    m_memory = memory;
}

template <class T>
void KwayMerge<T>::setComparision(bool (*compareFunction)(const T &a, const T &b))
{
    _compareFunction = compareFunction;
}

template <class T>
void KwayMerge<T>::blockSort()
{
    std::ifstream *input = new std::ifstream(m_input_path.c_str(), std::ios::in);

    // Bail unless the file is legit
    if (input->good() == false)
    {
        std::cerr << "Error: The requested input file (" << m_input_path << ") could not be opnened. Exiting!\n";
        exit(1);
    }

    std::vector<T> blockData;
    unsigned int totalBytes = 0;
    _tempFileUsed = false;

    T line;

    while (*input >> line)
    {
        blockData.push_back(line);
        totalBytes += sizeof(line);

        // Sort the buffer and write to a temp file if we have filled up our quota
        if (totalBytes > m_memory)
        {
            if (_compareFunction != NULL)
            {
                //std::sort(lineBuffer.begin(), lineBuffer.end(), *_compareFunction);
                std::sort(blockData.begin(), blockData.end());
            }
            else
            {
                std::sort(blockData.begin(), blockData.end());
            }

            // Write the sorted data to a temp file
            writeToTempFile(blockData);
            // SortThread t * = new SortThread(m_input_path, m_output_path, lineBuffer, m_block_counter);
            // t.run();

            // Clear the buffer for the next run
            blockData.clear();
            _tempFileUsed = true;
            totalBytes = 0;
            m_block_counter++;
        }
    }

    // Handle the run (if any) from the last chunk of the input file
    if (blockData.empty() == false)
    {
        // Write the last "chunk" to the temp file if a temp file had to be used
        if (_tempFileUsed == true)
        {
            if (_compareFunction)
            {
                //std::sort(lineBuffer.begin(), lineBuffer.end(), *_compareFunction);
                std::sort(blockData.begin(), blockData.end());
            }
            else
            {
                std::sort(blockData.begin(), blockData.end());
            }
            // Write the sorted data to a temp file
            writeToTempFile(blockData);
        }
        else
        {
            std::ofstream outFile(m_output_path, std::ios::out);

            if (_compareFunction)
            {
                //std::sort(lineBuffer.begin(), lineBuffer.end(), *_compareFunction);
                std::sort(blockData.begin(), blockData.end());
            }
            else
            {
                std::sort(blockData.begin(), blockData.end());
            }

            for (size_t i = 0; i < blockData.size(); ++i)
            {
                outFile << blockData[i] << '\n';
            }
            outFile.close();
        }
    }
}

template <class T>
void KwayMerge<T>::writeToTempFile(const std::vector<T> &blockData)
{
    std::cout << "Write to temp file [" << m_file_counter << "]\n";
    // Name the current temp file
    std::stringstream tempFileSS;
    tempFileSS << m_input_path << "." << m_file_counter;
    std::string tempFileName = tempFileSS.str();

    std::ofstream *output;
    output = new std::ofstream(tempFileName.c_str(), std::ios::out);

    for (size_t i = 0; i < blockData.size(); ++i)
    {
        *output << blockData[i] << '\n';
    }

    // Update the temp file number and add the temp file to the list of temp files.
    ++m_file_counter;
    output->close();
    delete output;

    _vTempFileNames.push_back(tempFileName);
}

template <class T>
void KwayMerge<T>::merge()
{
    std::cout << "KwayMerge::merge()...\n";
    // Skip this step if there are no temp files to merge.
    if (_tempFileUsed == false)
        return;

    std::ofstream outFile;
    outFile.open(m_output_path.c_str(), std::ios::out);
    // Open the sorted temp files p for merging.
    // Loads ifstream pointer into _vTempFiles
    openTempFiles();

    // Priority queue for the buffer
    std::priority_queue<MinHeapFile<T>> buildMinHeap;

    // extract the first line from each temp file
    T line;

    for (size_t i = 0; i < _vTempFiles.size(); ++i)
    {
        *_vTempFiles[i] >> line;
        buildMinHeap.push(MinHeapFile<T>(line, _vTempFiles[i], _compareFunction));
    }

    // keep working until the queue is empty
    while (!buildMinHeap.empty())
    {
        MinHeapFile<T> lowest = buildMinHeap.top();

        // Write the entry from the top of the queue
        outFile << lowest.data << '\n';

        // Remove this record from the queue
        buildMinHeap.pop();

        // Add the next line from the lowest stream to the queue
        flush(outFile);
        if (*(lowest.stream) >> line)
        {
            buildMinHeap.push(MinHeapFile<T>(line, lowest.stream, _compareFunction));
        }
    }

    // Clean the temp files
    closeTempFiles();
    outFile.close();
}

template <class T>
void KwayMerge<T>::openTempFiles()
{
    std::cout << "openTempFiles()\n";
    for (size_t i = 0; i < _vTempFileNames.size(); ++i)
    {
        std::ifstream *file;

        /*	if (is_regular_file(_vTempFileNames[i]))
			cout << "is regular File\n";*/
        file = new std::ifstream(_vTempFileNames[i].c_str(), std::ios::in);

        if (file->good() == true)
        {
            _vTempFiles.push_back(file);
        }
        else
        {
            std::cerr << "Unable to open tem file (" << _vTempFileNames[i]
                      << "). Exiting...\n";
            exit(1);
        }
    }
}

template <class T>
void KwayMerge<T>::closeTempFiles()
{
    std::cout << "closeTempFiles()\n";
    // delete the pointers to the temp file.
    for (size_t i = 0; i < _vTempFiles.size(); ++i)
    {
        _vTempFiles[i]->close();
        delete _vTempFiles[i];
    }

    // delete the temp files from the file system.
    for (size_t i = 0; i < _vTempFileNames.size(); ++i)
    {
        remove(_vTempFileNames[i].c_str());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
class Utils
{
public:
    static std::string getFileName(std::string file_path)
    {
        // Get last dot position
        std::size_t dotPos = file_path.rfind('.');
        std::size_t sepPos = file_path.rfind('/');

        if (sepPos != std::string::npos)
        {
            return file_path.substr(sepPos + 1, file_path.size() - (dotPos != std::string::npos ? 1 : dotPos));
        }
        return "";
    }

    static bool ASCENDING(const std::string &a, const std::string &b) { return a <= b; }
    static bool DESCENDING(const std::string &a, const std::string &b) { return a >= b; }

    static void Generate_Random_Text_File(std::string gen_file_name, long long int gen_file_size)
    {
        // open file
        std::ofstream myfile;
        myfile.open(gen_file_name.c_str());
        long long int total_size_so_far = 0;
        int wordsize = 0;
        char letter;

        while (total_size_so_far < gen_file_size)
        {
            wordsize = 1 + rand() % 14; // random word length
            while (total_size_so_far + wordsize > gen_file_size)
                wordsize = 1 + rand() % 14;
            for (int j = 0; j < wordsize; j++)
            {
                letter = 'a' + rand() % 26;
                myfile << letter;
            }
            total_size_so_far += wordsize;
            if (total_size_so_far + 1 < gen_file_size)
            {
                myfile << '\n';
                total_size_so_far++;
            }
        }
        myfile.close();
        std::cout << "File " << gen_file_name << " has been generated!\n";
    }
};

int main()
{
    std::cout << "Hello World!\n";
    std::string inFile = "input.txt";
    std::string outFile = "output.txt";
    int memory = 1; // 1MB

    std::string tempPath = "D:\\_code_cpp\SearchEnginerTest\kwaymerge\kwaymerge\tmp";

    long long int sizeFile = 5; // MB

    //Generate_Random_Text_File(inFile, sizeFile * MB_TO_BYTE);

    // ----- START TIME
    auto start = std::chrono::system_clock::now();

    KwayMerge<std::string> *sorter = new KwayMerge<std::string>(inFile, outFile, Utils::ASCENDING, memory * MB_TO_BYTE, tempPath);
    sorter->Sort();

    // ----- END TIME
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    std::cout << "\n++++++++++ PROCESSED TIME = " << elapsed_seconds.count() << "++++++++++\n";

    return 0;
}