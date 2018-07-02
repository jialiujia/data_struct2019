#include <iostream>
#include "sort/sort.hpp"

using namespace std;

void BubbleSort_Test() {
    int R[] = {10, 20, 15, 11, 30, 10};
    BubbleSort(R, 6);
    for (int i = 0; i < 6; ++ i) {
        printf("%d\n", R[i]);
    }
}

void QuickSort_Test() {
    int R[] = {10, 20, 15, 11, 30, 10};
    QuickSort(R, 0, 5);
    for (int i = 0; i < 6; ++ i) {
        printf("%d\n", R[i]);
    }
}

void SelectSort_Test() {
    int R[] = {10, 20, 15, 11, 30, 10};
    SelectSort(R, 6);
    for (int i = 0; i < 6; ++ i) {
        printf("%d\n", R[i]);
    }
}

void HeapSort_Test() {
    int R[] = {10, 20, 15, 11, 30, 10};
    HeapSort(R, 6);
    for (int i = 0; i < 6; ++ i) {
        printf("%d\n", R[i]);
    }
}

void MergeSort_Test() {
    int R[] = {10, 20, 15, 11, 30, 10};
    MergeSort(R, 0, 5);
    for (int i = 0; i < 6; ++ i) {
        printf("%d\n", R[i]);
    }
}

int main() {
    MergeSort_Test();
}