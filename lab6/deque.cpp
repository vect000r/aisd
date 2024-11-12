#include "deque.hpp"
#include <cassert>

template <typename T>
Deque<T>::Deque(const Deque& other) : list(other.list) {}

template <typename T>
Deque<T>& Deque<T>::operator=(const Deque& other) {
    if (this != &other) {
        list = other.list;
    }
    return *this;
}

template <typename T>
void Deque<T>::push_front(const T& item) {
    list.push_front(item);
}

template <typename T>
void Deque<T>::push_back(const T& item) {
    list.push_back(item);
}

template <typename T>
void Deque<T>::pop_front() {
    if (!empty()) {
        list.pop_front();
    }
}

template <typename T>
void Deque<T>::pop_back() {
    if (!empty()) {
        list.pop_back();
    }
}

template <typename T>
T& Deque<T>::front() {
    assert(!empty());
    return list.front();
}

template <typename T>
const T& Deque<T>::front() const {
    assert(!empty());
    return list.front();
}

template <typename T>
T& Deque<T>::back() {
    assert(!empty());
    return list.back();
}

template <typename T>
const T& Deque<T>::back() const {
    assert(!empty());
    return list.back();
}

template <typename T>
bool Deque<T>::empty() const {
    return list.empty();
}

template <typename T>
std::size_t Deque<T>::size() const {
    return list.size();
}

template <typename T>
void Deque<T>::clear() {
    list.clear();
}

template <typename T>
void Deque<T>::display() const {
    list.display();
}

template <typename T>
void Deque<T>::display_reversed() const {
    list.display_reversed();
}


template class Deque<int>;