#include <iostream>
#include <queue>
#include <vector>
#include <functional>

/**
 * @brief A priority queue is a container adaptor that provides constant time look up 
 * of the  largest (by default) element, at the expense of logarithmic insertion and extraction.
 * 
 * A user-provided Compare can be supplied to change the ordering, e.g using std::greater<T> would
 * cause the smallest element to appear as the top().
 * 
 * Working with a priority_queue is similar to managing a heap in some random access container,
 * with the benefit of not being able to accidentally invalidate the heap.
 * 
 * *******************************************************************************************
 *   template <
 *       class T,
 *       class Container = std::vector<T>,
 *       class Compare = std::less<typename Container::value_type>
 *   > class priority_queue;
 * *******************************************************************************************
 * 
 */

#define BREAK_LINE_MSG(msg) std::cout << "_________[" << msg << "]_________\n"

template <typename T> void print_vector(T &v)
{
    std::cout << '\t';
    for (auto i : v)
        std::cout << i << " ";
    std::cout << '\n';
};

template<typename T> void print_queue(T& q) 
{
    std::cout << '\t';
    while (!q.empty()) 
    {
        std::cout << q.top() << " ";
        q.pop();
    }

    std::cout << '\n';
};

int main()
{
    std::vector<int> nums = {1, 8, 5, 6, 3, 4, 0, 9, 7, 2};

    BREAK_LINE_MSG("NUMBERS");
    print_vector(nums);

    BREAK_LINE_MSG("DEFAULT");
    std::priority_queue<int> pq;
    for (int n : nums) 
        pq.push(n);
    print_queue(pq);

    BREAK_LINE_MSG("COMPARISION :: LESS");
    std::priority_queue<int, std::vector<int>, std::less<int>> pq2;
    for (int n : nums) 
        pq2.push(n);
    print_queue(pq2);

    BREAK_LINE_MSG("COMPARISION :: GREATER");
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq3;
    for (int n : nums)
        pq3.push(n);
    print_queue(pq3);

    BREAK_LINE_MSG("COMPARISION :: LAMBDA");
    // Using lambda to compare elements
    auto cmp = [](int left, int  right) { return (left ^ 1) < (right ^ 1); };
    std::priority_queue<int, std::vector<int>, decltype(cmp)> pq4(cmp);
    for (int n : nums) 
        pq4.push(n);
    print_queue(pq4);

    return 0;
}