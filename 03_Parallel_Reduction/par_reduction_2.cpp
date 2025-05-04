/*
Parallel reduction for sum/min/max/mean operations in C++ using OpenMP
@author shubham0204 (Shubham Panchal)
@date   04/05/2024

Explanation:

```
int parallelSum(const std::vector<int>& arr) {
    int numPartitions = N_CPU_CORES;
    std::vector threadSums(numPartitions, 0);
    int partitionSize = arr.size() / numPartitions;
    #pragma omp parallel
    {
        int p = omp_get_thread_num();
        int threadSum = 0;
        for (size_t i = p * partitionSize; i < (p + 1) * partitionSize; i++) {
            threadSum += arr[i];
        }
        threadSums[p] = threadSum;
    }
    int sum = 0;
    for (size_t i = 0; i < numPartitions; i++) {
        sum += threadSums[i];
    }
    return sum;
}
```

We partition the array into N_CPU_CORES equal parts
and compute the sum of each partition on a separate thread.
The sum of the partition is stored in a threadSums vector.
Once all threads have completed their execution, we add up
all 'sums' from the threadSums vector (reduction) and return the final
sum of the entire array.

Compilation:
$ g++ par_reduction.cpp -fopenmp
$ time ./a.out par
$ time ./a.out seq
*/
#include <climits>
#include <cmath>
#include <cstdlib>
#include <omp.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <ctime>

#define TEST_ARRAY_SIZE 100000000
#define N_CPU_CORES 4
#define LOG(str1, str2) std::cout << str1 << ':' << str2 << '\n'

int sequentialSum(const std::vector<int>& arr) {
    int sum = 0;
    for (size_t i = 0; i < arr.size(); i++) {
        sum += arr[i];
    }
    return sum;
}

int parallelSum(const std::vector<int>& arr) {
    int numPartitions = N_CPU_CORES;
    std::vector threadSums(numPartitions, 0);
    int partitionSize = arr.size() / numPartitions;
    #pragma omp parallel
    {
        int p = omp_get_thread_num();
        int threadSum = 0;
        for (size_t i = p * partitionSize; i < (p + 1) * partitionSize; i++) {
            threadSum += arr[i];
        }
        threadSums[p] = threadSum;
    }
    int sum = 0;
    for (size_t i = 0; i < numPartitions; i++) {
        sum += threadSums[i];
    }
    return sum;
}

int sequentialMax(const std::vector<int> arr) {
    int max = INT_MIN;
    for (size_t i = 0; i < arr.size(); i++) {
        max = std::max(max, arr[i]);
    }
    return max;
}

int parallelMax(const std::vector<int> arr) {
    int numPartitions = N_CPU_CORES;
    int partitionSize = arr.size() / numPartitions;
    std::vector<int> threadResults(numPartitions, INT_MIN);
    #pragma omp parallel
    {
        int partitionIndex = omp_get_thread_num();
        int threadResult = INT_MIN;
        for (size_t i = partitionIndex * partitionSize; i < ((partitionIndex + 1) * partitionSize); i++) {
            threadResult = std::max(threadResult, arr[i]);
        }
        threadResults[partitionIndex] = threadResult;
    }
    int result = INT_MIN;
    for (size_t i = 0; i < numPartitions; i++) {
        result = std::max(result, threadResults[i]);
    }
    return result;
}

std::vector<int> generateRandomArray(int size) {
    std::vector<int> array(size);
    for (size_t i = 0; i < size; i++) {
        array[i] = rand() % 100 + 1;
    }
    return array;
}

int main(int argc, char* argv[]) {
    // set the seed for the random number generator
    srand(123);

    // set number of threads to be used by OpenMP
    // usually the number of cores present in the CPU
    omp_set_num_threads(N_CPU_CORES);

    std::vector<int> arr = generateRandomArray(TEST_ARRAY_SIZE);

    if (std::string(argv[1]) == "par") {
        LOG("using parallel operations", "");
        int sum = parallelSum(arr);
        int max = parallelMax(arr);
        LOG("sum", sum);
        LOG("max", max);
    } else if (std::string(argv[1]) == "seq") {
        LOG("using sequential operations", "");
        int sum = sequentialSum(arr);
        int max = sequentialMax(arr);
        LOG("sum", sum);
        LOG("max", max);
    }
    return 0;
}