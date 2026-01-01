Uses same data structure as previous chapter:
```C
typedef struct edgenode {
    int y;                 /* adjacency info */
    int weight;            /* edge weight, if any */
    struct edgenode *next; /* next edge in list */
} edgenode;

typedef struct {
    edgenode *edges[MAXV + 1]; /* adjacency info */
    int degree[MAXV + 1];      /* outdegree of each vertex */
    int nvertices;             /* number of vertices in the graph */
    int nedges;                /* number of edges in the graph */
    int directed;              /* is the graph directed? */
} graph;
```

## Minimum Spanning Trees
- A spanning tree of a connected graph G = (V,E) is a subset of edges from E forming a tree connecting all vertices of V.
- The minimum spanning tree is the spanning tree whose sum of edge weights is as small as possible.
- In other words: what is the smallest edge cost (calculated by sum of weights) we can keep and still have a connected graph?
- The MST is the smallest connected graph in terms of edge weight

### Prim's Algorithm
- starts from one vertex and grows the rest of the tree one edge at a time until all vertices are included.
- greedy algorithm: selects the best local option from all available choices
- in this case, heuristic is the smallest edge weight that will increase the number of vertices
- In C++ below, time complexity is $O(n^2 + m)$
	- We could use a priority queue to get the nearest vertex in $O(\log n)$ time
	- This gives a new time complexity of  $O(m \log n)$, because insertion in the second loop also takes $O(\log n)$
```
Prim-MST(G)
	Select an arbitrary vertex s to start the tree T_prim from.
	While (there are still non-tree vertices)
		Find the minimum-weight edge between a tree and non-tree vertex
		Add the selected edge and vertex to the tree T_prim.
```

```C++
int prims(Graph *g, Graph **mst, int start) {
    if (!g) return -1;
	
    start -= 1; // 1-based -> 0-based
    if (!g->in_range(start))
        return -1;
	
    *mst = new Graph(g->nnodes, g->directed);
	
    const int n = g->nnodes;
    std::vector<bool> intree(n, false);
    std::vector<int> distance(n, INT_MAX);
    std::vector<int> parent(n, -1);
	
    distance[start] = 0;
    int total_weight = 0;
	
    while (true) {
        // pick next vertex to add
        int v = -1;
        int best = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (!intree[i] && distance[i] < best) {
                best = distance[i];
                v = i;
            }
        }
        if (v == -1 || best == INT_MAX)
            break; // done / disconnected
		
        intree[v] = true;
		
        // add chosen edge to MST (skip root)
        if (parent[v] != -1) {
            (*mst)->insert_edge(parent[v] + 1, v + 1, distance[v]);
            total_weight += distance[v];
        }
		
        // relax edges out of v
        for (Graph::Edgenode *p = g->edges[v]; p; p = p->next) {
            int w = p->dest;
            if (!intree[w] && p->weight < distance[w]) {
                distance[w] = p->weight;
                parent[w] = v;
            }
        }
    }
	
    return total_weight;
}
```

### Kruskal's Algorithm
- More efficient on sparse graphs.
- May produce a different MST to prim's, but will have the same weight
- Does not start with a particular vertex
Kruskal’s algorithm builds up connected components of vertices, culminating in the complete minimum spanning tree. 
- Initially, each vertex forms its own separate component in the tree-to-be. 
- The algorithm repeatedly considers the lightest remaining edge and tests whether its two endpoints lie within the same connected component. 
	- If so, this edge will be discarded, because adding it would create a cycle. 
	- If the endpoints lie in different components, we insert the edge and merge the two components into one. 
- Since each connected component always is a tree, we never need to explicitly test for cycles.

```
Kruskal-MST(G)
	Put the edges into a priority queue ordered by increasing weight.
	count = 0
	while (count < n − 1) do
		get next edge (v, w)
		if (component(v) != component(w))
			increment count
			add (v, w) to T_kruskal
			merge component(v) and component(w)
```

