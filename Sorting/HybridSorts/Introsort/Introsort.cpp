#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>

class Introsort
{
private:
	std::vector<int> &m_nums;

private:
	void insertionSort(std::vector<int> &nums, int lo, int hi);
	int partition(std::vector<int> &nums, int lo, int hi);
	int randPartition(std::vector<int> &nums, int lo, int hi);
	void heapSort(std::vector<int> &nums, int lo, int hi);
	void introsortUtil(std::vector<int> &nums, int lo, int hi, int depthLimit);

public:
	Introsort(std::vector<int> &nums);
	void run();
	void print(std::string header = "List");
	~Introsort();
};

Introsort::Introsort(std::vector<int> &nums) : m_nums(nums) {}

void Introsort::insertionSort(std::vector<int> &nums, int lo, int hi)
{
	for (int i = lo + 1; i <= hi; i++)
	{
		int value = nums[i];
		int j = i;
		while (j > lo && nums[j - 1] > value)
		{
			nums[j] = nums[j - 1];
			j--;
		}
		nums[j] = value;
	}
}

int Introsort::partition(std::vector<int> &nums, int lo, int hi)
{
	int pivot = nums[hi];
	int idx = lo;

	for (int i = lo; i < hi; i++)
	{
		if (nums[i] <= pivot)
		{
			std::swap(nums[i], nums[idx]);
			idx++;
		}
	}

	std::swap(nums[idx], nums[hi]);

	return idx;
}

int Introsort::randPartition(std::vector<int> &nums, int lo, int hi)
{
	int idx = rand() % (hi - lo + 1) + lo;

	std::swap(nums[idx], nums[hi]);

	return partition(nums, lo, hi);
}

void Introsort::heapSort(std::vector<int> &nums, int lo, int hi)
{
	std::make_heap(nums.begin() + lo, nums.begin() + hi + 1);
	std::sort_heap(nums.begin() + lo, nums.begin() + hi + 1);
}

void Introsort::introsortUtil(std::vector<int> &nums, int lo, int hi, int depthLimit)
{
	if (hi - lo < 16)
	{
		insertionSort(nums, lo, hi);
	}
	else if (depthLimit == 0)
	{
		heapSort(nums, lo, hi);
	}
	else
	{
		int pivot = randPartition(nums, lo, hi);
		introsortUtil(nums, lo, pivot - 1, depthLimit - 1);
		introsortUtil(nums, pivot + 1, hi, depthLimit - 1);
	}
}
void Introsort::run()
{
	int len = m_nums.size();
	int depthLimit = 2 * log(len);

	// Perform a recursive Introsort
	introsortUtil(m_nums, 0, len - 1, depthLimit);
}

void Introsort::print(std::string header)
{
	std::cout << header << " :: ";
	for (int i : m_nums)
		std::cout << i << " ";
	std::cout << '\n';
}

int main()
{
	std::vector<int> nums = {3, 1, 23, -9, 233, 23, -313, 32, -9};

	Introsort *its = new Introsort(nums);
	its->print("Origin");
	its->run();
	its->print("Sorted");

	return 0;
}