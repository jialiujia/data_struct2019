//
// Created by 贾屹伦 on 2018/6/25.
//

#ifndef DATA_STRUCT2019_SORT_HPP
#define DATA_STRUCT2019_SORT_HPP

#define MAXSIZE 100

///直接插入排序
void InsertSort(int R[], int n);

///折半插入排序
void InsertHalfSort(int R[], int n);

///希尔排序（缩小增量排序）
void ShellSort(int R[], int n);

///冒泡排序
void BubbleSort(int R[], int n);

///快速排序
void QuickSort(int R[], int low, int high);

///简单选择排序
void SelectSort(int R[], int n);

///堆排序
void HeapSort(int R[], int n);

///归并排序
void MergeSort(int R[], int low, int high);


#endif //DATA_STRUCT2019_SORT_HPP
