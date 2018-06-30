//
// Created by 贾屹伦 on 2018/6/26.
//

#include "mfset.hpp"
#include "ptree.hpp"

void initMFSet(MFSet &mfSet, int n) {
    if (n > 0) {
        for (int i = 1; i <= n; ++ i) {
            mfSet.nodes[i].data = (char)('0' + i);
            mfSet.nodes[i].parent = -1;
            mfSet.rank[i] = 0;
        }
        mfSet.n = n;
    }
}

int findMFSet(MFSet mfSet, int i) {
    if (i <= 0 || i > mfSet.n) {
        return -1;
    }
    int j = i;
    while (mfSet.nodes[j].parent > 0) {
        j = mfSet.nodes[j].parent;
    }
    return j;
}

int mergeMFSet(MFSet &mfSet, int i, int j) {
    if (i <= 0 || i > mfSet.n || j <= 0 || j > mfSet.n) {
        return 0;
    }
    int p1 = findMFSet(mfSet, i);
    int p2 = findMFSet(mfSet, j);
    if (p1 != p2) {
        mfSet.nodes[p1].parent = j;
    } else {
        return 0;
    }

    return 1;
}

int mixMFSet(MFSet &mfSet, int i, int j) {
    if (i <= 0 || i > mfSet.n || j <= 0 || j > mfSet.n) {
        return 0;
    }

    int p1 = findMFSet(mfSet, i);
    int p2 = findMFSet(mfSet, j);

    if (p1 == p2) {
        return 0;
    }

    if (mfSet.rank[p1] > mfSet.rank[p2]) {
        mfSet.nodes[p2].parent = p1; //合并是从rank小的向rank大的连边
    } else {
        mfSet.nodes[p1].parent = p2;
        if (mfSet.rank[p1] == mfSet.rank[p2]) {
            ++ mfSet.rank[p2];
        }
    }
}

int fixMFSet(MFSet &mfSet, int i) {
    if (i <= 0 || i > mfSet.n) {
        return -1;
    }

    int root = findMFSet(mfSet, i);
    int k, t;
    for (k = i; k != root; k = t) {
        t = mfSet.nodes[k].parent;
        mfSet.nodes[k].parent = root;
    }
    return 1;
}

int equivalenceMFSet1(MFSet &mfSet, Relation R) {
    if (mfSet.n <= 0) {
        return 0;
    }

    for (int k = 1; k < mfSet.n; ++ k) {
        int r1 = findMFSet(mfSet, R.nodes[k].i); //分别求出当前元素所属子类
        int r2 = findMFSet(mfSet, R.nodes[k].j);

        mergeMFSet(mfSet, r1, r2); //合并子类
    }
}

int equivalenceMFSet2(MFSet &mfSet, Relation R) {
    if (mfSet.n <= 0) {
        return 0;
    }

    for (int k = 1; k < mfSet.n; ++ k) {
        int r1 = fixMFSet(mfSet, R.nodes[k].i); //分别求出当前元素所属子类
        int r2 = fixMFSet(mfSet, R.nodes[k].j);

        mixMFSet(mfSet, r1, r2); //合并子类
    }
}

int subsetCountMFSet(MFSet mfSet) {
    if (mfSet.n <= 0) {
        return 0;
    }

    int count = 0;
    for (int i = 0; i < mfSet.n; ++ i) {
        if (mfSet.nodes[i].parent < 0) {
            ++ count;
        }
    }
    return count;
}