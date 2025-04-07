#include "setHashed.hpp"

bool SetHashed::empty() const {
    for (auto &bucket : buckets) {
        if (!bucket.empty()) {
            return false;
        }
    }
}

void SetHashed::push(int index) {
    buckets[hash(index)].add(index);
}

void SetHashed::pop(int index) {
    buckets[hash(index)].remove(index);
}

bool SetHashed::contains(int index) {
    return buckets[hash(index)].contains(index);
}

SetHashed SetHashed::unionWith(const SetHashed& otherSet) const {
    SetHashed result(bucketCount);
    for (size_t i = 0; i < bucketCount; ++i) {
        result.buckets[i] = buckets[i].unionWith(otherSet.buckets[i]);
    }
    return result;
}

SetHashed SetHashed::intersection(const SetHashed& otherSet) const {
    SetHashed result(bucketCount);
    for (size_t i = 0; i < bucketCount; ++i) {
        result.buckets[i] = buckets[i].intersection(otherSet.buckets[i]);
    }
    return result;
}

SetHashed SetHashed::difference(const SetHashed& otherSet) const {
    SetHashed result(bucketCount);
    for (size_t i = 0; i < bucketCount; ++i) {
        result.buckets[i] = buckets[i].difference(otherSet.buckets[i]);
    }
    return result;
}

bool SetHashed::isIdentical(const SetHashed& otherSet) const {
    for (auto &bucket : buckets) {
        for (auto &otherBucket : otherSet.buckets) {
            if (!bucket.isIdentical(otherBucket)) {
                return false;
            }
        }
    }
    return true;
}