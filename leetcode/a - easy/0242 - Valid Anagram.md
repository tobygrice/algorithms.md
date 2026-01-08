*Time: 8 minutes*

## Problem
Given two strings `s` and `t`, return `true` if `t` is an anagram of `s`, and `false` otherwise.

**Example 1:**
**Input:** `s = "anagram", t = "nagaram"`
**Output:** `true`

**Example 2:**
**Input:** `s = "rat", t = "car"`
**Output:** `false`

**Constraints:**
- `1 <= s.length, t.length <= 5 * 104`
- `s` and `t` consist of lowercase English letters.

**Follow up:** What if the inputs contain Unicode characters? How would you adapt your solution to such a case?

## Solution
```C++
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.length() != t.length()) return false;
		
        std::unordered_map<char, int> s_map, t_map;
        for (int i = 0; i < s.length(); i++) {
            s_map[s.at(i)]++;
            t_map[t.at(i)]++;
        }
		
        return (t_map == s_map);
    }
};
```

## Notes
If `s` and `t` are different lengths, they are not anagrams so we can just return false.
Therefore, we can work on the assumption that `s` and `t` are of equal length, `n`.

First solution that comes to mind is to sort both strings and compare. This would take $O(n \log n)$ to sort and $O(n)$ to compare, for a total of $O(n \log n)$ time.

Can we find a solution that runs in $O(n)$?

We can iterate over the strings and build a hash map for each that counts occurrences of each character. `unordered_map` gives insertion and search in constant time, so building these maps can be done in $O(n)$.

We can then just compare these maps in $O(n)$ time and return the result, for a total time complexity of $O(n)$.

My initial solution was correct:
```cpp
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.length() != t.length()) return false;
		
        int n = s.length();
		
        std::unordered_map<char, int> s_map, t_map;
        s_map = {};
        t_map = {};
		
        for (int i = 0; i < n; i++) {
            char cur_s = s.at(i);
            char cur_t = t.at(i);
			
            if (s_map.contains(cur_s)) {
                s_map.at(cur_s)++;
            } else {
                s_map.insert({cur_s, 1});
            }
			
            if (t_map.contains(cur_t)) {
                t_map.at(cur_t)++;
            } else {
                t_map.insert({cur_t, 1});
            }
		}
		
        return (t_map == s_map);
    }
};
```
But there are some C++ tricks to simplify the code:
1. We don't need to initialise the maps
2. `s_map.at(key) = val` will throw error if `key` is not in the map, necessitating my checks
	- however, `s_map[key] = val` will add `{key, val}` to the map if `key` is not a key
	- it will also assume `val` is 0, so `s_map[key]++` will add `{key, 1}`
	- use this instead and no more checks are needed