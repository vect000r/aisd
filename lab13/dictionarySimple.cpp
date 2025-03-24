#include "dictionarySimple.hpp"
#include <algorithm> 

dictionarySimple::dictionarySimple() : size(0) {}

void dictionarySimple::insert(const std::string& x) {
    if (x.length() > MAX_STRING_LENGTH) {
        return;
    }
    
    if (!isFull() && !contains(x)) {
        elements[size] = x;
        size++;
    }
}

void dictionarySimple::remove(const std::string& x) {
    for (int i = 0; i < size; i++) {
        if (elements[i] == x) {
            for (int j = i; j < size - 1; j++) {
                elements[j] = elements[j + 1];
            }
            size--;
            return;
        }
    }
}

bool dictionarySimple::contains(const std::string& x) const {
    for (int i = 0; i < size; i++) {
        if (elements[i] == x) {
            return true;
        }
    }
    return false;
}

bool dictionarySimple::isFull() const {
    return size >= ARRAY_SIZE;
}

bool dictionarySimple::isEmpty() const {
    return size == 0;
}

int dictionarySimple::getSize() const {
    return size;
}