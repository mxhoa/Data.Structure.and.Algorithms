// ExternalSorting.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <string>
#include <queue>
#include <mutex>
#include <fstream>
#include <algorithm>
#include <functional>
/****************************************************************************************************************************
 *
 *	           |-block-|
 *			   |---------Segment---------------| = [Available Memory]
 *
 *	-----------|_______|_______|__...__|_______|----------------------------------------------------------------
 *
 *	-----------|_______|_______|__...__|_______|----------------------------------------------------------------
 *
 *	threads[i]     1       2      ...     n
 *
 *
 ****************************************************************************************************************************/
#define MB 1024 * 1024
#define MAX_BUFFER_SIZE 64 * 1024 * 1024

class ParalellQuickSort {
private:
	int m_block_size;
	int m_position;
	int m_number_elements;
	std::string m_input_path;
	std::string m_output_path;
	std::mutex* m_lock;

public:
	ParalellQuickSort() {}
	ParalellQuickSort(const std::string input, const std::string output, const int numElements, const int position, std::mutex* lock) :
		m_input_path(input),
		m_output_path(output),
		m_number_elements(numElements),
		m_position(position),
		m_lock(lock)
	{
		m_block_size = numElements * sizeof(int);
	}

	static void* run(void* obj)
	{
		((ParalellQuickSort*)obj)->readBlockSortAndWrite();
		delete ((ParalellQuickSort*)obj);
		return nullptr;
	}

	void readBlockSortAndWrite()
	{
		std::ifstream fileReader(m_input_path, std::ios::binary | std::ios::in);
		std::vector<int> nums(m_number_elements);

		// Read data from m_position in the input file
		fileReader.seekg(m_position);
		fileReader.read(reinterpret_cast<char*>(nums.data()), m_block_size);
		fileReader.close();
		// Sort 
		sort(nums.begin(), nums.end());
		// Lock to avoid another thread change data
		m_lock->lock();
		// Write the sorted nums to the output file.
		std::ofstream fileWriter(m_output_path, std::ios::binary | std::ios::out | std::ios::in);
		fileWriter.seekp(m_position);
		fileWriter.write(reinterpret_cast<const char*>(&nums[0]), m_block_size);
		fileWriter.close();
		// Unlock this block
		m_lock->unlock();
	}
};

class ExternalSorting
{
private:
	int m_numThreads;		// Number of cores in OS 
	int m_availableMemory;	// The RAM memory capacity

	std::string m_input_path;	
	std::string m_output_path;

	std::mutex *m_lock;		// Lock/Unlock sorted file write
	int m_fileSize;			// The actual size of the input.txt file

public:
	ExternalSorting(const int availableMemory, const int numThreads, const std::string input, const std::string output)
	{
		m_numThreads = numThreads;
		m_availableMemory = availableMemory * MB;	// convert to bytes
		m_input_path = input;
		m_output_path = output;

		// Get size of the input.txt file
		std::ifstream fileReader(m_input_path, std::ifstream::ate | std::ifstream::binary);
		m_fileSize = fileReader.tellg();
		fileReader.close();

		// If sizeof file > Memory => divide 
		m_availableMemory = m_availableMemory > m_fileSize ? m_fileSize : m_availableMemory;

		while (m_availableMemory % (m_numThreads * sizeof(int)) != 0 && m_numThreads > 1)
		{
			m_numThreads--;
		}

		if (m_numThreads == 1)
		{
			m_availableMemory /= 2;
		}

		//m_lock = new std::mutex();
	}

	void sort()
	{
		sortBlocks();

		//if (!(m_fileSize <= m_availableMemory && m_numThreads == 1))
		//{
		//	mergeSortedBlock();
		//}
	}

	void sortBlocks()
	{
		std::ofstream fileWriter(m_output_path, std::ios::binary | std::ios::out);
		fileWriter.seekp(m_fileSize - 1);
		fileWriter.write("", 1);
		fileWriter.close();


		int pthread_status;

		int threadCapacity = m_availableMemory / m_numThreads;

		for (int cur_seg_pos = 0; cur_seg_pos < m_fileSize; cur_seg_pos += m_availableMemory)
		{
			int cur_block_pos = 0;
			int actual_thread_count = 0;
			//std::pthread_t* threads = new pthread_t[m_numThreads];
			std::vector<std::thread> threadList(m_numThreads);
			for (int i = 0; i < m_numThreads && m_fileSize > cur_seg_pos + cur_block_pos; i++, actual_thread_count++)
			{
				int numElements = threadCapacity / sizeof(int);
				if (cur_block_pos + cur_seg_pos + threadCapacity > m_fileSize)
				{
					numElements = (m_fileSize - (cur_seg_pos + cur_block_pos)) / sizeof(int);
				}

				//std::thread t(&ParalellQuickSort::ParalellQuickSort, &qs, m_input_path, m_output_path, numElements, cur_seg_pos + cur_block_pos, m_lock)
				ParalellQuickSort *qs = new ParalellQuickSort(m_input_path, m_output_path, numElements, (cur_seg_pos + cur_block_pos), m_lock);
				//if ((pthread_status = pthread_create(&threads[i], NULL, &ParalellQuickSort::run, (void*)qs)) != 0)
				//{
				//	throw runtime_error("Create thread exception with status " + to_string(static_cast<long long>(pthread_status)));
				//}
				threadList.push_back(std::thread(&ParalellQuickSort::run, &qs));

				cur_block_pos += threadCapacity;
			}

			std::for_each(threadList.begin(), threadList.end(), std::mem_fn(&std::thread::join));
			/*for (int i = 0; i < actual_thread_count; i++)
			{
				threadList[i].join();
			}*/

			threadList.clear();
		}
	}

