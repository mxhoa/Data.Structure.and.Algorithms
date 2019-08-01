#include <iostream>
#include <climits>
#include <algorithm>
#include <vector>
using namespace std;

// Dynamic progarmming with O(n) complexity, O(n) space 
// f[n] = max (f[n-1] + a[n], a[n])
// maxSum = max (f[n], maxSum)
int maxSubArraySum_DP(vector<int> a)
{
    int n = a.size();
    vector<int> f(n, INT_MIN);
    int maxSum = 0;
    f[0] = a[0];
    maxSum = f[0];
    for (int i = 1; i < a.size(); i++)
    {
        f[i] = max(f[i-1] + a[i], a[i]);
        maxSum = max(f[i], maxSum);
    }

    return maxSum;
}

// Optimize O(1) space 
int maxSubArray_DPOP(vector<int> a)
{
    int prev = a[0];
    int maxSum = prev;
    int next;
    for (int i = 1; i < a.size(); i++)
    {
        prev = max(prev + a[i], a[i]);
        maxSum = max(prev, maxSum);
    }

    return maxSum;
}

int main()
{
    vector<int> a = {-2, -3, 4, -1, -2, 1, 5, -3};
    cout << "maxSubArraySum_DP(a) " << maxSubArraySum_DP(a) << endl;
    cout << "maxSubArray_DPOP(a) " << maxSubArray_DPOP(a) << endl;
    return 0;
}