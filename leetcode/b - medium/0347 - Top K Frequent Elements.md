*Time: XX minutes*

## Problem
Given an integer array `nums` and an integer `k`, return _the_ `k` _most frequent elements_. You may return the answer in **any order**.

**Example 1:**
**Input:** `nums = [1,1,1,2,2,3], k = 2`
**Output:** `[1,2]`

**Example 2:**
**Input:** `nums = [1], k = 1`
**Output:** `[1]`

**Example 3:**
**Input:** `nums = [1,2,1,2,1,2,3,1,3,2], k = 2`
**Output:** `[1,2]`

**Constraints:**
- `1 <= nums.length <= 105`
- `-104 <= nums[i] <= 104`
- `k` is in the range `[1, the number of unique elements in the array]`.
- It is **guaranteed** that the answer is **unique**.

**Follow up:** Your algorithm's time complexity must be better than `O(n log n)`, where n is the array's size.

## Solution
```cpp
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> occurences;
        for (int n : nums) {
            occurences[n]++;
        }
        vector<pair<int,int>> occ_list;
        for (auto& [n, num_occ] : occurences) {
            occ_list.push_back({num_occ, n});
        }
        
        // priority queue of size k -> O(log k)
        // total time complexity O(n log k)
        priority_queue
	        <pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        // pair is <num_occ, val>
        for (int i = 0; i < k; i++) {
            pq.push(occ_list[i]);
        }
        for (int i = k; i < occ_list.size(); i++) {
            if (pq.top().first < occ_list[i].first) {
                pq.pop();
                pq.push(occ_list[i]);
            }
        }
		
        // extract all from pq -> O(k log k)
        vector<int> res;
        while (!pq.empty()) {
            res.push_back(pq.top().second);
            pq.pop();
        }
		
        return res;
    }
};
```

## Notes