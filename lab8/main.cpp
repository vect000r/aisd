#include "myqueue.hpp"
#include <iostream>

void runQueueTests() {
    std::cout << "Running Queue tests...\n";
    
    MyQueue<int> queue;

    std::cout << "Testing empty...\n";
    assert(queue.empty());
    assert(queue.size() == 0);
    
    std::cout << "Testing push and front...\n";
    queue.push(1);
    assert(!queue.empty());
    assert(queue.front() == 1);
    assert(queue.size() == 1);

    std::cout << "Testing multiple pushes...\n";
    queue.push(2);
    queue.push(3);
    assert(queue.front() == 1);
    assert(queue.size() == 3);

    std::cout << "Testing pop...\n";
    queue.pop();
    assert(queue.front() == 2);
    assert(queue.size() == 2);

    std::cout << "Testing clear...\n";
    queue.push(2);
    queue.push(3);
    queue.push(4);
    queue.push(5);
    queue.push(6);
    assert(queue.size() == 7);
    queue.clear();
    assert(queue.empty());

    std::cout << "\nAll tests passed successfully!\n";
}

int main() {
    try {
        runQueueTests();
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}