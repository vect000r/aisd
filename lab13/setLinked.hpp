#ifndef SETLINKED_HPP
#define SETLINKED_HPP

#include <vector>
#include <iostream>

struct Node {
    bool value;
    Node *next;
    Node() : value(bool()), next(nullptr) {}
    Node(const bool& item, Node *ptr=nullptr) : value(item), next(ptr) {}
    ~Node() {}
};



class SetLinked {
    Node *head, *tail;
    size_t universeSize;
public:
    SetLinked(size_t N);
    ~SetLinked() = default;
    void clear() { elements.clear(); }
    bool empty() const { return elements.size() == 0; }
    void add(int index);
    void remove(int index);
    bool contains(int index);
    SetLinked unionWith(const SetLinked& otherSet) const;
    SetLinked intersection(const SetLinked& otherSet) const;
    SetLinked difference(const SetLinked& otherSet) const;
    bool isIdentical(const SetLinked& otherSet) const;

};

#endif