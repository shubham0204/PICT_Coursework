def selection_sort(nums: list[int]):
    for i in range(len(nums)):
        min_element = nums[i]
        min_element_index = i
        for j in range(i + 1, len(nums)):
            if nums[j] < min_element:
                min_element = nums[j]
                min_element_index = j
        nums[i], nums[min_element_index] = nums[min_element_index], nums[i]


nums = [2, 3, 1]
selection_sort(nums)
print(nums)