Checking if `v` and `w` are in the same component can be done in $O(n)$ time using BFS or DFS
- This yields $O(mn)$ total
- However, we can implement the component check in $O(\lg m)$ time using a union-find data structure
- Yields $O(m \lg m)$ -> faster than Prim's for sparse graphs

```C
int kruskal(graph *g) {
	union_find s; /* union-find data structure */
	edge_pair e[g->nnodes]; /* array of edges data structure */
	int weight = 0; /* cost of the minimum spanning tree */
	
	union_find_init(&s, g->nvertices);
	
	to_edge_array(g, e);
	qsort(&e,g->nedges, sizeof(edge_pair), &weight_compare);
	
	for (int i = 0; i < (g->nedges); i++) {
		if (!same_component(&s, e[i].x, e[i].y)) {
			printf("edge (%d,%d) in MST\n", e[i].x, e[i].y);
			weight = weight + e[i].weight;
			union_sets(&s, e[i].x, e[i].y);
		}
	}
	
	return(weight);
}
```


#### Union-Find data structure
We implement our desired component operations in terms of two simpler operations, union and find: 
- `Find(i)` – Find the root of the tree containing element `i`, by walking up the parent pointers until there is nowhere to go. Return the label of the root. 
- `Union(i,j)` – Link the root of one of the trees (say containing `i`) to the root of the tree containing the other (say `j`) so `find(i)` now equals `find(j)`.

```C
void union_find_init(union_find *s, int n) {
    int i; /* counter */
    for (i = 1; i <= n; i++) {
        s->p[i] = i;
        s->size[i] = 1;
    }
    s->n = n;
}

int find(union_find *s, int x) {
    if (s->p[x] == x) {
        return (x);
    }
    return (find(s, s->p[x]));
}

void union_sets(union_find *s, int s1, int s2) {
    int r1, r2; /* roots of sets */
    r1 = find(s, s1);
    r2 = find(s, s2);
    if (r1 == r2) {
        return; /* already in same set */
    }
    if (s->size[r1] >= s->size[r2]) {
        s->size[r1] = s->size[r1] + s->size[r2];
        s->p[r2] = r1;
    } else {
        s->size[r2] = s->size[r1] + s->size[r2];
        s->p[r1] = r2;
    }
}

bool same_component(union_find *s, int s1, int s2) {
    return (find(s, s1) == find(s, s2));
}
```

## Shortest Paths
### Dijkstra's Algorithm
Starting from a particular vertex s, Dijkstra's finds the shortest path from s to all other vertices in the graph, including your desired destination t.

```
ShortestPath-Dijkstra(G, s, t)
	known = {s}
	for each vertex v in G, dist[v] = infinity
	dist[s] = 0
	for each edge (s, v), dist[v] = w(s, v)
	last = s
	while (last != t)
		select v_next, the unknown vertex minimizing dist[v]
		for each edge (vnext, x)
			dist[x] = min[dist[x], dist[v_next] + w(v_next, x)]
		last = v_next
		known = known ∪ {v_next}
```

Structurally, exactly the same as Prim's. The below implementation uses a priority queue.

```C++
void dijkstra(Graph *g, std::vector<int> **parent, std::vector<int> **distance, int start) {
    // convert to 0-based counting, conduct bounds check
    start -= 1;
    if (!g || !g->in_range(start)) {
        return; // start vertex not in graph
    }

    const int n = g->nnodes;
    std::vector<bool> visited(n, false);          /* has node n been visited? */
    *distance = new std::vector<int>(n, INT_MAX); /* shortest known dist from s to n */
    *parent = new std::vector<int>(n, -1); /* parent of node n in shortest path */

    using Item = std::pair<int, int>; // (distance, vertex)
    std::priority_queue<Item, std::vector<Item>, std::greater<Item>> pq;

    (**distance)[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        // pop closest unvisited node
        auto [dist_to_v, v] = pq.top();
        pq.pop();

        if (visited[v]) continue; // already visited
        if (dist_to_v != (**distance)[v]) continue; // stale entry

        visited[v] = true;

        // relax edges out of v
        for (Graph::Edgenode *p = g->edges[v]; p; p = p->next) {
            int w = p->dest;
            int dist_to_w = p->weight + dist_to_v;
            if (!visited[w] && dist_to_w < (**distance)[w]) {
                (**distance)[w] = dist_to_w;
                (**parent)[w] = v;
                pq.push({dist_to_w, w});
            }
        }
    }
}
```

