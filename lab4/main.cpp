#include "singlelist.hpp"

int main() {
    SingleList<int> list1;
    
    // Test empty
    assert(list1.empty());
    // Test push_front
    list1.push_front(1);
    assert(list1.front() == 1);
    // Test push_back
    list1.push_back(2);
    assert(list1.back() == 2);
    // Test pop_front
    list1.pop_front();
    assert(list1.front() == 2);
    // Test pop_back
    list1.pop_back();
    assert(list1.empty());
    // Test clear
    list1.push_front(1);
    list1.push_front(2);
    list1.push_front(3);
    list1.push_front(4);
    list1.push_front(5);
    list1.clear();
    assert(list1.empty());
    // Test display
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);
    list1.push_back(4);
    list1.push_back(5);
    list1.display();
    // Test reverse
    list1.reverse();
    assert(list1.front() == 5);
    list1.display();
    // Test size
    assert(list1.size() ==  5);
    
    std::cout << "All tests passed!";
}