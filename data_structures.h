#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

template <typename T>
struct Node {
    T item;
    Node<T>* next_node = nullptr;
};

template <typename T>
struct LinkedList {
    Node<T>* first_node = nullptr;
    Node<T>* last_node = nullptr;
    int size = 0;

    ~LinkedList() {
        Node<T>* current = first_node;
        while (current != nullptr) {
            Node<T>* next = current->next_node;
            delete current;
            current = next;
        }
    }

    void append(T item) {
        Node<T>* new_node = new Node<T>;
        new_node->item = item;

        if (first_node == nullptr) {
            first_node = new_node;
            last_node = new_node;
        } else {
            last_node->next_node = new_node;
            last_node = new_node;
        }

        size++;
    }

    Node<T>* get_node_at_index(int index) {
        if (index < 0 || index >= size) {
            return nullptr;
        }

        Node<T>* current = first_node;
        for (int i = 0; i < index; i++) {
            current = current->next_node;
        }

        return current;
    }

    void set_index(int index, T item) {
        Node<T>* node = get_node_at_index(index);
        if (node != nullptr) {
            node->item = item;
        }
    }
};

template <typename T>
struct TreeNode {
    T item;
    TreeNode<T>* left = nullptr;
    TreeNode<T>* right = nullptr;
    int height = 1;
};

template <typename T>
struct AVLTree {
    TreeNode<T>* root = nullptr;

    ~AVLTree() {
        destroy(root);
    }

    void build_from_sorted_array(T arr[], int size) {
        destroy(root);
        root = build_balanced(arr, 0, size - 1);
    }

    bool remove(T item) {
        bool removed = false;
        root = remove_node(root, item, removed);
        return removed;
    }

    T* least_over(T threshold) {
        TreeNode<T>* current = root;
        TreeNode<T>* best = nullptr;

        while (current != nullptr) {
            if (threshold < current->item) {
                best = current;
                current = current->left;
            } else {
                current = current->right;
            }
        }

        if (best == nullptr) {
            return nullptr;
        }

        return &best->item;
    }

private:
    void destroy(TreeNode<T>* node) {
        if (node == nullptr) {
            return;
        }

        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    TreeNode<T>* build_balanced(T arr[], int left, int right) {
        if (left > right) {
            return nullptr;
        }

        int mid = left + (right - left) / 2;
        TreeNode<T>* node = new TreeNode<T>;
        node->item = arr[mid];
        node->left = build_balanced(arr, left, mid - 1);
        node->right = build_balanced(arr, mid + 1, right);
        update_height(node);
        return node;
    }

    int height(TreeNode<T>* node) {
        if (node == nullptr) {
            return 0;
        }

        return node->height;
    }

    int max_value(int a, int b) {
        if (a > b) {
            return a;
        }

        return b;
    }

    void update_height(TreeNode<T>* node) {
        if (node != nullptr) {
            node->height = 1 + max_value(height(node->left), height(node->right));
        }
    }

    int balance_factor(TreeNode<T>* node) {
        if (node == nullptr) {
            return 0;
        }

        return height(node->left) - height(node->right);
    }

    TreeNode<T>* rotate_right(TreeNode<T>* node) {
        TreeNode<T>* new_root = node->left;
        TreeNode<T>* moved_subtree = new_root->right;

        new_root->right = node;
        node->left = moved_subtree;

        update_height(node);
        update_height(new_root);

        return new_root;
    }

    TreeNode<T>* rotate_left(TreeNode<T>* node) {
        TreeNode<T>* new_root = node->right;
        TreeNode<T>* moved_subtree = new_root->left;

        new_root->left = node;
        node->right = moved_subtree;

        update_height(node);
        update_height(new_root);

        return new_root;
    }

    TreeNode<T>* rebalance(TreeNode<T>* node) {
        if (node == nullptr) {
            return nullptr;
        }

        update_height(node);
        int balance = balance_factor(node);

        if (balance > 1) {
            if (balance_factor(node->left) < 0) {
                node->left = rotate_left(node->left);
            }
            return rotate_right(node);
        }

        if (balance < -1) {
            if (balance_factor(node->right) > 0) {
                node->right = rotate_right(node->right);
            }
            return rotate_left(node);
        }

        return node;
    }

    TreeNode<T>* min_node(TreeNode<T>* node) {
        TreeNode<T>* current = node;
        while (current != nullptr && current->left != nullptr) {
            current = current->left;
        }

        return current;
    }

    TreeNode<T>* remove_node(TreeNode<T>* node, T item, bool& removed) {
        if (node == nullptr) {
            return nullptr;
        }

        if (item < node->item) {
            node->left = remove_node(node->left, item, removed);
        } else if (node->item < item) {
            node->right = remove_node(node->right, item, removed);
        } else {
            removed = true;

            if (node->left == nullptr || node->right == nullptr) {
                TreeNode<T>* child = node->left;
                if (child == nullptr) {
                    child = node->right;
                }

                delete node;
                return child;
            }

            TreeNode<T>* successor = min_node(node->right);
            node->item = successor->item;
            bool ignored = false;
            node->right = remove_node(node->right, successor->item, ignored);
        }

        return rebalance(node);
    }
};

#endif