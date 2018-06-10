//
// Created by Administrator on 2018/5/31.
//

#include "queue.hpp"
#ifdef __APPLE__
    #include "mm_malloc.h"
#else
    #include "malloc.h"
#endif


void initQueue(SqQueue &queue) {
    queue.front = queue.rear = 0;
}

int isQueueEmpty(SqQueue queue) {
    return queue.front == queue.rear ? 1 : 0;
}

int enQueue(SqQueue &queue, int x) {
   if ((queue.rear + 1) % MAXSIZE == queue.front) {
       return 0;
   }

    queue.rear = (queue.rear + 1) % MAXSIZE;
    queue.data[queue.rear] = x;
    return 1;
}

int deQueue(SqQueue &queue, int &x) {
    if (queue.front == queue.rear) {
        return 0;
    }

    queue.front = (queue.front + 1) % MAXSIZE;
    x = queue.data[queue.front];
    return 1;
}

void initQueue(LiQueue* &queue) {
    queue = (LiQueue *) malloc(sizeof(LiQueue));
    queue ->front = queue ->rear = nullptr;
}

int isQueueEmpty(LiQueue *queue) {
    return queue ->front == nullptr || queue ->rear == nullptr ? 1 : 0;
}

int enQueue(LiQueue* &queue, int x) {
    QNode *node = (QNode *) malloc(sizeof(QNode));
    node ->data = x;
    if (queue ->rear == nullptr) {
        queue ->front = queue ->rear = node;
    } else {
        queue ->rear ->next = node;
        queue ->rear = node;
    }
    return 1;
}

int deQueue(LiQueue* &queue, int &x) {
    if (queue ->front == nullptr || queue ->rear == nullptr) {
        return 0;
    }

    QNode *node = queue ->front;
    x = node ->data;
    if (queue ->front == queue ->rear) {
        queue ->front = queue ->rear = nullptr;
    } else {
        queue ->front = queue ->front ->next;
    }
    free(node);
    return 1;
}