### All-pairs shortest paths
- We may want to find the shortest path between all pairs of nodes
	- E.g. find the central node, find the diameter
- To do so, we could run Dijkstra's n times for $O(n^3)$
- But there is a simpler algorithm, still $O(n^3)$ that uses an adjacency matrix

**Floyd–Warshall**
- Takes a graph in the form of an [[Chapter 07 - Graph Traversal#Adjacency matrix|adjacency matrix]]
- To store all pairs shortest paths, we need $n^2$ space anyway, so this is fine
- Computes shortest path in place

```C
void floyd(adjacency_matrix *g) {
    int i, j;      /* dimension counters */
    int k;         /* intermediate vertex counter */
    int through_k; /* distance through vertex k */
    for (k = 1; k <= g->nvertices; k++) {
	    // generate matrix k:
	    // k = k-1
	    // then for all A[i,j], check if it is better to go through k
	    // A[i,j] = min( A[i,j], A[i,k]+A[k,j] )
        for (i = 1; i <= g->nvertices; i++) {
            for (j = 1; j <= g->nvertices; j++) {
                through_k = g->weight[i][k] + g->weight[k][j];
                if (through_k < g->weight[i][j]) {
                    g->weight[i][j] = through_k;
                }
            }
        }
    }
}
```

## Network Flows and Bipartite Matching
*Skipped*

## Randomised min-cut
- The minimum-cut problem in graphs seeks to partition the vertices of graph G into sets V1 and V2 so that the smallest possible number of edges (x,y) span across these two sets, meaning x ∈ V1 and y ∈ V2. 
- In other words, what is the minimum number of edges we can cut to disconnect the graph?
- Identifying the minimum cut often arises in network reliability analysis: what is the smallest failure set whose deletion will disconnect the graph?

*Skipped*

## Design graphs, not algorithms
Designing novel graph algorithms is very hard, so don’t do it. Instead, try to design graphs that enable you to use classical algorithms to model your problem. It is better to solve graph problems by designing a graph for an existing algorithm, rather than modifying or inventing an algorithm to fit a graph. 
e.g. The maximum spanning tree can be found by negating the edge weights of the input graph $G$ and using a minimum spanning tree algorithm on the result. The spanning tree of $-G$ that has the most negative weight will define the maximum-weight tree in $G$. 

### Examples

*Problem:* Need an algorithm to design natural routes for video-game characters to follow through an obstacle-filled room. 

*Solution:* Best option is to divide room into a grid, where accessible areas are vertices in the graph. Then use a shortest path algorithm like Dijkstra's.

---

*Problem:* Given an arbitrary set of rectangles in the plane, how can I distribute them into a minimum number of buckets such that no rectangles in any given bucket intersect one another? In other words, there cannot be any overlapping area between two rectangles in the same bucket.

*Solution:* We formulate a graph where each vertex represents a rectangle, and there is an edge if two rectangles intersect. Each bucket corresponds to an independent set (see Section 19.2 (page 589)) of rectangles, so there is no overlap between any two. A vertex colouring (see Section 19.7 (page 604)) of a graph is a partition of the vertices into independent sets, so minimising the number of colours is exactly what the problem is asking for.

---

*Problem:* We need a way to separate the lines of text in the optical character-recognition system that we are building. Although there is some white space between the lines, problems like noise and the tilt of the page make it hard to find. How can we do line segmentation? 

*Solution:* Consider the following graph formulation. Treat each pixel in the image as a vertex in the graph, with an edge between two neighbouring pixels. The weight of this edge should be proportional to how dark the pixels are. A segmentation between two lines is a path in this graph from the left to right side of the page. We seek a relatively straight path that avoids as much blackness as possible. This suggests that the shortest path in the pixel graph will likely find a good line segmentation.