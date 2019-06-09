#include <iostream>
#include <vector>

class QuickSelect
{
private:
	std::vector<int> &m_dataset;

private:
	void swap(std::vector<int> &nums, int first, int second);
	void quickSelect(std::vector<int> &nums, int lower, int upper, int k);

public:
	QuickSelect(std::vector<int> &nums) : m_dataset(nums) {}
	void quickSelect(std::vector<int> &nums, int k);
};

void QuickSelect::swap(std::vector<int> &nums, int first, int second)
{
	int temp = nums[first];
	nums[first] = nums[second];
	nums[second] = temp;
}

void QuickSelect::quickSelect(std::vector<int> &nums, int lower, int upper, int k)
{
	if (lower >= upper)
		return;

	int pivot = nums[lower];
	int start = lower;
	int stop = upper;

	while (lower < upper)
	{
		while (nums[lower] <= pivot && lower < upper)
			lower++;
		while (nums[upper] > pivot && lower <= upper)
			upper--;

		if (lower < upper)
		{
			swap(nums, upper, lower);
		}
	}

	swap(nums, upper, start); // upper is the pivot position

	if (k < upper)
	{
		quickSelect(nums, start, upper - 1, k); // pivot -1 is the upper for left sub array.
	}
	if (k > upper)
	{
		quickSelect(nums, upper + 1, stop, k); // pivot + 1 is the lower for right sub array.
	}
}

void QuickSelect::quickSelect(std::vector<int> &nums, int k)
{
	quickSelect(nums, 0, nums.size() - 1, k);
}

int main()
{
	std::vector<int> data = {3, 4, 12, 18, 13, 2, 1, 6, 5, 7, 8, 10, 9};
	QuickSelect *qs = new QuickSelect(data);
	qs->quickSelect(data, 5);
	std::cout << "value at index 5 is : " << data[4] << std::endl;

	for (int i = 0; i < data.size(); i++)
	{
		std::cout << data.at(i) << "\t";
	}

	std::cout << std::endl;
	return 0;
}