#include <iostream>
#include "sort/sort.hpp"
#include "search/hash.hpp"

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

void BucketSort_Test() {
    int R[] = {10, 20, 15, 11, 30, 10};
    BubbleSort(R, 6);
    for (int i = 0; i < 6; ++ i) {
        printf("%d\n", R[i]);
    }
}

void RadixSort_Test() {
    int R[] = {50, 3, 542, 745, 2014, 154, 63, 616};
    RadixSort(R, 8);
    for (int i = 0; i < 8; ++ i) {
        printf("%d\n", R[i]);
    }
}

void Hash_test() {
    HashTable *hashTable;
    InitHashTable(hashTable);
    if (hashTable == nullptr) {
        printf("hashTable init error");
        return;
    }

    PutHashKV(hashTable, "a", "a");
    PutHashKV(hashTable, "b", "b");
    PutHashKV(hashTable, "c", "d");
    PutHashKV(hashTable, "ad", "aaa");
    PutHashKV(hashTable, "a", "c");
    PutHashKV(hashTable, "ass", "ass");
    PutHashKV(hashTable, "ass", "add");
    PutHashKV(hashTable, "ae", "ae");
    PutHashKV(hashTable, "agg", "r");
    printf("%d\n", hashTable ->size);

    RemoveHashKV(hashTable, "ad");
    printf("%d\n", hashTable ->size);
    char *r = GetHashValue(hashTable, "ae");
    printf(r);
}

int main() {
    Hash_test();
}