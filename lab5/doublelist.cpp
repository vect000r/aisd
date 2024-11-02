#include "doublelist.hpp"

template <typename T>
DoubleList<T>::DoubleList(const DoubleList& other) {
    head = tail = nullptr;
    DoubleNode<T> *node = other.head;
    while(node != nullptr) {
        push_back(node->value);
        node = node->next;
        node->prev = node;
    }
}

template <typename T>
DoubleList<T>& DoubleList<T>::operator=(const DoubleList& other) {
    if (this != &other) {
        while(!empty()) {
            pop_front();
        }
        DoubleNode<T> *node = other.head;
        while(node != nullptr) {
            push_back(node->value);
            node = node->next;
        }
    }
    return *this;
}

template <typename T>
std::size_t DoubleList<T>::size() const {
    std::size_t count = 0;
    DoubleNode<T> *node = head;
    while (node != nullptr) {
        ++count;
        node = node->next;
    }
    return count;
}

template <typename T>
void DoubleList<T>::push_back(const T& item) {
    if (empty()) {
        head = tail = new DoubleNode<T>(item);
    } else {
        tail = tail->next = new DoubleNode<T>(item, nullptr, tail);
    }
}

template <typename T>
void DoubleList<T>::pop_front() {
    assert(!empty());
    
    DoubleNode<T>* oldHead = head;  
    
    if (head == tail) {  
        head = tail = nullptr;
    } else {
        head = head->next;
        head->prev = nullptr; 
    }
    
    delete oldHead;
}

template <typename T>
void DoubleList<T>::pop_back() {
    assert(!empty());
    
    DoubleNode<T>* oldTail = tail;
    
    if (head == tail) {  
        head = tail = nullptr;
    } else {
        tail = tail->prev;  
        tail->next = nullptr;  
    }
    
    delete oldTail;
}

template <typename T>
void DoubleList<T>::clear() {
    while(!empty()) {
        pop_front();
    }
}

template <typename T>
void DoubleList<T>::display() {
    DoubleNode<T> *node = head;
    while(node != nullptr) {
        std::cout << node->value << " ";
        node = node->next;
    }
}

template <typename T>
void DoubleList<T>::display_reversed() {
    DoubleNode<T> *node = tail;
    while(node != nullptr) {
        std::cout << node->value << " ";
        node = node->prev;
    }
}

template <typename T>
DoubleList<T>::~DoubleList() {
    while(!empty()){
        pop_front();
    }
}

template class DoubleList<int>;