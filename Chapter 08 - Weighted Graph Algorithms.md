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

