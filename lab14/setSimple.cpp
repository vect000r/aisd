#include "setSimple.hpp"

SetSimple::SetSimple(size_t N) : universeSize(N) {
    elements.resize(N, false);
}

void SetSimple::add(int index) {
    if (index >= 0 && static_cast<size_t>(index) < universeSize) {
        elements[index] = true;
    }
}

void SetSimple::remove(int index) {
    if (index >= 0 && static_cast<size_t>(index) < universeSize) {
        elements[index] = false;
    }
}

bool SetSimple::contains(int index) const {
    return (index >= 0 && static_cast<size_t>(index) < universeSize) && elements[index];
}

SetSimple SetSimple::unionWith(const SetSimple& otherSet) const {
    if (universeSize != otherSet.universeSize) {
        throw std::invalid_argument("Sets must have the same universe size!");
    }

    SetSimple result(universeSize);

    for (size_t i = 0; i < universeSize; i++) {
        result.elements[i] = elements[i] || otherSet.elements[i];
    }

    return result;
}

SetSimple SetSimple::intersection(const SetSimple& otherSet) const {
    if (universeSize != otherSet.universeSize) {
        throw std::invalid_argument("Sets must have the same universe size!");
    }

    SetSimple result(universeSize);

    for (size_t i = 0; i < universeSize; i++) {
        result.elements[i] = elements[i] && otherSet.elements[i];
    }

    return result;
}

SetSimple SetSimple::difference(const SetSimple& otherSet) const {
    if (universeSize != otherSet.universeSize) {
        throw std::invalid_argument("Sets must have the same universe size!");
    }

    SetSimple result(universeSize);

    for (size_t i = 0; i < universeSize; i++) {
        result.elements[i] = elements[i] && !otherSet.elements[i];
    }

    return result;
}

bool SetSimple::isIdentical(const SetSimple& otherSet) const {
    if (universeSize != otherSet.universeSize) {
        return false;
    }

    for (size_t i = 0; i < universeSize; i++) {
        if (elements[i] != otherSet.elements[i]) {
            return false;
        }
    }
    
    return true;
}

// Funkcja dla zbioru liczb całkowitych n, n+1, n+2, ..., m gdzie n < m
SetSimple createSetConsecutiveIntegers(size_t universeSize, int n, int m) {
    SetSimple set(universeSize);
    
    if (n >= m) {
        return set; // Pusty zbiór jeśli warunek n < m nie jest spełniony
    }
    
    // Mapowanie: wartość n+i odpowiada indeksowi i
    for (int i = 0; i <= m - n && i < static_cast<int>(universeSize); i++) {
        set.add(i);
    }
    
    return set;
}

// Funkcja dla zbioru liczb całkowitych n, n+2, n+4, ..., m gdzie n < m
SetSimple createSetEvenStepIntegers(size_t universeSize, int n, int m) {
    SetSimple set(universeSize);
    
    if (n >= m) {
        return set; // Pusty zbiór jeśli warunek n < m nie jest spełniony
    }
    
    // Mapowanie: wartość n+2k odpowiada indeksowi k
    int k = 0;
    for (int val = n; val <= m && k < static_cast<int>(universeSize); val += 2, k++) {
        set.add(k);
    }
    
    return set;
}

// Funkcja dla zbioru liter a, b, c, ..., z bez polskich znaków
SetSimple createSetLetters(size_t universeSize) {
    SetSimple set(universeSize);
    
    // Mapowanie: litera 'a'+i odpowiada indeksowi i
    for (int i = 0; i < 26 && i < static_cast<int>(universeSize); i++) {
        set.add(i);
    }
    
    return set;
}

// Funkcja dla zbioru dwuliterowych napisów, gdzie każda litera jest z zakresu a-z bez polskich znaków
SetSimple createSetTwoLetterStrings(size_t universeSize) {
    SetSimple set(universeSize);
    
    // Mapowanie: napis składający się z liter 'a'+i oraz 'a'+j odpowiada indeksowi i*26+j
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            int index = i * 26 + j;
            if (index < static_cast<int>(universeSize)) {
                set.add(index);
            } else {
                return set; // Przerwij jeśli przekroczono rozmiar uniwersum
            }
        }
    }
    
    return set;
}

