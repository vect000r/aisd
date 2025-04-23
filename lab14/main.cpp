#include <iostream>
#include <cassert>
#include <string>
#include "setSimple.hpp"
#include "setHashed.hpp"

void testSetMappings() {
    std::cout << "\n===== TESTY FUNKCJI PRZYPORZĄDKOWANIA ZBIORÓW =====\n" << std::endl;
    
    // Test consecutive integers set
    {
        std::cout << "\n----- Test zbioru liczb całkowitych n, n+1, n+2, ..., m -----" << std::endl;
        
        const size_t universeSize = 20;
        int n = 5;
        int m = 12;
        
        std::cout << "Tworzenie zbioru liczb całkowitych od " << n << " do " << m 
                  << " (rozmiar uniwersum: " << universeSize << ")" << std::endl;
        
        SetSimple set = createSetConsecutiveIntegers(universeSize, n, m);
        printConsecutiveIntegersSet(set, universeSize, n);
        
        std::cout << "\nSprawdzanie obecności poszczególnych elementów:" << std::endl;
        for (int i = n - 2; i <= m + 2; i++) {
            bool belongs = false;
            if (i >= n && i <= m) {
                int index = i - n;
                if (index < universeSize) {
                    belongs = set.contains(index);
                }
            }
            std::cout << "  Czy " << i << " należy do zbioru? " 
                      << (belongs ? "TAK" : "NIE") << std::endl;
        }
        
        // Test z n >= m (pusty zbiór)
        std::cout << "\nTest pustego zbioru (n >= m):" << std::endl;
        SetSimple emptySet = createSetConsecutiveIntegers(universeSize, 10, 5);
        printSetElements(emptySet, universeSize);
        
        // Test z wartościami przekraczającymi rozmiar uniwersum
        std::cout << "\nTest z wartościami przekraczającymi rozmiar uniwersum:" << std::endl;
        int smallUniverseSize = 4; // Ustawiamy mały rozmiar uniwersum, aby pokazać ograniczenie
        SetSimple limitedSet = createSetConsecutiveIntegers(smallUniverseSize, 5, 20);
        std::cout << "Zbiór liczb od 5 do 20 z uniwersum rozmiaru " << smallUniverseSize << ":" << std::endl;
        printConsecutiveIntegersSet(limitedSet, smallUniverseSize, 5);
    }
    
    // Test even step integers set
    {
        std::cout << "\n----- Test zbioru liczb całkowitych n, n+2, n+4, ..., m -----" << std::endl;
        
        const size_t universeSize = 20;
        int n = 3;
        int m = 15;
        
        std::cout << "Tworzenie zbioru liczb całkowitych od " << n << " do " << m 
                  << " z krokiem 2 (rozmiar uniwersum: " << universeSize << ")" << std::endl;
        
        SetSimple set = createSetEvenStepIntegers(universeSize, n, m);
        printEvenStepIntegersSet(set, universeSize, n);
        
        std::cout << "\nSprawdzanie obecności poszczególnych elementów:" << std::endl;
        for (int i = n - 2; i <= m + 2; i++) {
            bool belongs = false;
            if (i >= n && i <= m && (i - n) % 2 == 0) {
                int index = (i - n) / 2;
                if (index < universeSize) {
                    belongs = set.contains(index);
                }
            }
            std::cout << "  Czy " << i << " należy do zbioru? " 
                      << (belongs ? "TAK" : "NIE") << std::endl;
        }
        
        // Test z n >= m (pusty zbiór)
        std::cout << "\nTest pustego zbioru (n >= m):" << std::endl;
        SetSimple emptySet = createSetEvenStepIntegers(universeSize, 10, 5);
        printSetElements(emptySet, universeSize);
        
        // Test z wartościami przekraczającymi rozmiar uniwersum
        std::cout << "\nTest z wartościami przekraczającymi rozmiar uniwersum:" << std::endl;
        int smallUniverseSize = 3; // Ustawiamy mały rozmiar uniwersum
        SetSimple limitedSet = createSetEvenStepIntegers(smallUniverseSize, 3, 25);
        std::cout << "Zbiór liczb od 3 do 25 z krokiem 2 z uniwersum rozmiaru " 
                  << smallUniverseSize << ":" << std::endl;
        printEvenStepIntegersSet(limitedSet, smallUniverseSize, 3);
    }
    
    // Test letters set
    {
        std::cout << "\n----- Test zbioru liter a, b, c, ..., z -----" << std::endl;
        
        const size_t universeSize = 30;
        
        std::cout << "Tworzenie zbioru wszystkich liter (rozmiar uniwersum: " 
                  << universeSize << ")" << std::endl;
        
        SetSimple set = createSetLetters(universeSize);
        printLettersSet(set, universeSize);
        
        std::cout << "\nSprawdzanie obecności poszczególnych liter:" << std::endl;
        char testLetters[] = {'a', 'e', 'j', 'z', 'A', '1'};
        for (char c : testLetters) {
            bool belongs = false;
            if (c >= 'a' && c <= 'z') {
                int index = c - 'a';
                if (index < universeSize) {
                    belongs = set.contains(index);
                }
            }
            
            std::cout << "  Czy '" << c << "' należy do zbioru? " 
                      << (belongs ? "TAK" : "NIE") << std::endl;
        }
        
        // Test z mniejszym rozmiarem uniwersum
        std::cout << "\nTest z mniejszym rozmiarem uniwersum:" << std::endl;
        int smallUniverseSize = 10;
        SetSimple smallSet = createSetLetters(smallUniverseSize);
        printLettersSet(smallSet, smallUniverseSize);
    }
    
    // Test two-letter strings set
    {
        std::cout << "\n----- Test zbioru dwuliterowych napisów a-z -----" << std::endl;
        
        const size_t universeSize = 26 * 26;
        
        std::cout << "Tworzenie zbioru wszystkich dwuliterowych napisów (rozmiar uniwersum: " 
                  << universeSize << ")" << std::endl;
        
        SetSimple set = createSetTwoLetterStrings(universeSize);
        printTwoLetterStringsSet(set, universeSize, 15);
        
        std::cout << "\nTestowanie mapowania między napisami a indeksami:" << std::endl;
        std::string testStrings[] = {"aa", "ab", "az", "ba", "zz", "a", "abc", "1a"};
        for (const std::string& str : testStrings) {
            std::cout << "  Mapowanie '" << str << "' -> ";
            
            if (str.length() == 2 && str[0] >= 'a' && str[0] <= 'z' && str[1] >= 'a' && str[1] <= 'z') {
                int index = (str[0] - 'a') * 26 + (str[1] - 'a');
                std::cout << index;
                
                if (index < universeSize) {
                    std::cout << " (należy do zbioru: " << (set.contains(index) ? "TAK" : "NIE") << ")";
                } else {
                    std::cout << " (poza zakresem uniwersum)";
                }
                std::cout << std::endl;
            } else {
                std::cout << "nieprawidłowy napis (nie należy do zbioru)" << std::endl;
            }
        }
        
        // Test z mniejszym rozmiarem uniwersum
        std::cout << "\nTest z mniejszym rozmiarem uniwersum:" << std::endl;
        int smallUniverseSize = 30;
        SetSimple smallSet = createSetTwoLetterStrings(smallUniverseSize);
        printTwoLetterStringsSet(smallSet, smallUniverseSize, 15);
    }
    
    std::cout << "\n===== WSZYSTKIE TESTY FUNKCJI PRZYPORZĄDKOWANIA ZBIORÓW ZAKOŃCZONE POMYŚLNIE =====\n" << std::endl;
}

