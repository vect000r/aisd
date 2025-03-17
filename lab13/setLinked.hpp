#ifndef SETLINKED_HPP
#define SETLINKED_HPP

#include <iostream>

struct Node {
    int index;       // Indeks elementu w uniwersum
    Node *next;
    Node() : index(-1), next(nullptr) {}
    Node(const int& idx, Node *ptr=nullptr) : index(idx), next(ptr) {}
    ~Node() {}
};

class SetLinked {
    Node *head;
    size_t universeSize;  // Rozmiar uniwersum (N)
public:
    SetLinked(size_t N);
    ~SetLinked();
    void clear();
    bool empty() const;
    void add(int index);
    void remove(int index);
    bool contains(int index) const;
    SetLinked unionWith(const SetLinked& otherSet) const;
    SetLinked intersection(const SetLinked& otherSet) const;
    SetLinked difference(const SetLinked& otherSet) const;
    bool isIdentical(const SetLinked& otherSet) const;
};

#endif