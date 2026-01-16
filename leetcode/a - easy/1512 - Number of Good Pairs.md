*Time: 15 minutes*

## Problem
Given an array of integers `nums`, return _the number of **good pairs**_.

A pair `(i, j)` is called _good_ if `nums[i] == nums[j]` and `i` < `j`.

**Example 1:**
**Input:** `nums = [1,2,3,1,1,3]`
**Output:** `4`
**Explanation:** There are 4 good pairs (0,3), (0,4), (3,4), (2,5) 0-indexed.

**Example 2:**
**Input:** `nums = [1,1,1,1]`
**Output:** `6`
**Explanation:** Each pair in the array are _good_.

**Example 3:**
**Input:** `nums = [1,2,3]`
**Output:** `0`

**Constraints:**
- `1 <= nums.length <= 100`
- `1 <= nums[i] <= 100`

## Solution
Optimal, $O(n) || O(n)$ - my solution was n^2
```cpp
class Solution {
public:
    int numIdenticalPairs(vector<int>& nums) {
        int good_pairs = 0;
        unordered_map<int, int> count;
        for (int num : nums) {
            good_pairs += count[num]++;
        }
        return good_pairs;
    }
};
```

## Notes
From Deepak Gupta:

Imagine this problem like, There is a gathering organized by some guy, the guest list is `[1,2,3,1,1,3]`.

The problem with the guest is they only handshake with like minded people. (Like minded here is basically the digit should be same , for example, 1 will handshake with 1 only, 2 will handshake with 2 only and so on)

So, finally we just need to count number of handshakes in the gathering.

(To distinguish , multiple 1's and 3's , a,b,c,d... letters are used)

One by one, guests are arriving at the gathering: `[1,2,3,1,1,3]`

**first guest: 1**

**second guest: 2**  
(at this moment, in gathering hall we have **1** (2 is about to enter) , since they are not like minded they wont shake hands)

**third guest:3**  
(at this moment, in gathering hall we have **1, 2** (3 is about to enter), since they are not like minded they won't shake hands)

**fourth guest : 1**  
(at this moment, fourth guest will see in gathering hall, there is **one like minded guy** ie(1) , so he will handshake with him)  
therefore totalHandShake = 1

**fifth guest : 1**  
(at this moment, fifth guest will see in gathering hall, there are **two like minded guys** ie(1,1) , so he will handshake with them)  
therefore totalHandShake = 1(last handshake between 1a-1b ) + 2(current handshake between 1a-1c, 1b-1c) = 3

**sixth guest : 3**  
(at this moment, sixth guest will see in gathering hall, there is **one like minded guy** ie(3) , so he will handshake with him)  
therefore totalHandShake = 3(last handshake) + 1(3a-3b) = 4