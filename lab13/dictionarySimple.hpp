#ifndef DICTIONARY_SIMPLE_HPP
#define DICTIONARY_SIMPLE_HPP

#include <string>

class dictionarySimple {
private:
    static const int MAX_STRING_LENGTH = 50;
    static const int ARRAY_SIZE = 100; // Możesz dostosować rozmiar tablicy według potrzeb
    
    std::string elements[ARRAY_SIZE]; // Jednowymiarowa tablica przechowująca ciągi znaków
    int size; // Aktualna liczba elementów w zbiorze
    
public:
    // Konstruktor
    dictionarySimple();
    
    // Operacje na zbiorze
    void insert(const std::string& x); // Wstawianie x do zbioru
    void remove(const std::string& x); // Usuwanie x ze zbioru
    bool contains(const std::string& x) const; // Sprawdzanie czy x należy do zbioru
    
    // Pomocnicze metody
    bool isFull() const; // Sprawdza czy zbiór jest pełny
    bool isEmpty() const; // Sprawdza czy zbiór jest pusty
    int getSize() const; // Zwraca aktualną liczbę elementów w zbiorze
};

#endif