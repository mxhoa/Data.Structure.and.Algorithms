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

#define DEFAULT_MEMORY 	1000000
#define MB_TO_BYTE 		1000000
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
	bool (*_compareFunction)(const std::string &a, const std::string &b);
	std::vector<std::string> m_data;

public:
	SortThread(const std::string output, std::vector<std::string> data, int blockId)
		: m_output_path(output), m_data(data), m_block_id(blockId)
	{
		_compareFunction = NULL;
	}

	SortThread(const std::string output, std::vector<std::string> data, int blockId, bool(compareFunction)(const std::string &a, const std::string &b))
		: m_output_path(output), m_data(data), m_block_id(blockId), _compareFunction(compareFunction) {}

	static void *run(void *obj)
	{
		((SortThread *)obj)->sortAndWrite();
		delete ((SortThread *)obj);
		return nullptr;
	}

	void sortAndWrite()
	{
		auto start = std::chrono::system_clock::now();
		std::stringstream fileName;
		fileName << m_output_path << "." << m_block_id;
		std::ofstream inFile(fileName.str(), std::ios::out);

		if (_compareFunction != nullptr)
		{
			sort(m_data.begin(), m_data.end(), *_compareFunction);
		}
		else
		{
			sort(m_data.begin(), m_data.end());
		}

		std::copy(m_data.begin(), m_data.end(), std::ostream_iterator<std::string>(inFile, "\n"));
		
		m_data.clear();
		inFile.close();
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		std::cout << "++++SortThread[" << m_block_id << "] - DONE :: " << elapsed_seconds.count() << " seconds\n";
	}
};

/*************************************************************************************************
 *
 * 		K-way merge sorted
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

class KwayMerge
{
public:
	// Constructor, using custom comparision function
	KwayMerge(const std::string &inFile,
			  const std::string &outFile,
			  bool (*compareFunction)(const std::string &a, const std::string &b) = NULL,
			  int memory = DEFAULT_MEMORY);

	// Destructor
	~KwayMerge(void);

	void Sort();
	void setMemrorySize(int memory);
	long long int getFileSize();
	void setComparision(bool (*compareFunction)(const std::string &a, const std::string &b));

private:
	// Driver the creation of sorted sub-files stored on disk
	void blockSort();

	// Drivers the merging of the sorted temp files.
	// Final, sorted and merged output is written to "out"
	void merge();
	void writeToTempFile(const std::vector<std::string> &blockData);
	void openTempFiles();
	void closeTempFiles();

private:
	std::string m_input_path;
	std::string m_output_path;
	bool (*_compareFunction)(const std::string &a, const std::string &b);
	std::vector<std::string> _vTempFileNames;
	std::vector<std::ifstream *> _vTempFiles;
	unsigned int m_memory;
	unsigned int m_file_counter;
	bool _tempFileUsed;

	// For multithreading operation.
private:
	long long int m_file_size;	// Size of the "input.txt" file
	long long int m_memory_block; // Size of block which is processed by each threads
	unsigned int m_num_threads;   // Number of threads
	unsigned int m_num_blocks;	// Number of blocks
	unsigned int m_block_counter;
};

KwayMerge::KwayMerge(const std::string &inFile,
					 const std::string &outFile,
					 bool (*compareFunction)(const std::string &a, const std::string &b),
					 int memory)
	: m_input_path(inFile), m_output_path(outFile), _compareFunction(compareFunction), m_memory(memory), m_file_counter(0)
{
	m_file_size = getFileSize();
	m_num_blocks = 0;
	m_block_counter = 0;
	//m_memory_block = m_memory / m_num_threads;
}


KwayMerge::~KwayMerge(void)
{
}

long long int KwayMerge::getFileSize()
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

void KwayMerge::Sort()
{
	blockSort();
	merge();
}

void KwayMerge::setMemrorySize(int memory)
{
	m_memory = memory;
}

void KwayMerge::setComparision(bool (*compareFunction)(const std::string &a, const std::string &b))
{
	_compareFunction = compareFunction;
}

void KwayMerge::blockSort()
{
	std::ifstream *input = new std::ifstream(m_input_path.c_str(), std::ios::in);

	// Bail unless the file is legit
	if (input->good() == false)
	{
		std::cerr << "Error: The requested input file (" << m_input_path << ") could not be opnened. Exiting!\n";
		exit(1);
	}

	_tempFileUsed = false;
	std::vector<std::string> blockData;
	long long int totalBytes = 0;
	int tmpCounter = 0;
	std::string iFile(m_input_path);
	long long int currentSize = 0;
	bool (*compareFunction)(const std::string &a, const std::string &b) = _compareFunction;

	std::string line;

	unsigned int m_num_threads = std::thread::hardware_concurrency();
	// unsigned int m_num_threads = 1;
	std::cout << "Number of Threads = " << m_num_threads << "\n";
	ThreadPool pool(m_num_threads);
	std::vector<std::future<int>> results;

	while (getline(*input, line, input->widen('\n')))
	{
		// getline(*input, line);
		// *input >> line;
		blockData.push_back(line);
		totalBytes += (long long int)line.length() + 1;
		currentSize += (long long int)line.length() + 1;

		if (currentSize == m_file_size + 1)
		{
			std::cout << "Line = " << line << std::endl;
		}

		// Sort the buffer and write to a temp file if we have filled up our quota
		if (totalBytes > m_memory || currentSize >= m_file_size)
		{
			pool.enqueue([iFile, blockData, tmpCounter] {
					std::cout << "_____CHUNK[" << tmpCounter << "] - BlockData.size() = " << blockData.size() << "\n";
					SortThread *t = new SortThread(iFile, blockData, tmpCounter);
					SortThread::run(t);
					// std::cout << "End :: CHUNK [" << tmpCounter << "]\n";
					
					return tmpCounter;
				});
			// results.emplace_back(
			// 	pool.enqueue([iFile, blockData, tmpCounter] {
			// 		std::cout << "_____CHUNK[" << tmpCounter << "] - BlockData.size() = " << blockData.size() << "\n";
			// 		SortThread *t = new SortThread(iFile, blockData, tmpCounter);
			// 		SortThread::run(t);
			// 		// std::cout << "End :: CHUNK [" << tmpCounter << "]\n";
			// 		return tmpCounter;
			// 	}));

			tmpCounter++;
			// Clear the buffer for the next run
			blockData.clear();
			_tempFileUsed = true;
			totalBytes = 0;
			m_block_counter++;
		}
	}

	std::cout << "Current Size = " << currentSize - 1 << std::endl;
	std::cout << "Block Counter = " << m_block_counter << std::endl;
}

void KwayMerge::writeToTempFile(const std::vector<std::string> &blockData)
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

void KwayMerge::merge()
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
	std::priority_queue<FileNode> buildHeap;

	// extract the first line from each temp file
	std::string line;

	for (size_t i = 0; i < _vTempFiles.size(); ++i)
	{
		*_vTempFiles[i] >> line;
		buildHeap.push(FileNode(line, _vTempFiles[i], _compareFunction));
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
		flush(outFile);
		if (*(lowest.stream) >> line)
		{
			buildHeap.push(FileNode(line, lowest.stream, _compareFunction));
		}
	}

	// Clean the temp files
	closeTempFiles();
	outFile.close();
}

void KwayMerge::openTempFiles()
{
	std::cout << "openTempFiles() :: m_block_counter = " << m_block_counter << " \n";
	for (unsigned int i = 0; i < m_block_counter; i++)
	{
		std::ifstream *file;
		std::stringstream tempFileSS;
		tempFileSS << m_input_path << "." << i;

		std::cout << "openTempFiles() - temp[" << i << "] \n";

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
	// for (size_t i = 0; i < _vTempFileNames.size(); ++i)
	// {
	// 	std::ifstream *file;

	// 	/*	if (is_regular_file(_vTempFileNames[i]))
	// 		cout << "is regular File\n";*/
	// 	file = new std::ifstream(_vTempFileNames[i].c_str(), std::ios::in);

	// 	if (file->good() == true)
	// 	{
	// 		_vTempFiles.push_back(file);
	// 	}
	// 	else
	// 	{
	// 		std::cerr << "Unable to open tem file (" << _vTempFileNames[i]
	// 				  << "). Exiting...\n";
	// 		exit(1);
	// 	}
	// }
}

