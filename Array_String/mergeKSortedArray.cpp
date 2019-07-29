#include <iostream>
#include <vector>
#include <queue>

typedef std::pair<int, std::pair<int,int>> heapNode;

std::vector<int> mergeKSortedArray(std::vector<std::vector<int>> &nums)
{
	std::vector<int> mergedArray;
	std::priority_queue<heapNode, std::vector<heapNode>, std::greater<heapNode>> buildHeap;

	for (int i = 0; i < nums.size(); i++)
	{
		buildHeap.push({nums[i][0], {i, 0}});
	}

	while (!buildHeap.empty())
	{
		int curr_arr = buildHeap.top().second.first;
		int curr_idx = buildHeap.top().second.second;

		mergedArray.push_back(buildHeap.top().first);

		buildHeap.pop();

		if (nums[curr_arr].size() != curr_idx + 1)
		{
			buildHeap.push({nums[curr_arr][curr_idx + 1], {curr_arr, curr_idx + 1}});
		}
	}
	return mergedArray;
}

int main()
{
	std::vector<std::vector<int>> nums = {	{0, 3, 6, 8, 9}, 
											{1, 2, 8, 10}, 
											{2, 5, 7, 13, 29}};
	std::vector<int> res = mergeKSortedArray(nums);

	for (int i : res)
	{
		std::cout << "->" << i;
	}
	std::cout << std::endl;
	return 0;
}
