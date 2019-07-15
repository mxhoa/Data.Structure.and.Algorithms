#include <iostream>
#include <vector>

class QuickSort
{
private:
	std::vector<int> &m_dataset;

private:
	int partition(std::vector<int> &nums, int lo, int hi);
	void exch(std::vector<int> &nums, int i, int j);
	void quickSortUtil(std::vector<int> &nums, int lo, int hi);

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

	std::cout << "++++ NUMS +++++\n";
	for (int i = 0; i < size; i++)
	{
		std::cout << "->" << m_dataset.at(i);
	}
	std::cout << std::endl;
}

void QuickSort::exch(std::vector<int> &nums, int i, int j)
{
	int tmp = nums[i];
	nums[i] = nums[j];
	nums[j] = tmp;
}

int QuickSort::partition(std::vector<int> &nums, int lo, int hi)
{
	if (lo == hi) return lo;
	int pivot = nums[lo];	// pivot is first element in nums
	int i = lo + 1;
	int j = hi;
	
	while (true)
	{
		while (nums[i] <= pivot && i < hi) i++;
		while (nums[j] > pivot && j > lo) j--;
		if (i >= j) break;
		exch(nums, i, j);
	}
	exch(nums, lo, j);
	return j;
}

void QuickSort::quickSortUtil(std::vector<int> &nums, int lo, int hi)
{
	if (lo >= hi) return;
	int s = partition(nums, lo, hi);
	quickSortUtil(nums, lo, s - 1);
	quickSortUtil(nums, s + 1, hi);
}

int main()
{
	std::vector<int> data = {1 , 5, 3, 2, 8, 11, 20, 17, 14, 15, 2, 1, 9, 10};
	QuickSort *qs = new QuickSort(data);
	qs->sort();
	qs->print();
	return 0; 
}