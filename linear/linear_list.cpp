//
// Created by Administrator on 2018/5/30.
//

#include "linear_list.hpp"
#include "stdio.h"
#include "stdlib.h"
#include <iostream>

void initList(Sqlist &L) {
    L.length = 0;
}

int findElem(Sqlist L, int e) {
    if (L.length == 0) {
        return -1;
    }
    int i;
    for (i = 0; i < L.length; ++ i) {
        if (L.data[i] == e) {
            return i;
        }
    }
    return -1;
}

int insertElem(Sqlist &L, int p, int e) {
    if (p < 0 || p >= L.length || L.length >= MAX_SIZE) {
        return 0;
    }

    int i;
    for (i = L.length - 1; i >= p ;-- i) {
        L.data[i + 1] = L.data[i];
    }
    L.data[p] = e;
    ++ L.length;
    return 1;
}

int deleteElem(Sqlist &L, int p, int &e) {
    if (p < 0 || p >= L.length || L.length >= MAX_SIZE) {
        return 0;
    }

    int i;
    e = L.data[p];
    for (i = p; i < L.length; ++ i) {
        L.data[i] = L.data[i + 1];
    }
    -- L.length;
    return 1;
}

int getElem(Sqlist L, int p, int &e) {
    if (p < 0 || p >= L.length || L.length >= MAX_SIZE) {
        return 0;
    }
    e = L.data[p];
    return 1;
}

void mergeP(LNode *A, LNode *B, LNode* &C) {
    int i = 0;
    LNode *p = A ->next;
    LNode *q = B ->next;

    C = A;
    C ->next = NULL;
    free(B);

    while (p != NULL && q != NULL) {
        if (p ->data <= q ->data) {
            C ->next = p;
            C = C ->next;
            p = p ->next;
        } else {
            C ->next = q;
            C = C ->next;
            q = q ->next;
        }
        C ->next = NULL;
        if (p != NULL) {
            C ->next = p;
        }
        if (q != NULL) {
            C ->next = q;
        }
    }
}

void createListR(LNode* &c, int a[], int n) {
    c = (LNode *) malloc(sizeof(LNode));
    int i;
    for(i = 0; i < n; ++ i) {
        LNode *s = (LNode *) malloc(sizeof(LNode));
        s ->data = i;
        c ->next = s;
        c = c ->next;
    }
    c ->next = NULL;
}

void createListF(LNode* &c, int a[], int n) {
    c = (LNode *) malloc(sizeof(LNode));
    int i = 0;
    for (i = 0; i < n; ++ i) {
        LNode *s = (LNode *) malloc(sizeof(LNode));
        s ->data = i;
        s ->next = c ->next;
        c ->next = s;
    }
}

void mergeM(LNode *A, LNode *B, LNode* &C) {
    int i = 0;
    LNode *p = A ->next;
    LNode *q = B ->next;

    C = A;
    C ->next = NULL;
    free(B);

    while (p != NULL && q != NULL) {
        if (p ->data <= q ->data) {
            LNode *s = p;
            s ->next = C ->next;
            C ->next = s;
            p = p ->next;
        } else {
            LNode *s = q;
            s ->next = C ->next;
            C ->next = s;
            q = q ->next;
        }

        while (p != NULL) {
            LNode *s = p;
            s ->next = C ->next;
            C ->next = s;
            p = p ->next;
        }
        while (q != NULL) {
            LNode *s = q;
            s ->next = C ->next;
            C ->next = s;
            q = q ->next;
        }
    }
}

int findAndDelete(LNode *C, int x) {
    LNode *p = C;
    int i = 0;
    while (p ->next != NULL) {
        if(p ->next ->data == x) {
            LNode *q = p ->next;
            p ->next = p ->next ->next;
            free(q);
            i = 1;
            break;
        } else {
            p = p ->next;
        }
    }
    return i;
}

void createDListR(DLNode* &L, int a[], int n) {
    int i = 0;
    L = (DLNode *) malloc(sizeof(DLNode));
    L ->next = NULL;
    L ->prior = NULL;
    DLNode *p = L;
    for(i = 0; i < n; ++ i) {
        DLNode *node = (DLNode *) malloc(sizeof(DLNode));
        node ->next = NULL;
        node ->prior = p;
        node ->data = a[i];
        p ->next = node;
        p = p ->next;
    }
}

DLNode* findNode(DLNode *C, int x) {
    DLNode *p = C ->next;
    while (p != NULL) {
        if (p ->data == x) {
            break;
        } else {
            p = p ->next;
        }
    }
    return p;
}

