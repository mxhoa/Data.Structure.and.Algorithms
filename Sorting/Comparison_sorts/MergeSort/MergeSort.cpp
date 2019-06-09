#include <iostream>
#include <vector>

class MergeSort
{
private:
    std::vector<int> &m_dataset;

private:
    void merge(std::vector<int> &arr, std::vector<int> &tempArray, int lowerIndex, int middleIndex, int upperIndex);
    void mergeSrt(std::vector<int> &arr, std::vector<int> &tempArray, int lowerIndex, int upperIndex);

public:
    MergeSort(std::vector<int> &data);
    virtual void sort();
};

MergeSort::MergeSort(std::vector<int> &data) : m_dataset(data) {}

void MergeSort::sort() 
{
    int size = m_dataset.size();
    std::vector<int> tempArray(size);
    mergeSrt(m_dataset, tempArray, 0, size - 1);
}

void MergeSort::mergeSrt(std::vector<int> &arr, std::vector<int> &tempArray, int lowerIndex, int upperIndex)
{
    if (lowerIndex >= upperIndex)
    {
        return;
    }

    int middeIndex = lowerIndex + (upperIndex - lowerIndex) / 2;
    mergeSrt(arr, tempArray, lowerIndex, middeIndex);
    mergeSrt(arr, tempArray, middeIndex + 1, upperIndex);
    merge(arr, tempArray, lowerIndex, middeIndex, upperIndex);
}


void MergeSort::merge(std::vector<int> &arr, std::vector<int> &tempArray, int lowerIndex, int middleIndex, int upperIndex)
{
    int lowerStart  = lowerIndex;
    int lowerStop   = middleIndex;
    int upperStart  = middleIndex + 1;
    int upperStop   = upperIndex;

    int count       = lowerIndex;

    while (lowerStart <= lowerStop && upperStart <= upperStop)
    {
        if (arr[lowerStart] < arr[upperStart])
        {
            tempArray[count++] = arr[lowerStart++];
        }
        else 
        {
            tempArray[count++] = arr[upperStart++];
        }
    }

    while (lowerStart <= lowerStop)
    {
        tempArray[count++] = arr[lowerStart++];
    }

    while(upperStart <= upperStop)
    {
        tempArray[count++] = arr[upperStart++];
    }

    for (int i = lowerIndex; i <= upperIndex; i++)
    {
        arr[i]= tempArray[i];
    }
}

int main()
{
    std::vector<int> nums = {10,2,6,4,8,1,9,5,3,7};
    MergeSort ms(nums);
    ms.sort();

    for (int i = 0; i < nums.size(); i++)
    {
        std::cout << nums.at(i) << '\t';
    }

    return 0;
}