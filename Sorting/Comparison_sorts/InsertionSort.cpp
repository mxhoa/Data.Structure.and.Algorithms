#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

template<class T> 
class InsertionSort
{
public:
    static T asending(T *num1, T *num2);
    static T desending(T *num1, T *num2);

public:
    InsertionSort();
    InsertionSort(T nums[], T size);
    InsertionSort(std::vector<T> nums);
    ~InsertionSort();

public:
    void sort(T(*cmp)(T*, T*));
    void print(std::string str = "");
    void free();

private:
    T   **m_values;
    T   m_size;
};

template <class T>
InsertionSort<T>::InsertionSort()
{
    this->m_size = 0;
}

template <class T>
InsertionSort<T>::InsertionSort(T nums[], T size)
{
    m_size = size;
    m_values = new T* [size];
    for (T i = 0; i < size; i++)
    {
        m_values[i] = new T;
        *m_values[i] = nums[i];
    }
}

template <class T>
InsertionSort<T>::InsertionSort(std::vector<T> nums)
{
    m_size = nums.size();
    m_values = new T* [m_size];
    for (T i = 0; i < m_size; i++)
    {
        m_values[i] = new T;
        *m_values[i] = nums.at(i);
    }
}

template <class T>
InsertionSort<T>::~InsertionSort()
{
    free();
    this->m_size = 0;
}

template <class T>
void InsertionSort<T>::sort(T (*cmp)(T *, T *))
{
    for (T i = 1; i < m_size; i++)
    {
        T j = i - 1;
        T *value = m_values[i];
        while (j >= 0 && cmp(m_values[j], value) > 0)
        {
            m_values[j + 1] = m_values[j];
            j--;
        }
        m_values[j + 1] = value;
    }
}

template <class T>
void InsertionSort<T>::free()
{
    for (T i = 0; i < this->m_size; i++)
    {
        delete[] m_values[i];
    }
    delete[] m_values;
}

template <typename T>
void InsertionSort<T>::print(std::string str)
{
    std::cout << str;
    for (T i = 0; i < m_size; i++)
    {
        std::cout << *m_values[i] << "\t";
    }
    std::cout << std::endl;
}

template <class T>
T InsertionSort<T>::asending(T *num1, T *num2)
{
    return (*num1 - *num2);
}

template <class T>
T InsertionSort<T>::desending(T *num1, T *num2)
{
    return (*num2 - *num1);
}

/*
template<typename T> 
T asending(T *num1, T *num2)
{
    return (*num1 - *num2);
}

template <typename T>
T desending(T *num1, T *num2)
{
    return (*num2 - *num1);
}

template<typename T> void insertionSort(T **nums, T size, T(*cmp)(T*,T*))
{
    for (int i = 1; i < size; i++)
    {
        int j = i - 1;
        T *value = nums[i];
        while (j >= 0 && cmp(nums[j], value) > 0)
        {
            nums[j + 1] = nums[j];
            j--;
        }
        nums[j + 1] = value;
    }
}

int main()
{
    int arr[20] = {15, 8, 9, 1, 4, 11, 7, 12, 13, 6, 5, 3, 16, 2, 10, 14, 20, 25, 23, 21};
    int n = sizeof(arr) / sizeof(int);


    int **nums = (int **)calloc(n, sizeof(int *));

    for (int i = 0; i < n; i++)
    {
        nums[i] = (int*)calloc(1, sizeof(int));
        *nums[i] = arr[i];
    }

    insertionSort(nums, n, asending);
}
*/

int main()
{
    int arr[20] = {15, 8, 9, 1, 4, 11, 7, 12, 13, 6, 5, 3, 16, 2, 10, 14, 20, 25, 23, 21};
    int n = sizeof(arr) / sizeof(int);
    vector<int> vt = {15, 8, 9, 1, 4, 11, 7, 12, 13, 6, 5, 3, 16, 2, 10, 14, 20, 25, 23, 21};

    InsertionSort<int> ins1(arr, n);
    InsertionSort<int> ins2(vt);

    ins1.sort(InsertionSort<int>::asending);
    ins1.print("ASENDING:   ");

    ins2.sort(InsertionSort<int>::desending);
    ins2.print("DESENDING:  ");

    return 0;
}