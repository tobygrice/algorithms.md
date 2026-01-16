*Time: 9 minutes*

## Problem
Given an array `nums` of size `n`, return _the majority element_.

The majority element is the element that appears more than `⌊n / 2⌋` times. You may assume that the majority element always exists in the array.

**Example 1:**
**Input:** `nums = [3,2,3]`
**Output:** `3`

**Example 2:**
**Input:** `nums = [2,2,1,1,1,2,2]`
**Output:** `2`

**Constraints:**
- `n == nums.length`
- `1 <= n <= 5 * 10^4`
- `-10^9 <= nums[i] <= 10^9`
- The input is generated such that a majority element will exist in the array.

**Follow-up:** Could you solve the problem in linear time and in `O(1)` space?

## Solution
Non-optimal, $O(n)$ || $O(n)$
```C++
// O(n) time
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> counts;
        for (int n : nums) {
            counts[n]++;
        }
        int majority = nums[0];
        for (int n : nums) {
            if (counts[majority] < counts[n]) {
                majority = n;
            }
        }
        return majority;
    }
};
// O(n) space
```
Optimal, $O(n)$ || $O(1)$
```C++
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int candidate = nums[0];
        int count = 1;
        
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == candidate) {
                count++;
            } else {
                count--;
            }
            
            if (count == 0) {
                candidate = nums[i];
                count = 1;
            }
        }
        return candidate;
    }
};
```

## Notes
Moore's voting algorithm:
1. Initialize two variables: `count` and `candidate`. Set `count` to 0 and `candidate` to an arbitrary value.
2. Iterate through the array `nums`:  
	- If `count` is 0, assign the current element as the new `candidate` and increment `count` by 1.
	- If the current element is the same as the `candidate`, increment `count` by 1.  
	- If the current element is different from the `candidate`, decrement `count` by 1.
3. After the iteration, the `candidate` variable will hold the majority element.

If there is a majority element in an array, it will always remain in the lead, even after encountering other elements.