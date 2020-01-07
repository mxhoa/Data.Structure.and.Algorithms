#include <iostream>
#include <vector>
using namespace std;

/***********************************************************************************************
 * @brief Climbing Stairs I
 * You are climbing a stair case. It takes n steps to reach to the top.
 * 
 * Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
 * 
 * Note: Given n will be a positive integer.
 * 
 * Example 1:
 * 		Input: 2
 * 		Output: 2
 * 		Explanation: There are two ways to climb to the top.
 * 			1. 1 step + 1 step
 * 			2. 2 steps
 * 
 * Example 2:
 * 		Input: 3
 * 		Output: 3
 * 		Explanation: There are three ways to climb to the top.
 * 			1. 1 step + 1 step + 1 step
 * 			2. 1 step + 2 steps
 * 			3. 2 steps + 1 step
 * 
 ************************************************************************************************/

/*
 * Approach 1: Brute Force Algorithm
 * 
 * In this brute force approach we take all possible step combinations i.e. 1 and 2, at every step. 
 * At every step we are calling the function climbStairsclimbStairs for step 11 and 22, and 
 * return the sum of returned values of both functions.
 * 
 * 	climbStairs(i,n)=(i + 1, n) + climbStairs(i + 2, n)
 * 
 * where i defines the current step and n defines the destination step.
 * 
 * Complexity Analysis
 * 	- Time complexity : O(2^n). Size of recursion tree will be 2^n
 * 	- Space complexity : O(n). The depth of the recursion tree can go upto n
*/
class Solution1
{
public:
    int climbStair_I(int n)
    {
        return climb_Stairs(0, n);
    }
    int climb_Stairs(int i, int n)
    {
        if (i > n)
            return 0;
        if (i == n)
            return 1;
        return climb_Stairs(i + 1, n) + climb_Stairs(i + 2, n);
    }
};

/*
 * Approach 2: Recursion with Memoization
 * 
 * In the previous approach we are redundantly calculating the result for every step. 
 * Instead, we can store the result at each step in memomemo array and directly returning 
 * the result from the memo array whenever that function is called again.
 * 
 * In this way we are pruning recursion tree with the help of memomemo array and reducing 
 * the size of recursion tree upto n.
 * 
 * Complexity Analysis
 * 	- Time complexity : O(n). Size of recursion tree can go upto n
 * 	- Space complexity : O(n). The depth of recursion tree can go upto n 
*/
class Solution2
{
public:
    int climbStair_I(int n)
    {
        vector<int> memo(n + 1);
        return climb_Stairs(0, n, memo);
    }

    int climb_Stairs(int i, int n, vector<int> &memo)
    {
        if (i > n)
            return 0;
        if (i == n)
            return 1;
        if (memo[i] > 0)
            return memo[i];

        memo[i] = climb_Stairs(i + 1, n, memo) + climb_Stairs(i + 2, n, memo);

        return memo[i];
    }
};

/*
 * Approach 3: Dynamic Programming
 * 
 * As we can see this problem can be broken into subproblems, and it contains the optimal substructure property 
 * i.e. its optimal solution can be constructed efficiently from optimal solutions of its subproblems, we can use 
 * dynamic programming to solve this problem.
 * 
 * One can reach i^{th} step in one of the two ways:
 * 		1. Taking a single step from (i-1)^{th} step.
 * 
 * 		2. Taking a step of 2 from (i-2)^{th} step.
 * 
 * So, the total number of ways to reach i^{th} is equal to sum of ways of reaching (i-1)^{th} step 
 * and ways of reaching (i-2)^{th} step.
 * 
 * Let dp[i] denotes the number of ways to reach on i^{th} step:
 * 
 * 		dp[i]=dp[i-1]+dp[i-2]
 * 
 * Complexity Analysis
 * 	- Time complexity : O(n). Single loop upto n.
 * 	- Space complexity : O(n). dp array of size n is used
*/

class Solution3
{
public:
    int climbStair_I(int n)
    {
        if (n == 1)
            return 1;

        vector<int> dp(n + 1);
        dp[1] = 1;
        dp[2] = 2;

        for (int i = 3; i <= n; i++)
        {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }
};

/* 
 * Approach 4: Fibonacci Number
 * In the above approach we have used dpdp array where dp[i]=dp[i-1]+dp[i-2]. 
 * It can be easily analysed that dp[i] is nothing but i^{th} fibonacci number.
 * 
 * 		Fib(n) = Fib(n-1) + Fib(n-2)
 * 
 * Now we just have to find n^{th} number of the fibonacci series having 1 and 2 their first
 * and second term respectively, i.e. Fib(1)=1 and Fib(2)=2
 * 
 * Complexity Analysis
 * 	- Time complexity : O(n). Single loop upto n is required to calculate n^{th} fibonacci number.
 * 	- Space complexity : O(1). Constant space is used. 
 */

class Solution4
{
public:
    int climbStair_I(int n)
    {
        if (n == 1)
            return 1;

        int first = 1;
        int second = 2;

        for (int i = 3; i <= n; i++)
        {
            int third = first + second;
            first = second;
            second = third;
        }
        return second;
    }
};

int main()
{
    int N = 4;
    std::cout << "Solution1 - Count ways: " << (new Solution1())->climbStair_I(N) << std::endl;
    std::cout << "Solution2 - Count ways: " << (new Solution2())->climbStair_I(N) << std::endl;
    std::cout << "Solution3 - Count ways: " << (new Solution3())->climbStair_I(N) << std::endl;
    std::cout << "Solution4 - Count ways: " << (new Solution4())->climbStair_I(N) << std::endl;

    return 0;
}