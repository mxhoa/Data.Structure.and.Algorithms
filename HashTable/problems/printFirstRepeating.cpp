
#include <iostream>
#include <vector>
#include <unordered_set>
/********************************************************************************************
 *      PRINT FIRST REPEATING
 * 
 ********************************************************************************************/
void printFirstRepeating(std::vector<int> &arr)
{
    std::unordered_multiset<int> ms;

    for (int i = 0; i < arr.size(); i++)
    {
        ms.insert(arr[i]);
        if (ms.count(arr[i]) > 1) {
            std::cout << "First Repeating number is : " << arr[i] << std::endl;
            return;
        }
    }

    std::cout << "Not exist the First Repeating number."<< std::endl;
}

int main()
{
    std::vector<int> nums = {1, 2, 3, 4, 4, 4, 5, 5, 6};
    
    printFirstRepeating(nums);

    return 0;
}