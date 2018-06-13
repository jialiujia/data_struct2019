//
// Created by Administrator on 2018/6/5.
//

#ifndef DATA_STRUCT2019_BTREE_HPP
#define DATA_STRUCT2019_BTREE_HPP

#define MAXSIZE 100
#define RED 0;
#define BLACK 1;

typedef struct bt_node { //查找二叉树结点
    char data;
    bt_node *lchild, *rchild;
} BTNode;

typedef struct tbt_node { //线索树节点
    char data;
    int ltag, rtag; //线索标记
    tbt_node *lchild, *rchild;
} TBTNode;

typedef struct st { //二叉树层次结构
    BTNode *p;
    int lno; //层次号
} St;

typedef struct huffman_node { //哈夫曼树结点
    int data;  //权值
    huffman_node *parent;
    huffman_node *left;
    huffman_node *right;
} HuffmanNode;

typedef struct rbtree_node { //红黑树结点
    int data;
    int color;
    rbtree_node *parent;
    rbtree_node *lchild;
    rbtree_node *rchild;
} RBTreeNode;

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

void postorderNonrecursion2(BTNode *bt); //非递归后序遍历(标准单栈法)

void createInThread(TBTNode *root); //建立中序线索二叉树

void Inorder(TBTNode *root); //中序遍历中序线索二叉树

void createPreThread(TBTNode *root); //建立先序线索二叉树

void Preorder(TBTNode *root); //先序遍历先序线索二叉树

void createPostThread(TBTNode *root); //建立后序线索树

void createBT(BTNode* &root, char pre[], char in[], int l1, int r1, int l2, int r2); //通过先序遍历和中序遍历建立二叉树，
                                                                                     //l1为先序遍历起点，r1为先序遍历终点
                                                                                     //l2为中序遍历起点，r2为中序遍历终点

void createHuffman(HuffmanNode* &root, int arr[], int size); //创建Huffman树

void destroyHuffman(HuffmanNode* &root); //销毁Huffman树

void preorderHuffman(HuffmanNode *root); //前序遍历Huffman树

void inorderHuffman(HuffmanNode *root); //中序遍历Huffman树

void postorderHuffman(HuffmanNode *root); //后序遍历Huffman树

#endif //DATA_STRUCT2019_BTREE_HPP
