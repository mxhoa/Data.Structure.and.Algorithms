/**
 * @brief [746]. Min Cost Climbing Stairs
 *              On a staircase, the i-th step has some non-negative cost cost[i] assigned (0 indexed).
 *              Once you pay the cost, you can either climb one or two steps. You need to find minimum cost to reach 
 *              the top of the floor, and you can either start from the step with index 0, or the step with index 1.
 * 
 * @file minCostClimbingStairs.cpp
 * @author your name
 * @date 2018-08-11
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int minCostClimbingStairs(vector<int>& cost)
{
    int f1 = cost[0];
    int f2 = cost[1];
    int current_cost = 0;

    for (int i = 2; i < cost.size(); i++)
    {
        current_cost = cost[i] + min(f1, f2);
        f1 = f2;
        f2 = current_cost;
    }
    return min(f1, f2);
}

int main()
{
    vector<int> cost1 = {10, 15, 25};
    vector<int> cost2 = {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};

    cout << "minCostClimbingStairs(cost1) = " << minCostClimbingStairs(cost1) << endl;
    cout << "minCostClimbingStairs(cost2) = " << minCostClimbingStairs(cost2) << endl;

    return 0;
}