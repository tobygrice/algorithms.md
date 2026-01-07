*Asked in mock interview 06/01, failed*

## Problem
Given an integer array `nums`, move all `0`'s to the end of it while maintaining the relative order of the non-zero elements.

**Note** that you must do this in-place without making a copy of the array.

**Example 1:**
**Input:** `nums = [0,1,0,3,12]`
**Output:** `[1,3,12,0,0]`

**Example 2:**
**Input:** `nums = [0]`
**Output:** `[0]`

**Constraints:**
- `1 <= nums.length <= 10^4`
- `-2^31 <= nums[i] <= 2^31 - 1`

**Follow up:** Could you minimize the total number of operations done?

## Solution
```C++
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        for (int l_ptr = 0, r_ptr=0; r_ptr < nums.size(); r_ptr++) {
            if (nums[r_ptr] != 0) {
                swap(nums[r_ptr], nums[l_ptr]);
                l_ptr++;
            }
        }
    }
};
```

## Notes
This was hard. It is easier to reword the problem as: 
>*Move all non-zero elements to the front of the array.*

Solving this problem yields the same result, with all the 0s at the back of the array.

To solve this, we iterate over the array with two pointers:
- left pointer, which is pointing to the first zero value in the array
- right pointer, which just iterates over the array
When we see a non-zero element at right pointer, we swap it with the element at left pointer.

e.g. `[0,1,0,3,4]`

First iteration (`r=0`):
```
nums = [0,1,0,3,4]
		L
		R
```
`nums[r]` is zero so we do nothing

Second iteration (`r=1`):
```
nums = [0,1,0,3,4]
		L R
```
`nums[r]` is non-zero, so we need to swap it with `nums[l]`, then increment `l`

Third iteration (`r=2`):
```
nums = [1,0,0,3,4]
		  L R
```
`nums[r]` is zero so we do nothing

Fourth iteration (`r=3`):
```
nums = [1,0,0,3,4]
		  L   R
```
`nums[r]` is non-zero, so we need to swap it with `nums[l]`, then increment `l`

Fifth iteration (`r=4`):
```
nums = [1,3,0,0,4]
		    L   R
```
`nums[r]` is non-zero, so we need to swap it with `nums[l]`, then increment `l`

Final values:
```
nums = [1,3,4,0,0]
			  L R
```

