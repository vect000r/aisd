/*
OBOWIĄZKOWE DO PRZESŁANIA: Implementacja dwóch algorytmów sortowania w C++, w tym co najmniej jednego zaawansowanego. 
Funkcje sortujące muszą być szablonami, muszą mieć podany interfejs tablicowy lub z iteratorami, wystarczy użyć standardowego porównywania (operator<). 
Proszę przesłać archiwum ZIP katalogu z programem, który zawiera Makefile i pliki źródłowe. 
Program powinien kompilować się poleceniem 'make'.
np. bubblesort, quicksort
wystarczy na std::vector, ale musi by szablonem dzialajacym dla roznych typow.
*/
#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
void bubbleSort(T& arr , int start, int end) {
    bool swapped;
    for(int i = start; i< end - 1; i++){
        swapped = false;
        for(int j = start; j < end-i-1; j++){
            if(arr[j] > arr[j + 1]){
                swapped = true;
                std::swap(arr[j], arr[j+1]);
            }
        }
        if(!swapped){
            break;
        }
    }
}



int main() {
    std::vector<int> v1 = { 9,4,7,3,6,8,2,1,5,0 };
    std::vector<float> v2 = { 9.0, 4.0, 7.0, 3.0, 6.0, 8.0, 2.0, 5.0, 1.0, 0.0};
    int arr1[10] = { 9,4,7,3,6,8,2,1,5,0 };

    bubbleSort(v1, 0, v1.size());
    bubbleSort(arr1, 0, 10);


    for(auto i: arr1){
        std::cout << i << "\n";
    }
    return 0;
}