prims E logV
- next best edge that is discovered
- pq only holds 
- investigate time complexity more
- use in dense (more edges)

kruskals E logE
- sorts all edges
- picks next best edge that doesn't form cycles (union-find guarantees)
- learn union-find
- use in sparse (less edges)

union-find
- path compression - update all nodes in a path to the parent root
- used in kruskals to detect if next edge creates a cycle
	- call union on target node and its parent
	- if it creates a cycle, don't add it, try next edge
- learn union first

heap
- only takes n time to heapify an unsorted array
- add all elements to heap first, then heapify (don't heapify at every insertion)

perfect hashing
- choose a hash function with no collision
- must know all items in hash table at compile time in order to choose such a function

dictionary vs hash map

dijkstras E logV
invariant = rule of data structure that you promise not to break

dijkstra
- greedy single-source shortest paths algorithm for weighted graphs with no negative edges using a pq to settle the next closest vertex
- E log V
bellman-ford
- brute force approach to dijkstra's, just iterate through every possible combination of E and V
- updates the distance to every vertex, `edges` amount of times
- solves dijkstra's problem of negative weights, with a worse time complexity
- handles negative cycles
- array of shortest distance to all other nodes, from a single given starting node
floyd-warshall
- gives an adjacency matrix to find the shortest distance from all nodes to all other nodes

bellman-ford + floyd-warshall
- run same algorithm again
- if improvement, we know there is a negative cycle -> set to -inf
- if no improvement

maximum flows - Ford-Fulkerson & Edmonds–Karp
- learn about
- minimum cut

[https://refactoring.guru/design-patterns/catalog](https://refactoring.guru/design-patterns/catalog "https://refactoring.guru/design-patterns/catalog")
- singleton, factory, (strategy but don't focus on it)

cycles in singly-linked lists
- can detect a cycle using slow and faster ptr
	- slow ptr increments by 1
	- fast ptr increments by 2 (fast = next->next)
- If they ever meet, cycle exits
Find head of cycle (first node in the cycle you reach when traversing from the head)
- keep hash map of visited nodes
- traverse down tree, check if each new node is in map
- if not, add it and move on
- if yes, this first detected duplicate is the head of the cycle (we have just cycled around)
- can use ptrs instead of values for more robust code

binary tree != binary search tree
- only BST has left smaller, right larger invariant

AVL vs Red black trees
- AVL is more balanced but takes longer to balance, takes logn to balance
- height 1.44logn
- faster search, slower insertion
- RB is less balanced buy insertion is amortised to O(1) additional time

quick sort
- important to differentiate worst case input from worst case random selection

bucket sort
- stable

