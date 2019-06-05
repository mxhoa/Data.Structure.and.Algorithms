#include <iostream>
#include <pthread.h>
#include <time.h>

#define     INPUT_MAX       20  // Number of elements in array
#define     THREAD_MAX      4   // Number of threads

using namespace std;


// array of size INPUT_MAX
int dataset[INPUT_MAX];
int threadCount    = 0;

void merge(int low, int mid, int high)
{
    int *leftPart   = new int[mid - low + 1];
    int *rightPart  = new int[high - mid];

    // leftPartSize is size of left part 
    // rightPartSize is size of right part 
    int leftPartSize    = mid - low + 1;
    int rightPartSize   = high - mid;
    int lRunner, rRunner;

    // Storing values in left part
    for (lRunner = 0; lRunner < leftPartSize; lRunner++)
    {
        leftPart[lRunner] = dataset[lRunner + low];
    }

    // Storing values in right part
    for (rRunner = 0; rRunner < rightPartSize; rRunner++)
    {
        rightPart[rRunner] = dataset[rRunner + mid + 1];
    }

    int k = low;
    lRunner = rRunner = 0;

    // Merge left and right in ascending order
    while (lRunner < leftPartSize && rRunner < rightPartSize)
    {
        if (leftPart[lRunner] <= rightPart[rRunner])
        {
            dataset[k++] = leftPart[lRunner++];
        }
        else 
        {
            dataset[k++] = rightPart[rRunner++];
        }
    }


    // Insert remaining values from left
    while (lRunner < leftPartSize)
    {
        dataset[k++] = leftPart[lRunner++];
    }

    // Insert remaining values from right
    while (rRunner < rightPartSize)
    {
        dataset[k++] = rightPart[rRunner++];
    }
}

void merge_sort(int low, int high)
{
    // Calculating mid point of array
    int mid = low + (high - low) / 2;
    if (low < high)
    {
        // Calling first half
        merge_sort(low, mid);

        // Calling second half
        merge_sort(mid + 1, high);

        // Merging the two halves
        merge(low, mid, high);
    }
}

// Thread function for multi-threading
void* merge_sort(void* arg)
{
    // WHich part out of 4 parts
    int thread_part = threadCount++;

    // Calculating low and high
    int low     = thread_part * (INPUT_MAX / 4);
    int high    = (thread_part + 1) * (INPUT_MAX / 4) - 1;

    // Evaluating mid point 
    int mid = low + (high - low) / 2;
    if (low < high) 
    {
        merge_sort(low, mid);
        merge_sort(mid + 1, high);
        merge(low, mid, high);
    }
}

// Client 
int main()
{
    // Generating random values in array
    for (int i = 0; i < INPUT_MAX; i++)
    {
        dataset[i] = rand() % 1000;
    }

    // t1 and t2 for check time 
    clock_t t1, t2;

    t1 = clock();
    pthread_t threads[THREAD_MAX];
    

    // Creating 4 threads
    for (int i = 0; i < THREAD_MAX; i++)
    {
        pthread_create(&threads[i], NULL, merge_sort, (void*)NULL);
    }

    // Joining all 4 threads
    for (int i = 0; i < THREAD_MAX; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // Merging the ginal 4 parts
    // 0N/4 ---> 1N/4 ---> 2N/4 ---> 3N/4 ---> 4N/4
    //  |...................|                     |
    //  |                   |.....................|
    //  |.........................................|


    /********  0N/4 ---> 1N/4 ---> 2N/4 ***********/
    merge(0, INPUT_MAX / 4 - 1, INPUT_MAX / 2 - 1);

    /********  2N/4 ---> 3N/4 ---> 4N/4 ***********/
    merge(INPUT_MAX / 2, 3 * INPUT_MAX / 4 - 1, INPUT_MAX - 1);

    /********  0N/4 ---> 2N/4 ---> 4N/4 ***********/
    merge(0, INPUT_MAX / 2 - 1, INPUT_MAX - 1);
    
    t2 = clock();

    // Displaying sorted array
    std::cout << "Sorted array: " << std::endl;
    for (int i = 0; i < INPUT_MAX; i++)
    {
        cout << dataset[i] << " ";
    }

    // Time taken by merge sort in second 
    std::cout << "Time taken: " << (t2 - t1) / (double)CLOCKS_PER_SEC << std::endl;

    return 0;
}