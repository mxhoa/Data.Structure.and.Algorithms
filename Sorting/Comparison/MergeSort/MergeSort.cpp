#include <iostream>
#include <vector>

using namespace std;

class MergeSort
{
private:
    std::vector<int> m_dataset;

public:
    MergeSort() {}
    MergeSort(std::vector<int> &nums) : m_dataset(nums) {}

public:
    bool init(std::vector<int> &nums);
    void sort();
    void print();

private:
    void merge(std::vector<int> &nums, std::vector<int> &cacheNums, int lo, int mi, int hi);
    void mergeSrt(std::vector<int> &nums, std::vector<int> &cacheNums, int lo, int hi);
};

bool MergeSort::init(std::vector<int> &nums)
{
    if (!m_dataset.empty())
    {
        m_dataset.clear();
    }
    m_dataset.assign(nums.begin(), nums.end());
    return true;
}

void MergeSort::sort()
{
    int size = m_dataset.size();
    std::vector<int> cacheNums(size);
    mergeSrt(m_dataset, cacheNums, 0, size - 1);
}

void MergeSort::print()
{
    std::cout << "========= SORTED ===============" << std::endl;
    for (int i = 0; i < m_dataset.size(); i++)
    {
        std::cout << m_dataset.at(i) << '\t';
    }

    cout << endl;
}

void MergeSort::merge(std::vector<int> &nums, std::vector<int> &cacheNums, int lo, int mi, int hi)
{
    int lCount = lo;
    int rCount = mi + 1;
    int count = lo;

    while (lCount <= mi && rCount <= hi)
    {
        if (nums[lCount] < nums[rCount])
        {
            cacheNums[count++] = nums[lCount++];
        }
        else
        {
            cacheNums[count++] = nums[rCount++];
        }
    }

    while (lCount <= mi)
    {
        cacheNums[count++] = nums[lCount++];
    }

    while (rCount <= hi)
    {
        cacheNums[count++] = nums[rCount++];
    }

    for (int i = lo; i <= hi; i++)
    {
        nums[i] = cacheNums[i];
    }
}

void MergeSort::mergeSrt(std::vector<int> &nums, std::vector<int> &cacheNums, int lo, int hi)
{
    if (hi <= lo)
        return;
    int mi = lo + (hi - lo) / 2;
    mergeSrt(nums, cacheNums, lo, mi);
    mergeSrt(nums, cacheNums, mi + 1, hi);
    merge(nums, cacheNums, lo, mi, hi);
}

int main()
{
    std::vector<int> nums = {10, 2, 6, 4, 8, 1, 9, 5, 3, 7};
    std::vector<int> nums2 = {32, 98, 76, 45, 63, 54, 77, 10, 2, 6, 4, 8, 1, 9, 5, 3, 7};
    MergeSort ms(nums);
    ms.sort();
    ms.print();

    ms.init(nums2);
    ms.sort();
    ms.print();

    return 0;
}