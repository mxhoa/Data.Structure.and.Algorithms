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
#include <iterator>
#include <fstream>

//using namespace std;

/* FOREGROUND */
#define RST "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"

#define FRED(x) KRED x RST
#define FGRN(x) KGRN x RST
#define FYEL(x) KYEL x RST
#define FBLU(x) KBLU x RST
#define FMAG(x) KMAG x RST
#define FCYN(x) KCYN x RST
#define FWHT(x) KWHT x RST

#define BOLD(x) "\x1B[1m" x RST
#define UNDL(x) "\x1B[4m" x RST

///////////////////////////////////////////////

#define DEFAULT_MEMORY 1000000
#define MB_TO_BYTE 1000000
#define BLOCK_SIZE 50 // Memory Size for each blocks (MB)
#define TEMP_PATH "./"
#define KB_TO_BYTE 1024

/************************************************************************************************
 *      THREAD POOLING
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
 *  SORT THREAD
 *
 ************************************************************************************************/

class SortThread
{
private:
    unsigned int m_chunk_id;          // The position of chunk in FILE
    unsigned int m_block_id;          // The position of block in BLOCK-DATA
    std::string m_output_path;        // Write the sorted data to output_path
    std::vector<std::string> &m_data; // data need to sort
    std::vector<bool> &m_status_list; // Status of each blocks in BLOCK-DATA

    std::mutex *m_locker;

public:
    SortThread(const std::string output,
               std::vector<std::string> &data,
               unsigned int chunkId,
               unsigned int blockId,
               std::vector<bool> &status,
               std::mutex *lock)
        : m_output_path(output),
          m_data(data),
          m_chunk_id(chunkId),
          m_block_id(blockId),
          m_status_list(status),
          m_locker(lock)
    {
    }
    ~SortThread()
    {
    }

    static void *run(void *obj)
    {
        ((SortThread *)obj)->sortAndWrite();
        delete ((SortThread *)obj);
        return nullptr;
    }

    void sortAndWrite()
    {
        std::cout << FGRN("++++SortThread_____CHUNK[" << m_chunk_id << "]__SORTING.........\n");
        auto start = std::chrono::system_clock::now();

        std::stringstream fileName;
        fileName << m_output_path << ".1." << m_chunk_id;
        std::ofstream inFile(fileName.str(), std::ios::out);

        sort(m_data.begin(), m_data.end());

        // std::cout << "++++SortThread ->>>>>> Write CHUNK[" << m_chunk_id << "]  --- BLOCK[" << m_block_id << "]" << std::endl;

        // Write to File
        std::copy(m_data.begin(), m_data.end(), std::ostream_iterator<std::string>(inFile, "\n"));

        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;

        // std::cout << FGRN("++++SortThread[") << m_block_id << FGRN("] - DONE :: ") << elapsed_seconds.count() << FGRN(" seconds\n");
        std::stringstream strss;
        strss << KMAG << "++++>SortThread_____CHUNK[" << m_chunk_id << "]__DONE :: " << elapsed_seconds.count() << " seconds" << RST << '\n';
        std::cout << strss.str() << std::endl;

        m_data.clear();
        // std::cout << "++++SortThread____BLOCK[" << m_block_id << "]__CLEARED " << std::endl;

        // Set status
        m_locker->lock();
        m_status_list.at(m_block_id) = false;
        m_locker->unlock();

        inFile.close();
    }
};

/*************************************************************************************************
 *
 *      ExternalSort
 *
 ************************************************************************************************/
class FileNode
{
public:
    std::string data;
    std::istream *stream;
    bool (*compFunc)(const std::string &a, const std::string &b);

public:
    FileNode(const std::string &data, std::istream *stream, bool (*compFunc)(const std::string &a, const std::string &b))
        : data(data), stream(stream), compFunc(compFunc) {}

    FileNode(const std::string &data, std::istream *stream)
        : data(data), stream(stream)
    {
        compFunc = NULL;
    }

    bool operator<(const FileNode &a) const
    {
        return !(compFunc(data, a.data));
    }
};

