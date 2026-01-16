*Time: XX minutes*

## Problem
Given an array of integers `nums`, sort the array in ascending order and return it.

You must solve the problem **without using any built-in** functions in `O(nlog(n))` time complexity and with the smallest space complexity possible.

**Example 1:**
**Input:** `nums = [5,2,3,1]`
**Output:** `[1,2,3,5]`
**Explanation:** After sorting the array, the positions of some numbers are not changed (for example, 2 and 3), while the positions of other numbers are changed (for example, 1 and 5).

**Example 2:**
**Input:** `nums = [5,1,1,2,0,0]`
**Output:** `[0,0,1,1,2,5]`
**Explanation:** Note that the values of `nums` are not necessarily unique.

**Constraints:**
- `1 <= nums.length <= 5 * 104`
- `-5 * 104 <= nums[i] <= 5 * 104`


## Solution
Mergesort:
```cpp
class Solution {
public:
    void merge(vector<int>& nums, int start, int m, int end) {
        vector<int> temp;
        temp.reserve(end - start + 1);
		
        int l = start;
        int r = m;
        while (l < m && r <= end) {
            if (nums[l] < nums[r]) {
                temp.push_back(nums[l++]);
            } else {
                temp.push_back(nums[r++]);
            }
        }
        while (l < m) {
            temp.push_back(nums[l++]);
        }
        while (r <= end) {
            temp.push_back(nums[r++]);
        }
		
        int i = start;
        for (int n : temp) {
            nums[i++] = n;
        }
    }
	
    void mergesort(vector<int>& nums, int start, int end) {
        if (end <= start) return;
        int m = start + ((end - start) / 2);
        mergesort(nums, start, m);
        mergesort(nums, m + 1, end);
        merge(nums, start, m + 1, end);
    }
	
    vector<int> sortArray(vector<int>& nums) {
        int n = nums.size();
        mergesort(nums, 0, n - 1);
        return nums;
    }
};
```
Using Quicksort (too slow on large input of identical values):
```cpp
class Solution {
public:
    void quicksort(vector<int>& nums, int start, int end) {
        if (start >= end) return;
        srand(static_cast<unsigned int>(time(0)));
        int pivot_ind = rand() % (end - start + 1) + start;
        int pivot_val = nums[pivot_ind];
        
        // partition O(n)
        int lp; // left pointer
        int rp; // right pointer
        int new_pivot_idx;
        for (lp = start, rp = start; rp <= end; rp++) {
            if (nums[rp] <= pivot_val) {
                swap(nums[lp], nums[rp]);
                if (nums[lp] == pivot_val) new_pivot_idx = lp;
                lp++;
            }
		}
		
        lp -= 1; // lp is now last value leq to pivot
        // we need to swap nums[lp] with a pivot from the left
		
        swap(nums[new_pivot_idx], nums[lp]);
		
        // recurse (work halves)
        quicksort(nums, start, lp - 1);
        quicksort(nums, lp + 1, end);
    }
	
    vector<int> sortArray(vector<int>& nums) {
        int n = nums.size();
        quicksort(nums, 0, n - 1);
        return nums;
    }
};
```
## Notes
Quick sort:
1. select a random index to pivot
2. partition
3. recurse

```
srand(static_cast<unsigned int>(time(0)));
int dice_roll = rand() % (max_val - min_val + 1) + min_val;
```