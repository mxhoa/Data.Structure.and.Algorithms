#include <iostream>
#include <bitset>

/**
 * 
 * You are given two 32-bit numbers, N and M ( N > M ), and two bit positions, i and j.
 * Please write a method to set all bits between i and j in N equal to M
 * (M becomes a substring of N located at i and starting at j)
 * EXAMPLE: 
 *      Input:  N = 10000000000, 
 *              M = 10101, 
 *              i = 2, j = 6 
 *      
 *      Output: N = 10001010100
 */
int updateBits(int n, int m, int i, int j)
{
    int oneMask = ~0;

    int leftMask = oneMask << (j + 1);

    int rightMask = ((1 << i) - 1);

    int mask = leftMask | rightMask;

    int n_cleared = n & mask; // clear bits [j...i]
    int m_shifted = m << i;   // Move m into correct position

    return n_cleared | m_shifted;
}

int main()
{
    int m = 0b10000000000;
    int n = 0b10011;
    int i = 2;
    int j = 6;

    std::cout << "updateBits = " << std::bitset<16>(updateBits(m,n,i,j)) << std::endl;

    return 0;
}