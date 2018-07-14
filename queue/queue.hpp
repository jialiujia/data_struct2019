//
// Created by Administrator on 2018/5/31.
//

#ifndef DATA_STRUCT2019_QUEUE_HPP
#define DATA_STRUCT2019_QUEUE_HPP

#define MAX_CAPACITY 100

typedef struct sq_queue {
    int data[MAX_CAPACITY];
    int front;
    int rear;
} SqQueue;

typedef struct q_node {
    int data;
    q_node *next;
} QNode;

typedef struct li_queue {
    q_node *front; //队头指针
    q_node *rear;  //队尾指针
} LiQueue;

void initQueue(SqQueue &queue); //初始化顺序队

int isQueueEmpty(SqQueue queue); //判断队空

int enQueue(SqQueue &queue, int x); //进队

int deQueue(SqQueue &queue, int &x); //出队

void initQueue(LiQueue* &queue); //初始化链队

int isQueueEmpty(LiQueue *queue); //判断队空

int enQueue(LiQueue* &queue, int x); //进队

int deQueue(LiQueue* &queue, int &x); //出队

#endif //DATA_STRUCT2019_QUEUE_HPP
