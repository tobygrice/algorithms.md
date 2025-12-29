#include "Graph.h"
#include <iostream>
#include <queue>
#include <vector>

enum STATE { UNDISCOVERED, DISCOVERED, PROCESSED };

void process_vertex_early(int u) {}
void process_edge(int u, int v) {}
void process_vertex_late(int u) {}

void bfs(Graph *g, std::vector<int> **parent, int start) {
    start -= 1;
    if (!g->in_range(start)) return;
    if (!g || !parent) return;

    int n = g->nnodes;
    std::vector<STATE> state(n, STATE::UNDISCOVERED); /* holds state of node n */
    *parent = new std::vector<int>(n, -1); /* parent of node n in shortest path */
    std::queue<int> q; /* holds discovered nodes */

    state[start] = STATE::DISCOVERED;
    q.push(start);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        process_vertex_early(u);

        for (Graph::Edgenode* e = g->edges[u]; e != nullptr; e = e->next) {
            int v = e->dest;
            process_edge(u, v);
            if (state[v] == STATE::UNDISCOVERED) {
                state[v] = STATE::DISCOVERED;
                (**parent)[v] = u;
                q.push(v);
            }
        }

        process_vertex_late(u);
        state[u] = STATE::PROCESSED;
    }
}

int main(int argc, char **argv) {
    Graph g(5, false);

    // Same example edges as before
    g.insert_edge(1, 2);
    g.insert_edge(1, 5);
    g.insert_edge(2, 5);
    g.insert_edge(2, 4);
    g.insert_edge(5, 4);
    g.insert_edge(3, 2);
    g.insert_edge(3, 4);

    std::cout << "Graph:\n";
    g.print_graph();

    std::vector<int> *parent = nullptr;
    bfs(&g, &parent, 1);

    delete parent;

    return 0;
}