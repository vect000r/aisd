#include "dictionarySimple.hpp"
#include <algorithm>
#include <cstring> 

dictionarySimple::dictionarySimple() : size(0) {}

void dictionarySimple::insert(const std::string& x) {
    // Early return if string exceeds max length or dictionary is full
    if (x.length() > MAX_STRING_LENGTH || isFull()) {
        return;
    }
    
    // Only search for the element if the dictionary isn't empty
    if (size > 0 && contains(x)) {
        return;
    }
    
    // Insert at the end
    elements[size++] = x;
}

void dictionarySimple::remove(const std::string& x) {
    for (int i = 0; i < size; i++) {
        if (elements[i] == x) {
            // Move the last element to the position of the removed element
            // This is more efficient than shifting all elements
            elements[i] = elements[--size];
            return;
        }
    }
}

bool dictionarySimple::contains(const std::string& x) const {
    // Use std::find for potentially more optimized search
    return std::find(elements, elements + size, x) != elements + size;
}

// These simple methods are already optimal
bool dictionarySimple::isFull() const {
    return size >= ARRAY_SIZE;
}

bool dictionarySimple::isEmpty() const {
    return size == 0;
}

int dictionarySimple::getSize() const {
    return size;
}