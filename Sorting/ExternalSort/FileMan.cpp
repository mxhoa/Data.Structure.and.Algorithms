#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <algorithm>
using namespace std;

/**
 *      INPUT/OUTPUT with Files 
 *  - ofstream  : Stream class to write on files
 *  - ifstream  : Stream class to read from files
 *  - fstream   : Stream class to both read and write from/to files
 */

void Generate_Random_Text_File(string gen_file_name, long long int gen_file_size)
{
    // open file
    ofstream myfile;
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
    cout << "File " << gen_file_name << " has been generated!" << endl;
}

int main()
{
    // ofstream myfile;
    // myfile.open("example.txt");
    // myfile << "Hello World\n";
    // myfile << "The sample program to check operation with Files\n";

    // for (int i = 0; i < 100; i++)
    // {
    //     myfile << "Number " << i << "\n";
    // }

    // myfile.close();

    // unsigned concurentThreadsSupported = std::thread::hardware_concurrency();

    // string line;
    // streampos begin, end;
    // ifstream myfile("input.txt");
    // begin = myfile.tellg();
    // myfile.seekg(0, ios::end);
    // end = myfile.tellg();
    // cout << "Size of File = " << (end - begin) << endl;

    // myfile.close();

    // if (myfile.is_open())
    // {
    //     while (getline(myfile, line))
    //     {
    //         cout << line << '\n';
    //     }
    //     myfile.close();
    // }

    // ofstream myfile("example.bin", ios::out | ios::binary);
    // int x = 123;
    // double fx = 34.54;
    // myfile.write((const char *)&x, sizeof(int));
    // myfile.write((const char *)&fx, sizeof(fx));

    // myfile.close();

    Generate_Random_Text_File("testfile.txt", 1000);

    vector<string> data;
    string word;
    ifstream myFile("testfile.txt");

    myFile.seekg(0, myFile.end);
    int fileSize = myFile.tellg();
    myFile.seekg(0, myFile.beg);

    cout << "File Size = " << fileSize << endl;

    long long int lines = 0;
    long long int blockSize = 0;

    auto start = std::chrono::system_clock::now();
    while (!myFile.eof())
    {
        lines++;
        myFile >> word;
        blockSize += sizeof(word);
        data.push_back(word);
    }

    cout << "The number of Lines = " << lines << endl;
    cout << "The size of blocks = " << blockSize << endl;

    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    cout << "\n++++++++ Count Timer = " << elapsed_seconds.count() << '\n';

    myFile.seekg(0, myFile.beg);
    const int blocks = fileSize / 3 + 1;

    vector<vector<char>> vect(3, vector<char>(blocks, 0));

    for (size_t j = 0; j < 3; j++)
    {
        myFile.read(&vect[j][0], blocks);
        for (size_t i = 0; i < blocks; i++)
        {
            cout << vect[i][j] << endl;
        }
    }

    // while (!myFile.eof())
    // {
    //     myFile >> word;
    //     data.push_back(word);
    // }
    // sort(data.begin(), data.end());

    // ofstream outFile("result.txt");
    // streampos pos;
    // for (int i = 0; i < data.size(); i++)
    // {
    //     outFile << data[i] << '\n';
    //     if (i == data.size() / 2)
    //     {
    //         pos = outFile.cur;
    //         cout << "Expected = " << data[i] << endl;
    //     }
    // }

    // cout << "Seek to middle of File" << endl;

    // string word1;
    // ifstream tmp("result.txt");
    // tmp.seekg(pos, tmp.beg);
    // while (!tmp.eof())
    // {
    //     tmp >> word1;
    //     cout << word1 << endl;
    // }
    // tmp.close();
    // outFile.close();
    myFile.close();
    return 0;
}