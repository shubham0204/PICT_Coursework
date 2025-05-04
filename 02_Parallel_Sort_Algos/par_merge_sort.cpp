/*
Parallel MergeSort implementation using OpenMP directives
@author shubham0204 (Shubham Panchal)
@date   17/04/2025

Usage:

1. Set `N_CPU_CORES` to the number of available CPU cores. Use `lscpu` in the terminal
   to get the number of CPU cores quickly on most Linux distros. Also, you may change the value
   of `TEST_ARR_SIZE` that represents the size of the array to be sorted.

2. Compile this code,

   g++ par_merge_sort.cpp -fopenmp -o main

3. Use the `time` utility in Linux to measure the time taken by the executable to run,

   time ./main par
   time ./main seq

The differences in the `real` or wall-time should be significant.
*/
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#define TEST_ARR_SIZE 100000
#define N_CPU_CORES 4

void merge(std::vector<int>& arr, int low, int mid, int high) {
    // create two arrays:
    // arr1 = arr[low:mid]
    // arr2 = arr[mid:high+1]
    int n1 = mid - low + 1;
    int n2 = high - mid;
    std::vector<int> arr1(n1);
    std::vector<int> arr2(n2);
    for (int i = 0; i < n1; i++) {
        arr1[i] = arr[low + i];
    }
    for (int i = 0; i < n2; i++) {
        arr2[i] = arr[mid + i + 1];
    }

    // merge two sorted arrays, arr1 and arr2
    int i = 0;
    int j = 0;
    int k = low;
    while (i < n1 && j < n2) {
        if (arr1[i] < arr2[j]) {
            arr[k] = arr1[i];
            i++;
        } else {
            arr[k] = arr2[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = arr1[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = arr2[j];
        j++;
        k++;
    }
}

void sequentialMergeSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        sequentialMergeSort(arr, low, mid);
        sequentialMergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

// merge sort with parallel recursion
// https://en.wikipedia.org/wiki/Merge_sort#Merge_sort_with_parallel_recursion
void parallelMergeSort(std::vector<int>& arr, int low, int high, int depth = 0) {
    if (low < high) {
        int mid = (low + high) / 2;
        if (depth < N_CPU_CORES) {
            #pragma omp parallel sections
            {
                #pragma omp section
                { parallelMergeSort(arr, low, mid, depth + 1); }
                #pragma omp section
                { parallelMergeSort(arr, mid + 1, high, depth + 1); }
            }
        } else {
            parallelMergeSort(arr, low, mid, depth + 1);
            parallelMergeSort(arr, mid + 1, high, depth + 1);
        }
        merge(arr, low, mid, high);
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
    srand(123);
    std::vector<int> nums = generateRandomArray(TEST_ARR_SIZE);
    if (std::string(argv[1]) == "seq") {
        std::cout << "executing sequential merge-sort ..." << '\n';
        sequentialMergeSort(nums, 0, nums.size());
    } else {
        std::cout << "executing parallel merge-sort ..." << '\n';
        parallelMergeSort(nums, 0, nums.size());
    }
    return 0;
}