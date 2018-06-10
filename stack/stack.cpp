//
// Created by Administrator on 2018/5/31.
//

#include "stack.hpp"
#include "stdio.h"
#include "stdlib.h"
#ifdef __APPLE__
#include "mm_malloc.h"
#else
#include "malloc.h"
#endif

void initStack(SqStack &stack) {
    stack.top = -1;
}

int isEmpty(SqStack stack) {
    return stack.top == -1 ? 1 : 0;
}

int push(SqStack &stack, int x) {
    if (stack.top == MAXSIZE -1) {
        return 0;
    }

    stack.data[++ stack.top] = x;
    return 1;
}

int pop(SqStack stack, int &x) {
    if (stack.top == -1) {
        return 0;
    }

    x = stack.data[stack.top --];
    return 1;
}

void initStack(LNode* &lst) {
    lst = (LNode *) malloc(sizeof(LNode));
}

int isEmpty(LNode *lst) {
    return lst ->next == NULL ? 1 : 0;
}

void push(LNode* &lst, int x) {
    LNode *node = (LNode *) malloc(sizeof(LNode));
    node ->data = x;node ->next = NULL;
    node ->next = lst ->next;
    lst ->next = node;
}

int pop(LNode* &lst, int &x) {
    if (lst ->next == NULL) {
        return 0;
    }

    LNode *node = lst ->next;
    x = node ->data;
    lst ->next = lst ->next ->next;
    free(node);
    return 1;
}

int match(char exp[], int n) {
    if (n < 2) {
        return 0;
    }
    SqStack stack;
    stack.top = -1;
    int i;
    for (i = 0; i < n; ++ i) {
        if (exp[i] == '(') {
            stack.data[++ stack.top] = 1;
        } else if (exp[i] == ')') {
            if (stack.top == -1) {
                return 0;
            } else {
                -- stack.top;
            }
        }
    }

    if (stack.data[0] != 1 || stack.top != -1) {
        return 0;
    } else {
        return 1;
    }
}

int op(int a, char Op, int b) {
    switch (Op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case 'x':
        case 'X':
        case '*':
            return a * b;
        case '/':
            if (b == 0) {
                return -999;
            } else {
                return a / b;
            }
        default:
            return -999;
    }
}

int com(char exp[]) {
    int top = -1;
    int stack[MAXSIZE];
    int i = 0;

    while (exp[i] != '\0') {
        if (exp[i] >= '0' && exp[i] <= '9') {
            stack[++ top] = exp[i] - '0';
        } else {
            int a, b;
            if (top < 1) {
                return -999;
            } else {
                a = stack[top --];
                b = stack[top --];
                int c = op(b, exp[i], a);
                if (c == -999) {
                    return -999;
                } else {
                    stack[++ top] = c;
                }
            }
        }
        ++ i;
    }

    if (top != 0) {
        return -999;
    } else {
        return stack[0];
    }
}



