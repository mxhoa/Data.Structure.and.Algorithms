/**
 *  =========== 303. Range Sum Query - Immutable  =======================================
 *  @ Description: Given an integer array nums, find the sum of the elements between 
 * 					indices i and j (i ≤ j), inclusive.

 * 	@ Example:
 * 		Given nums = [-2, 0, 3, -5, 2, -1]
 * 		
 * 		sumRange(0, 2) -> 1
 * 		sumRange(2, 5) -> -1
 * 		sumRange(0, 5) -> -3
 */

#include <iostream>
#include <vector>
#include <map>
#include <utility>

using namespace std;

class NumArray1{
    map<pair<int, int>, int> mp;

  public:
    NumArray1(vector<int> nums) {
        for (int i = 0; i < nums.size(); i++)
        {
            int sum = 0;
            for (int j = i; j < nums.size(); j++)
            {
                sum += nums[j];
                mp[make_pair(i,j)] += sum;
            }
        }
    }

    int sumRange(int i, int j)
    {
        return mp[make_pair(i,j)];
    }
};

class NumArray
{
    vector<int> sum;

public:
    NumArray(vector<int> nums)
    {   int s = 0;
        sum.push_back(s);
        for (int i = 0; i < nums.size(); i++)
        {
            s += nums[i];
            sum.push_back(s);
        }
    }

    int sumRange(int i, int j)
    {
        return sum[j+1] - sum[i];
    }
};

int main()
{
    vector<int> nums1 = {-2, 0, 3, -5, 2, -1};

    NumArray num = NumArray(nums1);
    cout << "num.sumRange(0, 2)= " << num.sumRange(0, 2) << endl;
    cout << "num.sumRange(2, 5)= " << num.sumRange(2, 5) << endl;
    cout << "num.sumRange(0, 5)= " << num.sumRange(0, 5) << endl;
}