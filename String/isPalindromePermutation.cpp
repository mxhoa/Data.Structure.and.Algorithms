#include <iostream>
#include <string>
using namespace std;

/**
 * @brief      Palindrome Permutation
 *              Given a string, write a function to check if it is a permutation of a palinfrome.
 *              A palindrome is a word or phrase that is the same forwards and backwards. 
 *              A permutation is a rearrangement of letters.
 *              The palindrome does not need to be limited to just dictionary words.
 *              
 * @Example:
 *          INPUT :  "Tact Coa"
 *          OUTPUT:  True 
 *                   (We will created permutations: "taco cat", "atco cta", etc.)
 */     




/**
 * @brief       Gets the character number.
 *              Map each charater to a number: a -> 0, b -> 1, c -> 2. etc.
 *              This is case insensitive. Non-letter characters map to -1.
 *
 */
int getCharNumber(char c)
{
    int num = -1;
    if (c >= 'a' && c <= 'z')
    {
        num = c - 'a';
    }
    else if (c >= 'A' && c <= 'Z')
    {
        num = c - 'A';
    }
    
    return num;
}

/**
 * @brief       Toggle the i-th bit in the interger
 */
int toggle(int bitVector, int index)
{
    if (index < 0)
        return bitVector;
    
    int mask = 1 << index;
    if ((bitVector & mask) == 0)
    {
        bitVector |= mask;
    }
    else
    {
        bitVector &= ~mask;
    }
    return bitVector;
}

/**
 * @brief      Check that exactly one bit set by subtracting one from the integer and 
 *              ANDing it with the original integer
 *              a       = 00010000 = 16 
 *              a - 1   = 00001111 = 15
 *              a&(a-1) = 00000000 = 0
 *             
 * @param[in]  bitVector  The bit vector
 *
 * @return      TRUE - If have exactly one bit has set. 
 */
bool checkExistOne(int  bitVector)
{
    return (bitVector & (bitVector-1)) == 0;
}


bool isPalindromePermutation(string str)
{
    int bitVector = 0;
    int index = 0;
    for (int i = 0; i < str.length(); i++)
    {
        index = getCharNumber(str[i]);
        bitVector = toggle(bitVector, index);
    }
    
    return bitVector == 0 || checkExistOne(bitVector);
}


int main()
{
    std::string str0("Tact Coa");
    std::string str1("A big Cat");
    std::string str2("Aba cbc");
    
    cout << "Hello, World!" << endl;
    
    cout << str0 << "= " << isPalindromePermutation(str0) << endl;
    cout << str1 << "= " << isPalindromePermutation(str1) << endl;
    cout << str2 << "= " << isPalindromePermutation(str2) << endl;
}