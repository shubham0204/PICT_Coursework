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
$ ./a.out
*/

#include <iostream>
#include <omp.h>
#include <vector>

template <typename E> E parallelSum(const std::vector<E>& arr) {
    E sum = 0;
    #pragma omp parallel for reduction(+ : sum)
    for (size_t i = 0; i < arr.size(); i++) {
        sum += arr[i];
    }
    return sum;
}

template <typename E> E parallelMin(const std::vector<E>& arr) {
    E minElement = 0;
    #pragma omp parallel for reduction(min : minElement)
    for (size_t i = 0; i < arr.size(); i++) {
        if (minElement > arr[i]) {
            minElement = arr[i];
        }
    }
    return minElement;
}

template <typename E> E parallelMax(const std::vector<E>& arr) {
    E maxElement = 0;
    #pragma omp parallel for reduction(max : maxElement)
    for (size_t i = 0; i < arr.size(); i++) {
        if (maxElement < arr[i]) {
            maxElement = arr[i];
        }
    }
    return maxElement;
}

template <typename E> E parallelMean(const std::vector<E>& arr) {
    E sum = parallelSum(arr);
    return sum / arr.size();
}

int main(int argc, char* argv[]) {
    std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int sum = parallelSum(arr);
    std::cout << "sum is " << sum << '\n';
    int max = parallelMax(arr);
    std::cout << "max is " << max << '\n';
    int min = parallelMin(arr);
    std::cout << "min is " << min << '\n';
    int mean = parallelMean(arr);
    std::cout << "mean is " << mean << '\n';
    return 0;
}