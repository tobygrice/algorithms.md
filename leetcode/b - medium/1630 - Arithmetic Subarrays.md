*Time: 39 minutes*
## Problem
A sequence of numbers is called **arithmetic** if it consists of at least two elements, and the difference between every two consecutive elements is the same. More formally, a sequence `s` is arithmetic if and only if `s[i+1] - s[i] == s[1] - s[0]` for all valid `i`.

For example, these are **arithmetic** sequences:
```
1, 3, 5, 7, 9
7, 7, 7, 7
3, -1, -5, -9
```
The following sequence is not **arithmetic**:
```
1, 1, 2, 5, 7
```

You are given an array of `n` integers, `nums`, and two arrays of `m` integers each, `l` and `r`, representing the `m` range queries, where the `ith` query is the range `[l[i], r[i]]`. All the arrays are **0-indexed**.

Return _a list of_ `boolean` _elements_ `answer`_, where_ `answer[i]` _is_ `true` _if the subarray_ `nums[l[i]], nums[l[i]+1], ... , nums[r[i]]` _can be **rearranged** to form an **arithmetic** sequence, and_ `false` _otherwise._

**Example 1:**
**Input:** `nums = [4,6,5,9,3,7], l = [0,0,2], r = [2,3,5]`
**Output:** `[true,false,true]`
**Explanation:**
In the 0th query, the subarray is `[4,6,5]`. This can be rearranged as `[6,5,4]`, which is an arithmetic sequence.
In the 1st query, the subarray is `[4,6,5,9]`. This cannot be rearranged as an arithmetic sequence.
In the 2nd query, the subarray is `[5,9,3,7]`. This can be rearranged as `[3,5,7,9]`, which is an arithmetic sequence.

**Example 2:**
**Input:** `nums = [-12,-9,-3,-12,-6,15,20,-25,-20,-15,-10], l = [0,1,6,4,8,7], r = [4,4,9,7,9,10]`
**Output:** `[false,true,false,false,true,true]`

**Constraints:**
- `n == nums.length`
- `m == l.length`
- `m == r.length`
- `2 <= n <= 500`
- `1 <= m <= 500`
- `0 <= l[i] < r[i] < n`
- `-10^5 <= nums[i] <= 10^5`

## Solution
My solution $O(m \cdot n \log n)$:
```cpp
class Solution {
public:
    bool seq_from(vector<int>& nums, int l, int r) {
        vector<int> subarray(nums.begin() + l, nums.begin() + r + 1);
        sort(subarray.begin(), subarray.end());
        int jump = subarray[1] - subarray[0];
        for (int i = 2; i < subarray.size(); i++) {
            if (subarray[i] - subarray[i-1] != jump) {
                return false;
            }
        }
        return true;
    }

    vector<bool> checkArithmeticSubarrays(vector<int>& nums, vector<int>& l, vector<int>& r) {
        int m = l.size();        
        vector<bool> answer;
        for (int i = 0; i < m; i++) {
            // function to sort nums from l[i] to r[i]
            // check if arithmetic sequence
            answer.push_back(seq_from(nums, l[i], r[i]));
        }
        return answer;
    }
};
```

Optimal solution $O(m \cdot n)$ described in notes.
## Notes
We can check if an arithmetic sequence exits from `i` to `j` by sorting then counting
- $O(n \log n)$
We would have to perform this operation `m` times (length of `l` and `r` arrays)
- $O(m \cdot n \log n)$

```cpp
class Solution {
public:
    bool seq_from(vector<int>& nums, int l, int r) {
        vector<int> subarray(nums.begin() + l, nums.begin() + r + 1);
        sort(subarray.begin(), subarray.end());
        int jump = subarray[1] - subarray[0];
        for (int i = 2; i < subarray.size(); i++) {
            if (subarray[i] - subarray[i-1] != jump) {
                return false;
            }
        }
        return true;
    }

    vector<bool> checkArithmeticSubarrays(vector<int>& nums, vector<int>& l, vector<int>& r) {
        int m = l.size();        
        vector<bool> answer;
        for (int i = 0; i < m; i++) {
            // function to sort nums from l[i] to r[i]
            // check if arithmetic sequence
            answer.push_back(seq_from(nums, l[i], r[i]));
        }
        return answer;
    }
};
```

---

There is a way to check if an arithmetic sequence exists in $O(n)$ time.
1. calculate min and max elements of array
2. the increment value must be `(max - min) / (num_elements - 1)`
3. because we know the starting value, ending value, and increment value, we know the only arithmetic sequence that works for that array
4. so, we add all elements of the array to a set
5. then check if each element in the arithmetic sequence is in that set

```cpp
bool seq_from(vector<int>& nums, int l, int r) {    
	int min = INT_MAX;
	int max = INT_MIN;
	int n = r - l + 1;

	unordered_set<int> nums_in_subarray;
	nums_in_subarray.reserve(n);
	for (int i = l; i <= r; i++) {
		if (nums[i] < min) min = nums[i];
		if (nums[i] > max) max = nums[i];
		nums_in_subarray.insert(nums[i]);
	}
	
	if ((max - min) % (n - 1) != 0) return false;
	int inc = (max - min) / (n - 1);
	if (inc == 0) return true;
	
	for (int i = min; i <= max; i += inc) {
		if (!nums_in_subarray.contains(i)) {
			return false;
		}
	}
	return true;
}
```

This `seq_from` function runs in $O(n)$ time, instead of $O(n \log n)$ as above. However, the time on leetcode was significantly slower with this $O(n)$ solution.

