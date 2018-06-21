//
// Created by 贾屹伦 on 2018/6/18.
//

#include "picture.hpp"
#include "stdio.h"

void Visit(char data) {
    printf("%c\n", data);
}

void DFS(AGraph *G, int v, int visit[MAXSIZE]) {
    for (int i = 0; i < G ->n; ++ i) {
        visit[i] = 0;
    }
    Visit(G->adjlist[v].data);
    visit[v] = 1;

    ArcNode *node = G->adjlist[v].firstArc;
    while (node != nullptr) {
        if (visit[node ->adjvex] != 1) {
            DFS(G, node ->adjvex, visit);
        }
        node = node ->nextArc;
    }
}

void BFS(AGraph *G, int v, int visit[MAXSIZE]) {
    int rear, front, que[MAXSIZE];
    for (int i = 0; i < G ->n; ++ i) {
        visit[i] = 0;
    }
    rear = front = 0;
    Visit(G ->adjlist[v].data);
    visit[v] = 1;
    rear = (rear + 1) % MAXSIZE;
    que[rear] = v;
    while (front != rear) {
        front = (front + 1) % MAXSIZE;
        int pop = que[front];
        ArcNode *node = G ->adjlist[pop].firstArc;
        while (node != nullptr) {
            if (visit[node ->adjvex] != 1) {
                Visit(G ->adjlist[node ->adjvex].data);
                visit[node ->adjvex] = 1;
                rear = (rear + 1) % MAXSIZE;
                que[rear] = node ->adjvex;
            }

            node = node ->nextArc;
        }
    }
}

void getFurthestNode(AGraph *G, int v, int visit[MAXSIZE], int &furthest) {
    for (int i = 0; i < G ->n; ++ i) {
        visit[i] = 0;
    }

    int rear, front, que[MAXSIZE];
    rear = front = 0;
    Visit(G ->adjlist[v].data);
    visit[v] = 1;
    rear = (rear + 1) % MAXSIZE;
    que[rear] = v;
    while (front != rear) {
        front = (front + 1) % MAXSIZE;
        furthest = que[front];
        ArcNode *node = G ->adjlist[furthest].firstArc;
        while (node != nullptr) {
            if (visit[node ->adjvex] != 1) {
                Visit(G ->adjlist[node ->adjvex].data);
                visit[node ->adjvex] = 1;
                rear = (rear + 1) % MAXSIZE;
                que[rear] = node ->adjvex;
            }
            node = node ->nextArc;
        }
    }
}

void DFS(AGraph *G, int v, int visit[MAXSIZE], int &vn, int &en) {
    visit[v] = 1;
    ++ vn;
    ArcNode *node = G ->adjlist[v].firstArc;
    while (node != nullptr) {
        ++ en;
        if (visit[node ->adjvex] != 1) {
            DFS(G, node ->adjvex, visit, vn, en);
        }
        node = node ->nextArc;
    }
}

int verifyIsTree(AGraph *G) {
    //无向图判断是否是树的条件是有n-1条边的连通图
    int v, vn, en;
    v = vn = en = 0;
    int visit[MAXSIZE];
    for (int i = 0; i < G ->n; ++ i) {
        visit[i] = 0;
    }
    DFS(G, v, visit, vn, en); //深度遍历
    if (vn == G ->n && (G->n - 1) == en / 2) {
        return 1;
    }
    return 0;
}

int DFSTrave(AGraph *G, int i, int j) {
    int visit[MAXSIZE];
    for (int k = 0; k < G ->n; ++ k) {
        visit[k] = 0;
    }
    DFS(G, i, visit);
    if (visit[j] == 1) {
        return 1;
    }
    return 0;
}

void Prim(MGraph g, int v0, float &sum) {
    int v;
    float lowcost[MAXSIZE];
    int vest[MAXSIZE];
    v = v0;
    /* 将v0到其他点的所有边当作候选边 */
    for (int i = 0; i < g.n; ++ i) {
        lowcost[i] = g.edges[v][i];
    }
    vest[v0] = 1;
    sum = 0;

    /* 重复以下步骤n-1次 */
    for (int i = 0; i < g.n - 1; ++ i) {
        int j; float k = 0, min = INF;

        /* 从候选边中挑出最小边，把顶点vi并入生成树中 */
        for (j = 0; j < g.n; ++ j) {
            if (vest[i] != 1 && lowcost[j] < min) {
                k = lowcost[j];
                min = k;
            }
        }
        sum +=k;
        vest[j] = 1;
        /* 考察所有剩余顶点，如果（v， vi）的权值比lowcost[vi]小，则用新权值更新lowcost */
        for (int m = 0; m < g.n; ++ m) {
            if (vest[m] != 1 && g.edges[j][m] < lowcost[m]) {
                lowcost[m] = g.edges[j][m];
            }
        }
    }
}

///并查集中查找根结点
int getRoot(int a, int v[]) {
    while (a != v[a]) {
        a = v[a];
    }
    return a;
}

void Kruskal(MGraph g, float &sum, Road road[]) {
    int a, b, N, E;
    int v[MAXSIZE];
    N = g.n;
    E = g.e;
    sum = 0;
    for (int i = 0; i < E; ++i) {
        v[i] = i;
    }

    //对road进行小到大排序
    //sort(road, E);

    for (int j = 0; j < E; ++j) {
        a = getRoot(road[j].a, v);
        b = getRoot(road[j].b, v);

        if (a != b) {
            sum += road[j].w;
            v[a] = b;
        }
    }
}