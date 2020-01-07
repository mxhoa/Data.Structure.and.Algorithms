#include <iostream>
#include <vector>

/**********************************************************************************************
 * @brief Subset Sum Problem
 * @description: Given a set of non-negative integer, and a value sum, determine if there is 
 *               a subset of the given set with sum equal to given sum
 * 
 * @example:    
 *      Input:   nums[] = {3, 34, 4, 12, 5, 2}, sum = 9
 *      Output:  True  
 *               //There is a subset (4, 5) with sum 9.
 * 
 *
 ********************************************************************************************/

/**
 * The subset sum problem can be divided into two subproblems:
 *  - Sub1: Include the last element, recur for n = n - 1, sum = sum - nums[n - 1]
 *  - Sub2: Exclude the last element, recur for n = n - 1
 * If any of the above subproblems return TRUE, then return TRUE.
 * 
 */

class RecursiveSolution
{
public:
    bool isSubsetUtil(std::vector<int> &nums, int len, int sum)
    {
        if (sum == 0)
            return true;
        if (len == 0 && sum != 0)
            return false;

        if (nums[len - 1] > sum)
            return isSubsetUtil(nums, len - 1, sum);

        return isSubsetUtil(nums, len - 1, sum) ||
               isSubsetUtil(nums, len - 1, sum - nums[len - 1]);
    }

    bool isSubsetSum(std::vector<int> &nums, int sum)
    {
        int len = nums.size();

        return isSubsetUtil(nums, len, sum);
    }
};

/* 
 *  ##[i][j] | 0   1   2   3 ... sum
 *       [0] | T   F   F   F      F
 *       [1] | T   
 *       [2] | T
 *       ... | T
 *      [n-1]| T
 *       [n] | T                  ?
 * 
 */
class DPSolution
{
public:
    bool isSubsetSum(std::vector<int> &nums, int sum)
    {
        int len = nums.size();

        return isSubsetUtil(nums, len, sum);
    }

    bool isSubsetUtil(std::vector<int> &nums, int n, int sum)
    {
        // The value of subset[i][j] will be true if there is
        // a subset of set[0..j-1] with sum equal to i
        bool subset[n + 1][sum + 1];

        // If sum is 0, then answer is TRUE
        for (int i = 0; i <= n; i++)
            subset[i][0] = true;

        // If sum is not 0 and set is empty, then answer is false
        for (int i = 1; i <= sum; i++)
            subset[0][i] = false;

        // Fill the subset table in bottom up manner
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= sum; j++)
            {
                if (j < nums[i - 1])
                    subset[i][j] = subset[i - 1][j];

                if (j >= nums[i - 1])
                    subset[i][j] = subset[i - 1][j] || subset[i - 1][j - nums[i - 1]];
            }
        }

        return subset[n][sum];
    }
};

int main()
{
    std::vector<int> nums = {3, 34, 4, 12, 5, 2};
    int sum = 9;

    std::cout << "Result = " << (new RecursiveSolution())->isSubsetSum(nums, sum) << std::endl;
    std::cout << "Result = " << (new DPSolution())->isSubsetSum(nums, sum) << std::endl;

    return 0;
}