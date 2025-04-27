#ifndef SETSIMPLE_HPP
#define SETSIMPLE_HPP

#include <vector>
#include <iostream>

class SetSimple {
    std::vector<bool> elements;
    size_t universeSize;
public:
    SetSimple(size_t N);
    ~SetSimple() = default;
    void clear() { elements.clear(); }
    bool empty() const { return elements.size() == 0; }
    void add(int index);
    void remove(int index);
    size_t getUniverseSize() const { return universeSize; }
    bool contains(int index) const;
    SetSimple unionWith(const SetSimple& otherSet) const;
    SetSimple intersection(const SetSimple& otherSet) const;
    SetSimple difference(const SetSimple& otherSet) const;
    bool isIdentical(const SetSimple& otherSet) const;

};

#endif