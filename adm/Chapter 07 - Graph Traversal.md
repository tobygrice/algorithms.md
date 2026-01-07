- Graphs are important because they can be used to represent essentially **any** relationship
- Designing truly novel graph algorithms is a difficult task, but usually unnecessary. 
- Instead, you should correctly model your problem so you can take advantage of existing algorithms

## Flavours of Graphs
- undirected vs directed
	- formal definition: a graph G = (V,E) is undirected if the presence of edge (x, y) in E **implies** that edge (y, x) is also in E
- weighted vs unweighted
- simple vs non-simple
	- non-simple: graphs that allow self loops (edge (x,x)) and multiedges (identical edges that occur more than once in the graph)
	- simple graphs do not allow self loops or multiedges. All algorithms in this book only work on simple graphs.
- sparse vs dense
	- sparse: only a small fraction of the possible edges exist in the graph
	- dense: large fraction of possible edges are defined
	- complete: all possible edges are defined
	- no strict boundary between the two, but in general:
		- dense when $Θ(n^2)$ edges
		- sparse when $Θ(n)$ edges
- cyclic vs acyclic
	- a cycle is a closed path of 3 or more vertices
	- an acyclic graph does not contain any cycles
	- undirected acyclic graph: e.g. tree
	- directed acyclic graph (DAG): e.g. scheduling problems
- embedded vs topological
	- embedded: vertices and edges are assigned geometric positions. e.g. a drawing of a graph
- implicit vs explicit
	- e.g. the friendship graph of the world is represented implicitly. Each person knows who their friends are, but cannot find out about other people’s friendships except by asking them. The graph calculated implicitly as it is traversed
- labelled vs unlabelled

**Additional terminology:** 
- **Degree:** the degree of a vertex (node) is the number of edges adjacent (connected) to it.
- **Regular:** In a **regular** graph, each vertex has exactly the same degree

## Data Structures for Graphs
![[Pasted image 20251212160328.png]]
### Adjacency matrix 
- We can represent G using an $n × n$ matrix M, where element `M[i, j] = 1` if `(i, j)` is an edge of G, and 0 if it isn’t.
- Fast access to "does edge exist"
- Wasted space for sparse graphs - space is quadratic $n^2$, so can get very big for large graphs

### Adjacency lists
- use linked lists to store the neighbours of each vertex
- each vertex (node) maintains a linked list of pointers to neighbouring vertexes (nodes) connected by an edge
- harder to verify whether a given edge `(i, j)` is in G, since we must search through the appropriate list to find the edge
	- However, it is surprisingly easy to design graph algorithms that avoid any need for such queries.
- adjacency lists are the right data structure for most applications of graphs

Adjacency list is just an **array of linked lists**
![[Pasted image 20251212163448.png]]
Notes that each node appears **multiple times** if more than one node is pointed to it
- e.g. above, there are 3 objects representing the `3` node, all **separate, unlinked instances** in other nodes' lists.
- the 3 vertex itself is represented implicitly by its index and addresses: `edges[3]`:
```C
#define MAXV 100 /* maximum number of vertices */
typedef struct edgenode {
    int y;                 /* adjacency info */
    int weight;            /* edge weight, if any */
    struct edgenode *next; /* next edge in list */
} edgenode;

typedef struct {
	// personal note: calling the array below 'edges' is confusing but makes
	// sense when you think about it the right way. For a vertex v, the head
	// of its adjacency list can be accessed using edges[v]. 
	// note that the head of edges[v] is not v (unless v is a neighbour of 
	// itself), but whatever adjacent node is represented first in its list.
    edgenode *edges[MAXV + 1]; /* adjacency info. */
    int degree[MAXV + 1];      /* outdegree of each vertex */
    int nvertices;             /* number of vertices in the graph */
    int nedges;                /* number of edges in the graph */
    int directed;              /* is the graph directed? */
} graph;

// if !directed, x is added to y's adjacency list
void insert_edge(graph *g, int x, int y, bool directed) {
	// create p to represent y and insert it at the head of x's list
    edgenode *p;                  /* temporary pointer */
    p = malloc(sizeof(edgenode)); /* allocate edgenode storage */
    
    p->weight = 0;
    p->y = y;
    p->next = g->edges[x];
    
    g->edges[x] = p; /* insert at head of list */
    g->degree[x]++; /* inc degree of x, as 1 edge has been added */
    
    if (!directed) {
        insert_edge(g, y, x, true); // add x to y's AL
    } else {
	    // nedges is only incremented once even in an undirected graph:
	    // (x,y) and (y,x) are added, but nedges only increments once
        g->nedges++;
    }
}
```

