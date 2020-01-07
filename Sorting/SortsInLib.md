# The sorting algorithms used in Libraries

_[Refer]_ - [geeksforgeeks.org](https://www.geeksforgeeks.org)

Ever wondered how sort() function we use in C++/Java or sorted() in Python work internally?

Here is a list of all the inbuilt sorting algorithms of different programming languages and the algorithm they use internally.


## 1. ==[C]== - qsort() – [Quicksort](https://en.wikipedia.org/wiki/Quicksort)
- Time Complexity:
    |  Best Case    |  Average Case |   Worse Case  |
    | :-----------: | :-----------: | :-----------: |
    |  $O(NlogN)$   |  $O(NlogN)$   |   $O(N^2)$    |

- Auxiliary Space : $O(log N)$
- Stable : Depends on the implementation of the comparator function
- Adaptive : No

## 2. ==[C++]== - sort() – [Introsort](https://www.geeksforgeeks.org/know-your-sorting-algorithm-set-2-introsort-cs-sorting-weapon/)
> Introsort is a hybrid of Quicksort, Heap Sort and Insertion Sort.
- Time Complexity:
    |  Best Case    |  Average Case |   Worse Case  |
    | :-----------: | :-----------: | :-----------: |
    |  $O(NlogN)$   |  $O(NlogN)$   |  $O(NlogN)$   |

- Auxiliary Space: $O(logN)$
- Stable: No
- Adaptive: No

## 3. ==[C++]== - stable_sort() – [Mergesort](https://en.wikipedia.org/wiki/Merge_sort)
- Time Complexity:
    |  Best Case    |  Average Case |   Worse Case  |
    | :-----------: | :-----------: | :-----------: |
    |  $O(NlogN)$   |  $O(NlogN)$   |  $O(NlogN)$   |

- Auxiliary Space: O(N)
- Stable: Yes
- Adaptive: Yes

## 4. ==[Java 6]== - Arrays.sort() – [Quicksort](https://en.wikipedia.org/wiki/Quicksort)
- Time Complexity:
    |  Best Case    |  Average Case |   Worse Case  |
    | :-----------: | :-----------: | :-----------: |
    |  $O(NlogN)$   |  $O(NlogN)$   |    $O(N^2)$   |

- Auxiliary Space- O(logN)
- Stable- Depends
- Adaptive- No

## 5. ==[Java 7]== - Arrays.sort() – [Timsort](https://en.wikipedia.org/wiki/Timsort) 
> Timsort is a hybrid of Mergesort and Insertion Sort.
- Time Complexity:
    |  Best Case    |  Average Case |   Worse Case  |
    | :-----------: | :-----------: | :-----------: |
    |     $O(N)$    |  $O(NlogN)$   |  $O(NlogN)$   |

- Auxiliary Space: O(N)
- Stable: Yes
- Adaptive: Yes

## 6. ==[Java]== - Collections.sort() – [Mergesort](https://en.wikipedia.org/wiki/Merge_sort)
- Time Complexity:
    |  Best Case    |  Average Case |   Worse Case  |
    | :-----------: | :-----------: | :-----------: |
    |  $O(NlogN)$   |  $O(NlogN)$   |  $O(NlogN)$   |

- Auxiliary Space: O(N)
- Stable: Yes
- Adaptive: Yes

## 7. ==[Python]== - sorted() – [Timsort](https://en.wikipedia.org/wiki/Timsort)
> Timsort is a hybrid of Mergesort and Insertion Sort.
- Time Complexity:
    |  Best Case    |  Average Case |   Worse Case  |
    | :-----------: | :-----------: | :-----------: |
    |     $O(N)$    |  $O(NlogN)$   |  $O(NlogN)$   |

- Auxiliary Space: O(N)
- Stable: Yes
- Adaptive: Yes

## 8. ==[Python]== - sort() – [Timsort](https://en.wikipedia.org/wiki/Timsort)
> Timsort is a hybrid of Mergesort and Insertion Sort.
- Time Complexity:
    |  Best Case    |  Average Case |   Worse Case  |
    | :-----------: | :-----------: | :-----------: |
    |     $O(N)$    |  $O(NlogN)$   |  $O(NlogN)$   |

- Auxiliary Space: O(N)
- Stable: Yes
- Adaptive: Yes

