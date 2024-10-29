#ifndef SORTING_HPP
#define SORTING_HPP

#include <iostream>
#include <vector>

template <typename T>
void bubbleSort(T& arr, int start, int end);

template <typename T>
void mergeSort(T& arr, int left, int right);

template <typename T>
void merge(T& arr, int left, int middle, int right);

template <typename T>
void printArr(T& arr);

#endif 