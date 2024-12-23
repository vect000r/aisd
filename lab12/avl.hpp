#ifndef AVL_HPP
#define AVL_HPP

#include <iostream>
#include <queue>
#include <cassert>
#include <algorithm>

// Implementacja oparta na tej z rosettacode.org i tej pokazanej na laboratoriach

template <typename T>
struct AVLNode {
    T value;
    int balance;
    AVLNode *left, *right, *parent;
    AVLNode() : value(T()), balance(0), left(nullptr), right(nullptr), parent(nullptr) {}
    AVLNode(const T& item, AVLNode *p) : value(item), balance(0), left(nullptr), right(nullptr), parent(p) {}
    ~AVLNode() { delete left; delete right; }
};

template <typename T>
class AVLTree {
    AVLNode<T>* root;

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() { clear(); }

    void clear() { delete root; root = nullptr; }
    bool empty() const { return root == nullptr; }
    T& top() { assert(root != nullptr); return root->value; }

    bool insert(const T& item) {
        if (root == nullptr) {
            root = new AVLNode<T>(item, nullptr);
            return true;
        }
        AVLNode<T>* parent = nullptr;
        AVLNode<T>* current = root;
        while (current != nullptr) {
            parent = current;
            if (item < current->value) {
                current = current->left;
            } else if (item > current->value) {
                current = current->right;
            } else {
                return false;
            }
        }
        AVLNode<T>* newNode = new AVLNode<T>(item, parent);
        if (item < parent->value) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
        update_balance_insert(newNode);
        return true;
    }

    void remove(const T& item) {
        AVLNode<T>* node = search(root, item);
        if (node == nullptr) return;

        AVLNode<T>* parent = node->parent;
        AVLNode<T>* balance_start = nullptr;

        if (node->left == nullptr || node->right == nullptr) {
            AVLNode<T>* child = (node->left != nullptr) ? node->left : node->right;
            balance_start = parent;

            if (parent == nullptr) {
                root = child;
            } else if (parent->left == node) {
                parent->left = child;
            } else {
                parent->right = child;
            }
            if (child != nullptr) {
                child->parent = parent;
            }
            node->left = node->right = nullptr;
            delete node;
        } else {
            AVLNode<T>* successor = node->right;
            while (successor->left != nullptr) {
                successor = successor->left;
            }
            balance_start = successor->parent;
            if (balance_start == node) {
                balance_start = successor;
            }
            
            node->value = successor->value;
            
            if (successor->parent->left == successor) {
                successor->parent->left = successor->right;
            } else {
                successor->parent->right = successor->right;
            }
            if (successor->right != nullptr) {
                successor->right->parent = successor->parent;
            }
            successor->left = successor->right = nullptr;
            delete successor;
        }

        if (balance_start != nullptr) {
            rebalance(balance_start);
        }
    }

    T* search(const T& item) const {
        auto ptr = search(root, item);
        return ((ptr == nullptr) ? nullptr : &(ptr->value));
    }

    void preorder() { preorder(root); }
    void inorder() { inorder(root); }
    void postorder() { postorder(root); }
    
    void bfs() {
        if (root == nullptr) return;
        std::queue<AVLNode<T>*> q;
        q.push(root);
        while (!q.empty()) {
            AVLNode<T>* node = q.front();
            q.pop();
            visit(node);
            if (node->left != nullptr) q.push(node->left);
            if (node->right != nullptr) q.push(node->right);
        }
    }

    T* find_max() { return find_max(root); }
    T* find_min() { return find_min(root); }
    
    void display() { display(root, 0); }
    
    virtual void visit(AVLNode<T> *node) {
        assert(node != nullptr);
        std::cout << "visiting " << node->value << std::endl;
    }
    
    bool is_valid_avl() const { return is_valid_avl(root).first; }

private:
    AVLNode<T>* search(AVLNode<T>* node, const T& item) const {
        if (node == nullptr || node->value == item) return node;
        if (item < node->value) return search(node->left, item);
        return search(node->right, item);
    }

