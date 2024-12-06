#include "tree.hpp"
#include <iostream>

int main() {
    RandomBinaryTree<int> tree;
    tree.insert(7);
    tree.insert(8);
    tree.insert(6);
    tree.insert(4);
    tree.insert(9);
    tree.insert(11);
    
    int leaves1 = tree.count_leaves();
    int leaves2 = tree.count_leaves_iter();

    std::cout << "Leaves count calculated recursively: " << leaves1 << std::endl;
    std::cout << "Leaves count calculated iteratively: " << leaves2 << std::endl;
}