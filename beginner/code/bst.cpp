#include <iostream>

class BST {
    public:
        struct Node {
            Node* parent;
            Node* left;
            Node* right;
            int key;
            Node(int key) : parent(nullptr), left(nullptr), right(nullptr), key(key) {}
        };
    
    private:
        Node* root;

        Node* recursive_search(int key, Node* node) const {
            if (!node) {
                return nullptr; // not found
            }
            if (key < node->key) {
                return recursive_search(key, node->left);
            }
            if (key > node->key) {
                return recursive_search(key, node->right);
            }
            return node; // key == node
        }

        Node* recursive_insert(int key, Node* node_parent, Node* node) {
            if (!node) {
                Node* new_node = new Node(key);
                new_node->parent = node_parent; 
                // node_parent cannot be nullptr here as we check root exists in insert_key function
                if (key < node_parent->key) {
                    node_parent->left = new_node;
                } else {
                    node_parent->right = new_node;
                }
                return new_node;
            }
            if (key < node->key) {
                return recursive_insert(key, node, node->left);
            }
            if (key > node->key) {
                return recursive_insert(key, node, node->right);
            }
            return node; // key == node (don't allow duplicate keys)
        }

        void recursive_print(Node* node) const {
            if (!node) return;
            recursive_print(node->left);
            std::cout << node->key << " ";
            recursive_print(node->right);
        }

        void recursive_delete(Node* node) {
            if (!node) return;
            recursive_delete(node->left);
            recursive_delete(node->right);
            delete node;
        }

    public:
        BST() : root(nullptr) {} // note: always initialise member vars to something
        BST(int key) : root(new Node(key)) {}
        ~BST() { recursive_delete(root); }

        // prevent copy, otherwise shallow copy will lead to double free
        BST(const BST&) = delete;
        BST& operator=(const BST&) = delete;

        Node* search_key(int key) const {
            return recursive_search(key, root);
        }
        Node* insert_key(int key) {
            if (!root) {
                root = new Node(key);
                return root;
            } else {
                return recursive_insert(key, nullptr, root);
            }
        }
        void print() const {
            recursive_print(root);
            std::cout << std::endl;
        }
        bool delete_key(int key) {
            Node* to_delete = this->search_key(key);
            return delete_node(to_delete);
        }
        bool delete_node(Node* to_delete) {
            if (!to_delete) {
                return false; // not in tree
            }
            
            // note: maintaining parent ref is nice. For root, set parent to root
            Node** parent_ref = &root; // ptr to parent's reference to to_delete
            if (to_delete != root) {
                if (to_delete->parent->left == to_delete) {
                parent_ref = &to_delete->parent->left;
                } else {
                    parent_ref = &to_delete->parent->right;
                }
            }
            
            // note: had issues here, by far easiest to *keep* the target node and 
            // replace key with successor, then delete successor node recursively.
            if (to_delete->left && to_delete->right) {
                // two children
                Node* successor = to_delete->right;
                while (successor->left) {
                    successor = successor->left;
                }
                to_delete->key = successor->key;
                return delete_node(successor); // will have 0 or 1 child (leftmost node in subtree)
            }
            
            // update parent ref with new child
            // note: remember to update target's children with new parent
            if (to_delete->left) {
                // left child only
                *parent_ref = to_delete->left;
                to_delete->left->parent = to_delete->parent;
            } else if (to_delete->right) {
                // right child only
                *parent_ref = to_delete->right;
                to_delete->right->parent = to_delete->parent;
            } else {
                // no children
                *parent_ref = nullptr;
            }
            delete to_delete;
            return true;
        }
};

int main(int argc, char** argv) {
    BST tree; 

    return 0;
}