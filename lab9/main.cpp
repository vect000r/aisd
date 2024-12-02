#include <cassert>
#include <iostream>
#include "priorityqueue.hpp"

void runPriorityQueueTests() {
    std::cout << "Running priority queue tests...\n";

    MyPriorityQueue<int> pq;

    // Test empty on new queue
    std::cout << "Testing empty queue..." << std::endl;
    assert(pq.empty());
    assert(pq.size() == 0);

    // Test push and top
    std::cout << "Testing push and top..." << std::endl;
    pq.push(10);
    assert(!pq.empty());
    assert(pq.top() == 10);
    assert(pq.size() == 1);

    // Test multiple pushes
    std::cout << "Testing multiple pushes..." << std::endl;
    pq.push(20);
    pq.push(5);
    assert(pq.top() == 20); // Top should be the largest element
    assert(pq.size() == 3);

    // Test pop
    std::cout << "Testing pop..." << std::endl;
    pq.pop();
    assert(pq.top() == 10); // After popping 20, 10 is the largest
    pq.pop();
    assert(pq.top() == 5);
    assert(pq.size() == 1);

    // Test clear
    std::cout << "Testing clear..." << std::endl;
    pq.push(15);
    pq.push(25);
    pq.push(30);
    assert(pq.size() == 4);
    pq.clear();
    assert(pq.empty());

    // Test move semantics
    std::cout << "Testing move semantics..." << std::endl;
    MyPriorityQueue<int> pq2;
    pq2.push(50);
    pq2.push(60);
    assert(pq2.top() == 60);

    MyPriorityQueue<int> pq3 = std::move(pq2); // Move constructor
    assert(pq3.size() == 2);
    assert(pq3.top() == 60);
    assert(pq2.empty()); // pq2 should be empty after move

    MyPriorityQueue<int> pq4;
    pq4.push(100);
    pq4.push(200);
    pq4 = std::move(pq3); // Move assignment
    assert(pq4.size() == 2);
    assert(pq4.top() == 60);
    assert(pq3.empty()); // pq3 should be empty after move

    std::cout << "\nAll tests passed successfully!" << std::endl;
}

int main() {
    try {
        runPriorityQueueTests();
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
