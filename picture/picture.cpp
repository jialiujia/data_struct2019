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

///打印 Dijkstra 访问路径
void printDijkstraPath(int path[], int a) {
    int stack[MAXSIZE], top = -1;
    while (path[a] != -1) {
        stack[++ top] = a;
        a = path[a];
    }
    stack[++ top] = a;
    while (top != -1) {
        printf("%d", path[top --]);
    }
}

void Dijkstra(MGraph g, int v, float dist[], float path[]) {
    /*初始化*/
    int set[MAXSIZE];
    for (int i = 0; i < g.n; ++ i) {
        set[i] = 0;
        dist[i] = g.edges[v][i];
        if (g.edges[v][i] < INF) {
            path[i] = v;
        } else {
            path[i] = -1;
        }
    }
    path[v] = -1;set[v] = 1;
    /*初始化结束*/

    for (int i = 0; i < g.n - 1; ++ i) {
        float min = INF;
        int u = 0;
        for (int j = 0; j < g.n; ++ j) {
            if (set[j] != 1 && dist[j] < min) {
                u = j;
                min = dist[j];
            }
        }

        set[u] = 1;
        /*已新并入的顶点为中间点，对通往剩余顶点路径进行检测*/
        for (int k = 0; k < g.n; ++ k) {
            if (set[k] != 1 && g.edges[u][k] + dist[u] < dist[k])  {
                dist[k] = g.edges[u][k] + dist[u];
                path[k] = u;
            }
        }
    }
}

///打印 Floyd 访问路径
void printFloydPath(int u, int v, int path[][MAXSIZE]) {
    if (path[u][v] == -1) {
        printf("%d", v);
    } else {
        printFloydPath(u, path[u][v], path); //处理前半段路径
        printFloydPath(path[u][v], v, path); //处理后半段路径
    }
}

void Floyd(MGraph g, int path[][MAXSIZE]) {
    /*初始化*/
    float A[MAXSIZE][MAXSIZE];
    for (int i = 0; i < g.n; ++ i) {
        for (int j = 0; j < g.n; ++ i) {
            A[i][j] = g.edges[i][j];
            path[i][j] = -1;
        }
    }
    /*初始化结束*/

    /*已新并入的顶点为中间点，对通往剩余顶点路径进行检测*/
    for (int i = 0; i < g.n; ++ i) {
        for (int j = 0; j < g.n; ++ j) {
            for (int k = 0; k < g.n; ++ k) {
                if (A[i][j] > A[i][k] + A[k][j]) {
                    A[i][j] = A[i][k] + A[k][j];
                    path[i][j] = k;
                }
            }
        }
    }
}

int TopSort(AGraph *G, int &path[]) {
    int stack[MAXSIZE], top = -1, n = 0;
    for (int i = 0; i < G->n; ++ i) {
        if (G ->adjlist[i].iCount == 0) {
            stack[++ top] = i;
        }
    }

    while (top != -1) {
        int no = stack[top --];
        ++ n;
        ArcNode *node = G ->adjlist[no].firstArc;
        while (node != nullptr) {
            -- (G ->adjlist[node ->adjvex].iCount); //子结点入度减一
            if (G ->adjlist[node ->adjvex].iCount == 0) {
                stack[++ top] = node ->adjvex;
            }
            node = node ->nextArc;
        }
    }

    if (n != G->n) {
        return 0;
    }
    path = stack;
    return 1;
}

///获取当前结点所有入度结点
int getInNode(AGraph *G, int node, int &parent[]) {
    int result = 0;
    for (int i = 0; i < G->n; ++ i) {
        ArcNode *p = G ->adjlist[i].firstArc;
        while (p != nullptr) {
            if (p ->adjvex == node) {
                parent[++ result] = i;
            }
            p = p ->nextArc;
        }
    }
    return result;
}

///获取当前结点的出度结点
int getOutNode(AGraph *G, int node, int &child[]) {
    int result = 0;
    ArcNode *p = G ->adjlist[node].firstArc;
    while (p != nullptr) {
        child[++ result] = p ->adjvex;
        p = p ->nextArc;
    }
    return result;
}

