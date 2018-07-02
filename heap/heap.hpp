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

///创建最小堆
int createminHeap(Heap &heap, int data[], int size);

///获取元素所在的索引
int getIndex(Heap heap, int data);

///最小堆的向下调整算法,
///注：数组实现的堆中，第N个节点的左孩子的索引值是(2N+1)，右孩子的索引是(2N+2)。
void minheapFilterdown(Heap &heap, int start, int end);

///删除最小堆中的data
int minheapRremove(Heap &heap, int data);

///最小堆的向上调整算法(从end开始向上直到0，调整堆)
void minheapFilter_up(Heap &heap, int end);

///将data插入到最小二叉堆中
int minheapInsert(Heap &heap, int data);

///最大堆的向下调整算法,
///注：数组实现的堆中，第N个节点的左孩子的索引值是(2N+1)，右孩子的索引是(2N+2)。
void maxheapFilterdown(Heap &heap, int start, int end);

///删除最大堆中的data
int maxheapRremove(Heap &heap, int data);

///最大堆的向上调整算法(从end开始向上直到0，调整堆)
void maxheapFilter_up(Heap &heap, int end);

///将data插入到最大二叉堆中
int maxheapInsert(Heap &heap, int data);


#endif //DATA_STRUCT2019_HEAP_HPP
