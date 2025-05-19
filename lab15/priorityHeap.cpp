#include "priorityHeap.hpp"

// Helper function to maintain heap property by moving up
void PriorityHeap::percolateUp(size_t index) {
    // Keep going up the heap as long as the parent is greater than the current element
    while (index > 0 && heap[parent(index)] > heap[index]) {
        // Swap with parent
        std::swap(heap[index], heap[parent(index)]);
        // Move up to parent position
        index = parent(index);
    }
}

// Helper function to maintain heap property by moving down
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

// Get the priority (value) at given index
int PriorityHeap::priority(int index) const {
    if (index < 0 || index >= static_cast<int>(heap.size())) {
        throw std::out_of_range("Index out of range");
    }
    return heap[index];
}

// Add a new element to the priority queue
void PriorityHeap::add(int value) {
    if (isFull()) {
        throw std::overflow_error("Priority queue is full");
    }
    
    // Add the new element at the end of the heap
    heap.push_back(value);
    
    // Maintain the heap property by heapifying up
    percolateUp(heap.size() - 1);
}

// Remove and return the minimum element
int PriorityHeap::removeMin() {
    if (isEmpty()) {
        throw std::underflow_error("Priority queue is empty");
    }
    
    // The minimum element is at the root of the min-heap
    int min = heap[0];
    
    // Replace the root with the last element
    heap[0] = heap.back();
    heap.pop_back();
    
    // If the heap is not empty, maintain the heap property
    if (!isEmpty()) {
        percolateDown(0);
    }
    
    return min;
}

// Display the elements of the priority queue
void PriorityHeap::display() const {
    std::cout << "Priority Queue (heap): ";
    for (const auto& element : heap) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}