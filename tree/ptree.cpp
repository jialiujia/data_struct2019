//
// Created by 贾屹伦 on 2018/6/26.
//

#include "ptree.hpp"
#include "mfset.hpp"
#include "btree.hpp"
#include "stdio.h"
#include "../heap/heap.hpp"
#ifdef __APPLE__
#include "mm_malloc.h"
#else
#include "malloc.h"
#endif

__inline void Visit(char data) {
    printf("%c", data);
}

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
        value = NULL;
    }

    value = tree.nodes[0].data;
}

void getPTreeData(PTree tree, int i, char &value) {
    if (i < 0 || i >= tree.n || tree.n == 0) {
        value = NULL;
    }

    value = tree.nodes[i - 1].data;
}

int getPTreePosition(PTree tree, char node) {
    if (tree.n == 0) {
        return -1;
    }

    for (int i = 0; i < tree.n; ++ i) {
        if (node == tree.nodes[i].data) {
            return i;
        }
    }

    return -1;
}

void replacePTreeData(PTree &tree, char node, char newValue) {
    int position = getPTreePosition(tree, node);
    if (position != -1) {
        tree.nodes[position].data = newValue;
    }
}

void getChildValue(PTree tree, char node, int i, char &value) {
    int p = getPTreePosition(tree, node);
    int child = 0;
    value = NULL;
    if (p == -1) {
        value = NULL;
    } else if (i < 0) {
        value = NULL;
    } else {
        for (int j = p + 1; j < tree.n; ++ j) {
            if (i != 0) {
                if (tree.nodes[j].parent == p && (++ child) == i) {
                    value = tree.nodes[j].data;
                    break;
                }
            } else {
                if (tree.nodes[j].parent == p
                    && (j + 1 == tree.n || tree.nodes[j + 1].parent != p)) {
                    value = tree.nodes[j].data;
                    break;
                }
            }
        }
    }
}

void getChildBrotherValue(PTree tree, char node, int brother, char &value) {
    int p;
    if (tree.n == 0) {
        value = NULL;
    } else if (brother != 0 && brother != 1) {
        value = NULL;
    } else if ((p = getPTreePosition(tree, node)) == -1) {
        value = NULL;
    } else if (p == 0) {
        value = NULL;
    } else if (brother == 0 && tree.nodes[p - 1].parent != tree.nodes[p].parent) {
        value = NULL;
    } else if (brother == 1 && tree.nodes[p + 1].parent != tree.nodes[p].parent) {
        value = NULL;
    } else if (brother == 0) {
        value = tree.nodes[p - 1].data;
    } else {
        value = tree.nodes[p + 1].data;
    }
}

int getChildCount(PTree tree, char node) {
    int p = getPTreePosition(tree, node);
    if (p == -1) {
        return 0;
    }

    int count = 0;
    for (int i = p + 1; i < tree.n; ++ i) {
        if (tree.nodes[i].parent == p) {
            ++ count;
        }
    }
    return count;
}

int getChildPosition(PTree tree, char node, int i) {
    char value;
    getChildValue(tree, node, i, value);
    if (value == NULL) {
        return -1;
    }

    int position = getPTreePosition(tree, value);
    if (position == -1) {
        return -1;
    }
    return position;
}

int insertNode(PTree &tree, char node, int i, char value) {
    int p = getChildPosition(tree, node, i);
    if (p == -1) {
        return 0;
    }

    PTNode ptNode;
    ptNode.data = value;
    ptNode.parent = tree.nodes[p].parent;

    for (int j = tree.n - 1; j >= p; -- j) {
        if (tree.nodes[j].parent >= p) {
            ++ tree.nodes[j].parent;
        }
        tree.nodes[j + 1] = tree.nodes[j];
    }

    tree.nodes[p] = ptNode;
    ++ tree.n;
    return 1;
}

int insertPTree(PTree &tree, char node, int i, PTree p) {
    int position = getChildPosition(tree, node, i);
    if (position == -1) {
        return 0;
    }

    for (int j = 0; j < p.n; ++ j) {
        if (j == 0) {
            insertNode(tree, node, i, p.nodes[0].data);
        } else {
            insertNode(tree, p.nodes[p.nodes[j].parent].data, 0, p.nodes[j].data);
        }
    }
    return 1;
}

int deletePTree(PTree &tree, char node, int i) {
    int p = getChildPosition(tree, node, i);
    if (p == -1) {
        return 0;
    }

    for (int j = p + 1; j < tree.n; ++ j) {
        if (tree.nodes[j].parent >= p) {
            -- tree.nodes[j].parent;
        }
        tree.nodes[j - 1] = tree.nodes[j];
    }
    -- tree.n;
    return 1;
}

void levelOrder(PTree tree) {
    for (int i = 0; i < tree.n; ++ i) {
        Visit(tree.nodes[i].data);
    }
}