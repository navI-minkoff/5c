#ifndef INC_5C_SORTING_H
#define INC_5C_SORTING_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <string.h>
#include <time.h>

void inputArray_(int *const a, const size_t n);

void outputArray_(const int *const a, const size_t n);

// обмен значений по адресам a и b
void swap(int *a, int *b);

int isOrdered(const int *a, const size_t n);

void generateRandomArray(int *a, size_t size);

void generateOrderedArray(int *a, size_t size);

void generateOrderedBackwards(int *a, size_t size);

// сортировка пузырьком массива a размера n
void bubbleSort(int *a, const size_t n);

// сортировка выбором массива a размера n
void selectionSort(int *a, const size_t n);

// сортировка вставками массива a размера n
void insertionSort(int *a, const size_t size);

// сортировка рассческой массива a размера n
void combSort(int *a, const size_t n);

// сортировка шелла массива a размера n
void shellSort(int *a, size_t size);

// цифровая сортировка массива a размера n
void radixSort(int *a, size_t n);

// пиромидальная сортировка массива a размера n
void heapSort(int *a, size_t n);

// сортировка слиянием массива a размера n
void mergeSort(int *a, size_t n);

// быстрая сортировка массива a размера n
void qsort_(int *array, size_t n);

long long getBubbleSortNComps(int *a, const size_t n);

long long getSelectionSortNComps(int *a, const size_t n);

long long getInsertionSortNComps(int *a, const size_t size);

long long getCombSortNComps(int *a, const size_t n);

long long getShellSortNComps(int *a, const size_t size);

long long getRadixSortNComps(int *a, const size_t n);

long long getHeapSortNComps(int *a, const size_t n);

long long getMergeSortNComps(int *a, const size_t n);

long long getQsortNComps(int *array, const size_t n);

#endif //INC_5C_SORTING_H
