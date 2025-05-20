#include "priorityHeap.hpp"


void PriorityHeap::percolateUp(size_t index) {
    // Keep going up the heap as long as the parent is greater than the current element
    while (index > 0 && heap[parent(index)] > heap[index]) {
        // Swap with parent
        std::swap(heap[index], heap[parent(index)]);
        // Move up to parent position
        index = parent(index);
    }
}


void PriorityHeap::percolateDown(size_t index) {
    size_t smallest = index;
    size_t left = leftChild(index);
    size_t right = rightChild(index);
    size_t heapSize = heap.size();

    // Check if left child is smaller than current smallest
    if (left < heapSize && heap[left] < heap[smallest]) {
        smallest = left;
    }

    // Check if right child is smaller than current smallest
    if (right < heapSize && heap[right] < heap[smallest]) {
        smallest = right;
    }

    // If one of the children is smaller, swap and continue heapifying down
    if (smallest != index) {
        std::swap(heap[index], heap[smallest]);
        percolateDown(smallest);
    }
}


int PriorityHeap::priority(int index) const {
    if (index < 0 || index >= static_cast<int>(heap.size())) {
        throw std::out_of_range("Index out of range");
    }
    return heap[index];
}


void PriorityHeap::add(int value) {
    if (isFull()) {
        throw std::overflow_error("Priority queue is full");
    }
    
    heap.push_back(value);
    
    percolateUp(heap.size() - 1);
}

int PriorityHeap::removeMin() {
    if (isEmpty()) {
        throw std::underflow_error("Priority queue is empty");
    }
    
    int min = heap[0];
    
    heap[0] = heap.back();
    heap.pop_back();
    
    if (!isEmpty()) {
        percolateDown(0);
    }
    
    return min;
}

void PriorityHeap::display() const {
    std::cout << "Priority Queue (heap): ";
    for (const auto& element : heap) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}