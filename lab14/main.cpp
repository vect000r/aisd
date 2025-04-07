#include <iostream>
#include <cassert>
#include <string>
#include "setSimple.hpp"
#include "setHashed.hpp"

// Zmodyfikowana funkcja testująca funkcje przyporządkowania zbiorów z ilustracją działania
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
            std::cout << "  Czy " << i << " należy do zbioru? " 
                      << (set.contains(i - 1) ? "TAK" : "NIE") << std::endl;
        }
        
        // Test z n >= m (pusty zbiór)
        std::cout << "\nTest pustego zbioru (n >= m):" << std::endl;
        SetSimple emptySet = createSetConsecutiveIntegers(universeSize, 10, 5);
        printSetElements(emptySet, universeSize);
        
        // Test z wartościami przekraczającymi rozmiar uniwersum
        std::cout << "\nTest z wartościami przekraczającymi rozmiar uniwersum:" << std::endl;
        int smallUniverseSize = 10;
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
        // Sprawdzamy kilka elementów z krokiem 1, aby pokazać, że tylko co drugi element jest w zbiorze
        for (int i = n; i <= n + 10; i++) {
            std::cout << "  Czy " << i << " należy do zbioru? ";
            
            // Obliczamy indeks dla tego elementu
            int index;
            if ((i - n) % 2 == 0) {  // Element z krokiem 2
                index = (i - n) / 2;
            } else {
                index = -1;  // Element nie należy do wzorca
            }
            
            if (index >= 0 && index < universeSize && set.contains(index)) {
                std::cout << "TAK" << std::endl;
            } else {
                std::cout << "NIE" << std::endl;
            }
        }
        
        // Test z n >= m (pusty zbiór)
        std::cout << "\nTest pustego zbioru (n >= m):" << std::endl;
        SetSimple emptySet = createSetEvenStepIntegers(universeSize, 10, 5);
        printSetElements(emptySet, universeSize);
        
        // Test z wartościami przekraczającymi rozmiar uniwersum
        std::cout << "\nTest z wartościami przekraczającymi rozmiar uniwersum:" << std::endl;
        int smallUniverseSize = 5;
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
            std::cout << "  Czy '" << c << "' należy do zbioru? ";
            if (c >= 'a' && c <= 'z') {
                std::cout << (set.contains(c - 'a') ? "TAK" : "NIE") << std::endl;
            } else {
                std::cout << "NIE (poza zakresem a-z)" << std::endl;
            }
        }
        
        // Test z mniejszym rozmiarem uniwersum
        std::cout << "\nTest z mniejszym rozmiarem uniwersum:" << std::endl;
        int smallUniverseSize = 10;
        SetSimple smallSet = createSetLetters(smallUniverseSize);
        std::cout << "Zbiór liter z uniwersum rozmiaru " << smallUniverseSize << ":" << std::endl;
        printLettersSet(smallSet, smallUniverseSize);
    }
    
    // Test two-letter strings set
    {
        std::cout << "\n----- Test zbioru dwuliterowych napisów a-z -----" << std::endl;
        
        const size_t universeSize = 26 * 26;
        
        std::cout << "Tworzenie zbioru wszystkich dwuliterowych napisów (rozmiar uniwersum: " 
                  << universeSize << ")" << std::endl;
        
        SetSimple set = createSetTwoLetterStrings(universeSize);
        
        // Wyświetlamy tylko część zbioru, bo jest duży
        printTwoLetterStringsSet(set, universeSize, 15);
        
        std::cout << "\nTestowanie mapowania między napisami a indeksami:" << std::endl;
        std::string testStrings[] = {"aa", "ab", "az", "ba", "zz", "a", "abc", "1a"};
        for (const std::string& str : testStrings) {
            int index = mapTwoLetterStringToIndex(str);
            std::cout << "  Mapowanie '" << str << "' -> ";
            
            if (index != -1) {
                std::cout << index << " -> " << mapIndexToTwoLetterString(index);
                std::cout << " (należy do zbioru: " << (set.contains(index) ? "TAK" : "NIE") << ")" << std::endl;
            } else {
                std::cout << "nieprawidłowy napis (nie należy do zbioru)" << std::endl;
            }
        }
        
        // Test z mniejszym rozmiarem uniwersum
        std::cout << "\nTest z mniejszym rozmiarem uniwersum:" << std::endl;
        int smallUniverseSize = 30;
        SetSimple smallSet = createSetTwoLetterStrings(smallUniverseSize);
        std::cout << "Zbiór dwuliterowych napisów z uniwersum rozmiaru " << smallUniverseSize << ":" << std::endl;
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

    // Test push
    {
        SetHashed set(10);
        set.push(1);
        set.push(2);
        set.push(3);
        assert(!set.empty());
        std::cout << "Push test passed!\n";
    }

    // Test pop
    {
        SetHashed set(10);
        set.push(1);
        set.pop(1);
        assert(set.empty());
        std::cout << "Pop test passed!\n";
    }

    // Test contains
    {
        SetHashed set(10);
        set.push(1);
        assert(set.contains(1));
        std::cout << "Contains test passed!\n";
    }

    // Test unionWith
    {
        SetHashed set1(10);
        SetHashed set2(10);
        SetHashed result(20);
        set1.push(1);
        set1.push(2);
        set2.push(3);
        set2.push(4);
        result = set1.unionWith(set2);
        assert(result.contains(1) && result.contains(3));
        std::cout << "unionWith test passed!\n";
    }

    // Test intersection
    {
        SetHashed set1(10);
        SetHashed set2(10);
        SetHashed result(20);
        set1.push(1);
        set1.push(2);
        set2.push(2);
        set2.push(3);
        result = set1.intersection(set2);
        assert(result.contains(2));
        std::cout << "Intersection test passed!\n";
    }

    // Test difference
    {
        SetHashed set1(10);
        SetHashed set2(10);
        SetHashed result(20);
        set1.push(1);
        set1.push(2);
        set2.push(1);
        set2.push(3);
        result = set1.difference(set2);
        assert(result.contains(2));
        std::cout << "Difference test passed!\n";
    }

    // Test isIdentical
    {
        SetHashed set1(10);
        SetHashed set2(10);
        set1.push(1);
        set2.push(1);
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