/**
 * ======================= 152. Maximum Product Subarray ===================================
 * @ Description: Given an integer array nums, find the contiguous subarray within an array 
 *                  (containing at least one number) which has the largest product.
 * 
 *   Example 1:
 *      Input: [2,3,-2,4]
 *      Output: 6
 *      Explanation: [2,3] has the largest product 6.
 *
 *   Example 2:
 *      Input: [-2,0,-1]
 *      Output: 0
 *      Explanation: The result cannot be 2, because [-2,-1] is not a subarray.
 */
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

// My Solution
int maxProduct(vector<int> &nums)
{
    int tmp_product;
    int max_product_low     = nums[0];
    int max_product_high    = nums[nums.size() - 1];

    tmp_product = nums[0];
    tmp_product = tmp_product == 0 ? 1 : tmp_product;
    for (int i = 1; i < nums.size(); i++)
    {
        max_product_low = (max_product_low < nums[i]) ? nums[i] : max_product_low;
        tmp_product *= nums[i];
        max_product_low = max(tmp_product, max_product_low);

        tmp_product = tmp_product == 0 ? 1 : tmp_product;
    }

    tmp_product = nums[nums.size() - 1];
    tmp_product = tmp_product == 0 ? 1 : tmp_product;
    for (int i = nums.size() - 2; i >= 0; --i)
    {
        tmp_product *= nums[i];
        max_product_high = (max_product_high < nums[i]) ? nums[i] : max_product_high;
        max_product_high = max(tmp_product, max_product_high);

        tmp_product = tmp_product == 0 ? 1 : tmp_product;
    }

    return max(max_product_low, max_product_high);
}


// From geekforgeek.com
int maxSubarrayProduct(vector<int> &arr)
{
    int n = arr.size();

    // max positive product ending at the current position
    int max_ending_here = 1;
 
    // min negative product ending at the current position
    int min_ending_here = 1;
 
    // Initialize overall max product
    int max_so_far = 1;
 
    /* Traverse through the array. Following values are maintained after the i'th iteration:
       max_ending_here is always 1 or some positive product ending with arr[i]
       min_ending_here is always 1 or some negative product ending with arr[i] */
    for (int i = 0; i < n; i++)
    {
        /* If this element is positive, update max_ending_here. 
           Update min_ending_here only if min_ending_here is 
           negative */
        if (arr[i] > 0)
        {
            max_ending_here = max_ending_here*arr[i];
            min_ending_here = min (min_ending_here * arr[i], 1);
        }
 
        /* If this element is 0, then the maximum product cannot end here, 
           make both max_ending_here and min_ending_here 0
           Assumption: Output is alway greater than or equal  to 1. */
        else if (arr[i] == 0)
        {
            max_ending_here = 1;
            min_ending_here = 1;
        }
 
        /* If element is negative. This is tricky
           max_ending_here can either be 1 or positive. 
           min_ending_here can either be 1 or negative.
           next min_ending_here will always be prev. 
           max_ending_here * arr[i] next max_ending_here
           will be 1 if prev min_ending_here is 1, otherwise 
           next max_ending_here will be prev min_ending_here *
           arr[i] */
        else
        {
            int temp = max_ending_here;
            max_ending_here = max (min_ending_here * arr[i], 1);
            min_ending_here = temp * arr[i];
        }
 
        // update max_so_far, if needed
        if (max_so_far <  max_ending_here)
          max_so_far  =  max_ending_here;
    }
 
    return max_so_far;
}

int main()
{
    vector<vector<int>> nums = {{-1, -2, -3, 0},      // Expected: 6
                                {0, 2, 3, -2},        // Expected: 6
                                {-5, -1, -10, 0, 60}, // Expected: 60
                                {6, -3, -10, 0, 2},   // Expected: 180
                                {2, -5, -2, -4, -3}}; // Expected: 240

    vector<int> expected = {6, 6, 60, 180, 240};

    int passed = 0;
    int total = nums.size();

    vector<int> results;

    for (int i = 0; i < nums.size(); i++)
    {
        results.push_back(maxProduct(nums[i]));
        passed += results[i] == expected[i] ? 1 : 0;
    }

    cout << "Passed/Total = " << passed << "/" << total << endl;

    return 0;
}