*Interview problem, solved in ~28 mins*

## Problem
You are given two integer arrays `nums1` and `nums2`, sorted in **non-decreasing order**, and two integers `m` and `n`, representing the number of elements in `nums1` and `nums2` respectively.

**Merge** `nums1` and `nums2` into a single array sorted in **non-decreasing order**.

The final sorted array should not be returned by the function, but instead be _stored inside the array_ `nums1`. To accommodate this, `nums1` has a length of `m + n`, where the first `m` elements denote the elements that should be merged, and the last `n` elements are set to `0` and should be ignored. `nums2` has a length of `n`.

**Example 1:**
**Input:** `nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3`
**Output:** `[1,2,2,3,5,6]`
**Explanation:** The arrays we are merging are `[1,2,3]` and `[2,5,6]`.
The result of the merge is `[1,2,2,3,5,6]` with the underlined elements coming from nums1.

**Example 2:**
**Input:** `nums1 = [1], m = 1, nums2 = [], n = 0`
**Output:** `[1]`
**Explanation:** The arrays we are merging are `[1]` and `[]`.
The result of the merge is `[1]`.

**Example 3:**
**Input:** `nums1 = [0], m = 0, nums2 = [1], n = 1`
**Output:** `[1]`
**Explanation:** The arrays we are merging are `[]` and `[1]`.
The result of the merge is `[1]`.
Note that because `m = 0`, there are no elements in `nums1`. The `0` is only there to ensure the merge result can fit in `nums1`.

## Solution
My solution:
```cpp
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
	    int m_next = m - 1;
	    int n_next = n - 1;
	    int next_insertion = m + n - 1;
        while (m_next + 1 && n_next + 1) {
	        if (nums1[m_next] < nums2[n_next]) {
		        nums1[next_insertion--] = nums2[n_next--];
			} else {
				nums1[next_insertion--] = nums1[m_next--];
			}
		}
		while (m_next + 1) {
			nums1[next_insertion--] = nums1[m_next--];
		}
		while (n_next + 1) {
			nums1[next_insertion--] = nums2[n_next--];
		}
	}
};
```
A slightly cleaner implementation
```cpp
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int m_next = m - 1;
        int n_next = n - 1;
        int next_insertion = m + n - 1;
        
        while (n_next >= 0) {
            if (m_next >= 0 && nums1[m_next] > nums2[n_next]) {
                nums1[next_insertion--] = nums1[m_next--];
            } else {
                nums1[next_insertion--] = nums2[n_next--];
            }
        }
    }
};
```
## Notes
Because we are merging in place, we need to merge from back of the two arrays to avoid writing over values we need in `nums1`. 
