#include <iostream>
#include <vector>

class QuickSort
{
private:
	std::vector<int> &m_dataset;

private:
	void swap(std::vector<int> &nums, int first, int sescond);
	void quickSortUtil(std::vector<int> &nums, int lower, int upper);

public:
	QuickSort(std::vector<int> &data);
	virtual void sort();
	void print();
};

QuickSort::QuickSort(std::vector<int> &data) : m_dataset(data) {}

void QuickSort::sort() {
	int  size = m_dataset.size();
	quickSortUtil(m_dataset, 0, size - 1);
}

void QuickSort::print() {
	int size = m_dataset.size();

	std::cout << "+++ NUMS +++++\n";
	for (int i = 0; i < size; i++)
	{
		std::cout << m_dataset.at(i) << "\t";
	}
	std::cout << "\n+++ END ++++\n";
}

void QuickSort::quickSortUtil(std::vector<int> &nums, int lower, int upper)
{
	if (lower >= upper) return;

	int pivot = nums[lower];
	int start = lower;
	int stop  = upper;

	while (lower < upper)
	{
		while (nums[lower] <= pivot && lower < upper)
		{
			lower++;
		}
		while (nums[upper] > pivot && lower <= upper)
		{
			upper--;
		}
		if (lower < upper)
		{
			swap(nums, lower, upper);
		}
	}

	swap(nums, upper, start);	//  upper is  the pivot position

	quickSortUtil(nums, start, upper - 1); 	// pivot - 1 is the upper for left sub array
	quickSortUtil(nums, upper + 1, stop);	// pivot + 1 is the lower for right sub array

}

void QuickSort::swap(std::vector<int> &nums, int first, int second)
{
	int temp = nums[first];
	nums[first] = nums[second];
	nums[second] = temp;
}

int main()
{
	std::vector<int> data = {3, 4, 2, 1, 6, 5, 8, 1, 1};
	QuickSort *qs = new QuickSort(data);
	qs->sort();

	qs->print();

	return 0; 
}