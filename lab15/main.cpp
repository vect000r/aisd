#include "priorityQueue.hpp"

void testPriorityQueue() {
    PriorityQueue pq(10); 
    pq.add(1);
    pq.add(3);
    pq.add(5);
    pq.display(); // Expected output: Priority Queue: {1, 3, 5}
    
    pq.remove(3);
    pq.display(); // Expected output: Priority Queue: {1, 5}
    
    try {
        pq.add(10); // This should throw an exception
    } catch (const std::out_of_range& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}

int main() {
    testPriorityQueue();
    return 0;
}