#include "Graph.h"

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