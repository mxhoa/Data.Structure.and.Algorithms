# Standard Template Library 

## I - Container library 

The Containers library is a generic collection of class templates and algorithms that allow programmers to easily implememmt common data structures like queues, lists and stacks. There are three classes of containers - sequence containers, associate containers, and unordered associative containers -- each of which is designed to support a different set of operations.

The container manages the storage space that is allocated for  its elements and provides member functions to access them, either directly or through iterators (objecs with properties similar to pointers).

Most containers have at least several member functions in common, and share functionalities. Which container is the best for the particular application depends not only on the offered functionality, but also on its efficiency for diferent workloads.

###  1. Sequence containers
Sequence containers implement data structures which can be accessed sequentially.

| No  |       Name          |         Description             |
|-----|:-------------------:|:--------------------------------|
| 1   |   **array**         | static contiguous array         |
| 2   |   **vector**        | dynamic contiguous array        |
| 3   |   **deque**         | double-ended queue              |
| 4   |   **forward_list**  |  single-linked list             |
| 5   |   **list**          | doubly-linked list              |


### 2. Associative containers
Associative containers implement sorted data structures that can be quickly searched (O(logN) complexity).

| No  |       Name          |             Description                                         |
|-----|:-------------------:|:----------------------------------------------------------------|
| 1   |   **set**           | collection of  unique keys, sorted by keys                      |
| 2   |   **map**           | collection of key-value pairs, sorted by keys, keys are unique  |
| 3   |   **multiset**      | collection of keys, sorted by keys                              |
| 4   |   **multimap**      | collection of key-value pairs, sorted by keys                   |

### 3. Unordered associative containers
Unordered associative containers implement unsorted (hashed) data structures that can be quickly searched (O(1) amortized, O(N) worst-case complexity).

| No  |       Name                    |             Description                                         |
|-----|:-----------------------------:|:----------------------------------------------------------------|
| 1   |   **unordered_set**           | collection of unique keys, hashed by keys                       |
| 2   |   **unordered_map**           | collection of key-value pairs, hashed by keys, keys are unique  |
| 3   |   **unordered_multiset**      | collection of keys, hashed by keys                              |
| 4   |   **unordered_multimap**      | collection of key-value pairs, hashed by keys.                  |


### 4. Container adaptors
Container adaptors provide a different interface for sequential containers.

| No  |       Name                    |             Description                                         |
|-----|:-----------------------------:|:----------------------------------------------------------------|
| 1   |   **stack**                   | collection of unique keys, hashed by keys                       |
| 2   |   **queue**                   | collection of key-value pairs, hashed by keys, keys are unique  |
| 3   |   **priority_queue**          | collection of keys, hashed by keys                              |

## II - Algorithms 

## III - Iterator 

## IV - Numeric 


