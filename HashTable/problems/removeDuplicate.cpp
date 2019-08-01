#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

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

int main()
{
    std::string str = "123454567889";
    removeDuplicate(str);
    std::cout << str << std::endl;

    return 0;
}