///根据拓扑有序序列求出各顶点所代表事件的最早发生时间
int getVE(AGraph *G, int topSort[], float &ve[MAXSIZE]) {

    for (int i = 0; i < G ->n; ++ i) {
        int inNode[G ->n - 1];
        int no = topSort[i];
        int num = getInNode(G, no, inNode);
        if (num == 0) {
            ve[i] = 0;
        } else {
            float max = 0;
            for (int j = 0; j < num; ++ j) {
                ArcNode *p = G ->adjlist[inNode[j]].firstArc;
                while (p ->adjvex != nullptr && p ->adjvex != no) {
                    p = p ->nextArc;
                }
                int k = 0;
                while (topSort[k] != inNode[j] && k < G->n) {
                    ++ k;
                }

                if (k >= G ->n) {
                    return 0;
                }

                if (ve[k] + p ->info > max) {
                    max = ve[k] + p ->info;
                }
            }
            ve[i] = max;
        }
    }
    return 1;
}

///根据拓扑有序序列求出各顶点所代表事件的最晚发生时间
int getVl(AGraph *G, int topSort[], float ve[MAXSIZE], float &vl[MAXSIZE]) {
    for (int i = G ->n - 1; i >= 0; -- i) {
        int outNode[G ->n - 1];
        int no = topSort[i];
        int num = getOutNode(G, no, outNode);
        if (num == 0) {
            vl[i] = ve[i];
        } else {
            float min = INF;
            ArcNode *p = G ->adjlist[no].firstArc;
            while (p != nullptr) {
                int k = 0;
                while (topSort[k] != p->adjvex && k < G->n) {
                    ++ k;
                }

                if (k >= G ->n) {
                    return 0;
                }
                if (ve[k] - p ->info < min) {
                    min = vl[k] - p ->info;
                }
                p = p ->nextArc;
            }
            vl[i] = min;
        }
    }
    return 1;
}

///获取AOE中各事件最早发生时间
int getEevent(AGraph *G, int topSort[], float ve[MAXSIZE], float &e[MAXSIZE]) {
    int count = -1;
    for (int i = 0; i < G ->n; ++i) {
        ArcNode *node = G ->adjlist[i].firstArc;
        int k = 0;
        while (topSort[k] != i && k < G ->n) {
            ++ k;
        }
        while (node != nullptr) {
            e[++ count] = ve[k];
            node = node ->nextArc;
        }
    }

    if (count == G ->e - 1) {
        return 1;
    }
    return 0;
}

///获取AOE中各事件最迟发生时间
int getLevent(AGraph *G, int topSort[], float vl[MAXSIZE], float &l[MAXSIZE]) {
    int count = -1;
    for (int i = 0; i < G ->n; ++ i) {
        ArcNode *node = G ->adjlist[i].firstArc;
        while (node != nullptr) {
            int no = node ->adjvex;
            int k = 0;
            while (topSort[k] != no && k < G ->n) {
                ++ k;
            }
            l[++ count] = vl[k] - node ->info;
            node = node ->nextArc;
        }
    }

    if (count == G ->e - 1) {
        return 1;
    }
    return 0;
}

int CriticalPath(AGraph *G, int &path[MAXSIZE], int &sum) {
    float ve[MAXSIZE], vl[MAXSIZE]; //最早发生时间和最迟发生时间数组
    float e[MAXSIZE], l[MAXSIZE]; //事件最早发生时间和事件最迟发生时间
    int arr[MAXSIZE];//拓扑排序数组
    sum = 0;
    int result = TopSort(G, arr); //拓扑排序
    if (result == 0) {
        return 0;
    }

    if (getVE(G, arr, ve) == 0) {
        return 0;
    }

    if (getVl(G, arr, ve, vl) == 0) {
        return 0;
    }

    if (getEevent(G, arr, ve, e) == 0) {
        return 0;
    }

    if (getLevent(G, arr, vl, l) == 0) {
        return 0;
    }

    int top = -1;
    for (int i = 0; i < G->e; ++ i) {
        if (e[i] == l[i]) {
            path[++ top] = i;
            sum += e[i];
        }
    }

    return 1;
}