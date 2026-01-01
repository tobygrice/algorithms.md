Know when to use which algorithm under each heading.
## Sorting
Selection Sort: O(n²) || O(1)
- Greedy: repeatedly selects the smallest remaining element and swaps it into the next position. (in-place) (comparison) (min-writes)

Insertion Sort: O(n²) (best O(n)) || O(1)
- Builds a sorted prefix by inserting each new element into its correct spot; excellent for small / nearly-sorted arrays. (stable) (in-place) (adaptive) (comparison) (cache)

Bubble Sort: O(n²) (best O(n)) || O(1)
- Repeatedly swaps adjacent out-of-order elements; early-exit makes it linear on already-sorted input. (stable) (in-place) (adaptive) (comparison) (cache)

Merge Sort: O(n log n) || O(n)
- Divide-and-conquer: sort halves then merge; predictable and widely used. (stable) (comparison) (cache)

Heap Sort: O(n log n) || O(1)
- Build a heap then repeatedly extract max/min into the end of the array; strong worst-case guarantees. (in-place) (comparison)
- Can construct heap in $O(n)$ by adding all elements first, then heapifying

Counting Sort: O(n + k) || O(n + k)
- Counts occurrences of keys in a bounded range of size k, then reconstructs the sorted output. (stable) (non-comp) (cache)

Radix Sort: O(d(n + k)) | O(n + k)
- Sorts by digits/characters over d passes (often using counting sort per digit); great for integers/strings with fixed-ish length. (stable) (non-comp) (cache)

Quick sort O(n log n) || O(1)

Quick Select: O(n) avg, O(n^2) worst
- *A partial sorting algorithm based on quicksort, used to find the $k$th largest element in an unsorted array*
- In a sorted array of size $n$, the $k$th largest element will be at index $n-k$ 
- Note that in quicksort, the pivot element is in its sorted index after partitioning
- Run quicksort, randomly selecting a pivot and partitioning
- After partitioning, if the pivot is at position $n-k$, we know that the pivot is the $k$th largest element and we can return.
- If not, we only need to recurse into the side with our target index (unlike quick sort which would recurse into both)

## Data Structures
Union Find: $O(α(V))$ || $O(V)$
- *"Maintains disjoint sets with fast find and union, using path compression."*
- Each union has a representative element (root of the tree)
	- `find(V)` will always return the representative of vertex `V`'s group
	- to do this, each node stores its parent, and the representative node (root) has itself as the parent
	- find moves up through the tree until `cnode.parent == cnode`, then returns `cnode`
- Union
	- Set parent of representative of union A = representative of union B.
	- `(find(A)).parent = find(B)` - assuming `find` returns a pointer to the representative
- Path compression
	- Rather than storing `parent` for each node and recursing up through the tree (`O(log n)`), flatten the tree and only store the representative.  
	- Gives O(V) `union` and `find` (amortised time)
Heap: O(log n)   ||   O(n)
- Tree-based structure that gives fast access to the most important element.
- Left child is at $2k$
- Right child is at $2k+1$
- Parent is at $\left\lfloor {k}/{2} \right\rfloor$
Trie: O(L)  || O(total characters)
- Prefix-tree for fast string/prefix lookup, great for autocomplete and dictionary membership in O(L).
- L is length of longest string in the trie
HashMap/HashSet: O(1)  ||  O(n) 
- fast exact lookups in average O(1).
- perfect Hashing: 
	- builds a collision-free hash function for a static key set, guaranteeing no collisions so lookups are truly constant-time.
Bit Manipulation
- A signed variable of $n$ bits can contain any integer between $-2^{n-1}$ and $2^{n-1} - 1$
- An unsigned variable of $n$ bits can contain any integer between $0$ and $2^{32}−1$.
- For C++, $n=32$
- Two's complement: flip the bits and add 1

### Balanced BSTs
**AVL Trees**
- $O(\log n)$ for search, insert, delete. Added rebalancing time is $O(\log n)$ worst case.
- *a balanced BST that balances frequently, best when you search more often than insert*
- height bounded by $1.44 \lg n$
- invariant: for any node, the height of its two subtrees differs by at most 1
	- balance factor = height of left subtree - height of right subtree
	- must be -1, 0, or 1
- balancing:
	- left/right rotate is O(1)
	- height of inserted node is always 1 (leaf node)
	- check balance factor (BF) of parent of inserted node.
		- if balance factor is invalid (dne -1, 0, or 1), balance appropriately, then exit.
			- tree is balanced
		- else, continue moving up the tree until a balance operation is performed or the root is reached ($O(\log n)$ time to balance)
**Red-Black Trees**
- $O(\log n)$ for search, insert, delete. *Average* added rebalancing time is $O(1)$ amortised 
  ($O(\log n)$ worst case).
- *A balanced BST that balances less frequently than AVL for faster insertion and deletion. Use when inserting/deleting more than searching.*
- height bounded by $2 \lg n$
- 5 invariants:
	1. Each node is either RED or BLACK
	2. The root is always BLACK.
	3. Every leaf node (NIL) is BLACK. All leaf nodes are NIL nodes.
	4. **If a node is RED, both children must be BLACK.**
	5. **Every path from a node to its descendant NIL nodes must have the same number of black nodes.**

