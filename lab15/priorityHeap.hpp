#ifndef PRIORITYHEAP_HPP
#define PRIORITYHEAP_HPP
#include <iostream>
#include <vector>
#include <stdexcept>

class PriorityHeap {
private:
    std::vector<int> heap; 
    size_t capacity;       
    
    size_t parent(size_t index) const { return (index - 1) / 2; }
    size_t leftChild(size_t index) const { return 2 * index + 1; }
    size_t rightChild(size_t index) const { return 2 * index + 2; }
    
    void percolateUp(size_t index);
    void percolateDown(size_t index);

public:
    PriorityHeap(size_t N) : capacity(N) { 
        heap.reserve(N);
    }
    
    ~PriorityHeap() = default;
    
    int priority(int index) const;
    void add(int value);
    int removeMin();
    bool isEmpty() const { return heap.empty(); }
    bool isFull() const { return heap.size() >= capacity; }
    void display() const;
};
#endif