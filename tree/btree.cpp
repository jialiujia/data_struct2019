//
// Created by Administrator on 2018/6/5.
//

#include "btree.hpp"
#include "stdio.h"
#include "../heap/heap.hpp"
#ifdef __APPLE__
#include "mm_malloc.h"
#else
#include "malloc.h"
#endif

__inline void visit(char c) {
    printf("%c ", c);
}

__inline void visit(int d) {
    printf("%d", d);
}

__inline int op(int a, int b, char Op) {
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
    return 1;
}

void level(BTNode *p) {
    BTNode *que[MAX_CAPACITY];
    int front, rear;
    front = rear = 0;
    if (p != nullptr) {
        rear = (rear + 1) % MAX_CAPACITY;
        que[rear] = p;
        while (front != rear) {
            front = (front + 1) % MAX_CAPACITY;
            BTNode *q = que[front];
            visit(q ->data);
            if (q ->lchild != nullptr) {
                rear = (rear + 1) % MAX_CAPACITY;
                que[rear] = q ->lchild;
            }

            if (q ->rchild != nullptr) {
                rear = (rear + 1) % MAX_CAPACITY;
                que[rear] = q ->rchild;
            }
        }
    }
}

int maxNode(BTNode *p) {
    int front, rear, Lno = 0;
    St que[MAX_CAPACITY];
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
        BTNode *stack[MAX_CAPACITY];
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
        BTNode *stack[MAX_CAPACITY];
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
        BTNode *stack1[MAX_CAPACITY];
        BTNode *stack2[MAX_CAPACITY]; //缓存出栈结点
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
        BTNode *stack[MAX_CAPACITY];
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
    if (root == nullptr) {
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

void rotateRBtreeLeft(RBTreeNode* &node) { //红黑树左旋
    if (node == nullptr) {
        return;
    }

    RBTreeNode *right = node ->rchild;
    node ->rchild = right ->lchild;
    if (right ->lchild != nullptr) {
        right ->lchild ->parent = node;
    }

    right ->parent = node ->parent;
    if (node ->parent != nullptr) {
        if (node ->parent ->lchild == node) {
            node ->parent ->lchild = right;
        } else {
            node ->parent ->rchild = right;
        }
    }

    right ->lchild = node;
    node ->parent = right;
}

void rotateRBtreeRight(RBTreeNode* &node) { //红黑树右旋
    if (node == nullptr) {
        return;
    }

    RBTreeNode *left = node ->lchild;
    if (left ->rchild != nullptr) {
        left ->rchild ->parent = node;
    }

    left ->parent = node ->parent;
    if (node ->parent != nullptr) {
        if (node ->parent ->lchild == node) {
            node ->parent ->lchild = left;
        } else {
            node ->parent ->rchild = left;
        }
    }

    left ->rchild = node;
    node ->parent = left;
}

RBTreeNode* successorRBTree(RBTreeNode *node) {
    if (node == nullptr) {
        return nullptr;
    }

    if (node ->rchild != nullptr) { // node的右子树不空，则node的后继是其右子树中最小的那个元素
        RBTreeNode *left = node ->rchild;
        if (left == nullptr) {
            return node ->rchild;
        }
        while (left ->lchild != nullptr) {
            left = left ->lchild;
        }
        return left;
    } else { //node的右孩子为空，则node的后继是其第一个向左走的祖先
        if (node ->parent == nullptr) {
            return nullptr;
        }

        RBTreeNode *parent = node ->parent;
        RBTreeNode *child = node;
        while (parent != nullptr && parent ->lchild != child) {
            parent = parent ->parent;
            child = parent;
        }

        return parent;
    }
}

RBTreeNode* predecessorRBTree(RBTreeNode *node) {
    if (node == nullptr) {
        return nullptr;
    }

    if (node ->lchild != nullptr) { //node的左子树不空，则node的前驱是其左子树中最大的那个元素
        RBTreeNode *right = node ->lchild;
       if (right == nullptr) {
           return node ->lchild;
       }

        while (right ->rchild != nullptr) {
            right = right ->rchild;
        }
        return right;
    } else { //node的左孩子为空，则node的前驱是其第一个向右走的祖先
        if (node ->parent == nullptr) {
            return nullptr;
        }

        RBTreeNode *parent = node ->parent;
        RBTreeNode *child = node;
        while (parent != nullptr && parent ->rchild != child) {
            parent = parent ->parent;
            child = parent;
        }
        return parent;
    }
}

void createRBtreeNode(RBTreeNode* &node, int key, int data) {
    node = (RBTreeNode *) (malloc(sizeof(RBTreeNode)));
    if (node == nullptr)
        return;
    node ->key = key;
    node ->data = data;
    node ->color = BLACK;
    node ->rchild = node ->rchild = node ->parent = nullptr;
}

void preorderRBTree(RBTreeNode *root) {
    if (root != nullptr) {
        visit(root ->data);
        preorderRBTree(root ->lchild);
        preorderRBTree(root ->rchild);
    }
}

void inorderRBTree(RBTreeNode *root) {
    if (root != nullptr) {
        inorderRBTree(root ->lchild);
        visit(root ->data);
        inorderRBTree(root ->rchild);
    }
}

void postorderRBTree(RBTreeNode *root) {
    if (root != nullptr) {
        postorderRBTree(root ->lchild);
        postorderRBTree(root ->rchild);
        visit(root ->data);
    }
}

int compare(int a, int b) {
    if (a > b) return 1;
    else if (a == b) return 0;
    else return -1;
}

int getRBTreeEntryData(RBTreeNode *root, int key) {
    RBTreeNode *node = root;
    while (node != nullptr) {
        int result = compare(key, node ->key);
        if (result > 0) {
            node = node ->rchild;
        } else if(result < 0) {
            node = node ->lchild;
        } else {
            return node ->data;
        }
    }

    return -1;
}

RBTreeNode* getRBTreeEntry(RBTreeNode *root, int key) {
    RBTreeNode *node = root;
    while (node != nullptr) {
        int result = compare(key, node ->key);
        if (result > 0) {
            node = node ->rchild;
        } else if(result < 0) {
            node = node ->lchild;
        } else {
            return node;
        }
    }

    return nullptr;
}

RBTreeNode* getMinimumRBTreeEntry(RBTreeNode *root) {
    if (root == nullptr) {
        return nullptr;
    }

    RBTreeNode *node = root;
    while (node ->lchild != nullptr) {
        node = node ->lchild;
    }

    return node;
}

int getMinimumRBTreeEntryData(RBTreeNode *root) {
    RBTreeNode *node = getMinimumRBTreeEntry(root);
    if (node == nullptr) {
        return -1;
    }

    return node ->data;
}

RBTreeNode* getMaximumRBTreeEntry(RBTreeNode *root) {
    if (root == nullptr) {
        return nullptr;
    }

    RBTreeNode *node = root;
    while (node ->rchild != nullptr) {
        node = node ->rchild;
    }

    return node;
}

int getMaximumRBTreeEntryData(RBTreeNode *root) {
    RBTreeNode *node = getMaximumRBTreeEntry(root);
    if (node == nullptr) {
        return -1;
    }

    return node ->data;
}

void fixUpInsertRBTree(RBTreeNode *root, RBTreeNode *node) { //红黑树插入修正函数
    if (node ->parent ->color == BLACK) { //如果父节点为黑则不处理
        return;
    }

    RBTreeNode *parent, *grandParent;
    while ((parent = node ->parent) != nullptr && parent ->color == RED) {
        grandParent = parent ->parent;
        if (parent == grandParent ->lchild) { //父节点是祖父结点的左孩子
            //第一种情况:叔叔结点为红色
            {
                RBTreeNode *uncle = grandParent ->rchild;
                if (uncle != nullptr && uncle ->color == RED) {
                    uncle ->color = BLACK;
                    parent ->color = BLACK;
                    grandParent ->color = RED;
                    node = grandParent;
                    continue;
                }
            }
            //第二种情况:叔叔结点是黑色，且当前节点是右孩子
            if (parent ->rchild == node) {
                RBTreeNode *tmp;
                rotateRBtreeLeft(parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            //第二种情况:叔叔结点是黑色，且当前节点是左孩子
            parent ->color = BLACK;
            grandParent ->color = RED;
            rotateRBtreeRight(grandParent);
        } else { //父节点是祖父结点的右孩子
            //第一种情况:叔叔结点为红色
            {
                RBTreeNode *uncle = grandParent ->lchild;
                if (uncle != nullptr && uncle ->color == RED) {
                    uncle ->color = BLACK;
                    parent ->color = BLACK;
                    grandParent ->color = RED;
                    node = grandParent;
                    continue;
                }
            }

            //第二种情况:叔叔结点是黑色，且当前节点是左孩子
            if (parent ->lchild == node) {
                RBTreeNode *tmp;
                rotateRBtreeRight(parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            //第二种情况:叔叔结点是黑色，且当前节点是右孩子
            parent ->color = BLACK;
            grandParent ->color = RED;
            rotateRBtreeLeft(grandParent);
        }
    }
    //将根节点设为黑色
    root ->color = BLACK;
}

int insertRBTreeNode(RBTreeNode* &root, int key, int value) {
    if (root == nullptr) {
        createRBtreeNode(root, key, value); //创建根节点
        if (root == nullptr) return 0;
        else return 1;
    } else if (getRBTreeEntry(root, key) != nullptr) { //防止重复键值插入
        return 0;
    } else {
        RBTreeNode *node = root;
        while (node != nullptr) {
            if (node ->key > key && node ->lchild != nullptr) {
                node = node ->lchild;
            } else if (node ->key < key && node ->rchild != nullptr) {
                node = node ->rchild;
            } else {
                break;
            }
        }
        RBTreeNode *insertNode;
        createRBtreeNode(insertNode, key, value);
        if (insertNode == nullptr) return 0;
        insertNode ->parent = node;
        insertNode ->color = RED; //设置节点的颜色为红色
        if (node ->key > key) {
            node ->lchild = insertNode;
        } else {
            node ->rchild = insertNode;
        }

        fixUpInsertRBTree(root, insertNode); //重新修正为一颗二叉查找树
        return 1;
    }
}

void fixUpRemoveRBTree(RBTreeNode *root, RBTreeNode *node, RBTreeNode *parent) { //红黑树删除修正函数
    while (node ->color == BLACK && node != root) {
        RBTreeNode *brother;
        if (parent ->lchild == node) {
            brother = parent ->rchild;
            //第一种情况：兄弟节点是红色。
            //把兄弟节点设为黑色，父节点设为红色，并对父节点左旋。
            if (brother ->color == RED) {
                parent ->color = RED;
                brother ->color = BLACK;
                rotateRBtreeLeft(parent);
                brother = parent ->rchild;
            }

            //第二种情况：兄弟节点是黑色，并且兄弟节点的两个孩子节点也为黑色
            //兄弟节点设为红色并且当前结点上移至父节点
            if (brother != nullptr && brother ->color == BLACK
                    && brother ->lchild != nullptr && brother ->lchild ->color == BLACK
                    && brother ->rchild != nullptr && brother ->rchild ->color == BLACK) {
                brother ->color = RED;
                node = parent;
                parent = node ->parent;
            } else {
                //第三种情况：兄弟节点是黑色，并且兄弟节点的左孩子为红色右孩子为黑色
                //交换兄弟节点与左孩子结点的颜色，并对兄弟节点右旋，新的兄弟节点是一个有红色右孩子的黑色结点
                if (brother != nullptr && brother ->color == BLACK
                        && brother ->lchild != nullptr && brother ->lchild ->color == RED
                        && brother ->rchild != nullptr && brother ->rchild ->color == BLACK) {
                    brother ->color = RED;
                    brother ->lchild ->color = BLACK;
                    rotateRBtreeRight(brother);
                    brother = parent ->rchild;
                }

                //第四种情况：兄弟节点是黑色，并且兄弟节点的右孩子为红色左孩子任意色
                //将兄弟节点的颜色转为父节点颜色，父节点设为黑色，兄弟节点右孩子设为黑色，对父节点左旋，当前结点设为根节点
                brother ->color = parent ->color;
                parent ->color = BLACK;
                brother ->rchild ->color = BLACK;
                rotateRBtreeLeft(parent);
                node = root;
                break;
            }
        } else {
            brother = parent ->lchild;
            //第一种情况：兄弟节点是红色。
            //把兄弟节点设为黑色，父节点设为红色，并对父节点右旋。
            if (brother ->color == RED) {
                parent ->color = RED;
                brother ->color = BLACK;
                rotateRBtreeRight(parent);
                brother = parent ->lchild;
            }

            //第二种情况：兄弟节点是黑色，并且兄弟节点的两个孩子节点也为黑色
            //兄弟节点设为红色并且当前结点上移至父节点
            if (brother != nullptr && brother ->color == BLACK
                && brother ->lchild != nullptr && brother ->lchild ->color == BLACK
                && brother ->rchild != nullptr && brother ->rchild ->color == BLACK) {
                brother ->color = RED;
                node = parent;
                parent = node ->parent;
            } else {
                //第三种情况：兄弟节点是黑色，并且兄弟节点的右孩子为红色左孩子为黑色
                //交换兄弟节点与右孩子结点的颜色，并对兄弟节点左旋，新的兄弟节点是一个有红色左孩子的黑色结点
                if (brother != nullptr && brother ->color == BLACK
                    && brother ->lchild != nullptr && brother ->lchild ->color == BLACK
                    && brother ->rchild != nullptr && brother ->rchild ->color == RED) {
                    brother ->color = RED;
                    brother ->rchild ->color = BLACK;
                    rotateRBtreeLeft(brother);
                    brother = parent ->lchild;
                }

                //第四种情况：兄弟节点是黑色，并且兄弟节点的左孩子为红色右孩子任意色
                //将兄弟节点的颜色转为父节点颜色，父节点设为黑色，兄弟节点左孩子设为黑色，对父节点右旋，当前结点设为根节点
                brother ->color = parent ->color;
                parent ->color = BLACK;
                brother ->lchild ->color = BLACK;
                rotateRBtreeRight(parent);
                node = root;
                break;
            }
        }
    }

    if (node != nullptr) {
        node ->color = BLACK;
    }
}

int removeRBTreeNode(RBTreeNode* &root, int key) {
    RBTreeNode *child, *parent;
    char color;
    RBTreeNode *node = getRBTreeEntry(root, key);
    if (node == nullptr) {
        return 0;
    }
    // 被删除节点的"左右孩子都不为空"的情况。
    if ( (node ->lchild!=nullptr) && (node->rchild!=nullptr) ) {
        // 被删节点的后继节点。(称为"取代节点")
        // 用它来取代"被删节点"的位置，然后再将"被删节点"去掉。
        RBTreeNode *replace = node;

        // 获取后继节点
        replace = successorRBTree(replace);

        // "node节点"不是根节点(只有根节点不存在父节点)
        if (node ->parent != nullptr) {
            if (node ->parent->lchild == node)
                node ->parent->lchild = replace;
            else
                node ->parent->rchild = replace;
        }
        else
            // "node节点"是根节点，更新根节点。
            root  = replace;

        // child是"取代节点"的右孩子，也是需要"调整的节点"。
        // "取代节点"肯定不存在左孩子！因为它是一个后继节点。
        child = replace->rchild;
        parent = replace ->parent;
        // 保存"取代节点"的颜色
        color = replace ->color;

        // "被删除节点"是"它的后继节点的父节点"
        if (parent == node) {
            parent = replace;
        }
        else {
            // child不为空
            if (child)
                child ->parent = parent;
            parent->lchild = child;

            replace->rchild = node->rchild;
            node ->rchild ->parent = replace;
        }

        replace->parent = node->parent;
        replace->color = node->color;
        replace->lchild = node->lchild;
        node->lchild->parent = replace;

        if (color == BLACK)
            fixUpRemoveRBTree(root, child, parent);
        destroyRBtreeNode(node);

        return 1;
    }

    if (node->lchild !=nullptr)
        child = node->lchild;
    else
        child = node->rchild;

    parent = node->parent;
    // 保存"取代节点"的颜色
    color = node->color;

    if (child)
        child->parent = parent;

    // "node节点"不是根节点
    if (parent) {
        if (parent->lchild == node)
            parent->lchild = child;
        else
            parent->rchild = child;
    }
    else
        root = child;

    if (color == BLACK)
        fixUpRemoveRBTree(root, child, parent);
    destroyRBtreeNode(node);
    return 1;
}

void destroyRBtreeNode(RBTreeNode* &node) {
    if (node != nullptr) {
        if (node ->parent != nullptr) {
           node ->parent = nullptr;
        }
        if (node ->rchild != nullptr) {
            node ->rchild = nullptr;
        }
        if (node ->lchild != nullptr) {
            node ->lchild = nullptr;
        }
    }
    free(node);
}
