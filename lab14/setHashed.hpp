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
    SetHashed(size_t size = 10) : bucketCount(size) {
        buckets.clear();
        for (size_t i = 0; i < size; ++i) {
            buckets.emplace_back(size);  
        }
    }
    
    ~SetHashed() = default;

    bool empty() const;
    void push(int index);
    void pop(int index);
    bool contains(int index) const;
    SetHashed unionWith(const SetHashed& otherSet) const;
    SetHashed intersection(const SetHashed& otherSet) const;
    SetHashed difference(const SetHashed& otherSet) const;
    bool isIdentical(const SetHashed& otherSet) const;
};

#endif