class ExternalSort
{
private:
    std::string m_input_path;  // input.txt
    std::string m_output_path; // output.txt
    unsigned int m_memory;     // Provided RAM
    bool (*_compFunc)(const std::string &a, const std::string &b);

    unsigned int m_file_size;   // Size of the original file on DISK
    unsigned int m_num_chunks;  // Counter the number of chunks
    unsigned int m_num_threads; // Number of supported threads
    unsigned int m_file_counter;

    unsigned long long int m_block_size; // Need to caculate this value for fiting MEM

    std::vector<std::string> _vTempFileNames; // save the temp file names
    std::vector<std::ifstream *> _vTempFiles; // save the ifstream files

    std::mutex *m_locker;

public:
    ExternalSort(const std::string &inFile,
                 const std::string &outFile,
                 unsigned int memory,
                 bool (*compFunc)(const std::string &a, const std::string &b) = nullptr);

    ~ExternalSort();

    void Sort();
    void setMemSize(unsigned int mem);
    void setComparision(bool (*compFunc)(const std::string &a, const std::string &b));

private:
    bool emptyFile();
    long long int getFileSize();
    long long int getAvailableMemory();
    bool hasEnoughMemoryToRead(long long int lower_memory_bound, long long int RAM);
    bool hasAvailableBlockToRead(std::vector<bool> &statusList);
    void sortBlocks();
    void mergePart(int lo, int hi, int id);
    void mergeUtil();
    void mergeFinal();
    void merge();
    // void mergePhase1();
    // void mergePhase2();
    // void mergePart();
    void openTempFiles();
    void closeTempFiles();
};

ExternalSort::ExternalSort(const std::string &inFile,
                           const std::string &outFile,
                           unsigned int memory,
                           bool (*compFunc)(const std::string &a, const std::string &b))
    : m_input_path(inFile), m_output_path(outFile), m_memory(memory), _compFunc(compFunc)
{
    if (emptyFile())
    {
        std::cerr << "File is empty\n"
                  << "Exit!\n";
        exit(1);
    }

    m_num_threads = std::thread::hardware_concurrency();
    m_file_size = getFileSize();
    m_num_chunks = 0;
    m_locker = new std::mutex();
}

ExternalSort::~ExternalSort()
{
}

bool ExternalSort::emptyFile()
{
    bool isEmpty = true;
    std::ifstream inFile(m_input_path, std::ios::in);
    isEmpty = inFile.peek() == std::ifstream::traits_type::eof();
    inFile.close();

    return isEmpty;
}
long long int ExternalSort::getFileSize()
{
    long long int fileSize = 0;
    std::ifstream inFile(m_input_path, std::ios::ate | std::ios::in);
    fileSize = inFile.tellg();
    inFile.close();
    return fileSize;
}

long long int ExternalSort::getAvailableMemory()
{
    long long int totalMem;
    long long int freeMem;
    long long int avalMem;
    std::string ignore;

    std::ifstream ifs("/proc/meminfo", std::ios_base::in);
    ifs >> ignore >> totalMem >> ignore >> ignore >> freeMem >> ignore >> ignore >> avalMem;
    ifs.close();

    return avalMem;
}

bool ExternalSort::hasEnoughMemoryToRead(long long int lower_memory_bound, long long int RAM)
{
    // If remain memory greater than 5% RAM => return TRUE
    return (getAvailableMemory() - lower_memory_bound > RAM / 20);
}

bool ExternalSort::hasAvailableBlockToRead(std::vector<bool> &statusList)
{
    for (size_t i = 0; i < statusList.size(); i++)
    {
        if (!statusList[i])
            return true;
    }
    return false;
}

void ExternalSort::setMemSize(unsigned int mem)
{
    m_memory = mem;
}

void ExternalSort::setComparision(bool (*compFunc)(const std::string &a, const std::string &b))
{
    _compFunc = compFunc;
}

void ExternalSort::Sort()
{
    sortBlocks();
    mergeUtil();
    mergeFinal();
}

