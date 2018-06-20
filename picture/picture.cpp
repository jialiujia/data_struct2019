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