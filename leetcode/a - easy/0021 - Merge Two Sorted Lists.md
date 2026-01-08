*Time: failed*

## Problem
You are given the heads of two sorted linked lists `list1` and `list2`.

Merge the two lists into one **sorted** list. The list should be made by splicing together the nodes of the first two lists.

Return _the head of the merged linked list_.

**Example 1:**
![](https://assets.leetcode.com/uploads/2020/10/03/merge_ex1.jpg)

**Input:** `list1 = [1,2,4], list2 = [1,3,4]`
**Output:** `[1,1,2,3,4,4]`

**Example 2:**
**Input:** `list1 = [], list2 = []`
**Output:** `[]`

**Example 3:**
**Input:** `list1 = [], list2 = [0]`
**Output:** `[0]`

**Constraints:**
- The number of nodes in both lists is in the range `[0, 50]`.
- `-100 <= Node.val <= 100`
- Both `list1` and `list2` are sorted in **non-decreasing** order.

## Solution
```cpp
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode dummy_head; // dummy head to attach our output list to
        ListNode* tail = &dummy_head; // pointer to the tail of the output list
        while (list1 && list2) {
            if (list1->val > list2->val) {
                tail->next = list2;
                list2 = list2->next;
            } else {
                tail->next = list1;
                list1 = list1->next;
            }
            tail = tail->next;
        }
		
        if (list1) {
            tail->next = list1;
        } else if (list2) {
            tail->next = list2;
        }
		
        return dummy_head.next;
    }
};
```
## Notes
The critical key is to use a `dummy_head` to start building the output list. 
I tried to build the list 'in place' by inserting nodes into the middle of one of the lists, but this requires an unnecessarily complex algorithm that is tricky to reason about, and doesn't make a whole lot of sense.

much, much easier to have a dummy that works as follows:
```
list1 = 1 -> 2 -> 4 ->
list2 = 1 -> 3 -> 4 ->

dummy = X ->

---

# AFTER ITERATION 1
list1 = 2 -> 4 ->
list2 = 1 -> 3 -> 4 ->
dummy = X -> 1

# AFTER ITERATION 2
list1 = 2 -> 4 ->
list2 = 3 -> 4 ->
dummy = X -> 1 -> 1

# AFTER ITERATION 3
list1 = 4 -> 
list2 = 3 -> 4 -> 
dummy = X -> 1 -> 1 -> 2

# AFTER ITERATION 4
list1 = 4 -> 
list2 = 4 -> 
dummy = X -> 1 -> 1 -> 2 -> 3

# AFTER ITERATION 5
list1 = nullptr
list2 = 4 -> 
dummy = X -> 1 -> 1 -> 2 -> 3 -> 4

--- while loop ends ---
if (list2) conditional results in:
dummy = X -> 1 -> 1 -> 2 -> 3 -> 4 -> 4 ->

return dummy.next
1 -> 1 -> 2 -> 3 -> 4 -> 4 ->
```