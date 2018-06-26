//
// Created by 贾屹伦 on 2018/6/26.
//

#include "ptree.hpp"
#include "mfset.hpp"

void initPTree(PTree &tree) {
    tree.n = 0;
}

void clearPTree(PTree &tree) {
    tree.n = 0;
}

int isPTreeEmpty(PTree tree) {
    return tree.n == 0 ? 1 : 0;
}

int getPTreeDegree(PTree tree) {
    if (tree.n == 0) {
        return 0;
    }

    int max = 0;
    int count = 0;
    int curParent = 0;

    for (int i = 1; i < tree.n; ++ i) {
        if (tree.nodes[i].parent != curParent) {
            curParent = tree.nodes[i].parent;
            count = 1;
        } else {
            ++ count;
        }

        if (max < count) {
            max = count;
        }
    }

    return max;
}

int getPTreeDepth(PTree tree) {
    if (tree.n == 0) {
        return 0;
    }

    int k = tree.n - 1;
    int level = 1;

    while (k != -1) {
        k = tree.nodes[k].parent;
        ++ level;
    }
    return level;
}

void getPTreeRootData(PTree tree, char &value) {
    if (tree.n == 0) {
        value = nullptr;
    }

    value = tree.nodes[0].data;
}

void getPTreeData(PTree tree, int i, char &value) {
    if (i < 0 || i >= tree.n || tree.n == 0) {
        value = nullptr;
    }

    value = tree.nodes[i - 1].data;
}