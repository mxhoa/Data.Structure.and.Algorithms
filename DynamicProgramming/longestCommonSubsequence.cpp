/**
 * @brief Longest Common Subsequence
 *         https://www.geeksforgeeks.org/longest-common-subsequence/
 *        LCS Problem Statement: Given two sequences, find the length of longest subsequence present 
 *        in both of them. A subsequence is a sequence that appears in the same relative order, 
 *        but not necessarily contiguous. For example, “abc”, “abg”, “bdf”, “aeg”, ‘”acefg”, .. etc 
 *        are subsequences of “abcdefg”. So a string of length n has 2^n different possible subsequences.
 *
 *   It is a classic computer science problem, the basis of diff (a file comparison program that outputs 
 *      the differences between two files), and has applications in bioinformatics.
 *
 *   Examples:
 *      LCS for input Sequences “ABCDGH” and “AEDFHR” is “ADH” of length 3.
 *      LCS for input Sequences “AGGTAB” and “GXTXAYB” is “GTAB” of length 4.
 * 
 * @file longestCommonSubsequence.cpp
 * @author your name
 * @date 2018-06-24
 */

#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

/**************************** 1. Optimal Substructure ****************************************
 * Let the input sequences be 
 *     X[0..m-1] 
 *     Y[0..n-1] of lengths m and n respectively. 
 *     
 * And let L(X[0..m-1], Y[0..n-1]) be the length of LCS of the two sequences X and Y. 
 * Following is the recursive definition of L(X[0..m-1], Y[0..n-1]).
 * 
 * If last characters of both sequences match 
 *     (X[m-1] == Y[n-1])
 *     => L(X[0..m-1], Y[0..n-1]) = 1 + L(X[0..m-2], Y[0..n-2])
 * 
 * If last characters of both sequences do not match 
 *     (X[m-1] != Y[n-1])
 *     => L(X[0..m-1], Y[0..n-1]) = MAX ( L(X[0..m-2], Y[0..n-1]), L(X[0..m-1], Y[0..n-2])
 * 
 **********************************************************************************************/

int longestCommonSubsequence(string X, string Y, int m, int n)
{
    if (m == 0 || n == 0)
        return 0;
    if (X[m - 1] == Y[n - 1])
        return longestCommonSubsequence(X, Y, m - 1, n - 1) + 1;
    else 
        return max(longestCommonSubsequence(X, Y, m - 1, n), 
                    longestCommonSubsequence(X, Y, m, n - 1));
}

/************************* 2. Overlapping Subproblems *********************************
 * 
 *                         lcs("AXYT", "AYZX")
 *                         /                 \
 *             lcs("AXY            /              \                /              \ 
 * ", "AYZX")            lcs("AXYT", "AYZ")
 * lcs("AX", "AYZX")   lcs("AXY", "AYZ")   lcs("AXY", "AYZ") lcs("AXYT", "AY")
 * 
 **************************************************************************************/
int longestCommonSubsequence_Opt(string X, string Y)
{
    int m = X.length();
    int n = Y.length();

    int L[m + 1][n + 1];
    int i, j;

    for (i = 0; i <= m; i++)
    {
        for (j = 0; j <= n; j++)
        {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i-1][j-1] + 1;
            else 
                L[i][j] = max(L[i][j-1], L[i-1][j]);
        }
    }

    return L[m][n];
}

int longestCommonSubsequence_print(string X, string Y)
{
    int maxLen = 1;
    int m = X.length();
    int n = Y.length();
    int L[m+1][n+1];

    for (int i = 0; i <= m; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                L[i][j] = 1 + L[i-1][j-1];
            else 
                L[i][j] = max(L[i-1][j], L[i][j-1]);
        }
    }
    maxLen = L[m][n];

    // Following code is used to print longest common substring
    int index = L[m][n];
    
    // Create a character array to store the longest common substring
    char lcs[index + 1];
    lcs[index] = '\0';

    // Start from the right-most-bottom-most corner and one by one 
    // store characters in lcs[]
    int i = m, j = n;
    while (i > 0 && j > 0)
    {
        // If current character in X[] and Y are same, then current 
        // character is part of LCS
        if (X[i - 1] == Y[j-1])
        {
            lcs[index - 1] = X[i - 1];
            i--; j--; index--;
        }
        else if (L[i-1][j-1] > L[i][j-1])
            i--;
        else 
            j--;
    }

    cout << "Longest Common Subsequence" << X << " and " << Y << " is : " << lcs << endl;

    return maxLen;    
}
int main()
{
    string X = "AGGTAB";
    string Y = "GXTXAYB";

    cout << "longest = " << longestCommonSubsequence(X, Y, 6, 7) << endl;
    cout << "longest_lcs = " << longestCommonSubsequence_Opt(X, Y) << endl;
    cout << "longest_lcs = " << longestCommonSubsequence_print(X, Y) << endl;

    return 0;
}