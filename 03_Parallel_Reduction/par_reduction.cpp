/**

Parallel reduction for sum/min/max/mean operations in C++ using OpenMP
@author shubham0204 (Shubham Panchal)
@date   05/02/2024

Explanation:

```
template <typename T>
T parallelSum(std::vector<T>& arr) {
    T sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (size_t i = 0; i < arr.size(); i++) {
        sum += arr[i];
    }
    return sum;
}
```
For each iteration of the loop is assigned to one of the threads in the team created
by `omp parallel for`. The `reduction(+:sum)` clause tells the compiler to create a
private copy of `sum` for each thread and combine the results at the end of the loop
using the `+` operator.

Compilation:
$ g++ par_reduction.cpp -fopenmp
$ time ./a.out par
$ time ./a.out seq
*/

#include <algorithm>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <omp.h>
#include <vector>

#define N_CPU_CORES 4
#define TEST_ARR_SIZE 10000000
#define LOG(str1, str2) std::cout << str1 << ' ' << str2 << '\n'

int sequentialSum(const std::vector<int>& arr) {
    int sum = 0;
    for (size_t i = 0; i < arr.size(); i++) {
        sum += arr[i];
    }
    return sum;
}

int sequentialMax(const std::vector<int>& arr) {
    int max = INT_MIN;
    for (size_t i = 0; i < arr.size(); i++) {
        max = std::max(max, arr[i]);
    }
    return max;
}

int sequentialMin(const std::vector<int>& arr) {
    int min = INT_MAX;
    for (size_t i = 0; i < arr.size(); i++) {
        min = std::min(min, arr[i]);
    }
    return min;
}

int sequentialMean(const std::vector<int>& arr) { return sequentialSum(arr) / arr.size(); }

int parallelSum(const std::vector<int>& arr) {
    int sum = 0;
    #pragma omp parallel for reduction(+ : sum)
    for (size_t i = 0; i < arr.size(); i++) {
        sum += arr[i];
    }
    return sum;
}

int parallelMin(const std::vector<int>& arr) {
    int minElement = 0;
    #pragma omp parallel for reduction(min : minElement)
    for (size_t i = 0; i < arr.size(); i++) {
        if (minElement > arr[i]) {
            minElement = arr[i];
        }
    }
    return minElement;
}

int parallelMax(const std::vector<int>& arr) {
    int maxElement = 0;
    #pragma omp parallel for reduction(max : maxElement)
    for (size_t i = 0; i < arr.size(); i++) {
        if (maxElement < arr[i]) {
            maxElement = arr[i];
        }
    }
    return maxElement;
}

int parallelMean(const std::vector<int>& arr) {
    int sum = parallelSum(arr);
    return sum / arr.size();
}

std::vector<int> generateRandomArray(long size) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100 + 1;
    }
    return arr;
};

int main(int argc, char* argv[]) {
    srand(time(nullptr));
    omp_set_num_threads(N_CPU_CORES);

    LOG("N_CPU_CORES", N_CPU_CORES);
    LOG("TEST_ARR_SIZE", TEST_ARR_SIZE);
    std::vector<int> arr = generateRandomArray(TEST_ARR_SIZE);

    if (std::string(argv[1]) == "seq") {
        std::cout << "executing sequential operations ..." << '\n';
        int sum = sequentialSum(arr);
        int max = sequentialMax(arr);
        int min = sequentialMin(arr);
        int mean = sequentialMean(arr);
        LOG("sum", sum);
        LOG("max", max);
        LOG("min", min);
        LOG("mean", mean);
    } else {
        std::cout << "executing parallel operations ..." << '\n';
        int sum = parallelSum(arr);
        int max = parallelMax(arr);
        int min = parallelMin(arr);
        int mean = parallelMean(arr);
        LOG("sum", sum);
        LOG("max", max);
        LOG("min", min);
        LOG("mean", mean);
    }

    return 0;
}