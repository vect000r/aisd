#include "sorting.hpp"
#include <algorithm>
#include <cmath>

template <typename T>
void bubbleSort(T& arr, int start, int end) {
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
    std::vector<typename T::value_type> temp(right - left + 1); // tworze tymczasowy vector elementów typu T
    int left1 = left;
    int right1 = middle;
    int left2 = middle + 1;
    int right2 = right;
    int i = 0;

    // przepisanie funkcji merge z lekcji 16 kursu Python na C++
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

    for(auto j = 0u; j < temp.size(); j++){
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

// Tworze instancje tych funkcji w zależności od potrzeb
template void bubbleSort<int[10]>(int(&arr)[10], int start, int end);
template void mergeSort<std::vector<int>>(std::vector<int>& arr, int left, int right);
template void printArr<std::vector<int>>(std::vector<int>& arr);
template void printArr<int[10]>(int(&arr)[10]);