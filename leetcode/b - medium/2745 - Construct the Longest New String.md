*Time: 26 minutes*
## Problem
You are given three integers `x`, `y`, and `z`.

You have `x` strings equal to `"AA"`, `y` strings equal to `"BB"`, and `z` strings equal to `"AB"`. You want to choose some (possibly all or none) of these strings and concatenate them in some order to form a new string. This new string must not contain `"AAA"` or `"BBB"` as a substring.

Return _the maximum possible length of the new string_.

A **substring** is a contiguous **non-empty** sequence of characters within a string.

**Example 1:**
**Input:** x = 2, y = 5, z = 1
**Output:** 12
**Explanation:** We can concatenate the strings "BB", "AA", "BB", "AA", "BB", and "AB" in that order. Then, our new string is "BBAABBAABBAB". 
That string has length 12, and we can show that it is impossible to construct a string of longer length.

**Example 2:**
**Input:** x = 3, y = 2, z = 2
**Output:** 14
**Explanation:** We can concatenate the strings "AB", "AB", "AA", "BB", "AA", "BB", and "AA" in that order. Then, our new string is "ABABAABBAABBAA". 
That string has length 14, and we can show that it is impossible to construct a string of longer length.

**Constraints:**
- `1 <= x, y, z <= 50`

## Solution:
```Rust
impl Solution {
    pub fn longest_string(x: i32, y: i32, z: i32) -> i32 {
         2 * (2 * min(x,y) + 1 + z)
    }
}
```

## Notes
Looking at the example inputs, I noticed a pattern:
> ABABAABBAABBAA

The solution was formed by repeating AB, then alternating between AA and BB

This is pretty much the answer to how to solve the problem.

We can include all AB strings, but we will be limited on how long the AABB string can be by the smaller of the two.
- Whichever we have more of, we start and end with
- e.g. x=2 and y=100
- max string: BBAABBAABB
- We start and end with BB

For AB, if our AABB string starts with BB, we need to put our AB string after the AABB string
`ABABAB + BBAABB -> not allowed`
`BBAABB + ABABAB -> good`
This proves we can include all AB strings

If `x=y` then we can include all strings

This gives us the final formula for *number* of strings:

`min(x,y) + min(x,y) + 1 + z`

`return (4 * min(x,y) + 2 + 2z)`

Which we can multiply by two for the final answer, as each string is two chars long

Using if statements:

```C++
if (x > y) {
	return 2*(y + 1 + y + z);
}
if (x < y) {
	return 2*(x + x + 1 + z);
}
return 2*(x + y + z);
```



ABABABABABAABBAA