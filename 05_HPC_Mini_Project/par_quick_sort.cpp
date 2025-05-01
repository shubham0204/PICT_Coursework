/*
Parallel QuickSort implementation using OpenMP directives
@author shubham0204 (Shubham Panchal)
@date   14/04/2025

Usage:

1. Set `N_CPU_CORES` to the number of available CPU cores. Use `lscpu` in the terminal
   to get the number of CPU cores quickly on most Linux distros. Also, you may change the value
   of `TEST_ARR_SIZE` that represents the size of the array to be sorted.

2. Compile this code,

   g++ par_quick_sort.cpp -fopenmp -o main

3. Use the `time` utility in Linux to measure the time taken by the executable to run,

   time ./main par
   time ./main seq

The differences in the `real` or wall-time should be significant.
*/
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <omp.h>
#include <string>
#include <vector>

#define N_CPU_CORES 4
#define TEST_ARR_SIZE 1000000

int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void sequentialQuickSortImpl(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int partitionIndex = partition(arr, low, high);
        sequentialQuickSortImpl(arr, low, partitionIndex - 1);
        sequentialQuickSortImpl(arr, partitionIndex + 1, high);
    }
};

void sequentialQuickSort(std::vector<int>& arr) { sequentialQuickSortImpl(arr, 0, arr.size() - 1); }

void parallelQuickSortImpl(std::vector<int>& arr, int low, int high, int depth = 0) {
    if (low < high) {
        int partitionIndex = partition(arr, low, high);

        if (depth < N_CPU_CORES) {
            // The task pragma can be used to explicitly define a task.
            // Use the task pragma when you want to identify a block of code to be
            // executed in parallel with the code outside the task region. The task
            // pragma can be useful for parallelizing irregular algorithms such as
            // pointer chasing or recursive algorithms.
#pragma omp task
            { parallelQuickSortImpl(arr, low, partitionIndex - 1, depth + 1); }
#pragma omp task
            { parallelQuickSortImpl(arr, partitionIndex + 1, high, depth + 1); }
        } else {
            parallelQuickSortImpl(arr, low, partitionIndex - 1, depth + 1);
            parallelQuickSortImpl(arr, partitionIndex + 1, high, depth + 1);
        }
    }
}

void parallelQuickSort(std::vector<int>& arr) {
// The omp parallel directive explicitly instructs the compiler to parallelize
// the chosen block of code.
#pragma omp parallel
    {
// The omp single directive identifies a section of code that must be run by a
// single available thread.
#pragma omp single nowait
        { parallelQuickSortImpl(arr, 0, arr.size() - 1); }
    }
}

std::vector<int> generateRandomArray(int size) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100 + 1;
    }
    return arr;
};

int main(int argc, char* argv[]) {
    srand(time(nullptr));
    std::vector<int> nums = generateRandomArray(TEST_ARR_SIZE);
    if (std::string(argv[1]) == "seq") {
        std::cout << "executing sequential quicksort ..." << '\n';
        sequentialQuickSort(nums);
    } else {
        std::cout << "executing parallel quicksort ..." << '\n';
        parallelQuickSort(nums);
    }
    return 0;
}