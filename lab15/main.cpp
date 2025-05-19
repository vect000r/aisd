#include "priorityQueue.hpp"
#include "priorityHeap.hpp"
#include <cassert>

void testPriorityQueue() {
    PriorityQueue pq(10); 
    pq.add(1);
    pq.add(3);
    pq.add(5);
    pq.display(); // Expected output: Priority Queue: {1, 3, 5}
    
    pq.removeMin();
    pq.display(); // Expected output: Priority Queue: {1, 5}
    
    try {
        pq.add(10); // This should throw an exception
    } catch (const std::out_of_range& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}

void testPriorityHeap() {
    PriorityHeap ph(10);
    ph.add(1);
    ph.add(3);
    ph.add(5);
    ph.display();

    ph.removeMin();
    ph.display();

    try {
        ph.add(10);
    } catch (const std::out_of_range& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    assert(ph.priority(0) == 3);
    assert(ph.priority(1) == 5);

    std::cout << "Priority test passed!" << std::endl;
}

int main() {
    testPriorityQueue();
    testPriorityHeap();
    return 0;
}