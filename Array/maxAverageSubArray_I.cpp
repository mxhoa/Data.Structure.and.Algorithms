#include <iostream>
#include <vector>

using namespace std;
/**
 * @brief [643] Maximum Average Subarray I
 * Given an array consisting of n integers, find the contiguous subarray of given length k 
 * that has the maximum average value. And you need to output the maximum average value.
 * 
 * Example 1:
 *  - Input: [1,12,-5,-6,50,3], k = 4
 *  - Output: 12.75
 *    Explanation: Maximum average is (12-5-6+50)/4 = 51/4 = 12.75
 * 
 */
class Solution
{
public:
    double findMaxAverage(vector<int> &nums, int k)
    {
        double sum = 0;
        double max = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (i < k)
            {
                sum += nums[i];
                max = sum;
            }
            else
            {
                sum += nums[i] - nums[i - k];
                max = std::max(max, sum);
            }
        }

        return max / k;
    }
};

int main()
{
    vector<int> nums = {1, 12, -5, -6, 50, 3};
    int k = 4;

    cout << "result = " << (new Solution())->findMaxAverage(nums, k) << endl;

    return 0;
}