*Time: 5 minutes*
## Problem
Given an integer array `nums`, return `true` if any value appears **at least twice** in the array, and return `false` if every element is distinct.

**Example 1:**
**Input:** `nums = [1,2,3,1]`
**Output:** `true`
**Explanation:**
The element 1 occurs at the indices 0 and 3.

**Example 2:**
**Input:** `nums = [1,2,3,4]`
**Output:** `false`
**Explanation:**
All elements are distinct.

**Example 3:**
**Input:** `nums = [1,1,1,3,3,4,3,2,4,2]`
**Output:** `true`

**Constraints:**
- `1 <= nums.length <= 105`
- `-109 <= nums[i] <= 109`
## Solution
```C++
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        std::unordered_set<int> seen_nums = {};
        for (auto n : nums) {
            if (seen_nums.contains(n)) {
                return true;
            }
            seen_nums.insert(n);
        }
        return false;
    }
};
```

## Notes
Brute force compares each element to all other elements
- $O(n^2)$
Alternative solution is to sort array then iterate across checking for repeated elements
- $O((n \log n) + n) = O(n \log n)$
Hash set allows insertion and search in constant time. Iterate across array and add each element to a hash set. At each iteration, check if the element is already in the set.
- $O(n)$

