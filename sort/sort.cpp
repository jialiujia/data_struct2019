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

void QuickSort(int R[], int low, int high) {
    if (low >= high) {
        return;
    }

    int i = low, j = high;
    int tmp = R[low];
    while (i < j) {
        while (i < j && R[j] >= tmp) { -- j; }
        if (i < j) {
            R[i] = R[j];
            ++ i;
        }

        while (i < j && R[i] < tmp) { ++ i; }
        if (i < j) {
            R[j] = R[i];
            -- j;
        }
    }
    R[i] = tmp;
    QuickSort(R, low, i - 1); //temp左边关键字排序
    QuickSort(R, i + 1, high); //temp右边关键字排序
}

void SelectSort(int R[], int n) {
    for (int i = 0; i < n; ++ i) {
        int k = i;
        /* 找出最小元素 */
        for (int j = i + 1; j < n; ++ j) {
            if (R[k] > R[j]) {
                k = j;
            }
        }

        int tmp = R[i];
        R[i] = R[k];
        R[k] = tmp;
    }
}

///最大堆的向下调整
void Sift(int R[], int low, int high) {
    int c = low;

    for (int i = (c * 2) + 1; i <= high; c = i, i = (2 * i) + 1) {
        if (i < high && R[i] < R[i + 1]) { // i为左孩子，比较左右孩子大小
            ++ i;
        }

        if (R[c] < R[i]) {
            int tmp = R[c];
            R[c] = R[i];
            R[i] = tmp;
        } else {
            break;
        }
    }
}

void HeapSort(int R[], int n) {
    /* 初始化最大堆 */
    for (int i = (n / 2 + n % 2); i >= 0; -- i) {
        Sift(R, i, n - 1);
    }

    for (int i = n - 1; i > 0; -- i) {
        int tmp = R[i];
        R[i] = R[0];
        R[0] = tmp;
        Sift(R, 0, i - 1);
    }
}

///将两段有序序列合并成一段有序序列
void Merge(int R[], int low, int mid, int high) {
    int A[MAXSIZE];
    int B[MAXSIZE];
    int count1 = 0, count2 = 0;

    for (int i = low; i <= mid; ++ i) {
        A[count1] = R[i];
        ++ count1;
    }

    for (int j = mid + 1; j <= high; ++ j) {
        B[count2] = R[j];
        ++ count2;
    }

    int i = 0, j = 0, count = low;
    while (i < count1 && j < count2) {
        if (A[i] > B[j]) {
            R[count] = B[j];
            ++ count;
            ++ j;
        } else {
            R[count] = A[i];
            ++ count;
            ++ i;
        }
    }

    if (i < count1) {
        while (i < count1) {
            R[count] = A[i];
            ++ count;
            ++ i;
        }
    } else {
        while (j < count2) {
            R[count] = B[j];
            ++ count;
            ++ j;
        }
    }
}

void MergeSort(int R[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        MergeSort(R, low, mid);
        MergeSort(R, mid + 1, high);
        Merge(R, low, mid, high);
    }
}

///获取最大值
int getMax(int R[], int n) {
    int max = -1;
    for (int i = 0; i < n; ++ i) {
        if (max < R[i]) {
            max = R[i];
        }
    }
    return max;
}

void BucketSort(int R[], int n) {
    int max = getMax(R, n);
    if (max == -1) {
        return;
    }

    int bucket[MAXSIZE];

    for (int i = 0; i <= max; ++ i) {
        bucket[i] = 0;
    }

    for (int i = 0; i < n; ++ i) {
        ++ bucket[R[i]];
    }

    int count = 0;
    for (int i = 0; i <= max; ++ i) {
        while (bucket[i] > 0) {
            R[count] = i;
            ++ count;
            -- bucket[i];
        }
    }
}

///指数排序
void countSort(int R[], int n, int radix) {
    int bucket[10];
    for (int &i : bucket) {
        i = 0;
    }

    for (int i = 0; i < n; ++ i) {

        ++ bucket[(R[i] / radix) % 10];
    }

    int count = 0;
    int output[n];
    for (int i = 0; i <= 9; ++ i) {
        for (int j = 0; j < n, bucket[i] > 0; ++ j) {
            if (R[j] / radix % 10 == i) {
                output[count] = R[j];
                ++ count;
                -- bucket[i];
            }
        }
    }

    for (int i = 0; i < n; ++ i) {
        R[i] = output[i];
    }
}

void RadixSort(int R[], int n) {
    int max = getMax(R, n);
    if (max == -1) { return; }
    for (int i = 1; max / i > 0; i *= 10) {
        countSort(R, n, i);
    }
}

void CountSort(int A[], int B[], int n) {
    for (int i = 0; i < n; ++ i) {
        int count = 0;
        for (int j = 0; j < n; ++ j) {
            if (A[j] < A[i]) {
                ++ count;
            }
        }

        B[count] = A[i];
    }
}

void DoubleBubbleSort(int R[], int n) {
    int low = 0;
    int high = n - 1;
    int flag = 1;
    while (flag == 1) {
        flag = 0;
        for (int j = high; j > low; -- j) {
            if (R[j - 1] > R[j]) {
                int tmp = R[j];
                R[j] = R[j - 1];
                R[j - 1] = tmp;
                flag = 1;
            }
        }
        ++ low;

        for (int i = low; i < high; ++ i) {
            if (R[i] > R[i + 1]) {
                int tmp = R[i];
                R[i] = R[i + 1];
                R[i + 1] = tmp;
                flag = 1;
            }
        }
        --high;
    }
}