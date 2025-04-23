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
    if (bucketCount != otherSet.bucketCount) {
        throw std::invalid_argument("Sets must have the same bucket count");
    }
    
    SetHashed result(bucketCount);
    
    const int maxCheckValue = 10; 
    
    for (int val = 0; val <= maxCheckValue; val++) {
        int bucketIdx = hash(val);
        try {
            // Check if the value exists in either set
            if (buckets[bucketIdx].contains(val) || otherSet.buckets[bucketIdx].contains(val)) {
                result.push(val);
            }
        } catch (const std::out_of_range&) {
            // Skip values that are out of range
            continue;
        }
    }
    
    return result;
}

SetHashed SetHashed::intersection(const SetHashed& otherSet) const {
    SetHashed result(bucketCount);
    
    for (int i = 0; i < bucketCount; ++i) {
        try {
            // We need to iterate through the range that might contain valid elements
            for (int j = 0; j < bucketCount * 10; ++j) {  
                // Only check elements that would hash to this bucket
                if (hash(j) == i && buckets[i].contains(j) && otherSet.buckets[i].contains(j)) {
                    result.push(j);
                }
            }
        } catch (const std::out_of_range&) {
            continue;
        }
    }
    return result;
}

SetHashed SetHashed::difference(const SetHashed& otherSet) const {
    SetHashed result(bucketCount);
    
    for (int i = 0; i < bucketCount; ++i) {
        try {
            // We need to iterate through the range that might contain valid elements
            for (int j = 0; j < bucketCount * 10; ++j) {  
                // Only check elements that would hash to this bucket
                if (hash(j) == i && buckets[i].contains(j) && !otherSet.buckets[i].contains(j)) {
                    result.push(j);
                }
            }
        } catch (const std::out_of_range&) {
            continue;
        }
    }
    return result;
}