## Graph Traversal
- Mazes are naturally represented by graphs, where each graph vertex denotes a junction of the maze, and each graph edge denotes a passageway in the maze. Thus, any graph traversal algorithm must be powerful enough to get us out of an arbitrary maze. 
- For **efficiency**, we must make sure we don’t get trapped in the maze and visit the same place repeatedly. For **correctness**, we must do the traversal in a systematic way to guarantee that we find a way out of the maze.
- We need to track visited nodes/edges
- Each vertex will exist in one of three states: 
	- Undiscovered – the vertex is in its initial, virgin state. 
	- Discovered – the vertex has been found, but we have not yet checked out all its incident edges. 
	- Processed – the vertex after we have visited all of its incident edges.
- We must also maintain a structure containing the vertices that we have discovered but not yet completely processed. 
- Initially, only the single start vertex is considered to be discovered.
- To completely explore a vertex v, we must evaluate each edge leaving v. 
- If an edge goes to an undiscovered vertex x, we mark x discovered and add it to the list of work to do in the future. 
- If an edge goes to a processed vertex, we ignore that vertex, because further contemplation will tell us nothing new about the graph. 
- Similarly, we can ignore any edge going to a discovered but not processed vertex, because that destination already resides on the list of vertices to process

## Breadth-First Search
- In a breadth-first search of an undirected graph, we assign a direction to each edge, from the discoverer u to the discovered v. We thus denote u to be the parent of v.
- Since each node has exactly one parent, except for the root, this defines a tree on the vertices of the graph: ![[Pasted image 20251212195034.png]]
- This defines a shortest path from the root to every other node in the tree
```
BFS(G, s)
	Initialize each vertex u ∈ V[G] so
		state[u] = "undiscovered"
		p[u] = null, i.e. no parent is in the BFS tree
	state[s] = "discovered"
	Q = {s}
	while Q is not empty do
		u = dequeue[Q]
		process_vertex_early(u); // early process vertex u if desired
		for each vertex v that is adjacent to u
			process_edge(u, v); // process edge (u, v) if desired
			if state[v] = "undiscovered" then
				state[v] = "discovered"
				p[v] = u
				enqueue[Q, v]
		state[u] = "processed"
		process_vertex_late(u); // late process vertex u if desired
```

The exact behavior of bfs depends upon the functions `process_vertex_early(u)`, `process_vertex_late(u)`, and `process_edge()`. 
- Through these functions, we can customize what the traversal does as it makes its one official visit to each edge and each vertex. 
- e.g. if we set `process_edge` to `nedges++`, we would get an accurate count of the number of edges in the graph

### BFS for shortest path
- Because BFS checks all neighbouring nodes first, starting from the root, the order in which nodes are discovered directly correspond to their distance from the root.
	- i.e. neighbouring nodes will be discovered in the first pass
	- then all nodes that are 1 hop away
	- then all nodes that are 2 hops away, etc
- In this way, BFS determines the shortest path from the root to any given node in the tree (unweighted)
- To determine the shortest path, we can use the parent array `p` (see pseudocode) which contains the node from which a given node was discovered (its parent)
- We start at the target node, look at its parent, look at that parent, etc, all the way back to the root
- This gives us a reverse order path from the target to the root
- We can find it in the correct order using recursion:
```C
void find_path(int start, int end, int parents[]) {
	if ((start == end) || (end == -1)) {
		printf("\n%d", start);
	} else {
		find_path(start, parents[end], parents);
		printf(" %d", end);
	}
}
```
Important to remember:
- the shortest path tree from `x` to `y` is only useful if BFS was performed with `x` as the root of the search (and not some other node `z`). 
- BFS gives the shortest path only if the graph is **unweighted**

### BFS for connected components
- We say that a graph is **connected** if there is a path between any two vertices. 
	- Every person can reach every other person through a chain of links if the friendship graph is connected. 
