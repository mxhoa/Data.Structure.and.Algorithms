#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include "count_map.h"

/********************************************************************************************
 *      ANAGRAM SOLVER
 * An anagram is a word or phrase formed by reordering the letters of another word or phrase
 * Two words are anagram if they are of same size and there characters are same
 ********************************************************************************************/
bool isAnagram(std::string &str1, std::string &str2)
{
    int size1 = str1.size();
    int size2 = str2.size();

    if (size1 != size2)
        return false;
    
    CountMap<char> *cm = new CountMap<char>();

    for (auto ch : str1)
        cm->add(ch);

    for (auto ch : str2)
        cm->remove(ch);
    
    return (cm->size() == 0);
}

/********************************************************************************************
 *      REMOVE DUPLICATE
 * Remove duplicates in an array of numbers
 ********************************************************************************************/
void removeDuplicate(std::string &str)
{
    int index = 0;
    std::unordered_set<char> hs;

    for (auto ch : str)
    {
        if (hs.find(ch) == hs.end())
        {
            str[index++] = ch;
            hs.insert(ch);
        }
    }
    str[index] = '\0';
}

/********************************************************************************************
 *      FIND MISSING
 * There is a list of integers we need to find the missing number in the list.
 ********************************************************************************************/
int findMissing(std::vector<int> &arr, int start, int end)
{
    std::unordered_set<int> hs;
    for (auto i : arr)
    {
        hs.insert(i);
    }

    for (int curr = start; curr <= end; curr++)
    {
        if (hs.find(curr) == hs.end())
        {
            return curr;
        }
    }

    return std::numeric_limits<int>::max();
}

/********************************************************************************************
 *      PRINT REPEATING
 * Print the repeating integer in a list of integers
 ********************************************************************************************/
void printRepeating(std::vector<int> &arr)
{
    std::unordered_set<int> hs;
    std::cout << "Repeating elements are: ";
    for (auto val:arr)
    {
        if (hs.find(val) != hs.end())
        {
            std::cout << val << " ";
        }
        else
        {
            hs.insert(val);
        }
        
    }
}

/********************************************************************************************
 *      PRINT FIRST REPEATING
 * 
 ********************************************************************************************/
void printFirstRepeating(std::vector<int> &arr)
{
    int i;
    int size = arr.size();
    CountMap<int> *hs = new CountMap<int>();

    for (i = 0; i < size; i++)
    {
        hs->add(arr[i]);
    }

    for (i = 0; i < size; i++)
    {
        hs->remove(arr[i]);
        if (hs->containsKey(arr[i]))
        {
            std::cout << "First Repeating number is : " << arr[i] << std::endl;
            return;
        }
    }
}