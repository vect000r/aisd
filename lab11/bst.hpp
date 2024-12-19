#ifndef BST_HPP
#define BST_HPP

#include <cassert>
#include <iostream>

template <typename T>
struct BSTNode {
    T value;
    BSTNode *left, *right;
    BSTNode() : value(T()), left(nullptr), right(nullptr) {}
    BSTNode(const T& item) : value(item), left(nullptr), right(nullptr) {}
    ~BSTNode() = default;
};

template <typename T>
class BinarySearchTree {
    BSTNode<T> *root;

public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree() { clear(); }
    
    void clear() { clear(root); root = nullptr; }
    bool empty() const { return root == nullptr; }
    
    void insert(const T& item) { root = insert(root, item); }
    
    T* find_min() {
        auto node = root;
        if (node == nullptr) return nullptr;
        while (node->left != nullptr) node = node->left;
        return &(node->value);
    }

    T* find_max() {
        auto node = root;
        if (node == nullptr) return nullptr;
        while (node->right != nullptr) node = node->right;
        return &(node->value);
    }
    
    void display() { 
        if (root == nullptr) {
            std::cout << "Empty tree" << std::endl;
            return;
        }
        displayRecursive(root, 0); 
    }

private:
    BSTNode<T>* insert(BSTNode<T>* node, const T& item) {
        if (node == nullptr) {
            return new BSTNode<T>(item);
        }
        if (item < node->value) {
            node->left = insert(node->left, item);
        } else {
            node->right = insert(node->right, item);
        }
        return node;
    }

    void clear(BSTNode<T>* node) {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    void displayRecursive(BSTNode<T>* node, int level) {
        if (node == nullptr) return;
        displayRecursive(node->right, level + 1);
        std::cout << std::string(level * 4, ' ') << node->value << std::endl;
        displayRecursive(node->left, level + 1);
    }
};

#endif