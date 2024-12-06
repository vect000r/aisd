#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <cassert>
#include <stack>

template <typename T>
struct BSTNode {
    T val;
    BSTNode *left, *right;
    BSTNode() : val(T()), left(nullptr), right(nullptr) {}
    BSTNode(const T& item) : val(item), left(nullptr), right(nullptr) {}
    ~BSTNode() { delete left; delete right; }
};

template <typename T>
class RandomBinaryTree {
    BSTNode<T> *root;
public:
    RandomBinaryTree() : root(nullptr) {}
    ~RandomBinaryTree() { delete root; }
    void clear() { delete root; root = nullptr; }
    bool empty() const { return root == nullptr; }
    T& top() { assert(root != nullptr); return root->val; }
    BSTNode<T>* insert(BSTNode<T>* node, const T& item) {
        if (node == nullptr) {
            return new BSTNode<T>(item); // Tworzymy nowy węzeł, jeśli drzewo (lub poddrzewo) jest puste
        }
        if (item < node->val) {
            node->left = insert(node->left, item); // Wstawiamy do lewego poddrzewa
        } else {
            node->right = insert(node->right, item); // Wstawiamy do prawego poddrzewa
        }
        return node;
    }
    void insert(const T& item) { root = insert(root, item); }
    virtual void visit(BSTNode<T> *node) {
        assert(node != nullptr);
        std::cout << "visiting " << node->val << std::endl;
    }
    int calc_leaves(BSTNode<T> *node) {
        if (node == nullptr) {
            return 0; // Brak węzła to brak liści
        }
        if (node->left == nullptr && node->right == nullptr) {
            return 1; // Węzeł bez dzieci to liść
        }
        // Dodajemy wyniki z rekurencyjnych wywołań
        return calc_leaves(node->left) + calc_leaves(node->right);
    }

    int calc_leaves_iterative(BSTNode<T>* root) {
        if (root == nullptr) {
            return 0; // Jeśli drzewo jest puste, liczba liści to 0
        }

        int leaf_count = 0;
        std::stack<BSTNode<T>*> stack;
        stack.push(root);

        while (!stack.empty()) {
            BSTNode<T>* current = stack.top();
            stack.pop();

            // Jeśli węzeł jest liściem, zwiększamy licznik
            if (current->left == nullptr && current->right == nullptr) {
                ++leaf_count;
            } else {
                // Dodajemy dzieci do stosu, jeśli istnieją
                if (current->right != nullptr) {
                    stack.push(current->right);
                }
                if (current->left != nullptr) {
                    stack.push(current->left);
                }
            }
        }

        return leaf_count;
    }

    int count_leaves() {
        return calc_leaves(root);
    }

    int count_leaves_iter() {
        return calc_leaves_iterative(root);
    }
};

#endif