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
    bool contains(int index) const;
    SetSimple unionWith(const SetSimple& otherSet) const;
    SetSimple intersection(const SetSimple& otherSet) const;
    SetSimple difference(const SetSimple& otherSet) const;

    bool isIdentical(const SetSimple& otherSet) const;

};

SetSimple createSetConsecutiveIntegers(size_t universeSize, int n, int m);
SetSimple createSetEvenStepIntegers(size_t universeSize, int n, int m);
SetSimple createSetLetters(size_t universeSize);
SetSimple createSetTwoLetterStrings(size_t universeSize);
void printConsecutiveIntegersSet(const SetSimple& set, size_t universeSize, int n);
void printEvenStepIntegersSet(const SetSimple& set, size_t universeSize, int n);
void printLettersSet(const SetSimple& set, size_t universeSize);
void printTwoLetterStringsSet(const SetSimple& set, size_t universeSize, int limit);
std::string mapIndexToTwoLetterString(int index);
int mapTwoLetterStringToIndex(const std::string& str);
void printSetElements(const SetSimple& set, size_t universeSize);




#endif