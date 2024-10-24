#include "singlelist.hpp"



template <typename T>
SingleList<T>::SingleList(const SingleList& other) {
    head = tail = nullptr;
    
    SingleNode<T> *node = other.head;
    while (node != nullptr) {
        push_back(node->value);
        node = node->next;
    }
}

template <typename T>
SingleList<T>& SingleList<T>::operator=(const SingleList& other) {
    if (this != &other) {
        while (!empty()) {
            pop_front();
        }
        SingleNode<T> *node = other.head;
        while (node != nullptr) {
            push_back(node->value);
            node = node->next;
        }
    }
    return *this;
}

template <typename T>
std::size_t SingleList<T>::size() const {
    std::size_t count = 0;
    SingleNode<T> *node = head;
    while (node != nullptr) {
        ++count;
        node = node->next;
    }
    return count;
}

template <typename T>
void SingleList<T>::push_front(const T& item) {
    if (!empty()) {
        head = new SingleNode<T>(item, head);
    } else {
        head = tail = new SingleNode<T>(item);
    }
}

template <typename T>
void SingleList<T>::push_back(const T& item) {
    if (!empty()) {
        tail->next = new SingleNode<T>(item);
        tail = tail->next;
    } else {
        head = tail = new SingleNode<T>(item);
    }
}

template <typename T>
void SingleList<T>::pop_front() {
    assert(!empty());
    SingleNode<T> *node = head;
    if (head == tail) {
        head = tail = nullptr;
    } else {
        head = head->next;
    }
}

template <typename T>
void SingleList<T>::pop_back() {
    assert(!empty());
    SingleNode<T> *node = tail;
    if (head == tail) {
        head = tail = nullptr;
    } else {
        SingleNode<T> *before = head;
        while (before->next != tail) {
            before = before->next;
        }
        tail = before;
        tail->next = nullptr;
    }
    delete node;
}

template <typename T>
void SingleList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

template <typename T>
void SingleList<T>::display() {
    SingleNode<T> *node = head;
    while (node != nullptr) {
        std::cout << node->value << " ";
        node = node->next;
    }
}

template <typename T>
void SingleList<T>::reverse() {
    if (head == nullptr || head->next == nullptr) {
        return;
    }
    
    
    SingleNode<T> *prev = nullptr;
    SingleNode<T> *current = head;
    SingleNode<T> *next = nullptr;
    tail = head;
    while (current != nullptr) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
}

template <typename T>
SingleList<T>::~SingleList() {
    while (!empty()) { 
        pop_front();
    }
}



template class SingleList<int>;