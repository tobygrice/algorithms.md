## Problem
Given an integer array `nums` sorted in **non-decreasing order**, remove some duplicates **in-place** such that each unique element appears **at most twice**. The **relative order** of the elements should be kept the **same**.

Since it is impossible to change the length of the array in some languages, you must instead have the result be placed in the **first part** of the array `nums`. More formally, if there are `k` elements after removing the duplicates, then the first `k` elements of `nums` should hold the final result. It does not matter what you leave beyond the first `k` elements.

Return `k` _after placing the final result in the first_ `k` _slots of_ `nums`.

Do **not** allocate extra space for another array. You must do this by **modifying the input array in place** with O(1) extra memory.

**Custom Judge:**
The judge will test your solution with the following code:
```

int[] nums = [...]; // Input array
int[] expectedNums = [...]; // The expected answer with correct length

int k = removeDuplicates(nums); // Calls your implementation

assert k == expectedNums.length;
for (int i = 0; i < k; i++) {
    assert nums[i] == expectedNums[i];
}
```

If all assertions pass, then your solution will be **accepted**.

**Example 1:**
**Input:** `nums = [1,1,1,2,2,3]`
**Output:** `5, nums = [1,1,2,2,3,_]`
**Explanation:** Your function should return k = 5, with the first five elements of nums being 1, 1, 2, 2 and 3 respectively.
It does not matter what you leave beyond the returned k (hence they are underscores).

**Example 2:**
**Input:** `nums = [0,0,1,1,1,1,2,3,3]`
**Output:** `7, nums = [0,0,1,1,2,3,3,_,_]`
**Explanation:** Your function should return k = 7, with the first seven elements of nums being 0, 0, 1, 1, 2, 3 and 3 respectively.
It does not matter what you leave beyond the returned k (hence they are underscores).

**Constraints:**
- `1 <= nums.length <= 3 * 10^4`
- `-10^4 <= nums[i] <= 10^4`
- `nums` is sorted in **non-decreasing** order.

## Solution
My solution. Time complexity is technically optimal but code is very messy and algorithm isn't perfect.
```C++
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int left_ptr = 0;
        int cur_val = nums[0];
        int num_occurences = 1;
        bool need_to_shift = false;
        for (int cur_ind = 1; cur_ind < nums.size(); cur_ind++) {
            if (cur_val == nums[cur_ind]) {
                num_occurences++;
                if (num_occurences <= 2) {
                    if (need_to_shift) swap(nums[left_ptr++], nums[cur_ind]);
                } else if (!need_to_shift) {
                    need_to_shift = true;
                    left_ptr = cur_ind;
                }
            } else {
                num_occurences = 1;
                cur_val = nums[cur_ind];
                if (need_to_shift) swap(nums[left_ptr++], nums[cur_ind]);
            }
        }
        return left_ptr;
    }
};
```
Optimal solution:
```C++
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() <= 2) return nums.size();
        
        int k = 2;
        for (int i = 2; i < nums.size(); i++) {
            if (nums[i] != nums[k - 2]) {
                nums[k++] = nums[i];
            }
        }
        return k;       
    }
};
```

## Notes
I will only discuss the optimal solution shown above.

The idea is this:
- `k` points to the next index to be filled of our valid output array
- we increment through `nums` with `i`
- if `nums[i]` is the same as the value two places before `k` (`nums[k-2]`)
	- then moving `nums[i]` to `nums[k]` would cause our output array to be invalid
	- so we increment `i` and leave `k` where it is (do nothing)
- else, we have a valid value to move to the back of our output array
	- copy `nums[i]` to `nums[k]`
	- increment `k`

We can start `k` and `i` at 2 because we know for certain the first two elements must be valid.

Feel free to run the algorithm on the following example: `nums = [1,1,1,2,2,2,3,3]`
```
[1,1,1,2,2,2,3,3]
     i
     k
```

