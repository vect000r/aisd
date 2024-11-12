#ifndef DEQUE_HPP
#define DEQUE_HPP

#include "doublelist.hpp"

template <typename T>
class Deque {
private:
    DoubleList<T> list;

public:
    // Default constructor 
    Deque() = default;
    // Default destructor
    ~Deque() = default;
    
    // Copy constructor 
    Deque(const Deque& other);
    // Assignment operator
    Deque& operator=(const Deque& other);
    
    // Basic operations
    void push_front(const T& item);
    void push_back(const T& item);
    void pop_front();
    void pop_back();
    
    // Access elements
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    
    // Utility functions
    bool empty() const;
    std::size_t size() const;
    void clear();
    
    // Display functions
    void display() const;
    void display_reversed() const;
};

#endif // DEQUE_HPP