void KwayMerge::closeTempFiles()
{
	std::cout << "closeTempFiles() :: " << _vTempFiles.size() << " files \n";
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
/*
 * Get File Name from a Path
 */
std::string getFileName(std::string filePath)
{
	// Get last dot position
	std::size_t dotPos = filePath.rfind('.');
	std::size_t sepPos = filePath.rfind('/');

	if (sepPos != std::string::npos)
	{
		return filePath.substr(sepPos + 1, filePath.size() - (dotPos != std::string::npos ? 1 : dotPos));
	}
	return "";
}

// comparison functions for the ext. merge sort
bool alphaAsc(const std::string &a, const std::string &b) { return a <= b; }
bool ASCENDING(const std::string &a, const std::string &b) { return a <= b; }
bool DESCENDING(const std::string &a, const std::string &b) { return a >= b; }

void Generate_Random_Text_File(std::string gen_file_name, long long int gen_file_size)
{
	std::cout << "FILE: " << gen_file_size << " [" << gen_file_size / MB_TO_BYTE << "] MB is generating...\n";
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
	std::cout << "FILE: " << gen_file_name << " has been generated!\n";
}

int main(int argc, char *argv[])
{
	// std::cout << "Hello World!\n";
	// std::string inFile = "input.txt";
	// std::string outFile = "output.txt";
	// int memory = 10; // 1MB

	if (argc > 4)
	{
		std::cout << "The number of parameters over 4\n";
		return 0;
	}
	std::string inFile = argv[1];
	std::string outFile = argv[2];
	unsigned int memory = std::stoi(argv[3]);

	long long int sizeFile = 10000; // MB

	// Generate_Random_Text_File(inFile, sizeFile * MB_TO_BYTE);

	std::cout << "INPUT: " << inFile << "\n";
	std::cout << "OUPUT: " << outFile << "\n";
	std::cout << "MEMORY: " << argv[3] << "\n";
	std::cout << "File is sorting....\n";

	// ----- START TIME
	auto start = std::chrono::system_clock::now();

	KwayMerge *sorter = new KwayMerge(inFile, outFile, ASCENDING, memory * MB_TO_BYTE);
	sorter->Sort();

	// ----- END TIME
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	std::cout << "\n++++++++++ PROCESSED TIME = " << elapsed_seconds.count() << "++++++++++\n";

	return 0;
}