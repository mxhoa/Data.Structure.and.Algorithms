#include <iostream>
#include <vector>

/*
 * - Time Complexity: O(N)
 * - Space Complexity: O(1)
 */
bool linearSearchUnsorted(std::vector<int> &data, int value)
{
    int size = data.size();
    for (int i = 0; i < size; i++)
    {
        if (value == data[i])
        {
            return true;
        }
    }
    return false;
}