void ExternalSort::sortBlocks()
{
    std::ifstream *input = new std::ifstream(m_input_path.c_str(), std::ios::in);

    if (!input->good())
    {
        std::cerr << "ERROR: The requested input file (" << m_input_path << ") could not be opened. Exit!\n";
        exit(1);
    }

    std::mutex *lock = m_locker;
    std::string line;
    std::vector<bool> statusBlocks(m_num_threads, false);
    std::vector<std::vector<std::string>> dataBlocks(m_num_threads);

    ThreadPool pool(m_num_threads);
    std::vector<std::future<unsigned int>> results;

    // MEMORY - Calculating......
    long long int chunkSizeMin = m_memory / 20;
    long long int LOWER_MEMORY_BOUND = getAvailableMemory() - m_memory;
    std::cout << "CHUNK SIZE MIN    = " << chunkSizeMin / 1024 << " MB\n";
    std::cout << "LOWER_MEMORY_BOND = " << LOWER_MEMORY_BOUND / 1024 << " MB\n";

    unsigned int currBlockIndex = 0;
    unsigned int nextBlockIndex = 0;
    unsigned int chunkCounter = 0;
    long int startPos = 0;
    long long int currBlockSize = 0;
    std::string outFile = m_output_path;
    long long int updatedPoint = 0;

    std::cout << "MEMORY AVAILABLE = " << hasEnoughMemoryToRead(LOWER_MEMORY_BOUND, m_memory) << std::endl;
    std::cout << "BLOCK AVAILABLE  = " << hasAvailableBlockToRead(statusBlocks) << std::endl;

    while (getline(*input, line, input->widen('\n')))
    {
        if (!statusBlocks[currBlockIndex])
            statusBlocks[currBlockIndex] = true;

        if (statusBlocks[nextBlockIndex])
        {
            if (chunkCounter >= m_num_threads)
            {
                for (int i = 0; i < m_num_threads; i++)
                {
                    if (!statusBlocks[i])
                    {
                        nextBlockIndex = i;
                        // std::cout << ">>>>> Next Index Is ::::::::: " << i << std::endl;
                    }
                }
            }
        }
        currBlockSize = input->tellg() - startPos;

        // Write data to buffer
        dataBlocks[currBlockIndex].push_back(line);

        if (currBlockSize >= chunkSizeMin * 1024 || input->eof())
        {
            long long int remainAvailableMemory = (getAvailableMemory() - LOWER_MEMORY_BOUND);
            std::cout << FYEL("----> CHUNK[") << chunkCounter << FYEL("] LOADED  => BLOCK[") << currBlockIndex << FYEL("]<----") << '\n';

            std::cout << "_____REMAIN-MEM = " << remainAvailableMemory / 1024 << " MB || "
                      << "_____CHUNK-SIZE = " << currBlockSize / (1024 * 1024) << " MB" << std::endl;

            currBlockSize = 0;
            startPos = input->tellg();

            statusBlocks[currBlockIndex] = true;

            results.emplace_back(
                pool.enqueue([outFile, &dataBlocks, currBlockIndex, chunkCounter, &statusBlocks, lock] {
                    // std::stringstream strss;
                    // strss << KCYN << "_____ENQUEUE::CHUNK[" << chunkCounter << "]_____" << RST << "\n";
                    // std::cout << strss.str();

                    SortThread *t = new SortThread(outFile, dataBlocks[currBlockIndex], chunkCounter, currBlockIndex, statusBlocks, lock);
                    SortThread::run((void *)t);
                    return chunkCounter;
                }));

            chunkCounter++;
            m_num_chunks++;

            if (chunkCounter - updatedPoint > m_num_threads)
            {
                updatedPoint = chunkCounter;
                if (remainAvailableMemory > m_memory / 20)
                {
                    chunkSizeMin += remainAvailableMemory / 20;
                    std::cout << "______CHUNK SIZE HAS UPDATED = " << chunkSizeMin << " MB" << std::endl;
                }
            }
            currBlockIndex = (chunkCounter < m_num_threads) ? chunkCounter : nextBlockIndex;
            std::cout << FYEL("----> CHUNK[") << chunkCounter << FYEL("] LOADING => BLOCK[") << currBlockIndex << FYEL("]<----") << '\n';
            // std::cout << "====> BLOCK AVAILABLE  = " << hasAvailableBlockToRead(statusBlocks) << std::endl;
        }
    }
    input->clear();
    input->close();
    delete input;
}

