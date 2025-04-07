#ifndef SET_HASHED_HPP
#define SET_HASHED_HPP

#include "setLinked.hpp"
#include <vector>

class SetHashed {
private:
    int bucketCount;
    std::vector<SetLinked> buckets;

    int hash(int val) const {
        return val % bucketCount;
    }

public:
    SetHashed(int size = 10) : bucketCount(size) {
        buckets.reserve(size);
        for (int i = 0; i < size; i++) {
            size_t bucket_size = size;
            buckets.emplace_back(bucket_size);
        }
    }
    
    ~SetHashed() = default;

    bool empty() const;
    void push(int index);
    void pop(int index);
    bool contains(int index);
    SetHashed unionWith(const SetHashed& otherSet) const;
    SetHashed intersection(const SetHashed& otherSet) const;
    SetHashed difference(const SetHashed& otherSet) const;
    bool isIdentical(const SetHashed& otherSet) const;
};

#endif