void testSetHashed() {
    std::cout << "\n===== TESTY SETHASHED =====\n";
    
    // Test empty
    {
        SetHashed set(10);
        assert(set.empty());
        std::cout << "Empty test passed!\n";
    }

    // Test push i contains
    {
        SetHashed set(10);
        set.push(1);
        set.push(2);
        set.push(3);
        assert(!set.empty());
        assert(set.contains(1));
        assert(set.contains(2));
        assert(set.contains(3));
        assert(!set.contains(4));
        std::cout << "Push i contains test passed!\n";
    }

    // Test pop
    {
        SetHashed set(10);
        set.push(1);
        set.push(2);
        assert(set.contains(1));
        set.pop(1);
        assert(!set.contains(1));
        assert(set.contains(2));
        set.pop(2);
        assert(set.empty());
        std::cout << "Pop test passed!\n";
    }

    // Test unionWith
    {
        SetHashed set1(10);
        SetHashed set2(10);
        
        // Dodajemy elementy do pierwszego zbioru
        set1.push(1);
        set1.push(2);
        
        // Dodajemy elementy do drugiego zbioru
        set2.push(3);
        set2.push(4);
        
        // Kopiujemy zawartość pierwszego zbioru
        SetHashed result(10);
        result.push(1);
        result.push(2);
        
        // I dodajemy zawartość drugiego zbioru
        result.push(3);
        result.push(4);
        
        // Teraz porównujemy result z sumą zbiorów
        SetHashed unionResult = set1.unionWith(set2);
        
        assert(unionResult.contains(1));
        assert(unionResult.contains(2));
        assert(unionResult.contains(3));
        assert(unionResult.contains(4));
        
        std::cout << "unionWith test passed!\n";
    }
    // Test intersection
    {
        SetHashed set1(10);
        SetHashed set2(10);
        set1.push(1);
        set1.push(2);
        set2.push(2);
        set2.push(3);
        SetHashed result = set1.intersection(set2);
        assert(!result.contains(1));
        assert(result.contains(2));
        assert(!result.contains(3));
        std::cout << "Intersection test passed!\n";
    }

    // Test difference
    {
        SetHashed set1(10);
        SetHashed set2(10);
        set1.push(1);
        set1.push(2);
        set2.push(1);
        set2.push(3);
        SetHashed result = set1.difference(set2);
        assert(!result.contains(1));
        assert(result.contains(2));
        assert(!result.contains(3));
        std::cout << "Difference test passed!\n";
    }

    // Test isIdentical
    {
        SetHashed set1(10);
        SetHashed set2(10);
        set1.push(1);
        set1.push(2);
        set2.push(1);
        set2.push(2);
        assert(set1.isIdentical(set2));
        
        set1.push(3);
        assert(!set1.isIdentical(set2));
        
        set2.push(3);
        assert(set1.isIdentical(set2));
        std::cout << "isIdentical test passed!\n"; 
    }
    
    std::cout << "\n===== WSZYSTKIE TESTY ZAKONCZONE SUKCESEM =====\n";
}




int main() {
    try {
        testSetMappings();
        testSetHashed();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return 1;
    }
}