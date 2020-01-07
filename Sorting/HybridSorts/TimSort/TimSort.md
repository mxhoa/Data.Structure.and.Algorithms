# Tim-Sort 
Tim-sort is a sorting algorithm dereved from insertion sort and merge sort. It was designed to perform in an optimal way on different kind of real world data. It is an adaptive sorting algorithm which needs O(n log n) comparisons to sort an array of n elements. It was designed and implemented by Tim Peters in 2002 in python programming language. It has been python's standard sorting algorithm since version 2.3.

## Technique 
Consider an array of n elements which needs to be sorted. In Tim sort, the array is divided into several parts where each of them is called a Run. These Runs are sorted by using insertion sort one by one and then the sorted runs get combined using a combine function. The idea of Tim sort is originated from the fact that, insertion sort works more optimal on the short lists rather than working on the larger lists.


## Complexity
   
|    Complexity   |  Best Case    |  Average Case |   Worse Case  |
| :-------------: | :-----------: | :-----------: | :-----------: |
| Time Complexity |    $O(N)$     |  $O(NlogN)$   |  $O(NlogN)$   |
| Space Complexity|               |               |     $O(N)$    |



## Steps
1. Divide the array into the number of blocks known as run.
2. Consider size of run either 32 or 64.
3. Sort the individual elements of every run one by one using insertion sort.
4. Merge the sorted runs one by one using merge function of merge sort.
5. Double the size of merged sub-arrays after every iteration.



