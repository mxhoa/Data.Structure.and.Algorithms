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