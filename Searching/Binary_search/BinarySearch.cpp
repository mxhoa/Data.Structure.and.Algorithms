#include <iostream>
#include <vector>

/*
 * - Time Complexity: O(logN)
 * - Space Complexity: O(1)
 */
bool Binarysearch(std::vector<int> &data, int value)
{
    int size = data.size();
    int low = 0;
    int high = size - 1;
    int mid;
    while (low <= high)
    {
        mid = low + (high - low) / 2; // To avoid the overflow
        if (data[mid] == value)
        {
            return true;
        }
        else if (data[mid] < value)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return false;
}

