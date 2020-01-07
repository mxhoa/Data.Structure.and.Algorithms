#include <iostream>
#include <vector>

class TimSort
{
private:
    std::vector<int> m_nums;
    const int RUN_SIZE = 32;

public:
    TimSort(std::vector<int> &nums);
    void sort();
    void display(std::string msg = "");

private:
    void timSort(std::vector<int> &nums, int run_size);
    void mergeSort(std::vector<int> &nums, int lo, int mi, int hi);
    void insertionSort(std::vector<int> &nums, int lo, int hi);
};

TimSort::TimSort(std::vector<int> &nums) : m_nums(nums)
{
    std::cout << "Init :: num.size = " << nums.size() << std::endl;
}

void TimSort::insertionSort(std::vector<int> &nums, int lo, int hi)
{
    for (int i = lo + 1; i <= hi; i++)
    {
        int tmp = nums[i];
        int j = i - 1;
        while (nums[j] > tmp && j >= lo)
        {
            nums[j + 1] = nums[j];
            j--;
        }
        nums[j + 1] = tmp;
    }
}

void TimSort::mergeSort(std::vector<int> &nums, int lo, int mi, int hi)
{
    int l1 = mi - lo + 1;
    int l2 = hi - mi;
    int lo_part[l1];
    int hi_part[l2];

    // Store values of the low part
    for (int i = 0; i < l1; i++)
    {
        lo_part[i] = nums[lo + i];
    }

    // Store values of the high part
    for (int i = 0; i < l2; i++)
    {
        hi_part[i] = nums[mi + i + 1];
    }

    int i = 0;
    int j = 0;
    int k = lo;

    // Merge the two sorted array in larger sub array
    while (i < l1 && j < l2)
    {
        if (lo_part[i] <= hi_part[j])
        {
            nums[k] = lo_part[i++];
        }
        else
        {
            nums[k] = hi_part[j--];
        }
        k++;
    }

    // Copy the remaining elements of the low part
    while (i < l1)
    {
        nums[k++] = lo_part[i++];
    }

    // Copy the remaining elements of the high part
    while (j < l2)
    {
        nums[k++] = hi_part[j--];
    }
}

void TimSort::timSort(std::vector<int> &nums, int run_size)
{
    int len = nums.size();
    // Sort individual subarrays of size RUN
    for (int i = 0; i < len; i += run_size)
    {
        insertionSort(nums, i, std::min((i + run_size - 1), (len - 1)));
    }

    // Start merging from size
    for (int size = run_size; size < len; size = 2 * size)
    {
        for (int lo = 0; lo < len; lo += 2 * size)
        {
            int mi = lo + size - 1;
            int hi = std::min((lo + 2 * size - 1), (len - 1));

            mergeSort(nums, lo, mi, hi);
        }
    }
}

void TimSort::sort()
{
    timSort(m_nums, RUN_SIZE);
}

void TimSort::display(std::string msg)
{
    std::cout << "------ DISPLAY :: " << msg << " --------\n";
    for (int i : m_nums)
    {
        std::cout << i << " ";
    }
    std::cout << '\n';
}

int main()
{
    std::vector<int> nums = {12, 1, 20, 2, 3, 123, 54, 332, 90, 17, 21, 56};
    TimSort ts(nums);
    ts.sort();
    ts.display("SORTED");

    return 0;
}