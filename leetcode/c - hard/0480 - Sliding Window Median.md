*Time: 164 minutes*

## Problem
The **median** is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle values.

- For examples, if `arr = [2,3,4]`, the median is `3`.
- For examples, if `arr = [1,2,3,4]`, the median is `(2 + 3) / 2 = 2.5`.

You are given an integer array `nums` and an integer `k`. There is a sliding window of size `k` which is moving from the very left of the array to the very right. You can only see the `k` numbers in the window. Each time the sliding window moves right by one position.

Return _the median array for each window in the original array_. Answers within `10-5` of the actual value will be accepted.

**Example 1:**
**Input:** `nums = [1,3,-1,-3,5,3,6,7], k = 3`
**Output:** `[1.00000,-1.00000,-1.00000,3.00000,5.00000,6.00000]`
**Explanation:** 
```
Window position                Median
---------------                -----
[1  3  -1] -3  5  3  6  7        1
 1 [3  -1  -3] 5  3  6  7       -1
 1  3 [-1  -3  5] 3  6  7       -1
 1  3  -1 [-3  5  3] 6  7        3
 1  3  -1  -3 [5  3  6] 7        5
 1  3  -1  -3  5 [3  6  7]       6
```

**Example 2:**
**Input:** `nums = [1,2,3,4,2,3,1,4,2], k = 3`
**Output:** `[2.00000,3.00000,3.00000,3.00000,2.00000,3.00000,2.00000]`

**Constraints:**
- `1 <= k <= nums.length <= 105`
- `-231 <= nums[i] <= 231 - 1`

## Solution
Non-optimal:
```cpp
class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<double> ans;
        ans.reserve(n);
        for (int l = 0, r = k; r <= n; l++, r++) {
            // sort new vector from l to r
            // find median
            // add to output array
            vector<double> temp(nums.begin() + l, nums.begin() + r);
            sort(temp.begin(), temp.end());

            int med_ind = temp.size() / 2;
            double median;
            if (temp.size() % 2 == 0){
                median = (temp.at(med_ind) + temp.at(med_ind - 1)) / 2;
            } else {
                median = temp.at(med_ind);
            }
            ans.push_back(median);
        }
        return ans;
    }
};
```
Attempt 2, using `multiset`:
```cpp
class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<double> ans;
        ans.reserve(n);
        
        // declare and build initial set
        multiset<int> window_set;
        for (int i = 0; i < k; i++) {
            window_set.insert(nums[i]);
        }
		
        for (int l = 0, r = k; r <= n; l++, r++) {
            // find median and add to result
            int med_ind = window_set.size() / 2;
            double median;
            if (window_set.size() % 2 == 0){
                auto l_val_ptr = next(window_set.begin(), med_ind - 1);
                double r_val = *next(l_val_ptr, 1);
                double l_val = *l_val_ptr;
                median = (l_val + r_val) / 2;
            } else {
                median = *next(window_set.begin(), med_ind);
            }
            ans.push_back(median);
			
            // remove element at nums[l] and insert element at nums[r]
            auto l_index = window_set.find(nums[l]);
            window_set.erase(l_index);
            if (r < n) window_set.insert(nums[r]);
        }
		
        return ans;
    }
};
```
Attempt 3, using 2 `multiset`s:
```cpp
class Solution {
public:
	// O(log k)
    void balance_sets(multiset<double>& l_set, multiset<double>& r_set) {
        while (r_set.size() > l_set.size()) {
            auto r_min = r_set.begin();
            l_set.insert(*r_min);
            r_set.erase(r_min);
        } 
        while (l_set.size() - r_set.size() > 1) {
            auto l_max = prev(l_set.end());
            r_set.insert(*l_max);
            l_set.erase(l_max);
        }
    }
	
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<double> ans;
        ans.reserve(n);
        
        multiset<double> l_set, r_set;
        
        // build initial left set and right set O(k log k)
        vector<int> init_window(nums.begin(), nums.begin() + k);
        sort(init_window.begin(), init_window.end());
        int i;
        int mid = k / 2;
        for (i = 0; i < mid; i++) l_set.insert(init_window[i]);
        for (i = i; i < k; i++) r_set.insert(init_window[i]);
        balance_sets(l_set, r_set);
        
        // loop n-k times doing O(log k) work
        // time complexity is O((n-k) log k)
        // n dominates, so O(n log k)
        for (int l = 0, r = k; r <= n; l++, r++) {
		    // calculate median O(1)
            double median;
            if (l_set.size() == r_set.size()) {
                median = (*l_set.rbegin() + *r_set.begin()) / 2;
            } else {
                median = *l_set.rbegin();
            }
            ans.push_back(median);
			
            if (r >= n) break;
			
            // remove left value O(2 log k)
            auto ind_in_lset = l_set.find(nums[l]);
            if (ind_in_lset != l_set.end()) {
                // element is in left set
                l_set.erase(ind_in_lset);
            } else {
                // element is in right set
                auto ind_in_rset = r_set.find(nums[l]);
                r_set.erase(ind_in_rset);
            }
			
            balance_sets(l_set, r_set); // O(log k)
			
            // insert right value O(log k)
            if (l_set.empty() || nums[r] <= *l_set.rbegin()) {
                l_set.insert(nums[r]);
            } else {
                r_set.insert(nums[r]);
            }
			
            balance_sets(l_set, r_set); // O(log k)
        }
        return ans;
    }
};
```

## Notes
Solution 3 is $O(n \log k)$. There is a similar solution with the same time complexity, that uses a min heap and a max heap instead of two multisets. To remove elements from the heap as the window moves, we check each element against a multiset of elements 'to delete', and ignore it if it is in the set.

---
sorted list from i to j
sorted list from i+1 to j+1 is the same, just need to insert j+1

can use multiset, remove value at i and insert value at j
then find median
- finding median is harder, cannot index into multiset, need to perform n/2 iterations through the set

solution: two multisets
m1 has lower half up to and including median
m2 has upper half following median


```
// balance sets
void balance_sets(multiset<double>& m1, multiset<double>& m2) {
	if (m2.size() > m1.size()) {
		double m2min = *s.begin();
		m2.remove(m2min)
		m1.insert(m2min)
	} else if (m1.size() + 1 > m2.size()) {
		m1max = m1.max()
		m1.remove(m1max)
		m2.insert(m1max)
	}
}

// find median
if m1.size() == m2.size()
    median = (m1.max() + m2.min()) / 2
else
    median = m1.max();

ans.push(back_median)

// remove left value
if m1.contains(nums[l])
    m1.remove(nums[l])
else
    m2.remove(nums[l])

balance_sets(m1, m2);

// insert new right value
if m1.max() >= nums[r]
    m1.insert(nums[r])
else
    m2.insert(nums[2])

balance_sets(m1, m2);
```

sorted list from i to j
sorted list from i+1 to j+1 is the same, just need to insert j+1

can use multiset, remove value at i and insert value at j
then find median
- finding median is harder, cannot index into multiset, need to perform n/2 iterations through the set

solution: two multisets
m1 has lower half up to and including median
m2 has upper half following median
