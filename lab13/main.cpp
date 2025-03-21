#include <iostream>
#include <cassert>
#include <string>
#include "dictionarySimple.hpp"
#include "setSimple.hpp"
#include "setLinked.hpp"

void testDictionarySimple() {
    std::cout << "Testing dictionarySimple..." << std::endl;
    
    dictionarySimple dict;
    
    // Test isEmpty
    assert(dict.isEmpty() == true);
    assert(dict.getSize() == 0);
    
    // Test insert and contains
    dict.insert("apple");
    assert(dict.contains("apple") == true);
    assert(dict.contains("banana") == false);
    assert(dict.isEmpty() == false);
    assert(dict.getSize() == 1);
    
    // Test duplicate insert
    dict.insert("apple");
    assert(dict.getSize() == 1);
    
    // Test multiple inserts
    dict.insert("banana");
    dict.insert("cherry");
    assert(dict.getSize() == 3);
    assert(dict.contains("banana") == true);
    assert(dict.contains("cherry") == true);
    
    // Test remove
    dict.remove("banana");
    assert(dict.contains("banana") == false);
    assert(dict.getSize() == 2);
    assert(dict.contains("apple") == true);
    assert(dict.contains("cherry") == true);
    
    // Test removing non-existent element
    dict.remove("orange");
    assert(dict.getSize() == 2);
    
    // Test removing all elements
    dict.remove("apple");
    dict.remove("cherry");
    assert(dict.isEmpty() == true);
    assert(dict.getSize() == 0);
    
    std::cout << "dictionarySimple tests passed!" << std::endl;
}

void testSetSimple() {
    std::cout << "Testing SetSimple..." << std::endl;
    
    const size_t universeSize = 10;
    SetSimple set1(universeSize);
    SetSimple set2(universeSize);
    
    // Test empty set
    for (size_t i = 0; i < universeSize; i++) {
        assert(set1.contains(i) == false);
    }
    
    // Test add and contains
    set1.add(3);
    set1.add(5);
    set1.add(7);
    assert(set1.contains(3) == true);
    assert(set1.contains(5) == true);
    assert(set1.contains(7) == true);
    assert(set1.contains(0) == false);
    
    // Test remove
    set1.remove(5);
    assert(set1.contains(5) == false);
    assert(set1.contains(3) == true);
    
    // Test set operations
    set2.add(2);
    set2.add(3);
    set2.add(4);
    
    // Union
    SetSimple unionSet = set1.unionWith(set2);
    assert(unionSet.contains(2) == true);
    assert(unionSet.contains(3) == true);
    assert(unionSet.contains(4) == true);
    assert(unionSet.contains(7) == true);
    assert(unionSet.contains(5) == false);
    
    // Intersection
    SetSimple intersectionSet = set1.intersection(set2);
    assert(intersectionSet.contains(3) == true);
    assert(intersectionSet.contains(2) == false);
    assert(intersectionSet.contains(7) == false);
    
    // Difference
    SetSimple differenceSet = set1.difference(set2);
    assert(differenceSet.contains(7) == true);
    assert(differenceSet.contains(3) == false);
    
    // Identity
    SetSimple set3(universeSize);
    set3.add(3);
    set3.add(7);
    
    assert(set1.isIdentical(set3) == true);
    assert(set1.isIdentical(set2) == false);
    
    std::cout << "SetSimple tests passed!" << std::endl;
}

void testSetLinked() {
    std::cout << "Testing SetLinked..." << std::endl;
    
    const size_t universeSize = 10;
    SetLinked set1(universeSize);
    SetLinked set2(universeSize);
    
    // Test empty set
    assert(set1.empty() == true);
    assert(set1.contains(0) == false);
    
    // Test add and contains
    set1.add(3);
    set1.add(5);
    set1.add(7);
    assert(set1.contains(3) == true);
    assert(set1.contains(5) == true);
    assert(set1.contains(7) == true);
    assert(set1.contains(0) == false);
    assert(set1.empty() == false);
    
    // Test remove
    set1.remove(5);
    assert(set1.contains(5) == false);
    assert(set1.contains(3) == true);
    
    // Test set operations
    set2.add(2);
    set2.add(3);
    set2.add(4);
    
    // Union
    SetLinked unionSet = set1.unionWith(set2);
    assert(unionSet.contains(2) == true);
    assert(unionSet.contains(3) == true);
    assert(unionSet.contains(4) == true);
    assert(unionSet.contains(7) == true);
    assert(unionSet.contains(5) == false);
    
    // Intersection
    SetLinked intersectionSet = set1.intersection(set2);
    assert(intersectionSet.contains(3) == true);
    assert(intersectionSet.contains(2) == false);
    assert(intersectionSet.contains(7) == false);
    
    // Difference
    SetLinked differenceSet = set1.difference(set2);
    assert(differenceSet.contains(7) == true);
    assert(differenceSet.contains(3) == false);
    
    // Identity
    SetLinked set3(universeSize);
    set3.add(3);
    set3.add(7);
    
    assert(set1.isIdentical(set3) == true);
    assert(set1.isIdentical(set2) == false);
    
    // Test clear
    set1.clear();
    assert(set1.empty() == true);
    assert(set1.contains(3) == false);
    
    std::cout << "SetLinked tests passed!" << std::endl;
}

int main() {
    try {
        testDictionarySimple();
        testSetSimple();
        testSetLinked();
        
        std::cout << "All tests passed successfully!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return 1;
    }
}