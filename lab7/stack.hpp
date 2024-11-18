#ifndef STACK_HPP
#define STACK_HPP

#include <list>
#include <iostream>

template <typename T>
class Stack {
private:
    std::list<T> stack;

public:
    // Constructor
    explicit Stack(std::size_t s = 10) {} 
    
    // Destructor
    ~Stack() = default;
    
    // Copy constructor
    Stack(const Stack& other) : stack(other.stack) {}
    
    // Move constructor
    Stack(Stack&& other) noexcept : stack(std::move(other.stack)) {}
    
    // Copy assignment operator
    Stack& operator=(const Stack& other) {
        if (this != &other) {
            stack = other.stack;
        }
        return *this;
    }
    
    // Move assignment operator
    Stack& operator=(Stack&& other) noexcept {
        if (this != &other) {
            stack = std::move(other.stack);
        }
        return *this;
    }
    
    // Stack operations
    bool empty() const { return stack.empty(); }
    
    std::size_t size() const { return stack.size(); }
    
    void push(const T& item) { stack.push_back(item); }
    
    void push(T&& item) { stack.push_back(std::move(item)); }
    
    T& top() { 
        if (empty()) {
            throw std::runtime_error("Stack is empty");
        }
        return stack.back(); 
    }
    
    const T& top() const { 
        if (empty()) {
            throw std::runtime_error("Stack is empty");
        }
        return stack.back(); 
    }
    
    void pop() { 
        if (empty()) {
            throw std::runtime_error("Stack is empty");
        }
        stack.pop_back(); 
    }
    
    void clear() { stack.clear(); }
    
    void display() const {
        for (const auto& item : stack) {
            std::cout << '\t' << item;
        }
        std::cout << '\n';
    }
};

#endif