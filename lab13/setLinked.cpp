#include "setLinked.hpp"

SetLinked::SetLinked(size_t N) {
    head = nullptr;
    universeSize = N;
}

void SetLinked::clear() {
    while(head != nullptr) {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
}

SetLinked::~SetLinked() {
    clear();
}



bool SetLinked::empty() const {
    return head == nullptr;
}

void SetLinked::add(int index) {
    if (index < 0 || index > static_cast<int>(universeSize)) {
        throw std::out_of_range("Indeks poza zakresem");
    }

    if (head == nullptr || head->index > index) {
        head = new Node(index, head);
        return;
    }

    if (head->index == index) {
        return;
    }

    Node *current = head;
    while(current->next != nullptr && current->next->index < index) {
        current = current->next;
    }

    if (current->next != nullptr && current->next->index == index) {
        return;
    }

    current->next = new Node(index, current->next);
}

void SetLinked::remove(int index) {
    if (index < 0 || index > static_cast<int>(universeSize)) {
        throw std::out_of_range("Indeks poza zakresem");
    }

    if (head == nullptr) {
        return;
    }

    if (head->index == index) {
        Node *temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node *current = head;
    while(current->next != nullptr && current->next->index < index) {
        current = current->next;
    }

    if (current->next != nullptr && current->next->index == index) {
        Node *temp = current;
        current = current->next;
        delete  temp;
    }
}

bool SetLinked::contains(int index) const {
    if (index < 0 || index > static_cast<int>(universeSize)) {
        throw std::out_of_range("Indeks poza zakresem");
    }
    
    Node *current = head;
    while(current->next != nullptr && current->next->index < index) {
        current = current->next;
    }
    
    return (current != nullptr && current->index == index);
}

SetLinked SetLinked::unionWith(const SetLinked& otherSet) const {
    if (universeSize != otherSet.universeSize) {
        throw std::invalid_argument("Rozmiary uniwersów muszą być te same!");
    }

    SetLinked result(universeSize);

    Node *current = head;
    while(current != nullptr) {
        result.add(current->index);
        current = current->next;
    }

    current = otherSet.head;
    while(current != nullptr) {
        result.add(current->index);
        current = current->next;
    }

    return result;
}

SetLinked SetLinked::intersection(const SetLinked& otherSet) const {
    if (universeSize != otherSet.universeSize) {
        throw std::invalid_argument("Rozmiary uniwersów muszą być te same!");
    }

    SetLinked result(universeSize);

    Node *current = head;
    while(current != nullptr) {
        if (contains(current->index) && otherSet.contains(current->index)) {
            result.add(current->index);
        }
        current = current->next;
    }

    return result;
}

SetLinked SetLinked::difference(const SetLinked& otherSet) const {
    if (universeSize != otherSet.universeSize) {
        throw std::invalid_argument("Rozmiary uniwersów muszą być te same!");
    }

    SetLinked result(universeSize);

    Node *current = head;
    while(current != nullptr) {
        if (contains(current->index) && !otherSet.contains(current->index)) {
            result.add(current->index);
        }
        current = current->next;
    }

    return result;
}

bool SetLinked::isIdentical(const SetLinked& otherSet) const {
    if (universeSize != otherSet.universeSize) {
        return false;
    }
        
    Node *current1 = head;
    Node *current2 = otherSet.head;
        
    while (current1 != nullptr && current2 != nullptr) {
        if (current1->index != current2->index) {
            return false;
        }
        current1 = current1->next;
        current2 = current2->next;
    }
        
    return (current1 == nullptr && current2 == nullptr);
}
