#include "deque.hpp"
#include <iostream>

int main() {
    Deque<int> deque1;

    // Test empty
    assert(deque1.empty());
    // Test push_front
    deque1.push_front(1);
    assert(deque1.front() == 1);
    // Test push_back
    deque1.push_back(2);
    assert(deque1.back() == 2);
    // Test pop_front
    deque1.pop_front();
    assert(deque1.front() == 2);
    // Test pop_back
    deque1.pop_back();
    assert(deque1.empty());
    // Test clear
    deque1.push_front(1);
    deque1.push_front(2);
    deque1.push_front(3);
    deque1.push_front(4);
    deque1.push_front(5);
    deque1.clear();
    assert(deque1.empty());
    // Test display
    deque1.push_back(1);
    deque1.push_back(2);
    deque1.push_back(3);
    deque1.push_back(4);
    deque1.push_back(5);
    deque1.display();
    // Test display_reverse
    deque1.display_reversed();
    // Test size
    assert(deque1.size() ==  5);

    std::cout << "All tests passed!";
}
