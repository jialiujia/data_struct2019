//
// Created by Administrator on 2018/6/4.
//

#include "matrix.hpp"
#include "stdio.h"
#include "stdlib.h"

void trsmat(int A[][MAX_CAPACITY], int B[][MAX_CAPACITY], int m, int n) {
    for (int i = 0; i < m; ++ i) {
        for (int j = 0; j < n; ++ j) {
            B[j][i] = A[i][j];
        }
    }
}

void addmat(int C[][MAX_CAPACITY], int A[][MAX_CAPACITY], int B[][MAX_CAPACITY], int m, int n) {
    for (int i = 0; i < m; ++ i) {
        for (int j = 0; j < n; ++ j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void mutmat(int C[][MAX_CAPACITY], int A[][MAX_CAPACITY], int B[][MAX_CAPACITY], int m, int n, int k) {
    for (int i = 0; i < m; ++ i) {
        for (int j = 0; j < k; ++ k) {
            C[i][j] = 0;
            for (int h = 0; h < n; ++ h) {
                C[i][j] += A[i][h] * B[h][j];
            }
        }
    }
}

void createtrimat(float A[][MAX_CAPACITY], int m, int n, float B[][3]) {
    int k = 1;
    for (int i = 0; i < m; ++ i) {
        for (int j = 0; j < n; ++ j) {
            if (A[i][j] != 0) {
                B[k][0] = A[i][j];
                B[k][1] = i;
                B[k][2] = j;
                ++ k;
            }
        }
    }

    B[0][0] = k - 1;
    B[0][1] = m;
    B[0][2] = n;
}

void printtrimat(float B[][3]) {
    int num = (int)(B[0][0]);
    int m = (int) B[0][1];
    int n = (int) B[0][2];
    int k = 1;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++ j) {
            if(B[k][1] == i && B[k][2] == j) {
                printf("%f", B[k][0]);
                printf(" ");
                ++ k;
            } else {
                printf("0");
                printf(" ");
            }
        }
        printf("\n");
    }
}

int createcrosslistmat(float A[][MAX_CAPACITY], int m, int n, int k, CrossList &list) {
    if (list.rhead) {
        free(list.rhead);
    }

    if (list.chead) {
        free(list.chead);
    }

    list.chead = static_cast<ol_node *>(malloc(sizeof(OLNode)));
    if (!list.chead) {
        return 0;
    }
    list.rhead = static_cast<ol_node *>(malloc(sizeof(OLNode)));
    if (!list.rhead) {
        return 0;
    }

    list.m = m;
    list.n = n;
    list.k = k;

    for(int i = 0; i < m; ++i) {
        list.rhead[i].right = nullptr;
        list.rhead[i].down = nullptr;
    }

    for(int j = 0; j < n; ++j) {
        list.chead[j].right = nullptr;
        list.rhead[j].down = nullptr;
    }

    OLNode *column_head[MAX_CAPACITY]; //缓存列指针
    for (int j = 0; j < n; ++ j) {
        column_head[j] = &(list.chead[j]);
    }

    for (int i = 0; i < m; ++ i) {
        OLNode* row_head = &list.rhead[i];
        for (int j = 0; j < n; ++ j) {
            if (A[i][j] != 0) {
                OLNode *node = static_cast<OLNode *>(malloc(sizeof(OLNode)));
                if (!node) {
                    return 0;
                }
                node ->row = i;
                node ->col = j;
                node ->val = A[i][j];
                node ->down = nullptr;
                node ->right = nullptr;

                row_head ->right = node;
                row_head = row_head ->right;

                OLNode *col_head = column_head[j];
                col_head ->down = node;
                column_head[j] = col_head ->down;
            }
        }
    }
    return 1;
}