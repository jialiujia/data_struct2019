//
// Created by 贾屹伦 on 2018/6/25.
//

#include "sort.hpp"

void InsertSort(int R[], int n) {
    for (int i = 1; i < n; ++i) {
        int j = i - 1;
        int temp = R[i];
        while (j >=0 && R[j] > temp) {
            R[j + 1] = R[j];
            --j;
        }

        R[j + 1] = temp;
    }
}

void InsertHalfSort(int R[], int n) {
    int low, high;
    for (int i = 1; i < n; ++ i) {
        low = i - 1;
        high = i;
        int temp = R[i];
        while (low <= high) {
            int m = (high + low) / 2;
            if (R[m] > temp) {
                high = m - 1;
            } else {
                low = m + 1;
            }
        }
        int j;
        for (j = i - 1; j >= high + 1; -- j) {
            R[j + 1] = R[j];
        }
        R[j + 1] = temp;
    }
}