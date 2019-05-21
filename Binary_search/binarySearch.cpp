#include <iostream>
#include <vector>

using namespace std;

/*
 * @DESCRIPTION:  https://leetcode.com/problems/binary-search/
 * Given a sorted (in ascending order) integer array nums of n elements and a target value, write a function to search target in nums. If target exists, then return its index, otherwise return -1.
 */

/*
 * Complexity Analysis
 *      - Time Complexity: O(log N)
 *      - Space Complexity: O(1). 
 */
int binarySearch(vector<int> &nums, int target)
{
    int lo = 0;
    int hi = nums.size() - 1;

    while (lo <= hi)
    {
        int idx = lo + (hi - lo) / 2;
        if (nums[idx] == target)
            return idx;
        if (nums[idx] > target)
            hi = idx - 1;
        else
            lo = idx + 1;
    }
    return -1;
}

int main()
{
    int target = 9;
    vector<int> nums = {-1,0,3,5,9,12};

    cout << "binarySearch(nums,target) = " << binarySearch(nums, target) << endl;

    return 0;
}