// Poprawione funkcje pomocnicze do wyświetlania zbiorów
// ======================================================

// Funkcja do wyświetlania elementów zbioru liczb całkowitych od n
void printConsecutiveIntegersSet(const SetSimple& set, size_t universeSize, int n) {
    std::cout << "Zbiór liczb całkowitych od " << n << " zawiera: {";
    bool first = true;
    for (size_t i = 0; i < universeSize; i++) {
        if (set.contains(i)) {
            if (!first) {
                std::cout << ", ";
            }
            std::cout << (n + i);  // Wartość n+i dla indeksu i
            first = false;
        }
    }
    std::cout << "}" << std::endl;
}

// Funkcja do wyświetlania elementów zbioru z krokiem 2
void printEvenStepIntegersSet(const SetSimple& set, size_t universeSize, int n) {
    std::cout << "Zbiór liczb całkowitych od " << n << " z krokiem 2 zawiera: {";
    bool first = true;
    for (size_t i = 0; i < universeSize; i++) {
        if (set.contains(i)) {
            if (!first) {
                std::cout << ", ";
            }
            std::cout << (n + 2*i);  // Wartość n+2i dla indeksu i
            first = false;
        }
    }
    std::cout << "}" << std::endl;
}

// Funkcja do wyświetlania elementów zbioru liter
void printLettersSet(const SetSimple& set, size_t universeSize) {
    std::cout << "Zbiór liter zawiera: {";
    bool first = true;
    for (size_t i = 0; i < universeSize && i < 26; i++) {
        if (set.contains(i)) {
            if (!first) {
                std::cout << ", ";
            }
            std::cout << static_cast<char>('a' + i);
            first = false;
        }
    }
    std::cout << "}" << std::endl;
}

// Funkcja do wyświetlania elementów zbioru dwuliterowych napisów
void printTwoLetterStringsSet(const SetSimple& set, size_t universeSize, int limit = 20) {
    std::cout << "Zbiór dwuliterowych napisów zawiera (pierwsze " << limit << " elementów): {";
    bool first = true;
    int count = 0;
    
    for (size_t i = 0; i < universeSize && i < 26*26 && count < limit; i++) {
        if (set.contains(i)) {
            if (!first) {
                std::cout << ", ";
            }
            char first_char = 'a' + (i / 26);
            char second_char = 'a' + (i % 26);
            std::cout << first_char << second_char;
            first = false;
            count++;
        }
    }
    
    if (count == limit && universeSize > static_cast<size_t>(limit)) {
        std::cout << ", ...";
    }
    
    std::cout << "}" << std::endl;
}

// Function to map an index to a two-letter string
std::string mapIndexToTwoLetterString(int index) {
    std::string result = "aa"; // Default
    
    if (index >= 0 && index < 26*26) {
        char first_char = 'a' + (index / 26);
        char second_char = 'a' + (index % 26);
        result[0] = first_char;
        result[1] = second_char;
    }
    
    return result;
}

// Function to map a two-letter string to an index
int mapTwoLetterStringToIndex(const std::string& str) {
    if (str.length() != 2 || 
        str[0] < 'a' || str[0] > 'z' || 
        str[1] < 'a' || str[1] > 'z') {
        return -1; // Invalid input
    }
    
    int first_char_value = str[0] - 'a';
    int second_char_value = str[1] - 'a';
    
    return first_char_value * 26 + second_char_value;
}

// Function to print all elements in a set
void printSetElements(const SetSimple& set, size_t universeSize) {
    std::cout << "Set elements: {";
    bool first = true;
    
    for (size_t i = 0; i < universeSize; i++) {
        if (set.contains(static_cast<int>(i))) {
            if (!first) {
                std::cout << ", ";
            }
            std::cout << i;
            first = false;
        }
    }
    
    std::cout << "}" << std::endl;
}