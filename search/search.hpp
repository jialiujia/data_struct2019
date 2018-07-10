//
// Created by 贾屹伦 on 2018/7/8.
//

#ifndef DATA_STRUCT2019_FIND_HPP
#define DATA_STRUCT2019_FIND_HPP

#include "../tree/btree.hpp"

#define MAXSIZE 100
#define MAX(a, b) ((a) >  (b) ? (a) : (b))

///索引表结构
typedef struct {
    int low, high;
    int key;
} IndexElem;

///平衡二叉树结点
typedef struct avl_node {
    int key;
    char data;
    int height; //当前高度
    avl_node *lchild;
    avl_node *rchild;
} AVLNode;

/* 顺序查找法,ASL=(n+1)/2 */
int Search(int R[], int n, int k);

/* 折半查找法,ASL=log2(n+1)-1 */
int Bsearch(int R[], int n, int k);

/* 分块查找,ASL=log2(b+1)-1 + (s+1)/2 */
int IndexSearch(int R[], int n, int k, IndexElem elem[], int length);

/* 二叉排序树查找法 */
BTNode* BSTSearch(BTNode *root, int key);

/* 二叉排序树插入新结点 */
int BSTInsert(BTNode* &root, int key);

/* 二叉排序树构造 */
void CreateBST(BTNode* &root, int key[], int n);

/* 获取AVL树的高度 */
int getAVLTreeHeight(AVLNode *node);

/* AVL树查找 */
AVLNode* AVLSearch(AVLNode *root, int key);

/* 将结点插入到AVL树中，并返回根节点 */
AVLNode* AVLInsert(AVLNode* &root, int key, char data);

/* 将结点从到AVL树中删除，并返回根节点 */
AVLNode* AVLDelete(AVLNode* &root, int key);



#endif //DATA_STRUCT2019_FIND_HPP
