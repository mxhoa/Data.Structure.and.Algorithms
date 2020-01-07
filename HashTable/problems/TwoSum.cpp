#include <iostream>
#include <vector>
#include <unordered_map>

/****************************************************** DAY 01 *****************************************************
 *
 * Given a list of numbers, return whether any two sums to k. 
 * 
 * For example, given [10, 15, 3, 7] and k of 17, return true since 10 + 7 is 17.
 *
 * Bonus: Can you do this in one pass?
 *
 *******************************************************************************************************************/

bool isSumPair(std::vector<int> nums, int sum)
{
    std::unordered_map<int, int> hs(nums.size());

    for (int i = 0; i < nums.size(); i++)
    {
        if (hs[sum - nums[i]] > 0)
            return true;
        hs[nums[i]]++;
    }
    return false;
}

/**
 * @brief Count the number of the sum pair
 */
int countSumPair(std::vector<int> nums, int sum)
{
    std::unordered_map<int, int> hs(nums.size());
    int counter = 0;

    for (int i = 0; i < nums.size(); i++)
    {
        if (hs[sum - nums[i]] > 0 && sum >= nums[i])
        {
            counter++;
            hs[sum - nums[i]]--;
            hs[nums[i]]--;
        }
        else
        {
            hs[nums[i]]++;
        }
    }
    return counter;
}

int main()
{
    std::vector<int> nums1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 12, 20};
    int sum1 = 7;

    std::vector<int> nums2 = {1, 5, 7, -1, 5};
    int sum2 = 6;

    std::cout << "isSumPair 1 = " << isSumPair(nums1, sum1) << std::endl;
    std::cout << "Count Pair 2 = " << countSumPair(nums1, sum1) << std::endl;

    std::cout << "isSumPair 2 = " << isSumPair(nums2, sum2) << std::endl;
    std::cout << "Count Pair 2 = " << countSumPair(nums2, sum2) << std::endl;

    return 0;
}
