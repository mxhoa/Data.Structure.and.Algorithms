#include <iostream>
#include <vector>

class BucketSort
{
private:
    std::vector<int> &m_dataset;
    int m_bucket_range = 0;
    int m_lower_range = 0;

public:
    BucketSort(std::vector<int> &nums, int lower_range, int upper_range);
    virtual void sort();
    void print();
};

BucketSort::BucketSort(std::vector<int> &nums, int lower_range, int upper_range) : m_dataset(nums)
{
    m_bucket_range = upper_range - lower_range;
    m_lower_range = lower_range;
}

void BucketSort::print()
{
    int size = m_dataset.size();
    for (auto a : m_dataset)
        std::cout << a << '\t';

    std::cout << '\n';
}

void BucketSort::sort()
{
    int size = m_dataset.size();
    std::vector<int> count(m_bucket_range, 0);

    for (auto value : m_dataset)
    {
        count[value - m_lower_range]++;
    }

    int j = 0;
    for (int i = 0; i < m_bucket_range; i++)
    {
        while (count[i] > 0)
        {
            m_dataset[j++] = i + m_lower_range;
            count[i]--;
        }
    }
}

int main()
{
    std::vector<int> data = {23, 24, 22, 21, 26, 25, 27, 28, 21, 21, 32, 29, 45, 41, 47, 49, 33, 39};

    BucketSort *m = new BucketSort(data, 20, 50);
    m->sort();
    m->print();

    return 0;
}