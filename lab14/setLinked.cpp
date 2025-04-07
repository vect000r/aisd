#include "setLinked.hpp"

SetLinked::SetLinked(size_t N) {
    head = nullptr;
    universeSize = N;
}

void SetLinked::clear() {
    while(head != nullptr) {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
}

SetLinked::~SetLinked() {
    clear();
}

bool SetLinked::empty() const {
    return head == nullptr;
}

void SetLinked::insertSorted(int index) {
    Node* newNode = new Node(index);
    if (!head || head->index >= index) {
        newNode->next = head;
        head = newNode;
    } else {
        Node* current = head;
        while (current->next && current->next->index < index) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

void SetLinked::add(int index) {
    if (index < 0 || index >= static_cast<int>(universeSize)) {
        throw std::out_of_range("Index out of range");
    }
    
    // Case 1: Empty list or index belongs at the beginning
    if (!head || head->index > index) {
        Node* newNode = new Node(index);
        newNode->next = head;
        head = newNode;
        return;
    }
    
    // Case 2: If head's index is equal to the given index, element already exists
    if (head->index == index) {
        return; // Element already exists
    }
    
    // Case 3: Find the correct position
    Node* current = head;
    while (current->next && current->next->index < index) {
        current = current->next;
    }
    
    // Check if element already exists
    if (current->next && current->next->index == index) {
        return; // Element already exists
    }
    
    // Insert new node
    Node* newNode = new Node(index);
    newNode->next = current->next;
    current->next = newNode;
}

bool SetLinked::contains(int index) const {
    if (index < 0 || index >= static_cast<int>(universeSize)) {
        throw std::out_of_range("Index out of range");
    }
    
    Node* current = head;
    while (current && current->index <= index) {
        if (current->index == index) {
            return true;
        }
        current = current->next;
    }
    
    return false;
}

void SetLinked::remove(int index) {
    if (index < 0 || index >= static_cast<int>(universeSize)) {
        throw std::out_of_range("Index out of range");
    }

    if (head == nullptr) {
        return;
    }

    if (head->index == index) {
        Node *temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node *current = head;
    while (current->next != nullptr && current->next->index < index) {
        current = current->next;
    }

    if (current->next != nullptr && current->next->index == index) {
        Node *temp = current->next;
        current->next = temp->next;
        delete temp;
    }
}



// Optimized union operation with linear time complexity
SetLinked SetLinked::unionWith(const SetLinked& otherSet) const {
    if (universeSize != otherSet.universeSize) {
        throw std::invalid_argument("Universe sizes must be the same!");
    }

    SetLinked result(universeSize);
    Node* current1 = head;
    Node* current2 = otherSet.head;
    Node* tail = nullptr; // Tail pointer for the result list

    // Merge the two sorted lists in linear time
    while (current1 && current2) {
        Node* newNode = nullptr;
        
        if (current1->index < current2->index) {
            newNode = new Node(current1->index);
            current1 = current1->next;
        } else if (current2->index < current1->index) {
            newNode = new Node(current2->index);
            current2 = current2->next;
        } else { // Equal indices
            newNode = new Node(current1->index);
            current1 = current1->next;
            current2 = current2->next;
        }
        
        // Add to the result list
        if (!result.head) {
            result.head = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
    }

    // Add remaining elements from first set
    while (current1) {
        Node* newNode = new Node(current1->index);
        if (!result.head) {
            result.head = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
        current1 = current1->next;
    }

    // Add remaining elements from second set
    while (current2) {
        Node* newNode = new Node(current2->index);
        if (!result.head) {
            result.head = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
        current2 = current2->next;
    }

    return result;
}

// Optimized intersection operation with linear time complexity
SetLinked SetLinked::intersection(const SetLinked& otherSet) const {
    if (universeSize != otherSet.universeSize) {
        throw std::invalid_argument("Universe sizes must be the same!");
    }

    SetLinked result(universeSize);
    Node* current1 = head;
    Node* current2 = otherSet.head;

    // Process both lists simultaneously in linear time
    while (current1 && current2) {
        if (current1->index < current2->index) {
            current1 = current1->next;
        } else if (current2->index < current1->index) {
            current2 = current2->next;
        } else { // Equal indices - add to result
            result.insertSorted(current1->index);
            current1 = current1->next;
            current2 = current2->next;
        }
    }

    return result;
}

// Optimized difference operation with linear time complexity
SetLinked SetLinked::difference(const SetLinked& otherSet) const {
    if (universeSize != otherSet.universeSize) {
        throw std::invalid_argument("Universe sizes must be the same!");
    }

    SetLinked result(universeSize);
    Node* current1 = head;
    Node* current2 = otherSet.head;

    // Process both lists simultaneously in linear time
    while (current1 && current2) {
        if (current1->index < current2->index) {
            // Element in first set but not in second
            result.insertSorted(current1->index);
            current1 = current1->next;
        } else if (current2->index < current1->index) {
            // Skip elements in second set but not in first
            current2 = current2->next;
        } else { // Equal indices - skip both
            current1 = current1->next;
            current2 = current2->next;
        }
    }

    // Add remaining elements from first set
    while (current1) {
        result.insertSorted(current1->index);
        current1 = current1->next;
    }

    return result;
}

bool SetLinked::isIdentical(const SetLinked& otherSet) const {
    if (universeSize != otherSet.universeSize) {
        return false;
    }
        
    Node *current1 = head;
    Node *current2 = otherSet.head;
        
    while (current1 != nullptr && current2 != nullptr) {
        if (current1->index != current2->index) {
            return false;
        }
        current1 = current1->next;
        current2 = current2->next;
    }
        
    return (current1 == nullptr && current2 == nullptr);
}