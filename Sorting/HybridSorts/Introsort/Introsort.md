# Introsort
----
_[Refer]_
- [Introsort or Introspective sort](https://www.geeksforgeeks.org/introsort-or-introspective-sort/)
- [Introsort - C++’s Sorting Weapon](https://www.geeksforgeeks.org/know-your-sorting-algorithm-set-2-introsort-cs-sorting-weapon/)

## 1. What is Introsort?
Simply putting, it is the best sorting algorithm around. It is a hybrid sorting algorithm, which means that it uses more than one sorting algorithms as a routine.

## 2. Which standard sorting algorithms are used in Introsort?
Introsort being a hybrid sorting algorithm uses three sorting algorithm to minimise the running time: [Quicksort](https://en.wikipedia.org/wiki/Quicksort), [Heapsort](https://en.wikipedia.org/wiki/Heapsort) and [Insertion sort](https://en.wikipedia.org/wiki/Insertion_sort)

## 3. How does it work?
Introsort begins with Quicksort and if the recursion depth goes more than a particular limit it switches to Heapsort to avoid Quicksort's worse case $O(N^2)$ time complexity. It also uses Insertion sort when the number of elements to sort is quite less. 
So first it create a partition. Three cases arises from here:
* If the partition size is such that there is a possibility to exceed the maximum depth limit then the Introsort switch to Heapsort. We define the maximum depth limit as $2*log(N)$
* If the partition size is too small then Quicksort decays to Insertion sort. We define this cutoff as 16 (due to research). So if the partition size is less than 16 then we will do insertion sort.
* If the partition size is under the limit and not too small (i.e - between 16 and $2*log(N)$, then it performs a simple quicksort.


## 4. Why is it better than simple Quicksort or Why the need of Introsort?
Since Quicksort can have a worse case $O(N^2)$ time complexity and it alse increases the recursion stack space ($O(log N)$ if tail recursion applied), so to avoid all these, we need to switch the algorithm from Quicksort to another if there is a chance of worse case. So Introsort solves this problem by switching to Heapsort.

Also due to larger constant factor, Quicksort can perform even worse than $O(N^2)$ sorting algorithm when N is small enough. So it switches to Insertion soort to decrease the running time of sorting.

Also if a bad pivot-selection is done then the quicksort does no better than the bubble-sort.

## 5. Why is Insertion Sort used (and not Bubble Sort, etc) ?
Insertion sort offers following advantages.
* It is a known and established fact that insertion sort is the most optimal comparision-based sorting algorithm for small arrays.
* It has a good locality of reference.
* It is an adaptive sorting algorithm, i.e- it outperforms all the other algorithms if the array elements are partially sorted.

## 6. Why is Heapsort used (and not Mergesort, etc)? 
This is solely because of memory requirements. Merge sort require $O(N)$ space whereas Heapsort is an in-place $O(1)$ space algorithm.

## 7. Why is Heapsort not used in place of Quicksort when the partition size is under the limit?
This question is same as why Quicksort generally outperforms Heapsort?
The answer is, although Heapsort also begin $O(NlogN)$ in average as well as worse case and $O(1)$ space also, we still don't use it when partition size is under the limit becase the extra hidden constant factor in Heapsort is quite larger than that of Quicksort.

## 8. Why is cut-off 16 for  switching from Quicksort to Insertion sort, and $2*log(N)$ for swithching from Quicksort to Heapsort?
These values are chosen empirically as an approximate becase of various tests and researches conducted.

