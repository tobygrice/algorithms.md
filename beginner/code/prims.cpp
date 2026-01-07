#include "Graph.h"
#include <climits> // for INT_MAX
#include <vector>
#include <queue>

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
    
    using Item = std::pair<int, int>; // (distance/key, vertex)
    std::priority_queue<Item, std::vector<Item>, std::greater<Item>> pq;

    distance[start] = 0;
    pq.push({0, start});
    int total_weight = 0;

    while (!pq.empty()) {
        // pick next vertex to add
        // v is closest vertex, best is distance to v
        auto [best, v] = pq.top();
        pq.pop();

        if (intree[v]) continue;
        if (best != distance[v]) continue;

        intree[v] = true;

        // add chosen edge to MST (skip root)
        if (parent[v] != -1) {
            (*mst)->insert_edge(parent[v] + 1, v + 1, best);
            total_weight += best;
        }

        // relax edges out of v
        for (Graph::Edgenode *p = g->edges[v]; p; p = p->next) {
            int w = p->dest;
            if (!intree[w] && p->weight < distance[w]) {
                distance[w] = p->weight;
                parent[w] = v;
                pq.push({distance[w], w});
            }
        }
    }

    return total_weight;
}

int main(int argc, char **argv) {

    Graph g(7, false);

    g.insert_edge(1, 2, 5);
    g.insert_edge(2, 3, 7);
    g.insert_edge(3, 4, 5);
    g.insert_edge(4, 5, 2);
    g.insert_edge(5, 6, 7);
    g.insert_edge(6, 1, 12);
    g.insert_edge(3, 5, 2);
    g.insert_edge(1, 7, 7);
    g.insert_edge(2, 7, 9);
    g.insert_edge(3, 7, 4);
    g.insert_edge(5, 7, 3);
    g.insert_edge(6, 7, 4);

    Graph *mst = nullptr;
    int weight = prims(&g, &mst, 1);

    std::cout << "MST weight = " << weight << std::endl;
    mst->print_graph();

    delete mst;

    return 0;
}