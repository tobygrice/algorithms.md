#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>

/**
 * Graph with 1-based vertex counting (vertices start at 1).
 * Requires `size` (number of nodes) and `directed` boolean to instantiate.
 * Implemented using adjacency list.
 */
class Graph {
  public:
    struct Edgenode {
        int dest;
        int weight;
        Edgenode *next;
    };
    Edgenode **edges;
    int *degree;
    int nedges;
    int nnodes;
    bool directed;

    Graph(const Graph &) = delete;
    Graph &operator=(const Graph &) = delete;

    Graph(int size, bool directed)
        : edges(new Edgenode *[size]()), // init to nullptr
          degree(new int[size]()),       // init to 0
          nedges(0), nnodes(size), directed(directed) {}

    virtual ~Graph() {
        for (int i = 0; i < nnodes; ++i) {
            Edgenode *p = edges[i];
            while (p) {
                Edgenode *next = p->next;
                delete p;
                p = next;
            }
        }
        delete[] edges;
        delete[] degree;
    }

    void insert_edge(int x, int y, int weight) {
        insert_edge_recursive(x - 1, y - 1, weight, directed);
    }
    void insert_edge(int x, int y) {
        insert_edge_recursive(x - 1, y - 1, 0, directed);
    } // assume unweighted
    void delete_edge(int x, int y) {
        delete_edge_recursive(x - 1, y - 1, directed);
    }

    void print_graph() {
        for (int i = 0; i < nnodes; i++) {
            std::cout << i + 1 << ": ";
            Edgenode *n = edges[i];
            while (n) {
                std::cout << "-(" << n->weight << ")-> " << n->dest + 1 << ", ";
                n = n->next;
            }
            std::cout << std::endl;
        }
    }

    bool in_range(int v) const { return v >= 0 && v < nnodes; }
  private:

    void insert_edge_recursive(int x, int y, int weight, bool directed) {
        if (!in_range(x) || !in_range(y))
            return; // out-of-bounds guard
        Edgenode *new_edge = new Edgenode();
        new_edge->dest = y;
        new_edge->weight = weight;
        new_edge->next = edges[x];

        edges[x] = new_edge;
        degree[x]++;

        if (!directed) {
            // add (y,x)
            insert_edge_recursive(y, x, weight, true);
        } else {
            nedges++;
        }
    }

    void delete_edge_recursive(int x, int y, bool directed) {
        if (!in_range(x) || !in_range(y))
            return; // out-of-bounds guard
        Edgenode *y_parent = edges[x];
        Edgenode *y_edge = edges[x];

        while (y_edge) {
            if (y_edge->dest == y) {
                // delete y_edge
                if (y_parent == y_edge) {
                    edges[x] = y_edge->next; // y_edge is head of adjacency list
                } else {
                    y_parent->next = y_edge->next;
                }
                delete y_edge;
                degree[x]--;
                if (!directed) {
                    // delete (y,x)
                    delete_edge_recursive(y, x, true);
                } else {
                    nedges--;
                }
                return;
            }
            y_parent = y_edge;
            y_edge = y_edge->next;
        }
    }
};

#endif // GRAPH_H