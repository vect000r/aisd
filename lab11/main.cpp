#include "bst.hpp"

void runBSTTests() {
    std::cout << "Running Binary Search Tree tests...\n";

    BinarySearchTree<int> bst;

    // Test empty on new tree
    std::cout << "Testing empty tree..." << std::endl;
    assert(bst.empty());
    assert(bst.find_min() == nullptr);
    assert(bst.find_max() == nullptr);

    // Test single element
    std::cout << "Testing single element..." << std::endl;
    bst.insert(10);
    assert(!bst.empty());
    assert(*bst.find_min() == 10);
    assert(*bst.find_max() == 10);

    // Test multiple inserts
    std::cout << "Testing multiple inserts..." << std::endl;
    bst.insert(5);
    bst.insert(15);
    bst.insert(3);
    bst.insert(7);
    bst.insert(12);
    bst.insert(17);
    assert(*bst.find_min() == 3);  // Should be smallest value
    assert(*bst.find_max() == 17); // Should be largest value

    // Test clear
    std::cout << "Testing clear..." << std::endl;
    bst.clear();
    assert(bst.empty());
    assert(bst.find_min() == nullptr);
    assert(bst.find_max() == nullptr);

    // Test tree with duplicate values
    std::cout << "Testing duplicate values..." << std::endl;
    bst.insert(10);
    bst.insert(10);
    bst.insert(5);
    bst.insert(5);
    assert(*bst.find_min() == 5);
    assert(*bst.find_max() == 10);

    // Test skewed tree (all left)
    std::cout << "Testing left-skewed tree..." << std::endl;
    BinarySearchTree<int> leftSkewed;
    leftSkewed.insert(5);
    leftSkewed.insert(4);
    leftSkewed.insert(3);
    leftSkewed.insert(2);
    leftSkewed.insert(1);
    assert(*leftSkewed.find_min() == 1);
    assert(*leftSkewed.find_max() == 5);

    // Test skewed tree (all right)
    std::cout << "Testing right-skewed tree..." << std::endl;
    BinarySearchTree<int> rightSkewed;
    rightSkewed.insert(1);
    rightSkewed.insert(2);
    rightSkewed.insert(3);
    rightSkewed.insert(4);
    rightSkewed.insert(5);
    assert(*rightSkewed.find_min() == 1);
    assert(*rightSkewed.find_max() == 5);

    // Test with negative numbers
    std::cout << "Testing negative numbers..." << std::endl;
    BinarySearchTree<int> negativeTree;
    negativeTree.insert(-5);
    negativeTree.insert(-10);
    negativeTree.insert(-3);
    negativeTree.insert(-7);
    negativeTree.insert(-1);
    assert(*negativeTree.find_min() == -10);
    assert(*negativeTree.find_max() == -1);

    std::cout << "\nAll tests passed successfully!" << std::endl;
}

int main() {
    try {
        runBSTTests();
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}