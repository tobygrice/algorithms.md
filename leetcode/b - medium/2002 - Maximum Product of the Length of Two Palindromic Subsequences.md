*Failed*
## Problem
Given a string `s`, find two **disjoint palindromic subsequences** of `s` such that the **product** of their lengths is **maximized**. The two subsequences are **disjoint** if they do not both pick a character at the same index.

Return _the **maximum** possible **product** of the lengths of the two palindromic subsequences_.

A **subsequence** is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters. A string is **palindromic** if it reads the same forward and backward.

**Example 1:**
![example-1](https://assets.leetcode.com/uploads/2021/08/24/two-palindromic-subsequences.png)

**Input:** s = "leetcodecom"
**Output:** 9
**Explanation**: An optimal solution is to choose "ete" for the 1st subsequence and "cdc" for the 2nd subsequence.
The product of their lengths is: 3 * 3 = 9.

**Example 2:**
**Input:** s = "bb"
**Output:** 1
**Explanation**: An optimal solution is to choose "b" (the first character) for the 1st subsequence and "b" (the second character) for the 2nd subsequence.
The product of their lengths is: 1 * 1 = 1.

**Example 3:**
**Input:** s = "accbcaxxcxx"
**Output:** 25
**Explanation**: An optimal solution is to choose "accca" for the 1st subsequence and "xxcxx" for the 2nd subsequence.
The product of their lengths is: 5 * 5 = 25.

**Constraints:**
- `2 <= s.length <= 12`
- `s` consists of lowercase English letters only.

## Solution
Neetcode solution https://www.youtube.com/watch?v=aoHbYlO8vDg
- compute all subsequences
	- represent as a bitmap
	- `leetcodecom` - input
	- `--et---e---` - subsequence
	- `00110001000` - bitmask
	- therefore all subsequences are simply values `00000000000 -> 11111111111`
- for each subsequence, check if its a palindrome
	- this is easy, just reverse the string and compare
	- tricky part (syntactically) is converting bitmask to string
- if the subsequence is a palindrome, store it in a hashmap
	- use subsequence bitmask as the key
	- with length of palindrome as value
- then, we can iterate over all pairs in this hashmap 
	- if the pairs are disjoint (a & b == 0), track the maximum product

```Python
class Solution:
    def maxProduct(self, s: str) -> int:
        N, pali = len(s), {}  # bitmask : length
		
        for mask in range(1, 2 ** N):
            subseq = ""
            for i in range(N):
                if mask & (1 << i):
                    subseq += s[i]
            if subseq == subseq[::-1]:
                pali[mask] = len(subseq)

        res = 0
        for m1 in pali:
            for m2 in pali:
                if m1 & m2 == 0:  # disjoint
                    res = max(res, pali[m1] * pali[m2])

        return res

```

## Notes
Longest palindrome starting at i:

```
vector<set<int>> longest_palindrome_starting_at = {{}}; 
for (int i = i; i < n; i++) {
	for (int j = i; j < n; j++) {
		for (int k = n - 1; k > j; k--) {
			if (a[j] == a[k]) {
				// add j and k to the palindrome set
				longest_palindrome_starting_at[i].insert(j)
				longest_palindrome_starting_at[i].insert(k)
				break;
			}
		}
	}
}
```

I don't need longest palindrome starting at `i`, I need *all* palindromes starting at `i`.

Does the longest palindrome *give* you all palindromes?
~~Yes~~ no

RARCECAR
- Longest palindrome starting at R: `RA[...]CECAR`
- Another palindrome starting at R that is not a subset of longest palindrome: `RAR[...]`

This algorithm doesn't even find the longest palindrome:
input: `AXBABXABABABABA`
my output: `AXBABXA`
correct output: `ABABABABA

After 1 hour, used hints:
- Imply I should generate all possible pairs of disjoint subsequences
- Then find the longest palindrome in each subsequence

I should do this in a way that doesn't use obscene space

generate 1 pair
- then find the longest palindrome in each subsequence
- multiply the two values
- keep track of max
- don't need to store anything other than current max

need a **working** algorithm to find the longest palindrome
- don't need to know the palindrome, just its length

`ABXBXAABBAABROOTBA` input
`AB-B-AABBAAB----BA` correct selection
`ABXBX-----------BA` algorithm above


Gave up at 2 hour mark.