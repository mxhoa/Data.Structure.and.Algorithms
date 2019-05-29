#include <iostream>
#include <vector>
#include <unordered_set>
#include <limits>

/********************************************************************************************
 *      FIND MISSING
 * There is a list of integers we need to find the missing number in the list.
 ********************************************************************************************/
int findMissing(std::vector<int> &nums, int start, int end)
{
    std::unordered_set<int> hs;
    for (auto i : nums)
        hs.insert(i);

    for (int curr = start; curr <= end; curr++)
    {
        if (hs.find(curr) == hs.end())
        {
            return curr;
        }
    }

    return std::numeric_limits<int>::max();
}


int main()
{
    std::vector<int> nums = {1, 2, 3, 4, 6, 7, 8, 9};
    std::cout << "Missing : " << findMissing(nums, 1, nums.size()) << std::endl;

    return 0;
}