## Graphs
### MST
MST = the cheapest way to connect all vertices in a graph to form a spanning tree (no cycles) with the lowest possible total edge weight. A spanning tree contains all vertices ($V$) and $V-1$ edges.

**Prim's: $O(E \log V)$   ||   $O(E + V)$     dense graph**
- *Greedy MST algorithm that grows a tree from the start node by repeatedly popping the smallest discovered edge.*
- Take the smallest edge in the graph that is connected to a discovered vertex
	- e.g. at step 1, take the smallest edge in the graph, which will be connected to two vertices, say A and B. From there, take the smallest edge that is connected to A or B. 
	- Say this edge connects C. We then take the smallest edge that is connected to A, B, or C. This continues until all vertices are connected.
- Time complexity $E \log V$:
	- Edges are stored in adjacency lists, we must check every edge once.
	- Each edge is added to a min-heap
	- Min-heap will never be bigger than $V$
		- therefore each heap operation is $O(\log V)$
		- we do this operation $E$ times
	- Gives time $E \log V$
**Kruskal's:  $O(E \log E)$  ||  $O(E + V)$    sparse graph**
- *Greedy MST algorithm that adds the next smallest edge using Union-find for cycle detection*
- Start on smallest edge in entire graph
- Repeatedly add the next smallest edge to the graph, that doesn't create a cycle
- Uses union-find data structure to determine if a cycle is formed:
	- If adding an edge `(v,u)` connects two nodes in the **same** union, do not add the edge
		- `if find(u) == find(v) { ignore edge }`
	- If adding an edge connects two nodes in different unions, add the edge and call `union`
		- `else { add (u,v) to MST; union(u, v) }`
- Time complexity $O(E \log E)$:
	- Initial heapify of all edges takes $O(E)$
	- We do 2 finds and possibly 1 union for each edge 
		- Pop min edge from heap $O(\log E)$
		- Union operations take $O(\alpha (V))$, 
			- **α(V)** is the inverse Ackermann function, which is effectively constant
		- therefore, time for *each* edge operation -> $O(\log E) + O(1) = O(\log E)$
	- Total time = $O(E) + O(E \cdot \log E) = O(E \log E)$
	- Alternatively, you could sort the array first in $E \log E$ time, then take the smallest element in constant time for $E$ constant operations, for the same final time complexity.
### Shortest Path
**Dijkstra: $O(E \log V))$   ||   $O(E + V)$**
- *Greedy single-source shortest paths algorithm for weighted graphs with no negative edge weights, using a priority queue to always settle the next closest vertex.*
- Fails with negative cycles
**Bellman-Ford:  $O(EV)$   ||   $O(E + V)$**
- *Dynamic-programming style single-source shortest paths algorithm that allows negative edges and can detect negative cycles reachable from the source.*
- Repeat $V-1$ times:
	- Iterate over all edges in the graph (in any order) and relax outward edges (if a distance improvement can be made, make it)
		- e.g. For edge `(u,v)` with cost `C`
		- `D[v] = min( D[v] , D[u]+C )`
	- The algorithm may solve it in less than $V-1$ iterations, depending on the graph.
- To check if there are negative cycles: do 1 more iteration, and if improvements are made to any vertices, there is a negative cycle
**Floyd-Warshall: $O(V^3)$   ||   $O(V^2)$**
- *Dynamic-programming style all-pairs shortest paths algorithm that allows negative edges and can detect negative cycles.*
- Computes $V$ matrices, the final of which contains the shortest path from $i$ to $j$.
- For `k = 1..V`, compute the following for all values of `i` and `j`: $$A_k[i,j] = \text {min} ( \{ A_{k-1}[i,j] \},  \{ A_{k-1}[i,k] + A_{k-1}[k,j] \})$$
- In other words: 
	- start with adjacency matrix of initial graph $A_0$ ($k=0$)
	- start with $A_{k} = A_{k-1}$, then for each edge, update it if it is shorter to travel there via $k$.
	- do this for every vertex (until $k=V$ where $V$ is the number of vertices)
- To check for negative cycles:
	-  a negative cycle is present iff any vertex can reach itself with a negative cost

### Max flow / min cut
https://www.youtube.com/watch?v=oHy3ddI9X3o
Max flow is the sum of capacities leaving start node S
**Residual Graphs**
- Shows where can we undo flow, and where can we push more flow
- e.g. ![[Pasted image 20260101212024.png]]
- Consider vertex $u$. There are 2 units of flow at $u$, and the arrows out of $u$ show where we can push those two units. 
	- The amount of flow at $u$ is the sum of edge weights from $u$ to the starting node (in the residual graph).
- The example above shows the residual graph for the greedy solution: $s \rightarrow u \rightarrow v \rightarrow t$.
- We can look at the edges to determine where we can push back flow.
- The existence of a path from $s$ to $u$ indicates a path where we can push more flow.
- This lets us develop a maximum flow solution: ![[Pasted image 20260101212855.png]]

Ford-Fulkerson: $O(Ef)$   ||  $O(E + V)$
- Max flow method that repeatedly finds an augmenting path in the residual graph using DFS and augments flow.
Edmonds–Karp: $O(VE^2)$   ||   $O(E + V)$
- Max flow method that repeatedly finds an augmenting path in the residual graph using BFS and augments flow

