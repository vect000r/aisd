#include "priorityQueue.hpp"

int PriorityQueue::priority(int index) const {
    if (index < 0 || index >= queue.getUniverseSize()) {
        throw std::out_of_range("Index out of range");
    }
    return index;
}

void PriorityQueue::add(int index) {
    if (index < 0 || index >= queue.getUniverseSize()) {
        throw std::out_of_range("Index out of range");
    }
    queue.add(index);
}

int PriorityQueue::removeMin() {
    int minIndex = -1;
    
    for (size_t i = 0; i < queue.getUniverseSize(); i++) {
        if (queue.contains(static_cast<int>(i))) {
            minIndex = static_cast<int>(i);
            break;
        }
    }

    if (minIndex == -1) {
        throw std::runtime_error("Priority queue is empty");
    }

    queue.remove(minIndex);
    
    return minIndex;
}

void PriorityQueue::display() const {
    std::cout << "Priority Queue: {";
    bool first = true;
    for (size_t i = 0; i < queue.getUniverseSize(); i++) {
        if (queue.contains(static_cast<int>(i))) {
            if (!first) {
                std::cout << ", ";
            }
            std::cout << i;
            first = false;
        }
    }
    std::cout << "}" << std::endl;
}

bool PriorityQueue::isEmpty() const {
    return queue.empty();
}