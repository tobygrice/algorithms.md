*Time: 98 minutes*

## Problem
We run a preorder depth-first search (DFS) on the `root` of a binary tree.

At each node in this traversal, we output `D` dashes (where `D` is the depth of this node), then we output the value of this node.  If the depth of a node is `D`, the depth of its immediate child is `D + 1`.  The depth of the `root` node is `0`.

If a node has only one child, that child is guaranteed to be **the left child**.

Given the output `traversal` of this traversal, recover the tree and return _its_ `root`.

**Example 1:**
![](https://assets.leetcode.com/uploads/2024/09/10/recover_tree_ex1.png)
**Input:** `traversal = "1-2--3--4-5--6--7"`
**Output:** `[1,2,5,3,4,6,7]`

**Example 2:**
![](https://assets.leetcode.com/uploads/2024/09/10/recover_tree_ex2.png)
**Input:** `traversal = "1-2--3---4-5--6---7"`
**Output:** `[1,2,5,3,null,6,null,4,null,7]`

**Example 3:**
![](https://assets.leetcode.com/uploads/2024/09/10/recover_tree_ex3.png)
**Input:** `traversal = "1-401--349---90--88"`
**Output:** `[1,401,null,349,88,90]`

**Constraints:**
- The number of nodes in the original tree is in the range `[1, 1000]`.
- `1 <= Node.val <= 10^9`

## Solution
```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* recoverFromPreorder(string traversal) {
        queue<pair<int,TreeNode*>> traversal_order; // {depth, value}
        int i = 0;
        int n = (int)traversal.size();
		
        // build queue of node traversal order
        while (i < n) {
            int depth = 0;
            while (i < n && traversal[i] == '-') {
                depth++;
                i++;
            }
            int val = 0;
            while (i < n && traversal[i] >= '0' && traversal[i] <= '9') {
                val = val * 10 + (traversal[i] - '0');
                i++;
            }
            traversal_order.push({depth, new TreeNode(val)});
        }
		
        stack<TreeNode*> current_path; // tracks current path through tree
        auto root_depth = traversal_order.front();
        traversal_order.pop();
        TreeNode* root = root_depth.second;
		
        // move through queue to build tree
        int prev_depth = 0;
        TreeNode* prev_node = root;
        current_path.push(prev_node);
        while(!traversal_order.empty()) {
            // pop from queue and store current depth/node
            auto curr_node_depth = traversal_order.front();
            traversal_order.pop();
            int curr_depth = curr_node_depth.first;
            TreeNode* curr_node = curr_node_depth.second;
			
            if (curr_depth > prev_depth) {
                // traversing down tree, insert left
                prev_node->left = curr_node;
            } else {
                // move back up the tree until we reach curr_depth
                while (current_path.size() > curr_depth) {
                    current_path.pop();
                }
                // insert right
                (current_path.top())->right = curr_node;                
            }
            // update prev values and current path
            prev_depth = curr_depth;
            prev_node = curr_node;
            current_path.push(curr_node);
        }
        return root;
    }
};
```
## Notes
~~build a hashmap of vectors~~
- ~~key is depth~~
- ~~value is vector~~
	- ~~contains nodes at that depth ordered by discovery~~
	- ~~how do we know parent of node?~~
~~build tree from hashmap~~

initially, traverse through string and store nodes in fifo queue
nodes stored as <depth, val>

Then iterate through queue:
if next depth > cur depth
- we are continuing to move down the tree, inserting left
else
- we are moving back up the tree until we get to that depth - 1, then inserting right
- we need access to parent
	- can keep a stack to track current path through tree
- keep popping from path stack until we reach desired depth
- then insert node right


Test case:
```
"1-401--349---90--88"
{0,1}, {1,401}, {2,349}, {3,90}, {2,88}

current_path = root -> 401 -> 349 -> 90
prev_depth = 3
prev_node = 90

curr_depth = 2
curr_node = 88

---

current_path = root -> 401 -> 88
prev_depth = 2
prev_node = 88

curr_depth = 2
curr_node = 88

```

Tree:
```
								1
							401
						349     88
					90
```