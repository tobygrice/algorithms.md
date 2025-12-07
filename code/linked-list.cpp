#include <iostream>

class LinkedList {
    private:
        struct Node {
            int data;
            Node* next;

            Node(int val) : data(val), next(nullptr) {}
        };

        Node* head;

    public:
        LinkedList() : head(nullptr) {}
        LinkedList(int data) : head(new Node(data)) {}

        void insert(int insertion_val) {
            Node *new_head = new Node(insertion_val);
            new_head->next = head;
            head = new_head;
        }

        bool deletion(int target) {
            if (head == nullptr) {
                return false;
            }

            if (head->data == target) {
                Node* old_head = head;
                head = head->next;
                delete old_head;
                return true;
            }

            Node* n_pred = head;
            Node* n = head->next;
            while (n != nullptr) {
                if (n->data == target) {
                    n_pred->next = n->next;
                    delete n;
                    return true;
                }
                n_pred = n;
                n = n->next;
            }

            return false;
        }

        bool search(int target) {
            Node* n = head;
            while (n != nullptr) {
                if (n->data == target) {
                    return true;
                }
                n = n->next;
            }
            return false;
        }

        void print() {
            Node* n = head;
            while (n != nullptr) {
                std::cout << n->data << " ";
                n = n->next;
            }
            std::cout << std::endl;
        }

        ~LinkedList() {
            Node* n = head;
            while (n != nullptr) {
                Node* next = n->next;
                delete n;
                n = next;
            }
        }
};


int main(int argc, char* argv[]) {
    LinkedList ll(0);

    for (int i = 1; i < 10; i++) {
        ll.insert(i);
    }

    ll.print();

    // std::cout << ll.search(3) << std::endl; // true
    // std::cout << ll.search(11) << std::endl; // false

    std::cout << ll.deletion(3) << std::endl; // true
    std::cout << ll.deletion(9) << std::endl; // true
    std::cout << ll.deletion(10) << std::endl; // false

    ll.print();

    return 0;
}