*Time: mock interview 13/01, had non-optimal solution in 20 mins*

## Problem
Given an integer array `nums` of length `n` where all the integers of `nums` are in the range `[1, n]` and each integer appears **at most** **twice**, return _an array of all the integers that appears **twice**_.

You must write an algorithm that runs in `O(n)` time and uses only _constant_ auxiliary space, excluding the space needed to store the output

**Example 1:**
**Input:** `nums = [4,3,2,7,8,2,3,1]`
**Output:** `[2,3]`

**Example 2:**
**Input:** `nums = [1,1,2]`
**Output:** `[1]`

**Example 3:**
**Input:** `nums = [1]`
**Output:** `[]`

**Constraints:**
- `n == nums.length`
- `1 <= n <= 10^5`
- `1 <= nums[i] <= n`
- Each element in `nums` appears **once** or **twice**.

## Solution
```cpp
class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> duplicates;
        for (int i = 0; i < nums.size(); i++) {
            int val = abs(nums[i]);
            if (nums[val - 1] < 0) {
                duplicates.push_back(val);
            } else {
                nums[val - 1] *= -1;
            }
        }
        return duplicates;
    }
};
```

## Notes
Important learning: you can modify the input array to store information
- use the provided constraints to develop a method that preserves original array

In this problem:
- every value is positive
- every value is between `1` and `n`
This combination allows for the following:
- *every value is positive* -> can flip a value to negative to indicate boolean information
- *every value is between `1` and `n`* -> can store information about a value by using it as an index

**This gives the following algorithm:**
- iterate over `nums` with `i`
- for `value` at `i`, check `nums[value - 1]` (0-based indexing)*
	- if positive, flip it to negative and continue
	- if negative, we have seen this value before, so add `value` to `results` array and continue

*\*we will need to index to `abs(value)`*



