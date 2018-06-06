//
// Created by Administrator on 2018/6/4.
//

#ifndef DATA_STRUCT2019_MATRIX_HPP
#define DATA_STRUCT2019_MATRIX_HPP

#define M 4
#define N 5
#define MAXSIZE 100

typedef struct ol_node {
    int row, col; //行号列号
    float val;
    ol_node *down, *right; //指向右节点、下节点指针
} OLNode;

typedef struct cross_list {
    ol_node *rhead, *chead;
    int m, n, k; //矩阵行数、列数、非零节点总数
} CrossList;

void trsmat(int A[][MAXSIZE], int B[][MAXSIZE], int m, int n); //矩阵置换

void addmat(int C[][MAXSIZE], int A[][MAXSIZE], int B[][MAXSIZE], int m, int n); //矩阵相加

void mutmat(int C[][MAXSIZE], int A[][MAXSIZE], int B[][MAXSIZE], int m, int n, int k); //矩阵相乘

void createtrimat(float A[][MAXSIZE], int m, int n, float B[][3]); //建立三元组

void printtrimat(float B[][3]); //打印三元组

int createcrosslistmat(float A[][MAXSIZE], int m, int n, int k, CrossList &list); //建立十字链表

#endif //DATA_STRUCT2019_MATRIX_HPP
