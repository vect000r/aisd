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
#include <cmath>

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

template <typename T>
void merge(T& arr, int left, int middle, int right){
    std::vector<typename T::value_type> temp(right - left + 1); // tworzymy tymczasowy vector elementów typu T
    int left1 = left;
    int right1 = middle;
    int left2 = middle + 1;
    int right2 = right;
    int i = 0;

    while(left1 <= right1 && left2 <= right2){
        if(arr[left1] <= arr[left2]){
            temp[i] = arr[left1];
            left1++;
        } else {
            temp[i] = arr[left2];
            left2++;
        }
        i++;
    }

    while(left1 <= right1){
        temp[i] = arr[left1];
        left1++;
        i++;
    }

    while(left2 <= right2){
        temp[i] = arr[left2];
        left2++;
        i++; 
    }

    for(int j = 0; j < temp.size(); j++){
        arr[left + j] = temp[j];
    }
};



template <typename T>
void mergeSort(T& arr, int left, int right){
    if(left < right){
        int middle = (left + right) / 2;
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);
        merge(arr, left, middle, right);
    }

};

template <typename T>
void printArr(T& arr){
    for(auto i: arr){
        std::cout << i << " ";
    }
    std::cout << "\n";
}

int main() {
    std::vector<int> v = { 9,4,7,3,6,8,2,1,5,0 };
    int arr[10] = { 9,4,7,3,6,8,2,1,5,0 };

    //bubbleSort(v1, 0, v1.size());
    //bubbleSort(arr1, 0, 10);
    mergeSort(v, 0, v.size() - 1);
    std::cout << "Result of using mergeSort() on a vector:" << "\n";
    printArr(v);
    
    bubbleSort(arr, 0, 10);
    std::cout << "Result of using bubbleSort() on an array:" << "\n";
    printArr(arr);
    

    return 0;
}