*Time: 14 minutes*

## Problem
Write a function to find the longest common prefix string amongst an array of strings.

If there is no common prefix, return an empty string `""`.

**Example 1:**
**Input:** `strs = ["flower","flow","flight"]`
**Output:** `"fl"`

**Example 2:**
**Input:** `strs = ["dog","racecar","car"]`
**Output:** `""`
**Explanation:** There is no common prefix among the input strings.

**Constraints:**
- `1 <= strs.length <= 200`
- `0 <= strs[i].length <= 200`
- `strs[i]` consists of only lowercase English letters if it is non-empty.

## Solution
My solution, $O(n)$ where $n$ is the number of characters in the `strs` array.
```cpp
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        // longest common prefix can only be the shortest string?
        // therefore fine to start with any value
        string curr_lcp = strs[0];
        for (int i = 1; i < strs.size(); i++) {
            int max_prefix_len = min(strs[i].length(), curr_lcp.length());
            curr_lcp.erase(max_prefix_len);
            for (int j = 0; j < max_prefix_len; j++) {
                if (curr_lcp[j] != strs[i][j]) {
                    curr_lcp.erase(j);
                    break;
                }
            }
        }
        return curr_lcp;
    }
};
```

## Notes
longest possible common prefix = ~~longest word~~ shortest word
- can find in O(n)
iterate through each string from the start, comparing characters
when mismatch, update longest common prefix
if longest prefix becomes "", just return early