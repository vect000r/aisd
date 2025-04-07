#include "setSimple.hpp"

SetSimple::SetSimple(size_t N) : universeSize(N) {
    elements.resize(N, false);
}

void SetSimple::add(int index) {
    if (index >= 0 && index < universeSize) {
        elements[index] = true;
    }
}

void SetSimple::remove(int index) {
    if (index >= 0 && index < universeSize) {
        elements[index] = false;
    }
}

bool SetSimple::contains(int index) const {
    return (index >= 0 && index < universeSize) && elements[index];
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
SetSimple createSetConsecutiveIntegers(size_t universeSize, int n, int m)  {
    SetSimple set(universeSize);
    
    if (n >= m) {
        return set; // Pusty zbiór jeśli warunek n < m nie jest spełniony
    }
    
    for (int i = n; i <= m && i < static_cast<int>(universeSize); i++) {
        set.add(i - 1); // Odejmujemy 1, zakładając że zbiór jest indeksowany od 0
    }
    
    return set;
}

// Funkcja dla zbioru liczb całkowitych n, n+2, n+4, ..., m gdzie n < m
SetSimple createSetEvenStepIntegers(size_t universeSize, int n, int m) {
    SetSimple set(universeSize);
    
    if (n >= m) {
        return set; // Pusty zbiór jeśli warunek n < m nie jest spełniony
    }
    
    for (int i = n; i <= m && i < static_cast<int>(universeSize); i += 2) {
        set.add(i - 1); // Odejmujemy 1, zakładając że zbiór jest indeksowany od 0
    }
    
    return set;
}

// Funkcja dla zbioru liter a, b, c, ..., z bez polskich znaków
SetSimple createSetLetters(size_t universeSize)  {
    SetSimple set(universeSize);
    
    for (char c = 'a'; c <= 'z' && (c - 'a') < static_cast<int>(universeSize); c++) {
        set.add(c - 'a'); // Mapujemy 'a' na 0, 'b' na 1, itd.
    }
    
    return set;
}

// Funkcja dla zbioru dwuliterowych napisów, gdzie każda litera jest z zakresu a-z bez polskich znaków
SetSimple createSetTwoLetterStrings(size_t universeSize)  {
    SetSimple set(universeSize);
    int index = 0;
    
    for (char c1 = 'a'; c1 <= 'z'; c1++) {
        for (char c2 = 'a'; c2 <= 'z'; c2++) {
            if (index < static_cast<int>(universeSize)) {
                set.add(index);
                index++;
            } else {
                return set; // Przerwij jeśli przekroczono rozmiar uniwersum
            }
        }
    }
    
    return set;
}

// Pomocnicza funkcja do mapowania dwuliterowego napisu na indeks
int mapTwoLetterStringToIndex(const std::string& str) {
    if (str.length() != 2 || str[0] < 'a' || str[0] > 'z' || str[1] < 'a' || str[1] > 'z') {
        return -1; // Nieprawidłowy napis
    }
    
    return (str[0] - 'a') * 26 + (str[1] - 'a');
}

// Pomocnicza funkcja do mapowania indeksu na dwuliterowy napis
std::string mapIndexToTwoLetterString(int index) {
    if (index < 0 || index >= 26 * 26) {
        return ""; // Nieprawidłowy indeks
    }
    
    std::string result = "aa";
    result[0] = 'a' + (index / 26);
    result[1] = 'a' + (index % 26);
    
    return result;
}

// Funkcja do wyświetlania elementów zbioru dla pierwszego przypadku
void printConsecutiveIntegersSet(const SetSimple& set, size_t universeSize, int n) {
    std::cout << "Zbiór liczb całkowitych od " << n << " zawiera: {";
    bool first = true;
    for (size_t i = 0; i < universeSize; i++) {
        if (set.contains(i)) {
            if (!first) {
                std::cout << ", ";
            }
            std::cout << (i + n);  // Przywracamy oryginalną wartość
            first = false;
        }
    }
    std::cout << "}" << std::endl;
}

// Funkcja do wyświetlania elementów zbioru dla drugiego przypadku
void printEvenStepIntegersSet(const SetSimple& set, size_t universeSize, int n) {
    std::cout << "Zbiór liczb całkowitych od " << n << " z krokiem 2 zawiera: {";
    bool first = true;
    for (size_t i = 0; i < universeSize; i++) {
        if (set.contains(i)) {
            if (!first) {
                std::cout << ", ";
            }
            std::cout << (n + (i * 2));  // Przywracamy oryginalną wartość
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
    
    for (size_t i = 0; i < universeSize && i < 26 * 26 && count < limit; i++) {
        if (set.contains(i)) {
            if (!first) {
                std::cout << ", ";
            }
            std::cout << mapIndexToTwoLetterString(i);
            first = false;
            count++;
        }
    }
    
    if (count == limit && universeSize > limit) {
        std::cout << ", ...";
    }
    
    std::cout << "}" << std::endl;
}

void printSetElements(const SetSimple& set, size_t universeSize) {
    std::cout << "Zbiór zawiera elementy: {";
    bool first = true;
    for (size_t i = 0; i < universeSize; i++) {
        if (set.contains(i)) {
            if (!first) {
                std::cout << ", ";
            }
            std::cout << i;
            first = false;
        }
    }
    std::cout << "}" << std::endl;
}