void ExternalSort::mergeUtil()
{
    int step = m_num_chunks / m_num_threads;

    std::vector<std::thread> mergeList(m_num_threads);
    for (int i = 0; i < m_num_threads; i++)
    {
        if (i == m_num_threads - 1)
        {
            mergeList[i] = std::thread(&ExternalSort::mergePart, this, i * step, m_num_chunks, i);
        }
        else
        {
            mergeList[i] = std::thread(&ExternalSort::mergePart, this, i * step, (i + 1) * step, i);
        }
    }
    for (int i = 0; i < m_num_threads; i++)
    {
        mergeList[i].join();
    }
}

void ExternalSort::mergeFinal()
{
    std::cout << "##### ExternalSort::mergeFinal() #######\n";

    std::vector<std::ifstream *> _vTempFileTable;
    std::vector<std::string> _vTempFileNameTable;

    // Open temp file output to write: "output.txt"
    // std::stringstream tempFileSS;
    // tempFileSS << m_output_path;
    std::ofstream outFile(m_output_path.c_str(), std::ios::out);

    for (size_t i = 0; i < m_num_threads; i++)
    {
        std::stringstream tmpFileOpen;
        tmpFileOpen << m_output_path << ".2." << i;
        std::ifstream *file = new std::ifstream(tmpFileOpen.str().c_str(), std::ios::in);

        std::cout << "Open file " << tmpFileOpen.str() << std::endl;

        if (file->good())
        {
            _vTempFileTable.push_back(file);
            _vTempFileNameTable.push_back(tmpFileOpen.str());
        }
        else
        {
            std::cerr << "Unable to open temp file (" << tmpFileOpen.str()
                      << "). Exiting.\n";
            exit(1);
        }
    }

    // Build Min Heap to merge
    std::string line;
    std::priority_queue<FileNode> buildHeap;

    for (size_t i = 0; i < _vTempFileNameTable.size(); i++)
    {
        *_vTempFileTable[i] >> line;
        buildHeap.push(FileNode(line, _vTempFileTable[i], _compFunc));
    }

    while (!buildHeap.empty())
    {
        FileNode lowest = buildHeap.top();
        outFile << lowest.data << '\n';
        buildHeap.pop();
        flush(outFile);

        if (*(lowest.stream) >> line)
        {
            buildHeap.push(FileNode(line, lowest.stream, _compFunc));
        }
    }

    // Close file temp and remove file in streams
    for (size_t i = 0; i < _vTempFileTable.size(); ++i)
    {
        _vTempFileTable[i]->close();
        delete _vTempFileTable[i];
        remove(_vTempFileNameTable[i].c_str());
    }

    // Close file output
    outFile.clear();
    outFile.close();
    std::stringstream strss;
    strss << KGRN << "----> ExternalSort::MergeFinal() -- DONE <------" << RST << std::endl;
    std::cout << strss.str();

    // std::cout << FGRN("mergePart(") << start << ", " << end << ", " << fid << FGRN(") --- DONE\n");
}
void ExternalSort::merge()
{
    std::cout << "############### ExternalSort::merge() #################\n";
    std::ofstream outFile(m_output_path.c_str(), std::ios::out);

    // Open file in streams from position start->end
    openTempFiles();

    // Priority queue for the buffer
    std::priority_queue<FileNode> buildHeap;

    // extract the first line from each temp file
    std::string line;

    for (size_t i = 0; i < _vTempFiles.size(); ++i)
    {
        *_vTempFiles[i] >> line;
        buildHeap.push(FileNode(line, _vTempFiles[i], _compFunc));
    }

    // keep working until the queue is empty
    while (!buildHeap.empty())
    {
        FileNode lowest = buildHeap.top();

        // Write the entry from the top of the queue
        outFile << lowest.data << '\n';

        // Remove this record from the queue
        buildHeap.pop();

        // Add the next line from the lowest stream to the queue
        // flush(outFile);
        if (*(lowest.stream) >> line)
        {
            buildHeap.push(FileNode(line, lowest.stream, _compFunc));
        }
    }

    // Clean the temp files
    closeTempFiles();
    outFile.close();
}

