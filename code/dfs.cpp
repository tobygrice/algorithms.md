#include "Graph.h"

#include <iostream>

enum STATE { UNDISCOVERED, DISCOVERED, PROCESSED };

class DFS : public Graph {
private:
    STATE *state;
    int *entry;
    int *exit;
    int *parent;

    int time;

public:
    DFS(int size, bool directed)
        : Graph(size, directed),    // initialise base class first
          state(new STATE[nnodes]), // undiscovered, discovered, processed
          entry(new int[nnodes]),   // entry time
          exit(new int[nnodes]),    // exit time
          parent(new int[nnodes]),  // parent node
          time(0) {
        for (int i = 0; i < nnodes; i++) {
            state[i] = STATE::UNDISCOVERED;
            entry[i] = -1;
            exit[i] = -1;
            parent[i] = -1;
        }
    }

    ~DFS() {
        delete[] state;
        delete[] entry;
        delete[] exit;
        delete[] parent;
    }

    void search(int u) {
        if (!in_range(u) || state[u] != STATE::UNDISCOVERED) {
            return;
        }

        state[u] = STATE::DISCOVERED;
        entry[u] = ++time;

        process_vertex_early(u);

        for (Edgenode *next_edge = edges[u]; next_edge; next_edge = next_edge->next) {
            int v = next_edge->dest;
            if (!directed && parent[u] == v) continue; // skip edge back to parent in undirected graph

            process_edge(u, v);

            if (state[v] == STATE::UNDISCOVERED) {
                parent[v] = u;
                search(v);
            }
        }
        process_vertex_late(u);
        state[u] = STATE::PROCESSED;
        exit[u] = ++time;
    }

    void process_vertex_early(int u) {}
    void process_edge(int u, int v) {}
    void process_vertex_late(int u) {}
};

int main(int argc, char **argv) {
    DFS dfs(5, false);

    // Same example edges as before
    dfs.insert_edge(1, 2);
    dfs.insert_edge(1, 5);
    dfs.insert_edge(2, 5);
    dfs.insert_edge(2, 4);
    dfs.insert_edge(5, 4);
    dfs.insert_edge(3, 2);
    dfs.insert_edge(3, 4);

    std::cout << "Graph:\n";
    dfs.print_graph();

    return 0;
}

