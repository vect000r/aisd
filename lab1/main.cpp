#include "sorting.hpp"

int main() {
    std::vector<int> v = { 9,4,7,3,6,8,2,1,5,0 };
    int arr[10] = { 7,3,9,4,1,5,2,6,8,0 };

    std::cout << "Vector before sorting:" << "\n";
    printArr(v);

    mergeSort(v, 0, v.size() - 1);
    std::cout << "Result of using mergeSort() on a vector:" << "\n";
    printArr(v);
    
    std::cout << "Array before sorting:" << "\n";
    printArr(arr);
    
    bubbleSort(arr, 0, 10);
    std::cout << "Result of using bubbleSort() on an array:" << "\n";
    printArr(arr);
    
    return 0;
}