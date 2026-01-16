*Time: 10 minutes*

## Problem
Given an integer `x`, return `true` _if_ `x` _is a_ _**palindrome**__, and_ `false` _otherwise_.

**Example 1:**
**Input:** `x = 121`
**Output:** `true`
**Explanation:** 121 reads as 121 from left to right and from right to left.

**Example 2:**
**Input:** `x = -121`
**Output:** `false`
**Explanation:** From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.

**Example 3:**
**Input:** `x = 10`
**Output:** `false`
**Explanation:** Reads 01 from right to left. Therefore it is not a palindrome.

**Constraints:**
- `-2^31 <= x <= 2^31 - 1`

**Follow up:** Could you solve it without converting the integer to a string?

## Solution
Using strings:
```cpp
class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;
		
        string xs = to_string(x);
        string rxs = xs;
        reverse(rxs.begin(), rxs.end());
		
        return xs == rxs;
    }
};
```
No strings (my solution):
```cpp
class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;
        if (x == 0) return true;
		
        vector<int> x_digits;
        while (x) {
            x_digits.push_back(x % 10);
            x /= 10;
        }
		
        int n = x_digits.size();
        for (int i = 0, j = n-1; i < j; i++, j--) {
            if (x_digits[i] != x_digits[j]) return false;
        }
        return true;
    }
};
```

No strings (better solution):
```cpp
class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) {
            return false;
        }
		
        long long reversed = 0;
        long long temp = x;
		
        while (temp != 0) {
            int digit = temp % 10;
            reversed = reversed * 10 + digit;
            temp /= 10;
        }
		
        return (reversed == x);
    }
};
```

## Notes
Super easy solution: convert to string, reverse, compare reverse to original, return result of comparison.

Solve without converting to string?

Two options: 
1. convert x to an array of digits
2. calculate num digits in x (by repeatedly dividing by 10 until < 1), then checking `mod 10 ** (numdigits - i)` against `mod 10 ** i`;  until `numdigits - i == i`