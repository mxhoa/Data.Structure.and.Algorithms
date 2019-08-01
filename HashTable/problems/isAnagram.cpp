#include <iostream>
#include <string>
#include <unordered_set>

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

    std::unordered_multiset<int> ms;

    for (auto ch : str1)
        ms.insert(ch);

    for (auto ch : str2)
        ms.erase(ch);

    return (ms.size() == 0);
}

int main()
{
    std::string str1 = "reset";
    std::string str2 = "rstee";

    std::cout << "Is Anagram = " << isAnagram(str1, str2) << std::endl;

    return 0;
}
