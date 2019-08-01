/**
 * Last K Lines: Write a method to print the last Klines of an input file using C ++.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>

void printLastKLines(const std::string input, int k)
{
	std::cout << "Print Last " << k << " Lines\n";
	
	std::ifstream inFile(input, std::ios::in);
	std::vector<std::string> Lines(k);

	int size = 0;
	std::string line;

	if (inFile.peek() == std::ifstream::traits_type::eof())
	{
		std::cout << "File is empty!\nExiting...\n";
		exit(1);
	}

	
	while (std::getline(inFile, line))
	{
		Lines[size % k] = line;
		size++;
	}

	inFile.close();

	int start = size > k ? (size % k) : 0;
	int count = size > k ? k : size;

	for (int i = 0; i < count; i++)
	{
		std::cout << Lines[(start + i) % k] << std::endl;
	}

}

void printLastKLines1(const std::string input, int k)
{
	std::cout << "Print Last " << k << " Lines\n";

	std::queue<std::string> q;
	std::ifstream inFile(input, std::ios::in);
	std::string line;

	if (inFile.peek() == std::ifstream::traits_type::eof())
	{
		std::cout << "File is empty!\nExiting...\n";
		exit(1);
	}

	while (std::getline(inFile, line))
	{
		q.push(line);
		if (q.size() > k)	
			q.pop();
	}

	inFile.close();

	while (!q.empty())
	{
		std::cout << q.front() << std::endl;
		q.pop();
	}

}

int main()
{
	std::string input("input.txt");
	std::ofstream outFile(input, std::ios::out);

	for (int i = 0; i < 100; i++)
	{
		outFile << "Number " <<  i << '\n';
	}
	outFile.close();

	printLastKLines(input, 6);
	// printLastKLines1("input.txt", 9);

	std::remove(input.c_str());

	return 0;

}