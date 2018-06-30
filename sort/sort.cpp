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

void ShellSort(int R[], int n) {
    int gap; //增量值

    for (gap = n / 2; gap > 0; gap = gap / 2) {
        for (int i = 0; i < gap; ++ i) {
            int count = 0;
            int tmp[MAXSIZE];
            for (int j = i; j < n; j += gap) {
                tmp[count] = R[j];
                ++ count;
            }
            InsertSort(tmp, count);
            for (int k = 0; k < count; ++ k) {
                R[i + gap * k] = tmp[k];
            }
        }
    }
}

void BubbleSort(int R[], int n) {
    for (int i = n - 1; i > 0; -- i) {
        int flag = 0;
        for (int j = 0; j < i; ++ j) {
            if (R[j] > R[j + 1]) {
                int tmp = R[j];
                R[j] = R[j + 1];
                R[j + 1] = tmp;
                flag = 1;
            }
        }

        if (flag == 0) {
            return;
        }
    }
}