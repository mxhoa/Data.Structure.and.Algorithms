#include <iostream>
#include <string>
#include <math.h>
using namespace std;

/**
 * @brief       ONE AWAY
 *              There are three types of edits that can be performed on strings: insert a character,
 *              remove a character, or replace a character. Given two strings, write a function to check if they are
 *              one edit (or zero edits) away.
 *              
 *              EXAMPLE
 *                  pale, ple   -> true     (remove/insert 'a')                 ONE edit
 *                  pales, pale -> true     (remove/insert 's')                 ONE edit
 *                  pale, bale  -> true     (replace 'p'->'b' or 'b'->'p')      ONE edit
 *                  pale, bae   -> false    (replace 'p'->'b' & remove 'l')     TWO edit
 *                  
 * @param[in]  str1  The string 1
 * @param[in]  str2  The string 2
 *
 * @return     { description_of_the_return_value }
 */


bool oneAway(string str1, string str2)
{
    int foundDifferent = false;
    int len1 = str1.length();
    int len2 = str2.length();
    
    if (abs(len1 - len2) > 1)
        return false;
    
    string gStr = len1 >= len2 ? str1 : str2;
    string lStr = len1 < len2 ? str1 : str2;
    
    int index1 = 0;
    int index2 = 0;
    
    while(index1 < (int)gStr.length() && index2 < (int)lStr.length())
    {
        if (gStr[index1] != lStr[index2])
        {
            if (foundDifferent)
                return false;
            foundDifferent = true;
            if (len1 == len2)
            {
                index1++;
                index2++;
            }
            else
            {
                index1++;
            }
        }
        else
        {
            index1++;
            index2++;
        }
    }
    
    return true;
}
int main()
{
    string str1 = "pale";
    string str2 = "base";
    
    cout << "res = " << oneAway(str1, str2) << endl;
    return 0;
}