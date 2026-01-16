*Time: 37 minutes*

## Problem
There are three stones in different positions on the X-axis. You are given three integers `a`, `b`, and `c`, the positions of the stones.

In one move, you pick up a stone at an endpoint (i.e., either the lowest or highest position stone), and move it to an unoccupied position between those endpoints. Formally, let's say the stones are currently at positions `x`, `y`, and `z` with `x < y < z`. You pick up the stone at either position `x` or position `z`, and move that stone to an integer position `k`, with `x < k < z` and `k != y`.

The game ends when you cannot make any more moves (i.e., the stones are in three consecutive positions).

Return _an integer array_ `answer` _of length_ `2` _where_:

- `answer[0]` _is the minimum number of moves you can play, and_
- `answer[1]` _is the maximum number of moves you can play_.

**Example 1:**
**Input:** `a = 1, b = 2, c = 5`
**Output:** `[1,2]`
**Explanation:** Move the stone from 5 to 3, or move the stone from 5 to 4 to 3.

**Example 2:**
**Input:** `a = 4, b = 3, c = 2`
**Output:** `[0,0]`
**Explanation:** We cannot make any moves.

**Example 3:**
**Input:** `a = 3, b = 5, c = 1`
**Output:** `[1,2]`
**Explanation:** Move the stone from 1 to 4; or move the stone from 1 to 2 to 4.

**Constraints:**
- `1 <= a, b, c <= 100`
- `a`, `b`, and `c` have different values.
## Solution
```cpp
class Solution {
public:
    vector<int> numMovesStones(int a, int b, int c) {
        vector<int> stones = {a, b, c};
        sort(stones.begin(), stones.end()); // O(1) sort
        
        int min_moves;
        int gap1 = stones[1] - stones[0] - 1;
        int gap2 = stones[2] - stones[1] - 1;
        pair<int, int> gaps = {min(gap1, gap2), max(gap1, gap2)};
		
        if (gaps.first >= 2) {
            min_moves = 2;
        } else if (gaps.first == 1) {
            min_moves = 1;
        } else if (gaps.second != 0) {
            // 0,1 consecutive, move second
            min_moves = 1;
        } else {
            // already consecutive
            min_moves = 0;
        }
		
        int max_moves = stones[2] - stones[0] - 2; 
		
        return {min_moves, max_moves};
    }
};
```

## Notes
Start by ordering the stones (put in vector and sort). We always give it 3 elements so this is $O(3 \log 3)$ which is $O(1)$.

**Min moves**
- take the **smaller** gap between the stones
- if this `gap >= 2`, we need 2 moves to end the game:
	- `start = a___b________c`
	- `move1 = ac_b__________`
	- `move2 = acb___________`
- if this `gap == 1`, we need one move to end the game:
	- `start = a_b________c`
	- `move1 = acb_________`
- if this `gap == 0` and the other gap is not zero, we need one move:
	- `start = ab________c`
	- `move1 = abc________`
- if this `gap == 0` and the other gap is zero, we need no moves:
	- `start = abc`

Max moves:
- move each end stone one place closer towards the middle stone:
	- `start = a_b___c` - `a = 0, c = 6`
	- `move1 = _ab___c`
	- `move2 = _ab__c_`
	- `move3 = _ab_c__`
	- `move4 = _abc___`
- formula: max moves is `c - a - 2`


