#include "Graph.h"
#include <climits> // for INT_MAX
#include <queue>
#include <vector>

void dijkstra(Graph *g, std::vector<int> **parent, std::vector<int> **distance, int start) {
    // convert to 0-based counting, conduct bounds check
    start -= 1;
    if (!g || !g->in_range(start)) {
        return; // start vertex not in graph
    }

    const int n = g->nnodes;
    std::vector<bool> visited(n, false);          /* has node n been visited? */
    *distance = new std::vector<int>(n, INT_MAX); /* shortest known dist from s to n */
    *parent = new std::vector<int>(n, -1);        /* parent of node n in shortest path */

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

int main(int argc, char **argv) {

    Graph g(6, true); // directed graph with 6 vertices

    g.insert_edge(1, 2, 5);
    g.insert_edge(1, 3, 2);
    g.insert_edge(2, 3, 1);
    g.insert_edge(2, 4, 4);
    g.insert_edge(2, 5, 2);
    g.insert_edge(3, 5, 7);
    g.insert_edge(4, 5, 6);
    g.insert_edge(4, 6, 3);
    g.insert_edge(5, 6, 1);

    std::vector<int> *parent;
    std::vector<int> *distance;
    dijkstra(&g, &parent, &distance, 1);

    for (int i = 0; i < g.nnodes; i++) {
        std::cout << i + 1 << ": dist " << (*distance)[i] << ", parent " << (*parent)[i] + 1 << std::endl;
    }

    // EXPECTED:
    // 1: dist 0, parent 0
    // 2: dist 5, parent 1
    // 3: dist 2, parent 1
    // 4: dist 9, parent 2
    // 5: dist 7, parent 2
    // 6: dist 8, parent 5

    delete parent;

    return 0;
}