- A **connected component** of an undirected graph is a maximal set of vertices such that there is a path between every pair of vertices.
	- e.g. If we envision tribes in remote parts of the world that have not yet been encountered, each such tribe would form a separate **connected component** in the friendship graph. 
	- A remote hermit, or extremely uncongenial fellow, would represent a connected component of one vertex.
- We can use BFS to find connected components:
	- begin by performing a search starting from an arbitrary vertex. 
	- Anything we discover during this search must be part of the same connected component. 
	- We then repeat the search from any undiscovered vertex (if one exists) to define the next component, and so on until all vertices have been found
```C
void connected_components(graph *g) {
	int c; /* component number */
	int i; /* counter */
	
	initialize_search(g);
	
	c = 0;
	for (i = 1; i <= g->nvertices; i++) {
		if (!discovered[i]) {
			c = c + 1;
			printf("Component %d:", c);
			bfs(g, i);
			printf("\n");
		}
	}
}
```

### BFS for two-colouring graphs
- The vertex-colouring problem seeks to assign a label (or colour) to each vertex of a graph such that no edge links any two vertices of the same colour, using as few colours as possible.
- A graph is bipartite if it can be coloured without conflicts while using only two colours.
	- e.g. consider a 'romantically interested in' graph in a purely heterosexual world, where we colour male in blue and female in pink
	- suppose we declare that the starting vertex is “male.” 
	- All vertices adjacent to this man must be “female,” provided the graph is indeed bipartite.
- We can augment BFS so that whenever we discover a new vertex, we colour it the opposite of its parent.
- We check whether any non-tree edge links two vertices of the same colour. 
	- Such a conflict means that the graph cannot be two-coloured.
- If the process terminates without conflicts, we have constructed a proper two-colouring.

```C
void twocolor(graph *g) {
    int i; /* counter */
    for (i = 1; i <= (g->nvertices); i++) {
        color[i] = UNCOLORED;
    }
    bipartite = true;
    initialize_search(g);
    for (i = 1; i <= (g->nvertices); i++) {
        if (!discovered[i]) {
            color[i] = WHITE;
            bfs(g, i);
        }
    }
}

void process_edge(int x, int y){
    if (color[x] == color[y]) {
        bipartite = false;
        printf("Warning: not bipartite, due to (%d,%d)\n", x, y);
    }
    color[y] = complement(color[x]);
}

int complement(int color) {
    if (color == WHITE) {
        return (BLACK);
    }
    if (color == BLACK) {
        return (WHITE);
    }
    return (UNCOLORED);
}
```

## Depth-First Search
The difference between BFS and DFS lies in the order in which they explore vertices. This order depends completely upon the container data structure used to store the discovered but not processed vertices.
- Queue (BFS) – FIFO queue, explore the oldest unexplored vertices first. Explorations radiate out slowly from the starting vertex, defining a breadth-first search. 
- Stack (DFS) – LIFO stack, explore the vertices along a path, visiting a new neighbour if one is available, and backing up only when we are surrounded by previously discovered vertices. Explorations quickly wander away from the starting point, defining a depth-first search.
We can implement DFS using recursion, eliminating the need for an explicit stack:
```
DFS(G, u)
	state[u] = "discovered"
	time = time + 1
	entry[u] = time
	process vertex u early, if desired
	for each vertex v that is adjacent to u
		process edge (u, v) if desired
		if state[v] = "undiscovered" then
			p[v] = u
			DFS(G, v)
	process vertex u late, if desired
	state[u] = "processed"
	exit[u] = time
	time = time + 1
```
The time intervals have interesting and useful properties with respect to depth-first search:
- **Who is an ancestor?** – Suppose that x is an ancestor of y in the DFS tree. This implies that we must enter x before y, since there is no way we can be born before our own parent or grandparent! We also must exit y before we exit x, because the mechanics of DFS ensure we cannot exit x until after we have backed up from the search of all its descendants. Thus, the time interval of y must be properly nested within the interval of ancestor x. 
- **How many descendants?** – The difference between the exit and entry times for`v`tells us how many descendants`v`has in the DFS tree. The clock gets incremented on each vertex entry and vertex exit, so half the time difference denotes the number of descendants of v.

### DFS for finding cycles
Back edges are the key to finding a cycle in an undirected graph. 
- If there is no back edge, all edges are tree edges, and no cycle exists in a tree.
- Any back edge going from x to an ancestor y creates a cycle with the tree path from y to x. 
- Such a cycle is easy to find using DFS:
```C
void process_edge(int x, int y) {
	if (parent[y] != x) { /* found back edge! */
		printf("Cycle from %d to %d:", y, x);
		find_path(y, x, parent);
		finished = true;
	}
}
```

