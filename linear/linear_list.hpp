//
// Created by Administrator on 2018/5/30.
//

/**
 * 线性表
 */
#ifndef DATA_STRUCT2019_LINEAR_LIST_HPP
#define DATA_STRUCT2019_LINEAR_LIST_HPP

#define MAX_SIZE 100

typedef struct sql_list {
    int data[MAX_SIZE];
    int length;
} Sqlist;

typedef struct l_node {
    int data;
    l_node *next;
} LNode;

typedef struct d_lnode {
    int data;
    d_lnode *prior;
    d_lnode *next;
} DLNode;

typedef struct s_list { //静态链表
    int data;
    int cur; //指向下一游标
} SList;

void initList(Sqlist &L);

int insertElem(Sqlist &L, int p, int e); //插入元素x

int findElem(Sqlist L, int e); //按元素值x查找元素

int deleteElem(Sqlist &L, int p, int &e); //删除p位置元素

int getElem(Sqlist L, int p, int &e);//求指定位置的元素

void mergeP(LNode *A, LNode *B, LNode* &C);//A、B递增合并到C

void createListR(LNode* &c, int a[], int n); //单链表尾插法

void createListF(LNode* &c, int a[], int n); //单链表头插法

void mergeM(LNode *A, LNode *B, LNode* &C); //A、B递减合并到C

int findAndDelete(LNode *C, int x); // 找到并删除x

void createDListR(DLNode* &L, int a[], int n); //尾插法建立双链表

DLNode* findNode(DLNode *C, int x); //查找节点

int insertElem(DLNode* &C, int p, int e); //插入元素x

int deleteElem(DLNode* &C, int p, int &e); //删除p位置元素

void initList(SList L[]); //初始化静态链表

int mallocList(SList L[]); //分配静态链表空闲结点

int insertElem(SList L[], int p, int x); //静态链表插入数据

int deleteElem(SList L[], int p); //静态链表删除结点

int  getLength(SList L[]); //获取静态链表长度

int getElemData(SList L[], int p, int &e); //获取静态链表元素

int getElem(SList L[], int p, SList &list); //获取静态链表元素

int getElem(SList L[], int p); //获取静态链表下标

void printList(SList L[]);


#endif //DATA_STRUCT2019_LINEAR_LIST_HPP
