#include <iostream>

class Graph {
    private:
        struct Edgenode {
            int val;
            int weight;
            Edgenode* next;
        };
        Edgenode** edges;
        int* degree;
        int nedges;
        int nnodes;
        bool directed;
        
        bool in_range(int v) const { return v >= 0 && v < nnodes; }

        void insert_edge(int x, int y, bool directed) {
            if (!in_range(x) || !in_range(y)) return; // out-of-bounds guard
            Edgenode* new_edge = new Edgenode();
            new_edge->val = y;
            new_edge->weight = 0;
            new_edge->next = edges[x];

            edges[x] = new_edge;
            degree[x]++;

            if (!directed) {
                // add (y,x)
                insert_edge(y, x, true);
            } else {
                nedges++;
            }
        }
        
        void delete_edge(int x, int y, bool directed) {
            if (!in_range(x) || !in_range(y)) return; // out-of-bounds guard
            Edgenode* y_parent = edges[x];
            Edgenode* y_edge = edges[x];

            while (y_edge) {
                if (y_edge->val == y) {
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
                        delete_edge(y, x, true);
                    } else {
                        nedges--;
                    }
                    return;
                }
                y_parent = y_edge;
                y_edge = y_edge->next;
            }
        }

    public:
        // Non-copyable to avoid double-free (Rule of 3/5)
        Graph(const Graph&) = delete;
        Graph& operator=(const Graph&) = delete;

        Graph(int size, bool directed) : 
            edges(new Edgenode*[size + 1]()), // init to nullptr
            degree(new int[size + 1]()), // init to 0
            nedges(0),
            nnodes(size+1),
            directed(directed) {}

        ~Graph() {
            for (int i = 0; i < nnodes; ++i) {
                Edgenode* p = edges[i];
                while (p) {
                    Edgenode* next = p->next;
                    delete p;
                    p = next;
                }
            }
            delete [] edges;
            delete [] degree;
        }

        void insert_edge(int x, int y) { insert_edge(x, y, directed); }
        void delete_edge(int x, int y) { delete_edge(x, y, directed); }

        void print_graph() {
            for (int i = 0; i < nnodes; i++) {
                std::cout << i << ": ";
                Edgenode* n = edges[i];
                while (n) {
                    std::cout << n->val << " -> ";
                    n = n->next;
                }
                std::cout << std::endl;
            }
        }
};

int main(int argc, char* argv[]) {

    Graph g(5, false);

    g.insert_edge(1,2);
    g.insert_edge(1,5);
    g.insert_edge(2,5);
    g.insert_edge(2,4);
    g.insert_edge(5,4);
    g.insert_edge(3,2);
    g.insert_edge(3,4);

    g.print_graph();
    /*
        0: 
        1: 5 -> 2 ->
        2: 3 -> 4 -> 5 -> 1 ->
        3: 4 -> 2 ->
        4: 3 -> 5 -> 2 ->
        5: 4 -> 2 -> 1 ->
    */

    g.delete_edge(2,5); // delete edge in the middle of a list
    g.delete_edge(2,5); // deleting non-existent edge is fine
    g.delete_edge(2,1); // delete edge at the tail of a list
    g.delete_edge(2,3); // delete edge at the head of a list
    g.delete_edge(0,3); // delete edge from empty list

    g.print_graph();

    /*
        0: 
        1: 5 ->
        2: 4 ->
        3: 4 ->
        4: 3 -> 5 -> 2 ->
        5: 4 -> 1 ->
    */

    return 0;
}