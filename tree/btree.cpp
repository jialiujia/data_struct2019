//
// Created by Administrator on 2018/6/5.
//

#include "btree.hpp"
#include "stdio.h
#include "../heap/heap.hpp"
#ifdef __APPLE__
#include "mm_malloc.h"
#else
#include "malloc.h"
#endif

void visit(char c) {
    printf("%c ", c);
}

void visit(int d) {
    printf("%d", d);
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
    int front, rear, Lno = 0;
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

void preorderNonrecursion(BTNode *bt) {
    if (bt != nullptr) {
        BTNode *stack[MAXSIZE];
        int top = -1;
        stack[++ top] = bt;
        while (top != -1) {
            BTNode *node = stack[top --];
            visit(node ->data);
            if (node ->rchild != nullptr) { //优先访问右子树
                stack[++ top] = node ->rchild;
            }
            if (node ->lchild != nullptr) {
                stack[++ top] = node ->lchild;
            }
        }
    }
}

void inorderNonrecursion(BTNode *bt) {
    if (bt != nullptr) {
        BTNode *stack[MAXSIZE];
        int top = -1;
        BTNode *node = bt;
        while (top != -1 || node != nullptr) {
            while (node != nullptr) {
                stack[++ top] = node;
                node = node ->lchild;
            }

            if (top != -1) {
                node = stack[top --];
                visit(node ->data);
                node = node ->rchild;
            }
        }
    }
}

void postorderNonrecursion(BTNode *bt) {
    if (bt != nullptr) {
        BTNode *stack1[MAXSIZE];
        BTNode *stack2[MAXSIZE]; //缓存出栈结点
        int top1 = -1;
        int top2 = -1;
        stack1[++ top1] = bt;
        while (top1 != -1) {
            BTNode *node = stack1[top1 --];
            stack2[++ top2] = node;
            if (node ->lchild != nullptr) {
                stack1[++ top1] = node ->lchild;
            }
            if (node ->rchild != nullptr) {
                stack1[++ top1] = node ->rchild;
            }
        }

        while (top2 != -1) {
            BTNode *node = stack2[top2 --];
            visit(node ->data);
        }
    }
}

void postorderNonrecursion2(BTNode *bt) {
    if (bt != nullptr) {
        BTNode *stack[MAXSIZE];
        int top = -1;
        BTNode *pre, *cur; //上次访问结点和当前访问结点
        cur = bt;
        pre = nullptr;
        while (cur != nullptr) {
            stack[++ top] = cur;
            cur = cur ->lchild;
        }

        while (top != -1) {
            cur = stack[top --];
            if (cur ->rchild == nullptr || cur ->rchild == pre) {
                //右结点为空或者右结点已被访问
                visit(cur ->data);
                pre = cur;
            } else { //访问右子树
                // 根节点再次入栈
                stack[++ top] = cur;
                cur = cur ->rchild;
                while (cur != nullptr) {
                    stack[++ top] = cur;
                    cur = cur ->lchild;
                }
            }
        }
    }
}

void InThread(TBTNode *p, TBTNode* &pre) {
    if (p != nullptr) {
        InThread(p, pre); //递归左子树线索化
        if (p ->lchild == nullptr) {
            p ->lchild = pre; //建立当前节点的前驱线索
            p ->ltag = 1;
        }

        if (p ->rchild == nullptr && pre != nullptr) {
            pre ->rchild = p; //建立前节点的后继线索
            pre ->rtag = 1;
        }
        pre = p;
        InThread(p ->rchild, pre); //递归右子树线索化
    }
}

void createInThread(TBTNode *root) {
    TBTNode *pre = nullptr;
    if (root != nullptr) {
        InThread(root, pre);
        pre ->rtag = 1;
        pre ->rchild = nullptr;
    }
}

TBTNode* First(TBTNode *p) { //获取最左下结点
    while (p ->ltag == 0) {
        p = p ->lchild;
    }
    return p;
}

TBTNode* Next(TBTNode *p) {
    if (p ->rtag == 1) { //若无子树则返回后继点
        return p ->rchild;
    } else {
        return First(p ->rchild);
    }
}

void Inorder(TBTNode *root) {
    for (TBTNode *p = First(root); p != nullptr; p = Next(p)) {
        visit(p ->data);
    }
}

void PreThread(TBTNode *p, TBTNode* &pre) {
    if (p != nullptr) {
        if(p ->lchild == nullptr) {
            p ->ltag = 1;
            p ->lchild = pre;
        }

        if (p ->rchild == nullptr && pre != nullptr) {
            pre ->rtag = 1;
            pre ->rchild = p;
        }

        pre = p;
        if (p ->ltag == 0) {
            PreThread(p ->lchild, pre);
        }

        if (p ->rtag == 0) {
            PreThread(p ->rchild, pre);
        }
    }
}

void createPreThread(TBTNode *root) {
    TBTNode *pre = nullptr;
    if (root != nullptr) {
        PreThread(root, pre);
        pre ->rtag = 1;
        pre ->rchild = nullptr;
    }
}

void Preorder(TBTNode *root) {
    if (root != nullptr) {
        TBTNode *p = root;
        while (p != nullptr) {
            while (p ->ltag == 0) {
                visit(p ->data);
                p = p ->lchild;
            }

            visit(p ->data);
            p = p ->rchild;
        }
    }
}

void PostThread(TBTNode *p, TBTNode* &pre) {
    if (p != nullptr) {
        PostThread(p ->lchild, pre); //递归线索化左子树
        PostThread(p ->rchild, pre); //递归线索化右子树

        if (p ->lchild == nullptr) {
            p ->ltag = 1;
            p ->lchild = pre;
        }

        if (p ->rchild == nullptr && pre != nullptr) {
            pre ->rtag = 1;
            pre ->rchild = p;
        }

        pre = p;
    }
}

void createPostThread(TBTNode *root) {
    TBTNode *pre = nullptr;
    if (root != nullptr) {
        PostThread(root, pre);
        pre ->rtag = 1;
        pre ->rchild = nullptr;
    }
}

void createBT(BTNode* &root, char pre[], char in[], int l1, int r1, int l2, int r2) {
    BTNode *node1;
    BTNode *node2;
    int i;
    if (l1 > r1) {
        return;
    }

    node1 = (BTNode *) malloc(sizeof(BTNode));
    node2 = (BTNode *) malloc(sizeof(BTNode));

    for (i = l2; i <= r2; ++ i) {
        if (pre[l1] == in[i]) {
            break;
        }
    }

    root->data = in[i];
    createBT(node1, pre, in, l1 + 1, i - l2 + l1, l2, i - 1); //遍历左子树
    root ->lchild = node1;
    createBT(node2, pre, in, l1 + i - l2 + 1, r1, i + 1, r2); //遍历右子树
    root ->rchild = node2;
}

void createHuffman(HuffmanNode* &root, int arr[], int size) {
    if (size <= 0) {
        return;
    }
    HuffmanNode *parent = nullptr;
    Heap heap;
    int result = createminHeap(heap, arr, size);
    if (result != 1) {
        return;
    }

    for (int i = 0; i < size - 1; ++i) {
        int left = heap.data[0];
        minheapRremove(heap, left);
        int right = heap.data[0];
        minheapRremove(heap, right);

        HuffmanNode *lchild;
        HuffmanNode *rchild;

        if (parent != nullptr) {
            if (right == parent ->data) {
                rchild = parent;
                lchild = (HuffmanNode *) malloc(sizeof(HuffmanNode));
            } else {
                lchild = parent;
                rchild = (HuffmanNode *) malloc(sizeof(HuffmanNode));
            }
        } else {
            rchild = (HuffmanNode *) malloc(sizeof(HuffmanNode));
            lchild = (HuffmanNode *) malloc(sizeof(HuffmanNode));
            parent = (HuffmanNode *) malloc(sizeof(HuffmanNode));
        }
        lchild ->data = left;
        rchild ->data = right;
        parent ->data = lchild ->data + rchild ->data;
        parent ->left = lchild;
        parent ->right = rchild;
        parent ->parent = nullptr;
        lchild ->parent = parent;
        rchild ->parent = parent;

        minheapInsert(heap, parent ->data);
    }

    root = parent;
}

void destroyHuffman(HuffmanNode* &root) {
    if (true == nullptr) {
        return;
    }

    if (root ->left != nullptr) {
        destroyHuffman(root ->left);
    }

    if (root ->right != nullptr) {
        destroyHuffman(root ->right);
    }

    free(root);
}

void preorderHuffman(HuffmanNode *root) {
    if (root != nullptr) {
        visit(root ->data);
        preorderHuffman(root ->left);
        preorderHuffman(root ->right);
    }
}

void inorderHuffman(HuffmanNode *root) {
    if (root != nullptr) {
        inorderHuffman(root ->left);
        visit(root ->data);
        inorderHuffman(root ->right);
    }
}

void postorderHuffman(HuffmanNode *root) {
    if (root != nullptr) {
        postorderHuffman(root ->left);
        postorderHuffman(root ->right);
        visit(root ->data);
    }
}
