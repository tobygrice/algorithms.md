*Time: failed*

## Problem
You are given a string `s` and a robot that currently holds an empty string `t`. Apply one of the following operations until `s` and `t` **are both empty**:

- Remove the **first** character of a string `s` and give it to the robot. The robot will append this character to the string `t`.
- Remove the **last** character of a string `t` and give it to the robot. The robot will write this character on paper.

Return _the lexicographically smallest string that can be written on the paper._

```
Example 1:
Input: s = "zza"
Output: "azz"
Explanation: Let p denote the written string.
Initially p="", s="zza", t="".
Perform first operation three times p="", s="", t="zza".
Perform second operation three times p="azz", s="", t="".

Example 2:
Input: s = "bac"
Output: "abc"
Explanation: Let p denote the written string.
Perform first operation twice p="", s="c", t="ba". 
Perform second operation twice p="ab", s="c", t="". 
Perform first operation p="ab", s="", t="c". 
Perform second operation p="abc", s="", t="".

Example 3:
Input: s = "bdda"
Output: "addb"
Explanation: Let p denote the written string.
Initially p="", s="bdda", t="".
Perform first operation four times p="", s="", t="bdda".
Perform second operation four times p="addb", s="", t="".
```

**Constraints:**
- `1 <= s.length <= 10^5`
- `s` consists of only English lowercase letters.

## Solution
First solution, using backtracking (too slow):
```cpp
class Solution {
public:
    string res = "{"; // '{' appears directly after 'z' in ascii
    void backtrack(string s, string t, string p) {
        if (p >= res) return; // prune, no need to explore this path any further
		
        if (s.empty() && t.empty()) {
            if (p < res) res = p;
            return;
        }
		
        // choice 1:
        // remove first character of s and append to t
        if (!s.empty()) {
            backtrack(s.substr(1), t + s[0], p);
        }
		
        // choice 2:
        // remove last character of t and append to p
        if (!t.empty()) {
            backtrack(s, t.substr(0, t.size() - 1), p + t.back());
        }
    }
	
    string robotWithString(string s) {
        backtrack(s, "", "");
        return res;
    }
};
```
Correct solution:
```cpp
class Solution {
public:
    bool s_has_char_before(vector<int>& occ_in_s, char t) {
        for (int c = 0; c < t - 'a'; c++) {
            if (occ_in_s[c] > 0) {
                return true;
            }
        }
        return false;
    }
	
    string robotWithString(string s) {
        int n = s.size();
        string t = "";
        string p = "";
        int si = 0; // index we are currently at in s 
			        // this method saves actually removing head of s
		
        vector<int> occ_in_s(26, 0);
        for (char c : s) {
            occ_in_s[c - 'a']++;
        }
		
        while (si < n) {
            t.push_back(s[si]);
            occ_in_s[s[si++] - 'a']--; // decrement frequency of s[si]
									   // then increment si
			
            while (!t.empty() && !s_has_char_before(occ_in_s, t.back())) {
                p.push_back(t.back());
                t.pop_back();
            }
        }
        
        return p;
    }
};
```
## Notes
I really like my backtracking solution, it sucks that it's not optimal. 

The correct solution above has optimal time complexity $O(n)$ but still runs quite slowly, only beats 20%. Some implementations use a stack for `s`, but I don't see how this would be any faster than the indexing solution above. 