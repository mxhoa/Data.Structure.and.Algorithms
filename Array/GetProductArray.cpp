#include <iostream>
#include <vector>

/****************************************************** DAY 02 *****************************************************
 * 
 * This problem was asked by Uber.
 * 
 * Given an array of integers, return a new array such that each element at index i of 
 * the new array is the product of all the numbers in the original array except the one at i.
 * 
 * Example 1:
 * 		- Input: [1, 2, 3, 4, 5]
 * 		- Output:[120, 60, 40, 30, 24]
 * 		
 * Example 2:
 * 		- Input:  [3, 2, 1]	
 * 		- Output: [2, 3, 6]
 * 
 * Follow-up: what if you can't use division?
 * 
 *******************************************************************************************************************/

std::vector<int> getProductArray(std::vector<int> &nums)
{
    int size = nums.size();
    std::vector<int> left(size);
    std::vector<int> right(size);

    int product = 1;
    int j = 0;
    for (auto i = nums.begin(); i != nums.end(); ++i)
    {
        product *= *i;
        left[j++] = product;
    }

    product = 1;
    j = size - 1;
    for (auto i = nums.rbegin(); i != nums.rend(); ++i)
    {
        product *= *i;
        right[j--] = product;
    }

    for (int i = 0; i < size; i++)
    {
        if (i == 0)
            nums[i] = right[i + 1];
        else if (i == size - 1)
            nums[i] = left[size - 2];
        else
            nums[i] = right[i + 1] * left[i - 1];
    }
    return nums;
}
int main()
{
    std::cout << "Hello, World!" << std::endl;
    std::vector<int> nums = {1, 2, 3, 4, 5};
    getProductArray(nums);

    for (auto i : nums)
        std::cout << i << " ";

    return 0;
}
