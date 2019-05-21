#include<iostream>
#include<limits.h>
#include<cmath>

using namespace std;
/**
 * @brief Find the square root of number
 * 
 * @Approach: Binary Search 
 * 
 * @param number    The number
 * @param min_range Min range
 * @return double   The square root of number.
 */
double squareRoot_1(int number, double min_range)
{
    double result       = 0;
    double lower_bound  = 0;
    double upper_bound  = number;

    while(lower_bound < upper_bound) 
    {
        result = lower_bound + (upper_bound - lower_bound)/2;
        double pow2 = result*result;

        if (fabs(pow2 - number) <= min_range)
            return result;
        else if (pow2 > number)
            upper_bound = result;
        else
            lower_bound = result;
    }
	return result;
}

/**
 * @brief   Find the square root of number.
 * 
 * @Approach: Babylonian method (BEST)
 * REF: https://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Babylonian_method
 * 
 * @param number    The number
 * @param min_range Min range
 * @return double   The square root of number.
 */
double squareRoot_2(double number, double min_range)
{
    double s = number;
    while ((s - number/s) > min_range)
    {
        s = (s + number/s) / 2;
    }
    return s;
}

int main()
{
    double min_range = 0.0001;
    int num = 1123;

    cout << "squareRoot_1(" << num << ") = " << squareRoot_1(num, min_range) << endl;
    cout << "squareRoot_2(" << num << ") = " << squareRoot_2(num, min_range) << endl;

    return 0;
}