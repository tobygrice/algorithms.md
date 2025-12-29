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

Counting Sort: O(n + k) || O(n + k)
- Counts occurrences of keys in a bounded range of size k, then reconstructs the sorted output. (stable) (non-comp) (cache)

Radix Sort: O(d(n + k)) | O(n + k)
- Sorts by digits/characters over d passes (often using counting sort per digit); great for integers/strings with fixed-ish length. (stable) (non-comp) (cache)


## Graphs
### MST
Prim: O(E logV)   ||   O(E + V)     dense graph
- Greedy MST algorithm that grows a tree from the start node by repeatedly popping the smallest discovered edge.
Kruskal:  O(E logE)  ||  O(E + V) sparse graph
- *"Greedy MST algorithm that adds the next smallest edge using Union-find for cycle detection"*
- Start on smallest edge in entire graph
- Repeatedly look for smallest edge that doesn't create a cycle
- If adding an edge `(v,u)` connects two nodes in the **same** union, do not add the edge
	- `if find(u) == find(v) { ignore edge }`
- If adding an edge connects two nodes in different unions, add the edge and call `union`
	- `else { add (u,v) to MST; union(u, v) }`


### Data Structures
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
Trie: O(L)  || O(total characters)
- Prefix-tree for fast string/prefix lookup, great for autocomplete and dictionary membership in O(L).
HashMap/HashSet: O(1)  ||  O(n) 
- fast exact lookups in average O(1).
- perfect Hashing: 
	- builds a collision-free hash function for a static key set, guaranteeing no collisions so lookups are truly constant-time.

### Shortest Path
Dijkstra: O(E log V))   ||   O(E + V)
- Greedy single-source shortest paths algorithm for weighted graphs with no negative edge weights, using a priority queue to always settle the next closest vertex.
Bellman-Ford:  O(EV))   ||   O(E + V)
- Dynamic-programming style single-source shortest paths algorithm that allows negative edges and can detect negative cycles reachable from the source.
Floyd-Warshall: O(V^3)   ||  O(V^2)
- All-pairs shortest paths via dynamic programming; supports negative edges and can detect negative cycles.


### Max flow / min cut
Ford-Fulkerson: O(Ef)   ||  O(E + V)
- Max flow method that repeatedly finds an augmenting path in the residual graph using DFS and augments flow.
Edmonds–Karp: O(VE^2   ||   O(E + V)
- Max flow method that repeatedly finds an augmenting path in the residual graph using BFS and augments flow