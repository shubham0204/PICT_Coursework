/*
Parallel BubbleSort implementation using OpenMP directives
@author shubham0204 (Shubham Panchal)
@date   17/04/2025

Usage:

1. Change the value of `TEST_ARR_SIZE` that represents the size of the array to be sorted.

2. Compile this code,

   g++ par_bubble_sort.cpp -fopenmp -o main

3. Use the `time` utility in Linux to measure the time taken by the executable to run,

   time ./main par
   time ./main seq

The differences in the `real` or wall-time should be significant.
*/
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <omp.h>
#include <utility>
#include <vector>

#define TEST_ARR_SIZE 100000

void sequentialBubbleSort(std::vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr.size() - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
};

void parallelBubbleSort(std::vector<int>& arr) {
    bool sorted = false;
    while (!sorted) {
        bool localSorted = true;
        // spawn a new thread for each iteration of the loop
        #pragma omp parallel for reduction(&&: localSorted)
        for (int i = 0; i < arr.size(); i += 2) {
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                localSorted = false;
            }
        }
        #pragma omp parallel for reduction(&&: localSorted)
        for (int i = 1; i < arr.size(); i += 2) {
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                localSorted = false;
            }
        }
        sorted = localSorted;
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
        std::cout << "executing sequential bubble-sort ..." << '\n';
        sequentialBubbleSort(nums);
    } else {
        std::cout << "executing parallel bubble-sort ..." << '\n';
        parallelBubbleSort(nums);
    }
    return 0;
}