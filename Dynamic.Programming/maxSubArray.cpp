/**
 * ============== 53. Maximum Subarray ==============================================
 * Given an integer array nums, find the contiguous subarray (containing at least one 
 * number) which has the largest sum and return its sum.
 * 
 * Example:
 * 		Input: [-2,1,-3,4,-1,2,1,-5,4],
 * 		Output: 6
 * 		Explanation: [4,-1,2,1] has the largest sum = 6.
 *
 * Follow up:
 * 	If you have figured out the O(n) solution, try coding another solution using the 
 * 	divide and conquer approach, which is more subtle.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int maxSubArray1(vector<int>& nums)
{
    int max_sub = nums[0];
    int current_sub = nums[0];

    for (int i = 1; i < nums.size(); i++)
    {
        current_sub = max(current_sub + nums[i], nums[i]);
        max_sub = max(max_sub, current_sub);
    }

    return max_sub;
}

int maxSubArray2(vector<int> &nums)
{
    int max_sum = nums[0];
    int tmp_sum = nums[0];

    for (int i = 1; i < nums.size(); i++)
    {
        if (tmp_sum < 0 || tmp_sum + nums[i] < 0)
            tmp_sum = nums[i];
        else
            tmp_sum += nums[i];

        if (max_sum < tmp_sum)
            max_sum = tmp_sum;
    }

    return max_sum;
}

int maxSubArray_print(vector<int>& nums, int &start_idx, int &end_idx)
{
    int max_sum = nums[0];
    int tmp_sum = nums[0];
    int s_idx = 0;
    int e_idx = 0;

    for (int i = 1; i < nums.size(); i++)
    {
        if (tmp_sum < 0 || tmp_sum + nums[i] < 0)
        {
            tmp_sum = nums[i];
            s_idx = i;
            e_idx = i;
        }    
        else
        {
            tmp_sum += nums[i];
            e_idx = i;
        }

        if (max_sum < tmp_sum)
        {
            max_sum = tmp_sum;
            start_idx = s_idx;
            end_idx = e_idx;
        }
    }

    return max_sum;
}



int main()
{
    vector<int> nums1 = {-2,1,-3,4,-1,2,1,-5,4};
    vector<int> nums2 = {-2,-1};

    int s, e;

    cout << "maxSubArray2(nums1) = " << maxSubArray2(nums1) << endl;
    cout << "maxSubArray2(nums2) = " << maxSubArray2(nums2) << endl;

    cout << "maxSubArray_print(nums1) = " << maxSubArray_print(nums1, s, e); 
    cout << " :: start-index = " << s << " -> end-index = " << e << endl;

    cout << "maxSubArray_print(nums2) = " << maxSubArray_print(nums2, s, e);
    cout << " :: start-index = " << s << " -> end-index = " << e << endl;

    return 0;
}