//
// Created by 贾屹伦 on 2018/6/26.
//

#ifndef DATA_STRUCT2019_PTREE_HPP
#define DATA_STRUCT2019_PTREE_HPP

#define MAXSIZE 100

/* 双亲树结点 */
typedef struct pt_node {
    int parent;
    char data;
} PTNode;

/* 双亲树 */
typedef struct {
    PTNode nodes[MAXSIZE]; //根结点默认0
    int n; //结点树
    int rank[MAXSIZE]; //秩
} PTree;

/* 初始化双亲树 */
void initPTree(PTree &tree);

/* 清空双亲树 */
void clearPTree(PTree &tree);

/* 双亲树是否为空 */
int isPTreeEmpty(PTree tree);

/* 返回双亲树的度 */
int getPTreeDegree(PTree tree);

/* 返回双亲树的深度 */
int getPTreeDepth(PTree tree);

/* 返回树的根结点值 */
void getPTreeRootData(PTree tree, char &value);

/* 返回树中第i个结点的值 */
void getPTreeData(PTree tree, int i, char &value);

/* 返回node的位置 */
int getPTreePosition(PTree tree, char node);

/* 替换node结点的值 */
void replacePTreeData(PTree &tree, char node, char newValue);

/* 返回node结点的第i个孩子的值, i = 0定义为最后一个孩子 */
void getChildValue(PTree tree, char node, int i, char &value);

/* 返回node结点的左右兄弟值 0——左兄弟，1——右兄弟 */
void getChildBrotherValue(PTree tree, char node, int brother, char &value);

/* 返回node结点的孩子数量 */
int getChildCount(PTree tree, char node);

/* 返回node结点第i个孩子在树中的位置, i = 0定义为最后一个孩子 */
int getChildPosition(PTree tree, char node, int i);

/* 将结点value插入为结点node的第i个孩子, i = 0定义为最后一个孩子 */
int insertNode(PTree &tree, char node, int i, char value);

/* 将树p插入为node结点的第i颗子树, i = 0定义为最后一个孩子 */
int insertPTree(PTree &tree, char node, int i, PTree p);

/* 删除树中node结点的第i颗子树 */
int deletePTree(PTree &tree, char node, int i);

/* 层序遍历双亲树 */
void levelOrder(PTree tree);


#endif //DATA_STRUCT2019_PTREE_HPP
