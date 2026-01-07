## Problem
Given an integer array `nums` of length `n`, you want to create an array `ans` of length `2n` where `ans[i] == nums[i]` and `ans[i + n] == nums[i]` for `0 <= i < n` (**0-indexed**).

Specifically, `ans` is the **concatenation** of two `nums` arrays.

Return _the array_ `ans`.

**Example 1:**
**Input:** `nums = [1,2,1]`
**Output:** `[1,2,1,1,2,1]`
**Explanation:** The array ans is formed as follows:
- `ans = [nums[0],nums[1],nums[2],nums[0],nums[1],nums[2]]`
- `ans = [1,2,1,1,2,1]`

**Example 2:**
**Input:** `nums = [1,3,2,1]`
**Output:** `[1,3,2,1,1,3,2,1]`
**Explanation:** The array ans is formed as follows:
- `ans = [nums[0],nums[1],nums[2],nums[3],nums[0],nums[1],nums[2],nums[3]]`
- `ans = [1,3,2,1,1,3,2,1]`

**Constraints:**
- `n == nums.length`
- `1 <= n <= 1000`
- `1 <= nums[i] <= 1000`

## Solution
```CPP
class Solution {
public:
    vector<int> getConcatenation(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            nums.push_back(nums.at(i));
        }
        return nums;
    }
};
```
Rust solutions:
```Rust
// direct translation of C++ solution:
impl Solution {
    pub fn get_concatenation(mut nums: Vec<i32>) -> Vec<i32> {
        let n = nums.len();
        for i in 0..n {
            let x = nums[i];
            nums.push(x);
        }
        nums
    }
}

// Rusty solution:
impl Solution {
    pub fn get_concatenation(nums: Vec<i32>) -> Vec<i32> {
        nums.iter()
            .chain(nums.iter())
            .copied()
            .collect()
    }
}
```

## Notes
1. `nums.iter()`
	- `nums: Vec<i32>`
	- `nums.iter()` returns an iterator over **references** to the elements:
	    - type: `std::slice::Iter<'_, i32>`
	    - item type: `&i32`
	- It yields `&nums[0]`, `&nums[1]`, … until the end.
	- **Key idea:** `iter()` _borrows_ the vector (`&nums`), it does not consume it.
2. `.chain(nums.iter())`
	- `chain` combines two iterators into one “back-to-back” iterator.
	- Both iterators must yield the same item type (`&i32` here).
	- The resulting iterator yields:
	    1. all items from the first `nums.iter()`, then
	    2. all items from the second `nums.iter()`.
	- So if `nums = [10, 20, 30]`, the chained iterator yields:  
		- `&10, &20, &30, &10, &20, &30`.
	- **Why calling `nums.iter()` twice is allowed:**
		- Each call creates an **immutable borrow** of `nums`.
		- Rust allows multiple immutable borrows simultaneously, so this is fine.
3. `.copied()`
	- Up to now, the iterator yields `&i32`, but we need a `Vec<i32>`.
	- `.copied()` converts an iterator of references into an iterator of values by **copying** each element.
	- Specifically:
		- before: `Iterator<Item = &i32>`
		- after: `Iterator<Item = i32>`
	- This works because `i32` implements the `Copy` trait (copying an `i32` is cheap and does not move ownership).
	- If the elements were not `Copy` (e.g., `String`), `.copied()` would not compile; you’d use `.cloned()` (or restructure the solution) instead.
4. `.collect()`
	- `collect()` consumes the iterator and builds a collection from it.
	- The target type is inferred from the function return type `Vec<i32>`, so:
	    - it allocates a new `Vec<i32>`
	    - pushes each `i32` produced by the iterator into it
	- Final result: a new vector of length `2 * nums.len()` containing `nums` twice.
**Notes on behavior / performance**
- This does **not** mutate `nums`; it builds a brand-new vector.
- It must allocate memory for the output vector (since we’re returning a new `Vec<i32>`).
- Whether `collect()` pre-allocates exactly `2n` capacity is an implementation detail; if you want guaranteed single allocation, build with `Vec::with_capacity(2*n)` and `extend` twice.