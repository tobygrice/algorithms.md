#ifndef HEAP_H
#define HEAP_H

#include <iostream>

class MinHeap {
private:
    int *data;
    int max_size;
    int n;

    void bubble_up(int curr_idx) {
        if (curr_idx == 0) return; // base case, at root
        int parent = (curr_idx - 1) / 2;
        int curr_key = data[curr_idx];
        if (data[parent] > curr_key) {
            // swap and recurse
            data[curr_idx] = data[parent];
            data[parent] = curr_key;
            bubble_up(parent);
        }
    }

    void bubble_down(int curr_idx) {
        int lchild = 2 * curr_idx + 1;
        int rchild = lchild + 1;

        int curr_key = data[curr_idx];

        int smallest_idx = curr_idx;
        if (lchild < n && data[lchild] < data[smallest_idx]) smallest_idx = lchild;
        if (rchild < n && data[rchild] < data[smallest_idx]) smallest_idx = rchild;

        if (smallest_idx != curr_idx && data[smallest_idx] < curr_key) {
            data[curr_idx] = data[smallest_idx];
            data[smallest_idx] = curr_key;
            bubble_down(smallest_idx);
        }
    }

public:
    MinHeap(int max_size) : data(new int[max_size]), max_size(max_size), n(0) {}
    ~MinHeap() { delete[] data; }

    void enqueue(int key) {
        if (n >= max_size) return; // full
        data[n] = key;
        bubble_up(n);
        n += 1;
    }

    int dequeue() {
        if (n == 0) exit(1);   // dequeue from empty heap
        int min = data[0];     // save min
        data[0] = data[--n];   // replace root with back and delete back
        bubble_down(0);
        return min;
    }

    void print_sorted() {
        while (n > 0) {
            std::cout << dequeue() << " ";
        }
        std::cout << std::endl;
    }
};

#endif

/*
int main(int argc, char** argv) {
    MinHeap mh(30);
    srand(time(NULL));

    for (int i = 0; i < 30; i++) {
        mh.enqueue(rand() % 100);
    }

    mh.print_sorted();

    return 0;
}
*/