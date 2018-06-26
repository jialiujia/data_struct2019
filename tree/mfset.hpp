//
// Created by 贾屹伦 on 2018/6/26.
//

#ifndef DATA_STRUCT2019_MFSET_HPP
#define DATA_STRUCT2019_MFSET_HPP

#include "ptree.hpp"
#define MAXSIZE 100

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




#endif //DATA_STRUCT2019_MFSET_HPP