void ExternalSort::mergePart(int lo, int hi, int id)
{
    std::cout << "##### ExternalSort::mergePart(" << lo << ", " << hi << ", " << id << ") #######\n";

    std::vector<std::ifstream *> _vTempFileTable;
    std::vector<std::string> _vTempFileNameTable;

    // Open temp file output to write: "output.txt.2.xx"
    std::stringstream tempFileSS;
    tempFileSS << m_output_path << ".2." << id;
    std::ofstream outFile(tempFileSS.str().c_str(), std::ios::out);

    for (size_t i = lo; i < hi; i++)
    {
        std::stringstream tmpFileOpen;
        tmpFileOpen << m_output_path << ".1." << i;
        std::ifstream *file = new std::ifstream(tmpFileOpen.str().c_str(), std::ios::in);

        std::cout << "Open file " << tmpFileOpen.str() << std::endl;

        if (file->good())
        {
            _vTempFileTable.push_back(file);
            _vTempFileNameTable.push_back(tmpFileOpen.str());
        }
        else
        {
            std::cerr << "Unable to open temp file (" << tmpFileOpen.str()
                      << "). Exiting.\n";
            exit(1);
        }
    }

    // Build Min Heap to merge
    std::string line;
    std::priority_queue<FileNode> buildHeap;

    for (size_t i = 0; i < _vTempFileNameTable.size(); i++)
    {
        *_vTempFileTable[i] >> line;
        buildHeap.push(FileNode(line, _vTempFileTable[i], _compFunc));
    }

    while (!buildHeap.empty())
    {
        FileNode lowest = buildHeap.top();
        outFile << lowest.data << '\n';
        buildHeap.pop();
        flush(outFile);

        if (*(lowest.stream) >> line)
        {
            buildHeap.push(FileNode(line, lowest.stream, _compFunc));
        }
    }

    // Close file temp and remove file in streams
    for (size_t i = 0; i < _vTempFileTable.size(); ++i)
    {
        _vTempFileTable[i]->close();
        delete _vTempFileTable[i];
        remove(_vTempFileNameTable[i].c_str());
    }

    // Close file output
    outFile.clear();
    outFile.close();
    std::stringstream strss;
    strss << KGRN << "----> MergePart(" << lo << ", " << hi << ", " << id << ") ---- DONE" << RST << std::endl;
    std::cout << strss.str();

    // std::cout << FGRN("mergePart(") << start << ", " << end << ", " << fid << FGRN(") --- DONE\n");
}

void ExternalSort::openTempFiles()
{
    std::cout << "############### ExternalSort::openTempFiles() = [" << m_num_chunks << "] Files ###### \n";

    for (unsigned int i = 0; i < m_num_chunks; i++)
    {
        std::ifstream *file;
        std::stringstream tempFileSS;
        tempFileSS << m_output_path << ".1." << i;

        _vTempFileNames.push_back(tempFileSS.str());

        file = new std::ifstream(tempFileSS.str().c_str(), std::ios::in);

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

void ExternalSort::closeTempFiles()
{
    std::cout << "############### ExternalSort::closeTempFiles() ################# \n";
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

// comparison functions for the ext. merge sort
bool ASCENDING(const std::string &a, const std::string &b) { return a <= b; }
bool DESCENDING(const std::string &a, const std::string &b) { return a >= b; }

int main(int argc, char *argv[])
{
    // std::cout << "SORT DATA\n";
    // std::cout << "Hello World!\n";
    // std::string inFile = "input1.txt";
    // std::string outFile = "output.txt";
    // int memory = 4000; // MB

    if (argc > 4)
    {
        std::cout << "The number of parameters over 4\n";
        return 0;
    }
    std::string inFile = argv[1];
    std::string outFile = argv[2];
    unsigned int memory = std::stoi(argv[3]);

    // ----- START TIME
    auto start = std::chrono::system_clock::now();

    ExternalSort *sorter = new ExternalSort(inFile, outFile, memory * 1024, ASCENDING);
    sorter->Sort();

    // ----- END TIME
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    std::cout << "\n++++++++++ PROCESSED TIME = " << elapsed_seconds.count() << "++++++++++\n";

    return 0;
}