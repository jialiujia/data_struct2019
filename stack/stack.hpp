//
// Created by Administrator on 2018/5/31.
//

#ifndef DATA_STRUCT2019_STACK_HPP
#define DATA_STRUCT2019_STACK_HPP

#define MAX_CAPACITY 100

typedef struct sq_stack {
    int data[100];
    int top; //栈顶指针
} SqStack;

typedef struct l_node {
    int data;
    l_node *next;
} LNode;

void initStack(SqStack &stack); //初始化栈

int isEmpty(SqStack stack); //是否栈空

int push(SqStack &stack, int x); //进栈

int pop(SqStack stack, int &x); //出栈

void initStack(LNode* &lst); //初始化链栈

int isEmpty(LNode *lst); //链栈是否为空

void push(LNode* &lst, int x); //进栈

int pop(LNode* &lst, int &x); //出栈

int match(char exp[], int n); //匹配小括号

int com(char exp[]); //后缀式计算.'\0'结尾

#endif //DATA_STRUCT2019_STACK_HPP
