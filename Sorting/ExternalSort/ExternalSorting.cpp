#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <algorithm>
#include <string>
#include <time.h>
#include <chrono>
#include <ctime>

using namespace std;

typedef pair<int, int> heapNode;

void generateFile(string file_name, long long int num)
{
    cout << "File is generating..." << '\n';
    ofstream myfile;
    myfile.open(file_name);
    // myfile << "Hello World\n";
    // myfile << "The sample program to check operation with Files\n";

    for (long long int i = 0; i < num; i++)
    {
        myfile << (rand() % RAND_MAX) << '\n';
    }

    myfile.close();
    cout << "File Generated" << '\n';
}
string ToString(int val)
{
    stringstream stream;
    stream << val;
    return stream.str();
}

// Merge all sorted Files into one
string mergeFiles(int counter)
{
    priority_queue<heapNode, vector<heapNode>, greater<heapNode>> minHeap;
    ifstream *handles = new ifstream[counter];

    for (long long int i = 1; i <= counter; i++)
    {
        string sortedInputFileName = "output" + ToString(i) + ".txt";
        handles[i - 1].open(sortedInputFileName.c_str());

        long long int firstValue;
        handles[i - 1] >> firstValue; // first value in the file (minimum in fife)
        minHeap.push({firstValue, i - 1});
    }

    string outputFileName = "output.txt";
    ofstream outputFile(outputFileName.c_str());
    while (!minHeap.empty())
    {
        heapNode minNode = minHeap.top();
        minHeap.pop();

        outputFile << minNode.first << '\n';
        long long int nextValue;
        flush(outputFile);
        if (handles[minNode.second] >> nextValue)
        {
            minHeap.push({nextValue, minNode.second});
        }
    }

    // Clean up
    for (long long int i = 1; i <= counter; i++)
    {
        handles[i - 1].close();
    }

    outputFile.close();
    delete[] handles; // free memory

    return outputFileName;
}

void sortAndWrite(long long int *values, long long int size, long long int numberOfChunks)
{
    sort(values, values + size);
    string outputFileName = "output" + ToString(numberOfChunks) + ".txt";
    ofstream outputFile(outputFileName.c_str());

    for (long long int i = 0; i < size; i++)
    {
        outputFile << values[i] << '\n';
    }
    outputFile.close();
}

int main()
{
    // Generate File
    long long int nums = 1000000;
    generateFile("input.txt", nums);

    // divide file into chunks of size that fits  in your memory
    long long int numberOfChunks = 1;
    long long int maxSizeOfMemeory = 1000000; // in bytes
    long long int chunkSize = maxSizeOfMemeory / sizeof(long long int);

    long long int *inputValues = new long long int[chunkSize];
    long long int readValue = 0;
    long long int currentCount = 0;
    bool unprocessData = true;

    auto start = std::chrono::system_clock::now();

    ifstream inputFile("input.txt");

    while (inputFile >> readValue)
    {
        unprocessData = true;
        inputValues[currentCount++] = readValue;
        if (currentCount == chunkSize)
        {
            cout << "Sort file[" << numberOfChunks << "]\n";
            sortAndWrite(inputValues, currentCount, numberOfChunks);
            numberOfChunks++;
            currentCount = 0;
            unprocessData = false;
        }
    }

    if (unprocessData)
    {
        sortAndWrite(inputValues, currentCount, numberOfChunks);
    }
    else
    {
        numberOfChunks--;
    }

    inputFile.close();
    delete[] inputValues; // free memory
    if (numberOfChunks != 0)
    {
        // priority_queue<heapNode, vector<heapNode>, greater<heapNode>> minHeap;
        cout << "Output is in file: " << mergeFiles(numberOfChunks);
    }

    // Some computation here
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    cout << "\n++++++++ TIME = " << elapsed_seconds.count() << '\n';

    return 0;
}