//
// Created by Administrator on 2018/6/5.
//

#include "btree.hpp"
#include "malloc.h"
#include "stdio.h

void visit(char c) {
    printf("%c ", c);
}

int op(int a, int b, char Op) {
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

void preorder(BTNode *p) {
    if (p != nullptr) {
        visit(p ->data);
        preorder(p ->lchild);
        preorder(p ->rchild);
    }
}

void inorder(BTNode *p) {
    if (p != nullptr) {
        inorder(p ->lchild);
        visit(p ->data);
        inorder(p ->rchild);
    }
}

void postorder(BTNode *p) {
    if (p != nullptr) {
        postorder(p ->lchild);
        postorder(p ->rchild);
        visit(p ->data);
    }
}

int comp(BTNode *p) {
    if (p == nullptr) {
        return -999;
    }
    if (p ->lchild != nullptr && p ->rchild != nullptr) {
        int a = comp(p ->lchild);
        int b = comp(p ->rchild);
        return op(a, b, p ->data);
    } else {
        return p->data - '0';
    }
}

int getDepth(BTNode *p) {
    if (p == nullptr) {
        return 0;
    } else {
        int l = getDepth(p ->lchild);
        int r = getDepth(p ->rchild);
        return ((l > r) ? l : r) + 1;
    }
}

void search(BTNode *p, BTNode* &q, int key) {
    if (p != nullptr) {
        if (p ->data == key) {
            q = p;
        } else {
            search(p ->lchild, q, key);
            if (q == nullptr) {
                search(p ->rchild, q, key);
            }
        }
    }
}

int trave(BTNode *p, int k, int n) {
    //n 初始为0
    if (p != nullptr) {
        ++ n;
        if (n == k) {
            return p ->data;
        }
        trave(p ->lchild, k, n);
        trave(p ->rchild, k, n);
    }
}

void level(BTNode *p) {
    BTNode *que[MAXSIZE];
    int front, rear;
    front = rear = 0;
    if (p != nullptr) {
        rear = (rear + 1) % MAXSIZE;
        que[rear] = p;
        while (front != rear) {
            front = (front + 1) % MAXSIZE;
            BTNode *q = que[front];
            visit(q ->data);
            if (q ->lchild != nullptr) {
                rear = (rear + 1) % MAXSIZE;
                que[rear] = q ->lchild;
            }

            if (q ->rchild != nullptr) {
                rear = (rear + 1) % MAXSIZE;
                que[rear] = q ->rchild;
            }
        }
    }
}

int maxNode(BTNode *p) {
    int front, rear, Lno;
    St que[MAXSIZE];
    front = rear = 0;
    if (p != nullptr) {
        ++ rear;
        St t{};
        t.lno = 1;t.p = p;
        que[rear] = t;
        while (front != rear) {
            ++ front;
            St st = que[front];
            Lno = st.lno;
            if (st.p ->lchild != nullptr) {
                ++ rear;
                St lst{};
                lst.p = st.p ->lchild;
                lst.lno = st.lno + 1;
            }

            if (st.p ->rchild != nullptr) {
                ++ rear;
                St rst{};
                rst.p = st.p ->rchild;
                rst.lno = st.lno + 1;
            }
        }

        int max = 0;
        for(int i = 1; i <= Lno; ++ i) {
            int k = 0;
            for(int j = 1; j <= rear; ++ j) {
                if (i == que[j].lno) {
                    ++ k;
                }
            }
            max = k > max ? k : max;
        }
        return max;
    } else {
        return 0;
    }
}


