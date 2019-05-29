/*
 * 5. Write a hashing algorithm for strings.
 * Hint: Use Horner's method
 * 
 * 
 * 
*/
#include <iostream>
#include <vector>

int hornerHash(std::vector<char> &key, int tableSize)
{
    int size = key.size();
    int h = 0;
    int i;
    for (i = 0; i < size; i++)
    {
        h = (32 * h + key[i]) % tableSize;
    }
    return h;
}