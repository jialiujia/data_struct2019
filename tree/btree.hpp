//
// Created by Administrator on 2018/6/5.
//

#ifndef DATA_STRUCT2019_BTREE_HPP
#define DATA_STRUCT2019_BTREE_HPP

#define MAXSIZE 100

typedef struct bt_node {
    char data;
    bt_node *lchild, *rchild;
} BTNode;

typedef struct st {
    BTNode *p;
    int lno; //层次号
} St;

void preorder(BTNode *p); //先序遍历

void inorder(BTNode *p); //中序遍历

void postorder(BTNode *p); //后序遍历

int comp(BTNode *p); //计算表达式值

int getDepth(BTNode *p); //求二叉树高度

void search(BTNode *p, BTNode* &q, int key); //查找值为key的结点

int trave(BTNode *p, int k, int n); //先序遍历第k个节点值

void level(BTNode *p); //层次遍历

int maxNode(BTNode *p); //求二叉树宽度

void preorderNonrecursion(BTNode *bt); //非递归先序遍历

void inorderNonrecursion(BTNode *bt); //非递归中序遍历

void postorderNonrecursion(BTNode *bt); //非递归后序遍历(逆后序双栈法)

#endif //DATA_STRUCT2019_BTREE_HPP
