#include "setSimple.hpp"

SetSimple::SetSimple(size_t N) : universeSize(N) {
    elements.resize(N, false);
}

void SetSimple::add(int index) {
    if (index >= 0 && index < universeSize) {
        elements[index] = true;
    }
}

void SetSimple::remove(int index) {
    if (index >= 0 && index < universeSize) {
        elements[index] = false;
    }
}

bool SetSimple::contains(int index) const {
    return (index >= 0 && index < universeSize) && elements[index];
}

SetSimple SetSimple::unionWith(const SetSimple& otherSet) const {
    if (universeSize != otherSet.universeSize) {
        throw std::invalid_argument("Sets must have the same universe size!");
    }

    SetSimple result(universeSize);

    for (size_t i = 0; i < universeSize; i++) {
        result.elements[i] = elements[i] || otherSet.elements[i];
    }

    return result;
}

SetSimple SetSimple::intersection(const SetSimple& otherSet) const {
    if (universeSize != otherSet.universeSize) {
        throw std::invalid_argument("Sets must have the same universe size!");
    }

    SetSimple result(universeSize);

    for (size_t i = 0; i < universeSize; i++) {
        result.elements[i] = elements[i] && otherSet.elements[i];
    }

    return result;
}

SetSimple SetSimple::difference(const SetSimple& otherSet) const {
    if (universeSize != otherSet.universeSize) {
        throw std::invalid_argument("Sets must have the same universe size!");
    }

    SetSimple result(universeSize);

    for (size_t i = 0; i < universeSize; i++) {
        result.elements[i] = elements[i] && !otherSet.elements[i];
    }

    return result;
}

bool SetSimple::isIdentical(const SetSimple& otherSet) const {
    if (universeSize != otherSet.universeSize) {
        return false;
    }

    for (size_t i = 0; i < universeSize; i++) {
        if (elements[i] != otherSet.elements[i]) {
            return false;
        }
    }
    
    return true;
}