//
// Created by 贾屹伦 on 2018/6/26.
//

#ifndef DATA_STRUCT2019_MFSET_HPP
#define DATA_STRUCT2019_MFSET_HPP

#include "ptree.hpp"
#define MAXSIZE 100

typedef PTree MFSet;

/* 二元关系 */
typedef struct {
    int i;
    int j;
} Node;

/* 等价关系 */
typedef struct {
    Node nodes[MAXSIZE];
    int n;
} Relation;

/* 初始化集合 */
void initMFSet(MFSet &mfSet, int n);

/* 查找集合中i所在子集的根 */
int findMFSet(MFSet mfSet, int i);

/* 求i和j的并集，i和j无交集 */
int mergeMFSet(MFSet &mfSet, int i, int j);

/* 集合按秩归并 */
int mixMFSet(MFSet &mfSet, int i, int j);

/* 查找集合中i所在子集的根，路径压缩 */
int fixMFSet(MFSet &mfSet, int i);

/* 求在等价关系下R集合的等价类 */
int equivalenceMFSet1(MFSet &mfSet, Relation R);

/* 求在等价关系下R集合的等价类 */
int equivalenceMFSet2(MFSet &mfSet, Relation R);

/* 返回集合中非空子集数目 */
int subsetCountMFSet(MFSet mfSet);

#endif //DATA_STRUCT2019_MFSET_HPP
