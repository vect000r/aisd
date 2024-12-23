#include "avl.hpp"

void runAVLTests() {
    std::cout << "Running AVL Tree tests...\n";

    AVLTree<int> avl;

    // Test empty on new tree
    std::cout << "Testing empty tree..." << std::endl;
    assert(avl.empty());


    // Test single element
    std::cout << "Testing single element..." << std::endl;
    avl.insert(10);
    assert(!avl.empty());
    assert(*avl.find_min() == 10);
    assert(*avl.find_max() == 10);

    // Test multiple inserts
    std::cout << "Testing multiple inserts..." << std::endl;
    avl.insert(5);
    avl.insert(15);
    avl.insert(3);
    avl.insert(7);
    avl.insert(12);
    avl.insert(17);
    assert(*avl.find_min() == 3);  // Should be smallest value
    assert(*avl.find_max() == 17); // Should be largest value

    // Test clear
    std::cout << "Testing clear..." << std::endl;
    avl.clear();
    assert(avl.empty());
    assert(avl.find_min() == nullptr);
    assert(avl.find_max() == nullptr);

    // Test tree with duplicate values
    std::cout << "Testing duplicate values..." << std::endl;
    avl.insert(10);
    avl.insert(10);
    avl.insert(5);
    avl.insert(5);
    assert(*avl.find_min() == 5);
    assert(*avl.find_max() == 10);

    // Test skewed tree (all left)
    std::cout << "Testing left-skewed tree..." << std::endl;
    AVLTree<int> leftSkewed;
    leftSkewed.insert(5);
    leftSkewed.insert(4);
    leftSkewed.insert(3);
    leftSkewed.insert(2);
    leftSkewed.insert(1);
    assert(*leftSkewed.find_min() == 1);
    assert(*leftSkewed.find_max() == 5);

    // Test skewed tree (all right)
    std::cout << "Testing right-skewed tree..." << std::endl;
    AVLTree<int> rightSkewed;
    rightSkewed.insert(1);
    rightSkewed.insert(2);
    rightSkewed.insert(3);
    rightSkewed.insert(4);
    rightSkewed.insert(5);
    assert(*rightSkewed.find_min() == 1);
    assert(*rightSkewed.find_max() == 5);

    // Test with negative numbers
    std::cout << "Testing negative numbers..." << std::endl;
    AVLTree<int> negativeTree;
    negativeTree.insert(-5);
    negativeTree.insert(-10);
    negativeTree.insert(-3);
    negativeTree.insert(-7);
    negativeTree.insert(-1);
    assert(*negativeTree.find_min() == -10);
    assert(*negativeTree.find_max() == -1);

    // Tests for is_valid
    // Left-heavy tree requiring rotation
    std::cout << "Testing validity of a left-heavy tree..." << std::endl;
    avl.insert(4);
    avl.insert(3);
    assert(avl.is_valid_avl());
        
    // Right-heavy tree requiring rotation
    std::cout << "Testing validity of a right-heavy tree..." << std::endl;
    avl.clear();
    avl.insert(10);
    avl.insert(15);
    avl.insert(20);
    assert(avl.is_valid_avl());
        
    // Complex tree with multiple rotations
    std::cout << "Testing validity of a complex tree requiring multiple rotations..." << std::endl;
    avl.clear();
    std::vector<int> values = {10, 20, 30, 40, 50, 25, 15, 5, 35};
    for (int val : values) {
        avl.insert(val);
        assert(avl.is_valid_avl());
    }
        
    // // Test after removals
    std::cout << "Testing validity after removals..." << std::endl;
    avl.remove(30);
    assert(avl.is_valid_avl());
    avl.remove(5);
    assert(avl.is_valid_avl());
        
    avl.clear();

    std::cout << "\nAll tests passed successfully!" << std::endl;
}

int main() {
    try {
        runAVLTests();
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}