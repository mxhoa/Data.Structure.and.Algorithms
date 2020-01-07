#include <iostream>
#include <vector>
/**************************************************************************************************************
 * @file climbStairs_II.cpp
 * @author your name (you@domain.com)
 * @brief Climb Stairs II
 * 
 * There's a staircase with N steps, and you can climb 1 or 2 steps at a time. 
 * Given N, write a function that returns the number of unique ways you can climb the staircase. 
 * The order of the steps matters.
 * 
 * For example, if N is 4, then there are 5 unique ways:
 *      1, 1, 1, 1
 *      2, 1, 1
 *      1, 2, 1
 *      1, 1, 2
 *      2, 2
 * 
 * What if, instead of being able to climb 1 or 2 steps at a time, you could climb any number from 
 * a set of positive integers X? For example, if X = {1, 3, 5}, you could climb 1, 3, or 5 steps at a time. 
 * Generalize your function to take in X.
 * @date 2019-08-14
 * 
 **************************************************************************************************************/

/**
 * Solution
 * It's always good to start off with some test cases. Let's start with small cases and see if we 
 * can find some sort of pattern.
 * 
 *      - N = 1: [1]
 *      - N = 2: [1, 1], [2]
 *      - N = 3: [1, 2], [1, 1, 1], [2, 1]
 *      - N = 4: [1, 1, 2], [2, 2], [1, 2, 1], [1, 1, 1, 1], [2, 1, 1]
 * 
 * What's the relationship?
 * 
 * The only ways to get to N = 3, is to first get to N = 1, and then go up by 2 steps, or get to N = 2 
 * and go up by 1 step. So f(3) = f(2) + f(1).
 * 
 * Does this hold for N = 4? Yes, it does. Since we can only get to the 4th step by getting to the 3rd step
 * and going up by one, or by getting to the 2nd step and going up by two. So f(4) = f(3) + f(2).
 * 
 * To generalize, f(n) = f(n - 1) + f(n - 2). That's just the Fibonacci sequence!
 *
 *  Time Complexity: O(2^N)
 *  Space Complexity: O(N)
 */
int climbStairs(int n)
{
    if (n <= 1)
        return 1;
    return climbStairs(n - 1) + climbStairs(n - 2);
}

/* 
 * Of course, this is really slow (O(2^N)) — we are doing a lot of repeated computations! 
 * We can do it a lot faster by just computing iteratively:
 *
 *  Time Complexity: O(N)
 *  Space Complexity: O(1)
 */
int climbStairs_I(int n)
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

/* 
 * Now, let's try to generalize what we've learned so that it works if you can take a number 
 * of steps from the set X. Similar reasoning tells us that if X = {1, 3, 5}, then our algorithm 
 * should be f(n) = f(n - 1) + f(n - 3) + f(n - 5). 
 * If n < 0, then we should return 0 since we can't start from a negative number of steps.
 *
 *  Time Complexity: O(|X|^N)
 *  Space Complexity: O(N)
 */
class RecursiveSolution
{
public:
    int climbStair_II(int n, std::vector<int> x)
    {
        if (n < 0)
            return 0;
        else if (n == 0)
            return 1;

        int counter = 0;
        for (auto i : x)
            counter += climbStair_II(n - i, x);
        return counter;
    }
};

/* This is again, very slow (O(|X|^N)) since we are repeating computations again. 
 * We can use a dynamic programming to speed it up.
 * 
 * Each entry fn[i] will contain the number of ways we can get to step i with the set X. 
 * Then, we'll build up the array from zero using the same recurrence as before:
 *
 *  Time Complexity: O(N * |X|)
 *  Space Complexity: O(N)
 */
class DynamicSolution
{
public:
    int climbStair_II(int N, std::vector<int> x)
    {
        std::vector<int> fn(N + 1);
        fn[0] = 1;

        for (int i = 1; i <= N; i++)
        {
            fn[i] = 0;
            for (int j : x)
            {
                if (i < j)
                    break;
                fn[i] += fn[i - j];
            }
        }
        return fn[N];
    }
};

int main()
{
    int N = 4;
    std::vector<int> x = {1, 2};
    std::cout << "RecursiveSolution - Count ways: " << (new RecursiveSolution())->climbStair_II(N, x) << std::endl;
    std::cout << "DynamicSolution   - Count ways: " << (new DynamicSolution())->climbStair_II(N, x) << std::endl;
    return 0;
}