#include <iostream>
#include <algorithm>
#include <vector>

class HeapSort
{
private:
    std::vector<int> &m_dataset;

private:
    void heapify(std::vector<int> &data, int n, int i);
    void sortUtil(std::vector<int> &data, int n);

public:
    HeapSort(std::vector<int> &data);
    void execute();
    void printList();
};

HeapSort::HeapSort(std::vector<int> &data) : m_dataset(data) {}

void HeapSort::heapify(std::vector<int> &data, int n, int i)
{
    // Find the largest among root, left child and right child
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && data[l] > data[largest])
        largest = l;
    if (r < n && data[r] > data[largest])
        largest = r;

    // Swap and continue heapifying if root is not largest
    if (largest != i)
    {
        std::swap(data[i], data[largest]);
        heapify(data, n, largest);
    }
}

void HeapSort::sortUtil(std::vector<int> &data, int n)
{
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(data, n, i);
    }

    // Heap sort
    for (int i = n - 1; i >= 0; i--)
    {
        std::swap(data[0], data[i]);

        // Heapify root element to get highest element at root again
        heapify(data, i, 0);
    }
}

void HeapSort::execute()
{
    int n = m_dataset.size();
    sortUtil(m_dataset, n);
}

void HeapSort::printList()
{
    for (auto i : m_dataset)
    {
        std::cout << i << '\t';
    }
    std::cout << "\n";
}

int main()
{
    std::vector<int> nums = {9, 4, 5, 1, 0, 4, 3, 8, 2, 6, 7};
    HeapSort *hs = new HeapSort(nums);
    hs->printList();
    hs->execute();
    hs->printList();

    return 0;
}