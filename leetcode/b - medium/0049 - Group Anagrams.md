## Problem
Given an array of strings `strs`, group the anagrams together. You can return the answer in **any order**.

**Example 1:**
> **Input:** `strs = ["eat","tea","tan","ate","nat","bat"]`
> **Output:** `[["bat"],["nat","tan"],["ate","eat","tea"]]`
> **Explanation:**
> - There is no string in strs that can be rearranged to form `"bat"`.
> - The strings `"nat"` and `"tan"` are anagrams as they can be rearranged to form each other.
> - The strings `"ate"`, `"eat"`, and `"tea"` are anagrams as they can be rearranged to form each other.

**Example 2:**
> **Input:** `strs = [""]`
> **Output:** `[[""]]`

**Example 3:**
> **Input:** `strs = ["a"]`
> **Output:** `[["a"]]`

**Constraints:**
- `1 <= strs.length <= 104`
- `0 <= strs[i].length <= 100`
- `strs[i]` consists of lowercase English letters.

## Solution
```C++
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> output = {};
        vector<int> length_of_strs_in_set = {};
        vector<map<char, int>> char_occurences_map = {};
		
        for (const auto& str : strs) {
            map<char, int> str_map = {};
            for (char c : str) {
                if (str_map.contains(c)) { 
                    str_map.at(c) += 1;
                } else { 
                    str_map.insert({c, 1});
                }
            }
			
            bool added_to_existing_set = false;
            for (int i = 0; i < output.size(); i++) {
                if (length_of_strs_in_set.at(i) == str.length()) {
                    if (str_map == char_occurences_map.at(i)) {
                        output.at(i).push_back(str);
                        added_to_existing_set = true;
                        break;
                    }
                }
            }
			
            if (!added_to_existing_set) {
                output.push_back({str});
                length_of_strs_in_set.push_back(str.length());
                char_occurences_map.push_back(str_map);
            }
        }
		
        return output;
    }
};
```

## Notes
How to determine if two strings are anagrams?
- same length
- same number of occurrences of each character

How to count occurrences?
- array of 26 integers corresponding to alphabet, values indicate number of occurrences
- sort two strings and repeatedly pop front, check if equal (use min heap)
	- nice but longer time complexity?
- a bitmap would be nice but we need to store integers up to 26, not binary values

Would be great if we could produce some unique integer that represents a string uniquely by number of occurrences of each character. Then we could just compare that value.

Should identical strings be considered anagrams? Yes?

Build hashmap for each string with {char: num occurences}
Then for each pair of strings:
- if they are the same size and num occurrences is same for all
- we know they are anagrams
- e.g. pair "eat" and "tea"
	- check `eat.num_occurences('e') = tea.num_occurences('e')`
	- check `eat.num_occurences('a') = tea.num_occurences('a')`
	- check `eat.num_occurences('a') = tea.num_occurences('t')`
	- strings are same length, so after this we are done

Later, we don't need to check every string against every string in a set - only 1
- if its an anagram of 1 item in the set then its an anagram of all of them

For each item:
- check if it anagrams with any set in vector
- if not, add it to new set

Don't need to store a hash map for every string, only every anagram set

Store these hashmaps in a seperate vector

```C++
vector<vector<string>> output = {};
vector<int> length_of_strs_in_set = {};
vector<map<char, int>> char_occurences_sets = {}; // len matches output

for str in strs
	// generate char occurences map for str
	map<char, int> str_map = {};
	for (char c : str) {
		if (str_map.contains(c)) { 
			str_map.at(c) += 1;
		} else { 
			str_map.insert({c, 1});
		}
	}
	
	bool added = false
	for i in 0..output.length()
		if length_of_strs_in_set(i) == str.length()
			// check str matches char_occurences.at(i)
			if (str_map == char_occurences_sets.at(i)): 
				output.at(i).push_back(str)
				added = true
				break
	if (!added)
		add to new set

```
