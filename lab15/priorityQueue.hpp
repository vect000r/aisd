#ifndef PRIORITYQUEUE_HPP
#define PRIORITYQUEUE_HPP

#include <iostream>
#include <vector>
#include <stdexcept>
#include "../lab13/setSimple.hpp"

class PriorityQueue {
private:
    SetSimple queue;
public:
    PriorityQueue(size_t N) : queue(N) {} 
    ~PriorityQueue() = default;
    int priority(int index) const;
    void add(int index);
    int removeMin();
    void display() const;
    bool isEmpty() const;
};


#endif