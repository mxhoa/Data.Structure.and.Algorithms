#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

/* 
 * DESCRIPTION: https://leetcode.com/problems/intersection-of-two-arrays/
 * Given two arrays, write a function to compute their intersection.
 */


vector<int> intersectionTwoArrays(vector<int> &nums1, vector<int> &nums2)
{
    unordered_map<int, bool> hs;
    vector<int> res;
    for (auto i : nums1)
        hs[i] = true;

    for (auto i : nums2)
    {
        if (hs[i])
        {
            res.push_back(i);
            hs[i] = false;
        }
    }

    return res;
}

int main()
{
    vector<int> nums1 = {4, 9, 5};
    vector<int> nums2 = {9, 4, 9, 8, 4};

    vector<int> res = intersectionTwoArrays(nums1, nums2);
    for (int i : res)
        cout << i << ' ';

    return 0;
}