int insertElem(DLNode* &C, int p, int e) {
    int i = 0;
    DLNode *node = C ->next;
    while (node != NULL) {
        if (p == i) {
            DLNode *eNode = (DLNode *) malloc(sizeof(DLNode));
            eNode ->data = e;
            eNode ->prior = node ->prior;
            eNode ->next = node;
            node ->prior ->next = eNode;
            node ->prior = eNode;
            return 1;
        }
        ++ i;
        node = node ->next;
    }
    return 0;
}

int deleteElem(DLNode* &C, int p, int &e) {
    int i = 0;
    DLNode *node = C ->next;
    while (node != NULL) {
        if (p == i) {
            e = node ->data;
            node ->prior ->next = node ->next;
            node ->next ->prior = node ->prior;
            node ->next = node ->prior = NULL;
            free(node);
            return 1;
        }
        ++ i;
        node = node ->next;
    }
    return 0;
}

void initList(SList L[]) {
    int i;
    for(i = 0; i < MAX_SIZE - 1; ++ i) {
        L[i].cur = i + 1;
    }
    L[MAX_SIZE - 1].cur = 0;
}

int mallocList(SList L[]) {
    int i = L[0].cur;
    if (i != 0) {
        L[0].cur = L[i].cur;
    }
    if (L[MAX_SIZE - 1].cur == 0) {
        L[MAX_SIZE - 1].cur = i;
    }
    return i;
}

int  getLength(SList L[]) {
    int rear = L[0].cur;
    int front = L[MAX_SIZE - 1].cur;

    if (front == 0) {
        return 0;
    }

    int length = 0;
    while (front != rear) {
        ++ length;
        front = L[front].cur;
    }

    return length;
}

int getElemData(SList L[], int p, int &e) {
    int rear = L[0].cur;
    int front = L[MAX_SIZE - 1].cur;

    if (front == 0) {
        return 0;
    }

    int position = 0;
    while (front != rear) {
        if (position == p) {
            e = L[front].data;
            return 1;
        }
        ++ position;
        front = L[front].cur;
    }

    return 0;
}

int getElem(SList L[], int p) {
    int rear = L[0].cur;
    int front = L[MAX_SIZE - 1].cur;

    if (front == 0) {
        return -1;
    }

    int position = 0;
    while (front != rear) {
        if (position == p) {
            return front;
        }
        ++ position;
        front = L[front].cur;
    }
    return -1;
}

int getElem(SList L[], int p, SList &list) {
    int rear = L[0].cur;
    int front = L[MAX_SIZE - 1].cur;

    if (front == 0) {
        return 0;
    }

    int position = 0;
    while (front != rear) {
        if (position == p) {
            list = L[front];
            return 1;
        }
        ++ position;
        front = L[front].cur;
    }

    return 0;
}

int insertElem(SList L[], int p, int x) {
    int length = getLength(L);
    if (length == 0) {
        return 0;
    }

    if (p < 0 || p >= length) {
        return 0;
    }
    int node = mallocList(L);
    L[node].data = x;
    if (p == 0) {
        int last = getElem(L, length - 1);
        int tmp = L[node].cur;
        L[node].cur = L[MAX_SIZE - 1].cur;
        L[MAX_SIZE - 1].cur = node;
        L[0].cur = tmp;
        L[last].cur = tmp;
        return 1;
    }
    int last = getElem(L, length - 1);
    int pNode = getElem(L, p - 1);
    int tmp =  L[node].cur;
    L[node].cur = L[pNode].cur;
    L[pNode].cur = node;
    L[last].cur = tmp;
    L[0].cur = tmp;
    return 1;
}

int deleteElem(SList L[], int p) {
    int length = getLength(L);
    if (length == 0) {
        return 0;
    }

    if (p < 0 || p >= length) {
        return 0;
    }

    if (p == 0) {
        int front = L[MAX_SIZE - 1].cur;
        int last = getElem(L, length - 1);
        L[MAX_SIZE - 1].cur = L[front].cur;
        L[front].cur = L[0].cur;
        L[0].cur = front;
        L[last].cur = front;
        L[front].data = 0;
        return 1;
    }

    if (p == length - 1) {
        int rear = getElem(L, p);
        L[rear].data = 0;
        L[rear].cur = L[0].cur;
        L[0].cur = rear;
        return 1;
    }

    int pre, next, last;
    pre = getElem(L, p - 1);
    next = getElem(L, p);
    last = getElem(L, length - 1);
    int tmp = L[next].cur;
    L[pre].cur = tmp;
    L[next].cur = L[0].cur;
    L[0].cur = next;
    L[last].cur = L[0].cur;
    return 1;
}

void printList(SList L[]) {
    int front = L[MAX_SIZE - 1].cur;
    int rear = L[0].cur;
    while (front != rear) {
        std::cout << L[front].data << " " << std::endl;
        front = L[front].cur;
    }
}