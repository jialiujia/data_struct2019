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
            DFS(G, node ->adjvex);
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