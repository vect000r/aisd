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
    
    // Create and process a separate result for each bucket
    for (int i = 0; i < bucketCount; ++i) {
        // For each bucket index, add all elements from this bucket to the result
        try {
            // We need to iterate through the range that might contain valid elements
            for (int j = 0; j < bucketCount * 10; ++j) {  
                // Only check elements that would hash to this bucket
                if (hash(j) == i && buckets[i].contains(j)) {
                    result.push(j);
                }
            }
            
            // And add all elements from the other bucket to the result
            for (int j = 0; j < bucketCount * 10; ++j) {  
                // Only check elements that would hash to this bucket
                if (hash(j) == i && otherSet.buckets[i].contains(j)) {
                    result.push(j);
                }
            }
        } catch (const std::out_of_range&) {
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