#include <cassert>
#include <iostream>
#include <string>
#include "stack.hpp"

void runStackTests() {
    std::cout << "Running stack tests...\n";
    
    Stack<int> stack;
    
    // Test empty on new stack
    std::cout << "Testing empty stack..." << std::endl;
    assert(stack.empty());
    assert(stack.size() == 0);
    
    // Test push and top
    std::cout << "Testing push and top..." << std::endl;
    stack.push(1);
    assert(!stack.empty());
    assert(stack.top() == 1);
    assert(stack.size() == 1);
    
    // Test multiple pushes
    std::cout << "Testing multiple pushes..." << std::endl;
    stack.push(2);
    stack.push(3);
    assert(stack.top() == 3);
    assert(stack.size() == 3);
    
    // Test pop
    std::cout << "Testing pop..." << std::endl;
    stack.pop();
    assert(stack.top() == 2);
    stack.pop();
    assert(stack.top() == 1);
    assert(stack.size() == 1);
    
    // Test clear
    std::cout << "Testing clear..." << std::endl;
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);
    assert(stack.size() == 5);
    stack.clear();
    assert(stack.empty());
    
    std::cout << "\nAll tests passed successfully!" << std::endl;
}

int main() {
    try {
        runStackTests();
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}