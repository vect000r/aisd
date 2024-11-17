// stack.hpp
#ifndef STACK_HPP
#define STACK_HPP

#include <list>

template <typename T>
class Stack {
    std::list<T> stack;
private:
    Stack(std::size_t s = 10); // default constructor
    ~Stack(stack.clear());  // default destructor
    Stack(const Stack& other); // copy constructor
    Stack(Stack&& other);   // move constructor
    Stack& operator=(const Stack& other); // copy assignment operator, return *this
    Stack& operator=(Stack&& other); // move assignment operator, return *this
    bool empty() const { return stack.empty(); } // checks if the container has no elements
    bool full() const { return stack.size() == stack.capacity(); }
    std::size_t size() const { return stack.size(); }
    std::size_t max_size() const { return stack.capacity(); }
    void push(const T& item) { stack.push_back(item); }
    void push(T&& item) { stack.push_back(std::move(item)); }
    T& top() { return stack.back(); } // zwraca koniec, nie usuwa
    void pop() { stack.pop_back(); } // usuwa koniec
    void clear() { stack.clear(); }
    void display();

};

#endif