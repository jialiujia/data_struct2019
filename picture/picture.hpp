//
// Created by 贾屹伦 on 2018/6/18.
//

#ifndef DATA_STRUCT2019_PICTURE_HPP
#define DATA_STRUCT2019_PICTURE_HPP

#define MAXSIZE 100

///领接矩阵
typedef struct {
    int no; //顶点编号
    char data;
} VertexType;

///领接矩阵图
typedef struct {
    float edges[MAXSIZE][MAXSIZE];
    int n, e; //顶点数和边数
    VertexType vex[MAXSIZE];
} MGraph;

///邻接表边
typedef struct arc_node {
    int adjvex; //该边所指向的结点
    arc_node *nextArc; //指向下一条边
    float info; //边的相关信息，如权值
} ArcNode;

///邻接表结点
typedef struct {
    char data;
    arc_node *firstArc; //指向第一条边
}VNode;

///邻接表图
typedef struct {
    VNode adjlist[MAXSIZE];
    int n, e; //顶点数和边数
} AGraph;

///深度优先搜索遍历
void DFS(AGraph *G, int v, int visit[MAXSIZE]); //v为开始结点

///广度优先遍历
void BFS(AGraph *G, int v, int visit[MAXSIZE]);

///广度优先遍历获取离初始结点最远的结点
void getFurthestNode(AGraph *G, int v, int visit[MAXSIZE], int &furthest);

///判断无向图是否是一棵树
int verifyIsTree(AGraph *G);

///两顶点间是否有路径
int DFSTrave(AGraph *G, int i, int j);


#endif //DATA_STRUCT2019_PICTURE_HPP
