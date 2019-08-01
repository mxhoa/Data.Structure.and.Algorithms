/**
 * @brief LONGEST PALINDROMIC SUBSTRING 
 *          Given a string, find the longest substring which is palindrome. For example,
 *          if the given string is "forgeeksskeegfor", the output should be "geeksskeeg"
 * 
 * 
 * @file longestPalindromicSubstring.cpp
 * @author your name
 * @date 2018-06-22
 */
#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

string longestPalindromicSubstring(string str)
{
    int max_len = 1;
    int hi = 0;
    int lo = 0;
    int counter = 0;

    for (int i = 0; i < str.length(); i++)
    {
        for (int j = str.length() - 1; j >= i; j--)
        {
            if (j - i + 1 < max_len)
                break;
            counter++;
            
            string tmp = str.substr(i, j - i);
            string sub(tmp);
            reverse(sub.begin(), sub.end());
            if (sub == tmp)
            {
                if (max_len < j - i + 1)
                {
                    max_len = j - i + 1;
                    hi = j;
                    lo = i;
                }
                break;
            }
        }
        if (str.length() - i < max_len)
            break;
    }
    cout << "Counter1 = " << counter << endl;
    return str.substr(lo, hi - lo);
}

string longestPalindromicSubstring2(string str)
{
    int maxLength = 1;
    int start = 0;
    int len = str.length();
    
    int lo, hi;
    int counter = 0;
    // One by one consider every character as center point of even and length palindromes
    for (int i = 1; i < len; i++)
    {
        // Find the longest even length palindrome with center point
        // as i-1 and i
        lo = i - 1;
        hi = i;
        while (lo >= 0 && hi < len && str[lo] == str[hi])
        {
            counter++;
            if (hi - lo + 1 > maxLength)
            {
                start = lo;
                maxLength = hi - lo + 1;
            }
            --lo;
            ++hi;
        }

        // Find the longest odd length palindrome with cenver
        // points as i 
        lo = i - 1;
        hi = i + 1;
        while (lo >= 0 && hi < len && str[lo] == str[hi])
        {
            counter++;
            if (hi - lo + 1 > maxLength)
            {
                start = lo;
                maxLength = hi - lo + 1;
            }
            --lo;
            ++hi;
        }
    }
    cout << "Counter 2 = " << counter << endl;
    return str.substr(start, maxLength);
}

string longestPalindromicSubstring_mxhoa(string str)
{
    int start = 0;
    int maxLen = 1;

    int lo;
    int hi;
    
    int counter = 0;

    for (int i = 1; i < str.length(); i++)
    {
        if (str.length() - i < maxLen)
            break;
        // Odd case
        lo = i - 1;
        hi = i;
        while (lo >= 0 && hi < str.length() && str[lo] == str[hi])
        {
            counter++;
            if (hi - lo + 1 > maxLen)
            {
                start = lo;
                maxLen = hi - lo + 1;
            }
            --lo;
            ++hi;
        }

        // Even case
        lo = i - 1;
        hi = i + 1;
        while (lo >= 0 && hi < str.length() && str[lo] == str[hi])
        {
            counter++;
            if (hi - lo + 1 > maxLen)
            {
                start = lo;
                maxLen = hi - lo + 1;
            }
            --lo;
            ++hi;
        }
    }
    cout << "MXHOA - Counter = " << counter << endl;
    return str.substr(start, maxLen);
}

string longestPalindromicSubstring_best(std::string s)
{
    if (s.size() < 2)
        return s;
    int len = s.length();
    int max_left = 0;
    int max_len = 1;
    int left, right;
    
    int counter = 0;

    for (int start = 0; start < len && len - start > max_len / 2;)
    {
        left = right = start;

        while (right < len - 1 && s[right + 1] == s[right])
        {
            counter++;
            ++right;
        }
        start = right + 1;

        while (right < len - 1 && left > 0 && s[right + 1] == s[left - 1])
        {
            counter++;
            ++right;
            --left;
        }

        if (max_len < right - left + 1)
        {
            max_len = right - left + 1;
            max_left = left;
        }
    }
    cout << "Best - Counter = " << counter << endl;
    return s.substr(max_left, max_len);

}
int main()
{
    string s("forgeeksdddddddddddddddskeegfor");
    cout << "longestPalindromicSubstring = " << longestPalindromicSubstring(s) << endl;
    cout << "longestPalindromicSubstring = " << longestPalindromicSubstring2(s) << endl;
    cout << "longestPalindromicSubstring = " << longestPalindromicSubstring_mxhoa(s) << endl;
    cout << "longestPalindromicSubstring = " << longestPalindromicSubstring_best(s) << endl;

    return 0;
}
