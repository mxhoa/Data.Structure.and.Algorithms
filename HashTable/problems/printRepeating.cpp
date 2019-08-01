#include <iostream>
#include <vector>
#include <unordered_set>

/********************************************************************************************
 *      PRINT REPEATING
 * Print the repeating integer in a list of integers
 ********************************************************************************************/
void printRepeating(std::vector<int> &nums)
{
    std::unordered_multiset<int> hs;
    std::cout << "Repeating elements are: \n";

    for (auto val : nums)
        hs.insert(val);

    for (auto val : nums)
    {
        if (hs.count(val) > 1)
        {
            std::cout << "No "<< val << " - " << hs.count(val) << " times" << std::endl;
            hs.erase(val);
        }
    }
}


int main()
{
    std::vector<int> nums = { 1, 2, 2, 2, 3, 4, 5, 5, 6, 7};
    printRepeating(nums);

    return 0;
}