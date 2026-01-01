**Terminology:**
- invariant
- instantiated
- thread
- CPU core
- divide and conquer
- comparison-based
- dense / sparse graph
- adjacency matrix and list
- amortised
> - deterministic
> - augmenting
- heuristic
- Big O Upper
- Big Θ theta
- Big Ω Omega
> - residual graph
> - augmenting path
- P / NP / NP-hard / NP-complete
> - Tabulation
- Memoisation

**Sorting:**
quick, bubble, insertion, bucket, merge, ***selection***, heap.
What is it? 
***What is it's time complexity in best average worst case?***
What is the best/worst case and how do you avoid worst case?
**Is it stable? is it cache-friendly? Is it divide and conquer? It comparison based? Is it in place? These specific questions will help you answer comparison questions.**
What is the minimum time complexity for a comparison based sorting algorithm? (this is a second year course question ADDS).

**Design Patterns:**
What is the strategy design pattern?
How can you make sure only one class is ever instantiated?
How can you make sure only one class is ever instantiated in a multi-threaded system?

**Trees:** 
What is a tree?
What is a binary tree?
What is a binary search tree?
What is the time complexity for searching in any one of those trees?
What is the height of those trees (as a range)?

**Balanced Search Trees:**
What is red black trees and what are it's invariants?
What is AVL tree and what are it's invariants?
What is the complexity of the rearrangement operations of both? Note: in this question, the insertion is log n, but I'm asking about what is the complexity for just the rearrangement part of that.
Why would we use one over another?

**MST:**
What is an MST?
What are the two main algorithms that get the MST?
How do they work? Specifically mention the data structure  + how the next edge is chosen.
How do they work?
When to use one over another? Look at the time complexity and compare both of them in the worst case when E=V^2. You don't explain this in detail I'm just saying for you to understand this.

**Union Find / Disjoint Set Union:**
What is it? Time complexity? 
What is Path compression?

**Tries:**
What is a Trie? Time Complexity? Uses?

**Hash map:**
What is a hash map and how does it work? time and space complexity?
What is a hash function and what are it's properties?
What are the two main ways to handle hash collisions?
What is perfect hashing and when would you use it? This is a bit tricky in my opinion, but AI will get you a valid answer. 

**Dijkstra:**
What is it? time? 
What are its invariants?
What happens when you input a negative edge weight to it? 
How does it choose the next edge?

**A*:**
What is it?
What are its invariants?
What happens when you break the heuristic invariant?

**Bellman-Ford:**
What is it and time complexity? 
What happens when we give it negative edges?
What happens when we give it cycles with negative weight.
How would you detect cycles and handle them appropriately? Time complexity of this?

**Floyd-Warshall:**
What is it? time complexity?
What happens when we give it negative edges?
What happens when we give it cycles with negative weight.
How would you detect cycles and handle them appropriately? Time complexity of this?

**BFS/DFS:**
What is BFS and DFS? Time complexity?

**Max Flow:**
What is the max flow problem? how to solve it (there's two ways)? 
How is it related to the minimum cut?

**Singly Linked List:**
What are the operations of a singly linked list? time?
when would you use it over an array or vector?
Given a pointer to a node in the middle of the singly linked list, i.e. there's at least one element before and one element after, how would you delete it? O(1) time answer exists

**Doubly Linked List:**
What is it and what time complexity is it?
when would you use a doubly linked list?
Given a pointer to any node in the doubly linked list, how would you delete that node?

**Topological Sort:**
What is topological sort? can you give me an algorithm for finding an answer with how it works and time complexity?
How do you do topological sort on a tree in O(n) time?

**Strongly Connected Components:**
How do you find strongly connected components in a graph? what algos? 

**Complexity Analysis:**
What are the big Three? Big O omega Theta
What is the master theorem? 
Can you give me all big three for this pseudocode?

**P / NP / NP-hard / NP-complete:**
What is each of those? 
What is a reduction in this context? 
What properties does the reduction need to follow? Time complexity of reduction?

**Dynamic Programming:**
What are the two approaches to DP?
When would you go for one over the other?

**Other questions:**
When would you use a trie over a hash map?
How does vector amortised time work?
What is a heuristic?
What are some of the shortest path algorithms/heuristics you know and what problems do they solve? (4)
Why would you use Dijkstra over Bellman-Ford or vice versa?
What is an adjacency list and adjacency matrix? What is the benefit for each of them?
What is caching?