	void mergeSortedBlock()
	{
		int threadCapacity = m_availableMemory / m_numThreads;
		int numBlocks = m_fileSize / threadCapacity;

		std::ofstream output(m_output_path, std::ios::binary | std::ios::out | std::ios::in);
		std::ifstream input(m_output_path, std::ios::binary | std::ios::in);

		int half_size = threadCapacity / sizeof(int);

		std::vector<int>* block = new std::vector<int>(half_size + half_size);
		std::vector<int>* buffer = new std::vector<int>(half_size + half_size);

		for (int gpos = 0; gpos < (int)numBlocks / 2; gpos++)
		{
			readBinaryFile(block, 0, gpos * threadCapacity, threadCapacity, input);

			for (int lpos = gpos + 1; lpos < numBlocks; lpos++)
			{

			}


			writeBinaryFile(block, 0, half_size, gpos * threadCapacity, output);

			int readNextBlockSize = (numBlocks - gpos) * threadCapacity > m_fileSize ? m_fileSize - (numBlocks - 1 - gpos) * threadCapacity : threadCapacity;
			readBinaryFile(block, half_size, (numBlocks - 1 - gpos) * threadCapacity, readNextBlockSize, input);

			for (int lpos = numBlocks - 1 - gpos; lpos >= 0; lpos--)
			{

			}

			writeBinaryFile(block, half_size, readNextBlockSize / sizeof(int), (numBlocks - 1 - gpos) * threadCapacity, output);
			std::cout << (int)(100 * gpos / (numBlocks / 2)) << "%\n";
		}
		delete block;
		delete buffer;

		input.close();
		output.close();
	}


	static void mergeSortVector(std::vector<int>* src, std::vector<int>* buffer, int spos, int size) 
	{
		int i = 0, j = 0, k = 0;
		while (i < spos && j < size - spos)
			(*buffer)[k++] = (*src)[i] < (*src)[j + spos] ? (*src)[i++] : (*src)[j++ + spos];

		while (i < spos)
			(*buffer)[k++] = (*src)[i++];

		while (j < size - spos)
			(*buffer)[k++] = (*src)[j++ + spos];
	}

	static void readBinaryFile(std::vector<int>* nums, const int bpos, const int pos, const int bytes, std::ifstream& io)
	{
		io.seekg(pos, std::ios_base::beg);
		io.read(reinterpret_cast<char*>(&(*nums)[bpos]), bytes);
	}

	static void writeBinaryFile(std::vector<int>* nums, const int bpos, const int size, const int pos, std::ofstream& io)
	{
		io.seekp(pos, std::ios_base::beg);
		io.write(reinterpret_cast<const char*>(&(*nums)[bpos]), size * sizeof(int));
		io.flush();
	}

	void generateBinaryFile(const std::string file_name, const int sign_number) {
		//std::ofstream out(file_name, std::ios::binary | std::ios::out | std:: ios::in | std::ios::trunc);
		std::ofstream out(file_name, std::ios::out | std::ios::in | std::ios::trunc);
		int buff_size = MAX_BUFFER_SIZE > sign_number ? sign_number : MAX_BUFFER_SIZE;

		std::vector<int> buff(buff_size);
		srand(time(0));
		int seek = 0;

		while (seek < sign_number * sizeof(int)) {

			if (seek / sizeof(int) + buff_size > sign_number) {
				buff_size = sign_number - seek / sizeof(int);
			}

			out.seekp(seek, std::ios::beg);
			for (int i = 0; i < buff_size; i++) {
				buff[i] = (i % 2 == 0 ? -1 : 1) * (rand() % 100000 + 1);
			}

			out.write(reinterpret_cast<const char*>(&buff[0]), buff_size * sizeof(int));
			seek += buff_size * sizeof(int);
		}

		out.close();
	}
};

int main()
{
	/*std::ofstream myfile;
	myfile.open("input.txt");

	for (long long int i = 0; i < 10000000; i++)
	{
		myfile << (rand() % RAND_MAX) << '\n';
	}

	myfile.close();

	std::cout << "Completed generate input.txt file\n";*/
	//int m_available_memory = atoi(argv[1]);			// m_AvailableMemory : Check available memory to use
	//int m_available_theads = atoi(argv[2]);			// m_ThreadNum 		 : MultiThread to sort
	//std::string m_input = std::string(argv[3]);		// input.txt 		
	//std::string m_output = std::string(argv[4]);	// output.txt

	int m_available_memory = 10;			// m_AvailableMemory : Check available memory to use
	int m_available_theads = 4;			// m_ThreadNum 		 : MultiThread to sort
	std::string m_input = "input.txt";		// input.txt 		
	std::string m_output = "output.txt";	// output.txt 

	if (m_available_memory == 0) {
		std::cout << "Memory size can't be zero";
		return 0;
	}

	if (m_available_theads == 0) {
		std::cout << "Max thread count can't be zero";
		return 0;
	}

	try {

		ExternalSorting c(m_available_memory, m_available_theads, m_input, m_output);
		c.generateBinaryFile("input1.txt", 1000);
		//c.sort();
		std::cout << "Successfully saved to file " << m_output << '\n';


		std::vector<int> buff(sizeof(int));
		std::ifstream fileout("input1.txt", std::ios::in | std::ios::binary);
		fileout.read(&buff, sizeof(int));
		std::cout << "read = " << buff << '\n';
		fileout.close();
	}
	catch (std::exception& exc) {
		std::cout << exc.what() << "-----------" << '\n';
	}
	
	return 0;
}