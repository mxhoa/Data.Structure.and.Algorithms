#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/**********************************************************************************************
 * [215] - Find the kth largest element in an unsorted array. 
 * Note that it is the kth largest element in the sorted order, not the kth distinct element
 **********************************************************************************************/


/*
 * Solution1: The smart approach for this problem is to use the selection algorithm 
 * 				(based on the partion method - the same one as used in quicksort).
 *
 * Time Complexity: O(N) best case / O(N^2) worst case
 * Space Complexity: O(1)
 **/

class Solution1
{
public:
	void exch(std::vector<int> &nums, int i, int j)
	{
		int tmp = nums[i];
		nums[i] = nums[j];
		nums[j] = tmp;
	}

	int partition(std::vector<int> &nums, int lo, int hi)
	{
		int p = nums[lo];
		int i = lo + 1;
		int j = hi;


		while (i <= j)
		{
			while (nums[i] < p && i < hi) i++;
			while (nums[j] > p && j > lo) j--;
			if (i >= j) break;
			exch(nums, i, j);
		}

		exch(nums, lo, j);

		return j;
	}


	int findKthLargestArray(std::vector<int> &nums, int k)
	{
		k = nums.size() - k;

		int lo = 0;
		int hi = nums.size() - 1;

		while (lo < hi)
		{
			int j = partition(nums, lo, hi);
			if (j < k)
				lo = j + 1;
			else if (j > k)
				hi = j - 1;
			else
				break;
		}

		return nums[k];

	}
};

/*
 * Solution 2: Other possibility is to use a min oriented priority queue that will store 
 * 			the K-th largest values. The algorithm iterates over the whole input and maintains 
 * 			the size of priority queue.
 * 
 *
 * - Time Complexity: O(N lg K)
 * - Space Complexity: O(K) 
 */


class Solution2
{
public:
	int findKthLargestArray(std::vector<int> &nums, int k)
	{
		std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

		for (int i : nums)
		{
			minHeap.push(i);

			if (minHeap.size() > k)
			{
				minHeap.pop();
			}
		}
		return minHeap.top();
	}
};


int main()
{
	std::vector<int> nums = {1, 3, 5, 7, 9, 11, 29, 27, 25, 23, 21, 19, 17, 15, 13, 99, 34, 72, 69};


    Solution1 s1;
    Solution2 s2;
    std::cout << s1.findKthLargestArray(nums, 5) << std::endl;
    std::cout << s2.findKthLargestArray(nums, 5) << std::endl;
    
    return 0;
}