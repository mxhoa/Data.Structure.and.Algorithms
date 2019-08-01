#include <iostream>
#include <vector>

using namespace std;

/* 
 * @DESCRIPTION: https://leetcode.com/problems/peak-index-in-a-mountain-array/
 */

/**
 * @brief Find the peak index in mountain in array
 * Complexity Analysis
 *      - Time Complexity: O(log N), where N is the length of A.
 *      - Space Complexity: O(1).
 */
int peakIndexInMountainArray(vector<int> &A)
{
    int lower_bound = 0;
    int higher_bound = A.size() - 1;
    int median = 0;

    while (lower_bound <= higher_bound)
    {
        median = (lower_bound + higher_bound) / 2;
        if (A[median - 1] > A[median])
        {
            higher_bound = median;
        }
        else if (A[median] < A[median + 1])
        {
            lower_bound = median;
        }
        else
        {
            return median;
        }
    }

    return median;
}

int main()
{
    vector<int> A = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,13,12,8,3,0};
    cout << "Peak Index in a Mountain Array = " << peakIndexInMountainArray(A) << endl;
    return 0;
}
