#ifndef DICTIONARY_SIMPLE_HPP
#define DICTIONARY_SIMPLE_HPP

#include <string>

class dictionarySimple {
private:
    static const int MAX_STRING_LENGTH = 50;
    static const int ARRAY_SIZE = 100; 
    
    std::string elements[ARRAY_SIZE]; 
    int size; 
    
public:
    dictionarySimple();
    void insert(const std::string& x); 
    void remove(const std::string& x); 
    bool contains(const std::string& x) const; 
    bool isFull() const; 
    bool isEmpty() const; 
    int getSize() const; 
};

#endif