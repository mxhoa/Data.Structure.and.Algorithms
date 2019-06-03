#include <iostream>
#include <vector>

/*
 * - Time Complexity: O(logN)
 * - Space Complexity: O(logN)
 */
bool BinarySearchRecursive(std::vector<int> &data, int low, int high, int value)
{
    if (low > high)
    {
        return false;
    }

    int mid = low + (high - low) / 2; // To avoid the overflow
    if (data[mid] == value)
    {
        return true;
    }
    else if (data[mid] < value)
    {
        return BinarySearchRecursive(data, mid + 1, high, value);
    }
    else
    {
        return BinarySearchRecursive(data, low, mid - 1, value);
    }
}