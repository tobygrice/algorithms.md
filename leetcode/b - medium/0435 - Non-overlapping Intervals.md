*Time: failed*

## Problem
Given an array of intervals `intervals` where `intervals[i] = [starti, endi]`, return _the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping_.

**Note** that intervals which only touch at a point are **non-overlapping**. For example, `[1, 2]` and `[2, 3]` are non-overlapping.

**Example 1:**
**Input:** `intervals = [[1,2],[2,3],[3,4],[1,3]]`
**Output:** `1`
**Explanation:** `[1,3]` can be removed and the rest of the intervals are non-overlapping.

**Example 2:**
**Input:** `intervals = [[1,2],[1,2],[1,2]]`
**Output:** `2`
**Explanation:** You need to remove two `[1,2]` to make the rest of the intervals non-overlapping.

**Example 3:**
**Input:** `intervals = [[1,2],[2,3]]`
**Output:** `0`
**Explanation:** You don't need to remove any of the intervals since they're already non-overlapping.

**Constraints:**
- `1 <= intervals.length <= 10^5`
- `intervals[i].length == 2`
- `-5 * 10^4 <= start_i < end_i <= 5 * 10^4`

## Solution
Incorrect
```cpp
class Solution {
public:
    bool fits_in_set(set<pair<int, int>> *current_intervals, pair<int, int> new_interval) {
        for (auto interval : *current_intervals) {
            if (new_interval.first < interval.first) {
                // new_interval starts lower
                // e.g. [2,3] [3,4]
                if (new_interval.second <= interval.first) {
                    // new interval
                    current_intervals->insert(new_interval);
                    return true;
                }
            } else if (interval.first < new_interval.first) {
                // interval 2 starts lower
                // e.g. [3,4] [2,3]
                if (interval.second <= new_interval.first) {
                    // new interval
                    current_intervals->insert(new_interval);
                    return true;
                }
            } // new_interval[0] == interval[0] (overlap)
        }
        return false;
    }

    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        // pq using min heap
        std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, std::greater<std::vector<int>>> pq;
        // pq sorted by diff, start, end
        for (int i = 0; i < intervals.size(); i++) {
            vector<int> curr = intervals.at(i);
            int diff = curr.at(1) - curr.at(0);
            curr.insert(curr.begin(), diff);
            pq.push(curr);
        }

        int num_to_remove = 0;
        set<pair<int, int>> current_intervals;
        vector<int> last = pq.top();
        current_intervals.insert({last.at(1), last.at(2)});
        pq.pop();
        while (!pq.empty()) {
            vector<int> next = pq.top();
            if (fits_in_set(&current_intervals, {next.at(1), next.at(2)})) {
                last = next;
            } else {
                num_to_remove++;
            }
            pq.pop();
        }
        return num_to_remove;
    }
};

```
Solution (Neetcode):
```cpp
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
		
        int num_removals = 0;
        int prev_end = intervals[0][1];
        for (int i = 1; i < intervals.size(); i++) {
            int start = intervals[i][0];
            int end = intervals[i][1];
            if (start >= prev_end) {
                // no overlap
                prev_end = end;
            } else {
                num_removals++;
                prev_end = min(prev_end, end); // take the smallest subrange
            }
        }

        return num_removals;
    }
};
```

## Notes
