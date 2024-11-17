#include "stack.hpp"

template <typename T>
Stack<T>::Stack(const Stack& other) {
    for(int i = 0, i <= this.size(), i++) {
        other.push(i);
    }
}

template <typename T>
Stack<T>::Stack(Stack&& other) {
    // TODO
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& other) {
    // TODO
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack&& other) {
    // TODO
}