    void preorder(AVLNode<T>* node) {
        if (node == nullptr) return;
        visit(node);
        preorder(node->left);
        preorder(node->right);
    }

    void inorder(AVLNode<T>* node) {
        if (node == nullptr) return;
        inorder(node->left);
        visit(node);
        inorder(node->right);
    }

    void postorder(AVLNode<T>* node) {
        if (node == nullptr) return;
        postorder(node->left);
        postorder(node->right);
        visit(node);
    }

    void display(AVLNode<T>* node, int depth) {
        if (node == nullptr) return;
        display(node->right, depth + 1);
        for (int i = 0; i < depth; ++i) std::cout << "    ";
        std::cout << node->value << std::endl;
        display(node->left, depth + 1);
    }

    std::pair<bool, int> is_valid_avl(AVLNode<T>* node) const {
        if (node == nullptr) return {true, 0};
        auto left = is_valid_avl(node->left);
        auto right = is_valid_avl(node->right);
        bool balanced = left.first && right.first && std::abs(left.second - right.second) <= 1;
        int height = std::max(left.second, right.second) + 1;
        return {balanced, height};
    }

    void update_balance_insert(AVLNode<T>* node) {
        while (node != nullptr) {
            updateHeight(node);
            if (std::abs(getBalance(node)) > 1) {
                rebalance(node);
                break;
            }
            node = node->parent;
        }
    }

    void rebalance(AVLNode<T>* node) {
        int balance = getBalance(node);
        
        if (balance > 1) {
            if (getBalance(node->right) < 0) {
                rotate_right(node->right);
            }
            rotate_left(node);
        }
        else if (balance < -1) {
            if (getBalance(node->left) > 0) {
                rotate_left(node->left);
            }
            rotate_right(node);
        }
    }

    int getHeight(AVLNode<T>* node) {
        if (node == nullptr) return 0;
        return std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    int getBalance(AVLNode<T>* node) {
        if (node == nullptr) return 0;
        return getHeight(node->right) - getHeight(node->left);
    }

    void updateHeight(AVLNode<T>* node) {
        if (node != nullptr) {
            node->balance = getBalance(node);
        }
    }

    void rotate_left(AVLNode<T>* node) {
        if (node == nullptr || node->right == nullptr) return;
        
        AVLNode<T>* rightChild = node->right;
        node->right = rightChild->left;
        
        if (rightChild->left != nullptr) {
            rightChild->left->parent = node;
        }
        
        rightChild->parent = node->parent;
        
        if (node->parent == nullptr) {
            root = rightChild;
        } else if (node == node->parent->left) {
            node->parent->left = rightChild;
        } else {
            node->parent->right = rightChild;
        }
        
        rightChild->left = node;
        node->parent = rightChild;
        
        updateHeight(node);
        updateHeight(rightChild);
    }

    void rotate_right(AVLNode<T>* node) {
        if (node == nullptr || node->left == nullptr) return;
        
        AVLNode<T>* leftChild = node->left;
        node->left = leftChild->right;
        
        if (leftChild->right != nullptr) {
            leftChild->right->parent = node;
        }
        
        leftChild->parent = node->parent;
        
        if (node->parent == nullptr) {
            root = leftChild;
        } else if (node == node->parent->right) {
            node->parent->right = leftChild;
        } else {
            node->parent->left = leftChild;
        }
        
        leftChild->right = node;
        node->parent = leftChild;
        
        updateHeight(node);
        updateHeight(leftChild);
    }

    T* find_max(AVLNode<T>* node) {
        if (node == nullptr) return nullptr;
        while (node->right != nullptr) {
            node = node->right;
        }
        return &(node->value);
    }

    T* find_min(AVLNode<T>* node) {
        if (node == nullptr) return nullptr;
        while (node->left != nullptr) {
            node = node->left;
        }
        return &(node->value);
    }
};

#endif