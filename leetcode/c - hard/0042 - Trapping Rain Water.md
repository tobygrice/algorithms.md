*Time: 181 minutes for non-optimal solution*

## Problem
Given `n` non-negative integers representing an elevation map where the width of each bar is `1`, compute how much water it can trap after raining.

**Example 1:**
![](https://assets.leetcode.com/uploads/2018/10/22/rainwatertrap.png)
**Input:** `height = [0,1,0,2,1,0,1,3,2,1,2,1]`
**Output:** `6`
**Explanation:** The above elevation map (black section) is represented by array `[0,1,0,2,1,0,1,3,2,1,2,1]`. In this case, `6` units of rain water (blue section) are being trapped.

**Example 2:**
**Input:** `height = [4,2,0,3,2,5]`
**Output:** `9`

**Constraints:**
- `n == height.length`
- `1 <= n <= 2 * 10^4`
- `0 <= height[i] <= 10^5`

## Solution
First attempt, wrong
```cpp
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();

        int left_wall = 0; // ind of left wall, largest wall seen so far
        int curr_left_wall = 0; // ind of largest wall seen since left_wall
        
        int elevation_since_clw = 0;
        int elevation_since_lw = 0;

        int capacity_from_curr_lw = 0;
        int capacity_from_lw = 0;
        int total_capacity = 0;

        for (int i = 1; i < n; i++) {
            if (height[i] <= height[i - 1]) {
                // no new bucket can be formed
                elevation_since_clw += height[i];
                elevation_since_lw += height[i];
            } 
            else if (height[i] >= height[left_wall]) {
                total_capacity += 
	                (height[left_wall] * (i - left_wall - 1)) - elevation_since_lw;
                capacity_from_curr_lw = 0;
                capacity_from_lw = 0;
                
                left_wall = i;
                curr_left_wall = i; // ? ERROR POINT

                // reset elevation trackers
                elevation_since_clw = 0;
                elevation_since_lw = 0;
            } 
            else if (height[i] >= height[curr_left_wall]) {
                capacity_from_lw = 
	                (height[i] * (i - left_wall - 1)) - elevation_since_lw;
                curr_left_wall = i;
                capacity_from_curr_lw = 0;

                elevation_since_clw = 0;
                elevation_since_lw += height[i];
            } 
            else {
                // height[i] is less than left_wall and curr_left_wall
                // but is greater than height[i-1] 
                // new bucket can be formed to curr_left_wall
                capacity_from_curr_lw = 
	                (height[i] * (i - curr_left_wall - 1)) - elevation_since_clw;
                elevation_since_clw += height[i];
                elevation_since_lw += height[i];
            }
        }

        return total_capacity + capacity_from_lw + capacity_from_curr_lw;
    }
};
```
Second attempt, correct but not optimal $O(n^2)$:
```cpp
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
		
        vector<pair<int, int>> tallest_wall_after(n);
        for (int i = 0; i < n; i++) {
            int elevation_between = 0;
            int max_height = i + 1;
            for (int j = i + 1; j < n; j++) {
                if (height[j] >= height[i]) {
                    tallest_wall_after[i] = {j, elevation_between};
                    break;
                } else if (height[j] >= height[max_height]) {
                    tallest_wall_after[i] = {j, elevation_between};
                    max_height = j;
                }
                elevation_between += height[j];
            }
        }
		
        int total_capacity = 0;
        int i = 0;
        while (i < n - 1) {
            int next_tallest_wall = tallest_wall_after[i].first;
            int elevation_between = tallest_wall_after[i].second;
			
            int width = (next_tallest_wall - i - 1);
            // if (width < 0) width = 0;
            int h_i = height[i];
            int h_ntw = height[next_tallest_wall];
            int height = min(h_i, h_ntw);
            int capacity = (width * height) - elevation_between;
            total_capacity += max(0, capacity);
			
            i = next_tallest_wall;
        }
		
        return total_capacity;
    }
};
```
Optimal solution, using two pointers $O(n)||O(1)$
```cpp
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
		
        int l_ptr = 0;
        int r_ptr = n - 1;
        
        int max_l = l_ptr;
        int max_r = r_ptr;
		
        int rain_water = 0;
        
        while (l_ptr < r_ptr) {
            if (height[max_l] <= height[max_r]) {
	            // left is guaranteed to be our min height
                int water_at_l = height[max_l] - height[l_ptr];
                if (water_at_l > 0) rain_water += water_at_l;
                if (height[++l_ptr] >= height[max_l]) {
                    max_l = l_ptr;
                }
            } else {
	            // right is guaranteed to be our min height
                int water_at_r = height[max_r] - height[r_ptr];
                if (water_at_r > 0) rain_water += water_at_r;
                if (height[--r_ptr] >= height[max_r]) {
                    max_r = r_ptr;
                }
            }
        }
		
        return rain_water;
    }
};
```
## Notes

`left_wall` is highest elevation seen so far
`curr_left_wall` is highest elevation *since* `left_wall` (therefore will be less than `left_wall`)

- iterate through array
- if `height[i]` less than `curr_left_wall` but greater than `height[i-1]`
	- new bucket between `i` and `curr_left_wall`
	- `capacity_from_curr_lw = height[i] * width - blocks between`
- if `height[i]` geq than `curr_left_wall`, less than `left_wall`
	- `curr_left_wall = i`
	- `capacity_from_lw = height[i] * width - blocks between`
- if `height[i]` geq `left_wall`
	- `total_capacity += height[left_wall] * width - blocks between`
	- `left_wall = i`
	- `curr_left_wall = ?`


when we hit the end: `total_capacity += capacity_from_lw + capacity_from_curr_lw`

---

### Optimal Solution
![](https://assets.leetcode.com/uploads/2018/10/22/rainwatertrap.png)
At each index `i`, the amount of rainwater that can be stored is the minimum of the tallest wall on the left and the tallest wall on the right, minus the height at `i`.
$$\text {water} = \text {min} (\text {maxLeft}, \text {maxRight}) - height_i$$
There are two ways we can determine the `max_left` and `max_right` heights for each index.
1. We can iterate over the array from left to right and store `max_left` for each `i`, then iterate from right to left and store `max_right` for each `i`. $O(n)$ time and $O(n)$ space
2. We can use a two pointer approach for $O(n)$ time and $O(1)$ space

**Two pointers - $O(n)||O(1)$**
- keep a `left` pointer and  `right` pointer. Left starts at index `0` and right starts at `n`
- also keep `max_left` and `max_right` variables.
	- If `max_left` is **less than** `max_right`, calculate water at `left` then increment `left`
	- else, `max_right` is **less than** `max_left`, calculate water at `right` then decrement `right`
- By doing this, we ensure that the result of our `min(max_left, max_right)` operation remains accurate. We may not know the larger of the two, but that doesn't matter because we will always have the correct minimum. 