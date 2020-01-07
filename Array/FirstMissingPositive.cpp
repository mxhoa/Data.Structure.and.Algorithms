#include <iostream>
#include <vector>
#include <climits>

/****************************************************** DAY 04 *****************************************************
 * This problem was asked by Stripe.
 * 
 * Given an array of integers, find the first missing positive integer in linear time and constant space. 
 * In other words, find the lowest positive integer that does not exist in the array. 
 * The array can contain duplicates and negative numbers as well.
 * 
 * For example, 
 *     - The input [3, 4, -1, 1] should give 2. 
 *     - The input [1, 2, 0] should give 3.
 * 
 * You can modify the input array in-place.
 *******************************************************************************************************************/

int firstMissingPositive_1(std::vector<int> nums)
{
    int size = nums.size();
    for (int i = 0; i < size; ++i)
    {
        while (nums[i] > 0 && nums[i] <= size && nums[nums[i] - 1] != nums[i])
            std::swap(nums[i], nums[nums[i] - 1]);
    }

    for (int i = 0; i < size; ++i)
    {
        if (nums[i] != i + 1)
            return i + 1;
    }

    return size + 1;
}

int firstMissingPositive_2(std::vector<int> A)
{
    int n = A.size();
    int m = INT_MIN;
    // Our original array. Storing maximum value
    for (int i = 0; i < n; i++)
    {
        if (A[i] > m)
        {
            m = A[i];
        }
    }

    // In case all values in our array are negative
    if (m < 1)
    {
        return 1;
    }
    if (n == 1)
    {

        //If it contains only one element
        if (A[0] == 1)
        {
            return 2;
        }
        else
        {
            return 1;
        }
    }
    int i = 0;
    int l[m] = {0};
    for (i = 0; i < n; i++)
    {
        if (A[i] > 0)
        {
            // Changing the value status at the index of our list
            if (l[A[i] - 1] != 1)
            {
                l[A[i] - 1] = 1;
            }
        }
    }

    // Encountering first 0, i.e, the element with least value
    for (i = 0; i < m; i++)
    {
        if (l[i] == 0)
        {
            return i + 1;
        }
    }

    // In case all values are filled between 1 and m
    return i + 1;
}

int main()
{
    std::vector<int> nums = {1, 2, 0};
    std::cout << "firstMissingPositive_1 = " << firstMissingPositive_1(nums) << std::endl;
    std::cout << "firstMissingPositive_2 = " << firstMissingPositive_2(nums) << std::endl;
    return 0;
}