### DFS for articulation vertices
**Articulation vertex** or **cut-node**: a single vertex whose deletion disconnects a connected component of the graph. e.g. red node:
![[Pasted image 20251215132152.png]]
The **connectivity** of a graph is the smallest number of vertices whose deletion will disconnect the graph - the connectivity is 1 if the graph has an articulation vertex.

A depth-first search of a general graph partitions the edges into tree edges and back edges.
- think of these back edges as security cables linking a vertex back to one of its ancestors. 
- the security cable from x back to y ensures that none of the vertices on the tree path between x and y can be articulation vertices.
![[Pasted image 20251215164456.png]]
Finding articulation vertices requires keeping track of the extent to which back edges (i.e., security cables) link chunks of the DFS tree back to ancestor nodes.
- Let `reachable_ancestor[v]` denote the earliest reachable ancestor of vertex `v`, meaning the **oldest** (furthest up the tree) ancestor of `v` that we can reach from a descendant of `v` by using a back edge
- Initially, `reachable_ancestor[v] = v`
- We update `reachable_ancestor[v]` whenever we encounter a back edge that takes us to an earlier ancestor than we have previously seen. 
- The relative age/rank of our ancestors can be determined from their entry times
Implementation:
```C
void process_vertex_early(int v) {
	reachable_ancestor[v] = v;
}

void process_edge(int x, int y) {
	int class; /* edge class */
	
	class = edge_classification(x, y);
	
	if (class == TREE) {
		tree_out_degree[x] = tree_out_degree[x] + 1;
	}
	if ((class == BACK) && (parent[x] != y)) {
		if (entry_time[y] < entry_time[reachable_ancestor[x]]) {
			reachable_ancestor[x] = y;
		}
	}
}
```
To use this reachability relation to determine articulation vertexes, we consider the following three cases (not mutually exclusive):
- Root cut-nodes – If the root of the DFS tree has two or more children, it must be an articulation vertex. No edges from the subtree of the second child can possibly connect to the subtree of the first child. 
- Bridge cut-nodes – If the earliest reachable vertex from`v`is v, then deleting the single edge `(parent[v], v)` disconnects the graph. Clearly `parent[v]` must be an articulation vertex, since it cuts `v` from the graph. Vertex `v` is also an articulation vertex unless it is a leaf of the DFS tree. For any leaf, nothing falls off when you cut it. 
- Parent cut-nodes – If the earliest reachable vertex from`v`is the parent of v, then deleting the parent must sever`v`from the tree unless the parent is the root. This is always the case for the deeper vertex of a bridge, unless it is a leaf.
The routine below systematically evaluates each of these three conditions as we back up from the vertex after traversing all outgoing edges. 
- We use `entry_time[v]` to represent the age of vertex v. 
- The reachability time `time_v` calculated below denotes the oldest vertex that can be reached using back edges. 
- Getting back to an ancestor above v rules out the possibility of v being a cutnode
```C
void process_vertex_late(int v) {
    bool root;             /* is parent[v] the root of the DFS tree? */
    int time_v;            /* earliest reachable time for v */
    int time_parent;       /* earliest reachable time for parent[v] */
    
    if (parent[v] == -1) { /* test if v is the root */
        if (tree_out_degree[v] > 1) {
            printf("root articulation vertex: %d \n", v);
        }
        return;
    }
    
    root = (parent[parent[v]] == -1); /* is parent[v] the root? */
    
    if (!root) {
        if (reachable_ancestor[v] == parent[v]) {
            printf("parent articulation vertex: %d \n", parent[v]);
        }
        if (reachable_ancestor[v] == v) {
            printf("bridge articulation vertex: %d \n", parent[v]);
            if (tree_out_degree[v] > 0) { /* is v is not a leaf? */
                printf("bridge articulation vertex: %d \n", v);
            }
        }
    }
    
    time_v = entry_time[reachable_ancestor[v]];
    time_parent = entry_time[reachable_ancestor[parent[v]]];
    
    if (time_v < time_parent) {
        reachable_ancestor[parent[v]] = reachable_ancestor[v];
    }
}
```