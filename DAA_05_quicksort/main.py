"""
Comparing the performance of quick sort and randomized quick sort
The number of comparisons made by quick sort and randomized quick sort
are calculated and compared.

Quick sort:
- Select the rightmost element as pivot
- Partition the array such that all elements less than pivot are on the left
    and all elements greater than pivot are on the right
- Recursively sort the left and right subarrays

Randomized quick sort:
- Select an element randomly as pivot from the array
- Partition the array such that all elements less than pivot are on the left
    and all elements greater than pivot are on the right
- Recursively sort the left and right subarrays

reference: https://people.engr.tamu.edu/andreas-klappenecker/csce411-s14/csce411-random3.pdf
"""

import random

n1 = 0  # number of compariso   ns in quick sort
n2 = 0  # number of comparisons in randomized quick sort


def quick_sort_partition(arr, left, right):
    global n1
    # select the rightmost element as pivot
    pivot = arr[right]
    i = left - 1
    for j in range(left, right):
        if arr[j] < pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
        n1 += 1
    arr[i + 1], arr[right] = arr[right], arr[i + 1]
    return i + 1


def quick_sort(arr, left, right):
    if left < right:
        pivot = quick_sort_partition(arr, left, right)
        quick_sort(arr, left, pivot - 1)
        quick_sort(arr, pivot + 1, right)


def randomized_quick_sort_partition(arr, left, right):
    global n2
    # select an element randomly as pivot from arr[left..right]
    pivot_index = random.randint(left, right)
    pivot = arr[pivot_index]
    arr[pivot_index], arr[right] = arr[right], arr[pivot_index]
    i = left - 1
    for j in range(left, right):
        if arr[j] < pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
        n2 += 1
    arr[i + 1], arr[right] = arr[right], arr[i + 1]
    return i + 1


def randomized_quick_sort(arr, left, right):
    if left < right:
        pivot = randomized_quick_sort_partition(arr, left, right)
        randomized_quick_sort(arr, left, pivot - 1)
        randomized_quick_sort(arr, pivot + 1, right)


arr = [10, 7, 8, 9, 1, 5]
n = len(arr)
quick_sort(arr, 0, n - 1)
print(f"Sorted array is: {arr}")
print(f"Number of comparisons in quick sort: {n1}")

arr = [10, 7, 8, 9, 1, 5]
n = len(arr)
randomized_quick_sort(arr, 0, n - 1)
print(f"Sorted array is: {arr}")
print(f"Number of comparisons in randomized quick sort: {n2}")
