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
