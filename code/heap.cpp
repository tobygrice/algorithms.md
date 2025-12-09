#include <iostream>
#include <cstdlib> // rand for testing

class MinHeap {
    private:
        int *data;
        int max_size;
        int n;

        void bubble_up(int key, int curr_idx) {
            if (curr_idx == 0) return; // base case, at root
            int parent = (curr_idx - 1) / 2;
            if (data[parent] > key) {
                // swap and recurse
                data[curr_idx] = data[parent];
                data[parent] = key;
                bubble_up(key, parent);
            }
        }

        void bubble_down(int key, int curr_idx) {
            int lchild = 2 * curr_idx + 1;
            int rchild = lchild + 1;

            int smallest_idx = curr_idx;
            if (lchild < n && data[lchild] < data[smallest_idx]) smallest_idx = lchild;
            if (rchild < n && data[rchild] < data[smallest_idx]) smallest_idx = rchild;

            if (smallest_idx != curr_idx && data[smallest_idx] < key) {
                data[curr_idx] = data[smallest_idx];
                data[smallest_idx] = key;
                bubble_down(key, smallest_idx);
            }
        }

    public:
        MinHeap(int max_size) : data(new int[max_size]), max_size(max_size), n(0) {}
        ~MinHeap() { delete [] data; }

        void enqueue(int key) {
            if (n + 1 > max_size) return; // full
            data[n] = key;
            bubble_up(key, n);
            n += 1;
        }

        int dequeue() {
            if (n == 0) exit(1); // dequeue from empty heap
            int min = data[0]; // save min
            data[0] = data[n-1]; // replace root with back
            n -= 1; // delete back element
            bubble_down(data[0], 0);
            return min;
        }

        void print_sorted() {
            while (n > 0) {
                std::cout << dequeue() << " ";
            }
            std::cout << std::endl;
        }
};

int main(int argc, char** argv) {
    MinHeap mh(30);
    srand(time(NULL));

    for (int i = 0; i < 30; i++) {
        mh.enqueue(rand() % 100);
    }

    mh.print_sorted();

    return 0;
}