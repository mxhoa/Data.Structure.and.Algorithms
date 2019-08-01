/**
 * @brief Longest Repeating Subsequence
 *          Given a string, find length of the longest repeating subseequence such that 
 *          the two subsequence don’t have same string character at same position, i.e., 
 *          any i’th character in the two subsequences shouldn’t have the same index in 
 *          the original string.
 *  
 *          https://www.geeksforgeeks.org/longest-repeating-subsequence/
 * 
 * 
 * @file longestRepeatingSubsequence.cpp
 * @author your name
 * @date 2018-06-25
 */
#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

int longestRepeatingSubsequence(string str)
{
    int n = str.length();
    int L[n+1][n+1];

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (str[i - 1] == str[j - 1] && i != j)
                L[i][j] = 1 + L[i-1][j-1];
            else
                L[i][j] = max(L[i-1][j], L[i][j-1]);
        }
    }

#if defined _PRINT_SOLUTION_1_
    int index = L[n][n];
    char lrs[index+1];
    lrs[index] = '\0';
    int i = n, j = n;
    while (i > 0 && j > 0)
    {
        if (str[i-1] == str[j-1] && i != j)
        {
            lrs[index - 1] = str[i-1];
            i--; j--; index--;
        }
        else if (L[i][j] > L[i][j-1])
            i--;
        else 
            j--;
    }

    cout << "lrs('" << str << "') = " << lrs << endl;

#else
    string res = "";
    int i = n, j = n;
    while (i > 0 && j > 0)
    {
        if (L[i][j] == L[i-1][j-1] + 1)
        {
            res = res + str[i-1];
            i--;
            j--;
        }
        else if (L[i][j] == L[i-1][j])
            i--;
        else 
            j--;
    }
    reverse(res.begin(), res.end());
    cout << "'" << str << "' ~ " << res << " :: len = " << L[n][n] << endl;
#endif 

    return L[n][n];
}


int longestRepeatingSubsequence_hash(string str)
{
    int counter = 0;
    unordered_map<char, int> mp;

    for (auto i : str)
        mp[i]++;
    
    for (auto i : str)
    {
        if (mp[i] > 0)
        {
            counter += mp[i] - 1;
            mp[i] = 0;
        }
    }
    return counter;
}

int longestRepeatingSubsequence_print(string str)
{

}
int main()
{

    longestRepeatingSubsequence("AABEBCDD");
    longestRepeatingSubsequence("ABBA");
    longestRepeatingSubsequence("abc");
    longestRepeatingSubsequence("aab");
    longestRepeatingSubsequence("aabb");
    longestRepeatingSubsequence("axxxy");

    // cout << "hash - AABEBCDD = " << longestRepeatingSubsequence_hash("AABEBCDD") << endl;
    // cout << "hash - ABBA = " << longestRepeatingSubsequence_hash("ABBA") << endl;
    // cout << "hash - abc = " << longestRepeatingSubsequence_hash("abc") << endl;
    // cout << "hash - aab = " << longestRepeatingSubsequence_hash("aab") << endl;
    // cout << "hash - aabb = " << longestRepeatingSubsequence_hash("aabb") << endl;
    // cout << "hash - axxxy = " << longestRepeatingSubsequence_hash("axxxy") << endl;


    return 0;
}