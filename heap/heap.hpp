//
// Created by 贾屹伦 on 2018/6/9.
//

#ifndef DATA_STRUCT2019_HEAP_HPP
#define DATA_STRUCT2019_HEAP_HPP

#define MAXSIZE 100
#define LENGTH ((sizeof(a)) / (sizeof(a[0])))

typedef struct heap {
    int data[MAXSIZE];
    int size = 0; //实际容量
} Heap;

int getIndex(Heap heap, int data); //获取元素所在的索引


void minheapFilterdown(Heap &heap, int start, int end); //最小堆的向下调整算法,
                                                       //注：数组实现的堆中，第N个节点的左孩子的索引值是(2N+1)，右孩子的索引是(2N+2)。

int minheapRremove(Heap &heap, int data); //删除最小堆中的data

void minheapFilter_up(Heap &heap, int end); //最小堆的向上调整算法(从end开始向上直到0，调整堆)

int minheapInsert(Heap &heap, int data); //将data插入到最小二叉堆中

void maxheapFilterdown(Heap &heap, int start, int end); //最大堆的向下调整算法,
                                                       //注：数组实现的堆中，第N个节点的左孩子的索引值是(2N+1)，右孩子的索引是(2N+2)。

int maxheapRremove(Heap &heap, int data); //删除最大堆中的data

void maxheapFilter_up(Heap &heap, int end); //最大堆的向上调整算法(从end开始向上直到0，调整堆)

int maxheapInsert(Heap &heap, int data); //将data插入到最大二叉堆中


#endif //DATA_STRUCT2019_HEAP_HPP
