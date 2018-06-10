//
// Created by 贾屹伦 on 2018/6/9.
//

#include "heap.hpp"

int createminHeap(Heap &heap, int data[], int size) {
    if (size <= 0) {
        return 0;
    }

    heap.size = size;
    for (int i = 0; i < size; ++ i) {
        heap.data[i] = data[i];
    }

    for (int i = (size / 2) - 1; i >= 0; -- i) {
        minheapFilterdown(heap, i, size - 1);
    }
    return 1;
}

int getIndex(Heap heap, int data) {
    if (heap.size == 0) {
        return -1;
    }

    for (int i = 0; i < heap.size; ++i) {
        if (heap.data[i] == data) {
            return i;
        }
    }

    return -1;
}

void minheapFilterdown(Heap &heap, int start, int end) {
    if (start >= end || start < 0 || end >= heap.size) {
        return;
    }

    int cur = start;
    int child = 2 * cur + 1;
    int tmp = heap.data[cur];

    while (child <= end) {
        if (child < end && heap.data[child] > heap.data[child + 1]) {
            ++ child;
        }

        if (tmp <= heap.data[child]) { //左右两孩子中选择较小者
            break;
        } else {
            heap.data[cur] = heap.data[child];
            cur = child;
            child = 2 * cur + 1;
        }
    }

    heap.data[cur] = tmp;
}

int minheapRremove(Heap &heap, int data) {
    if (heap.size == 0) {
        return 0;
    }

    int index = getIndex(heap, data);
    if (index == -1) {
        return 0;
    }

    heap.data[index] = heap.data[-- heap.size];
    minheapFilterdown(heap, index, heap.size - 1);
    return 1;
}

void minheapFilter_up(Heap &heap, int end) {
    if (end <= 0 || end >= heap.size) {
        return;
    }

    int cur = end;
    int start = (cur + 1) / 2;
    int tmp = heap.data[cur];
    while (cur > 0) {
        if (tmp >= heap.data[start]) {
            break;
        } else {
            heap.data[start] = heap.data[cur];
            cur = start;
            start = (cur + 1) / 2;
        }
    }

    heap.data[cur] = tmp;
}

int minheapInsert(Heap &heap, int data) {
    if (heap.size >= MAXSIZE) {
        return 0;
    }

    heap.data[heap.size] = data;
    minheapFilter_up(heap, heap.size);
    ++ heap.size;
    return 1;
}

void maxheapFilterdown(Heap &heap, int start, int end) {
    if (start >= end || start < 0 || end >= heap.size) {
        return;
    }

    int cur = start;
    int child = 2 * cur + 1;
    int tmp = heap.data[cur];

    while (child <= end) {
        if (child < end && heap.data[child] < heap.data[child + 1]) {
            ++ child;
        }

        if (tmp >= heap.data[child]) { //左右两孩子中选择较小者
            break;
        } else {
            heap.data[cur] = heap.data[child];
            cur = child;
            child = 2 * cur + 1;
        }
    }

    heap.data[cur] = tmp;
}

int maxheapRremove(Heap &heap, int data) {
    if (heap.size == 0) {
        return 0;
    }

    int index = getIndex(heap, data);
    if (index == -1) {
        return 0;
    }

    heap.data[index] = heap.data[-- heap.size];
    maxheapFilterdown(heap, index, heap.size - 1);
    return 1;
}

void maxheapFilter_up(Heap &heap, int end) {
    if (end <= 0 || end >= heap.size) {
        return;
    }

    int cur = end;
    int start = (cur + 1) / 2;
    int tmp = heap.data[cur];
    while (cur > 0) {
        if (tmp <= heap.data[start]) {
            break;
        } else {
            heap.data[start] = heap.data[cur];
            cur = start;
            start = (cur + 1) / 2;
        }
    }

    heap.data[cur] = tmp;
}

int maxheapInsert(Heap &heap, int data) {
    if (heap.size >= MAXSIZE) {
        return 0;
    }

    heap.data[heap.size] = data;
    maxheapFilter_up(heap, heap.size);
    ++ heap.size;
    return 1;
}