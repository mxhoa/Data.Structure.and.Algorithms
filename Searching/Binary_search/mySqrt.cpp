#include <iostream>
using namespace std;
/*
 * DESCRIPTION: https://leetcode.com/problems/sqrtx/ 
 */
int mySqrt(int x)
{
    if (x <= 1)
        return x;

    int lower_bound = 1;
    int upper_bound = x;

    while (true)
    {
        int middle = lower_bound + (upper_bound - lower_bound) / 2;
        if (middle > x / middle)
            upper_bound = middle - 1;
        else
        {
            if (middle + 1 > x / (middle + 1))
                return middle;
            lower_bound = middle + 1;
        }
    }
}

int main()
{
    int x = 8;
    cout << "mySqrt(" << x << ") = " << mySqrt(x) << endl;
    return 0;
}
