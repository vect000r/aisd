#include "setHashed.hpp"

bool SetHashed::empty() const {
    for (auto &bucket : buckets) {
        if (!bucket.empty()) {
            return false;
        }
    }
    return true; 
}

bool SetHashed::contains(int index) const { 
    return buckets[hash(index)].contains(index);
}

bool SetHashed::isIdentical(const SetHashed& otherSet) const {
    if (bucketCount != otherSet.bucketCount) {
        return false;
    }
    
    for (size_t i = 0; i < bucketCount; ++i) {
        if (!buckets[i].isIdentical(otherSet.buckets[i])) {
            return false;
        }
    }
    return true;
}

void SetHashed::push(int index) {
    buckets[hash(index)].add(index);
}

void SetHashed::pop(int index) {
    buckets[hash(index)].remove(index);
}

SetHashed SetHashed::unionWith(const SetHashed& otherSet) const {
    
    SetHashed result(bucketCount);
    
    for (int i = 0; i < 10; ++i) {  
        if (this->contains(i)) {
            result.push(i);
        }
    }
    
    for (int i = 0; i < 10; ++i) {
        if (otherSet.contains(i)) {
            result.push(i);
        }
    }
    
    return result;
}

// Poprawiona implementacja intersection
SetHashed SetHashed::intersection(const SetHashed& otherSet) const {
    SetHashed result(bucketCount);
    
    // Znajdujemy wspólne elementy obu zbiorów
    for (int i = 0; i < 1000; ++i) { // Przyjmujemy rozsądny zakres indeksów
        try {
            if (this->contains(i) && otherSet.contains(i)) {
                result.push(i);
            }
        } catch (const std::out_of_range&) {
            // Jeśli indeks jest poza zakresem, po prostu go pomijamy
            continue;
        }
    }
    
    return result;
}

// Poprawiona implementacja difference
SetHashed SetHashed::difference(const SetHashed& otherSet) const {
    SetHashed result(bucketCount);
    
    // Znajdujemy elementy obecne w this, ale nieobecne w otherSet
    for (int i = 0; i < 1000; ++i) { // Przyjmujemy rozsądny zakres indeksów
        try {
            if (this->contains(i) && !otherSet.contains(i)) {
                result.push(i);
            }
        } catch (const std::out_of_range&) {
            // Jeśli indeks jest poza zakresem, po prostu go pomijamy
            continue;
        }
    }
    
    return result;
}



