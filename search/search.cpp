//
// Created by 贾屹伦 on 2018/7/8.
//

#include "search.hpp"
#ifdef __APPLE__
#include "mm_malloc.h"
#else
#include "malloc.h"
#endif


int Search(int a[], int n, int k) {
    for (int i = 0; i < n; ++ i) {
        if (a[i] == k) {
            return i;
        }
    }

    return -1;
}

int Bsearch(int R[], int n, int k) {
    int low = 0;
    int high = n - 1;
    while (low < high) {
        int mid = (low + high) / 2;
        if (R[mid] == k) {
            return mid;
        }

        if (R[mid] > k) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;
}

int IndexSearch(int R[], int n, int k, IndexElem elem[], int length) {
    int low = 0, high = length - 1;
    int mid;
    while (low < high) {
        mid = (low + high) / 2;
        if (k < elem[mid].key) {
            high = mid - 1;
        } else if (k > elem[mid].key) {
            low = mid + 1;
        } else {
            break;
        }
    }

    for (int i = elem[mid].low; i <=elem[mid].high; ++ i) {
        if (k == R[i]) {
            return i;
        }
    }

    return -1;
}

BTNode* BSTSearch(BTNode *root, int key) {
    if (root == nullptr) {
        return nullptr;
    }

    if (root ->key == key) {
        return root;
    } else if (root ->key > key) {
        return BSTSearch(root ->lchild, key);
    } else {
        return BSTSearch(root ->rchild, key);
    }
}

int BSTInsert(BTNode* &root, int key) {
    if (root == nullptr) {
        root = (BTNode *)malloc(sizeof(BTNode));
        root ->lchild = root ->rchild = nullptr;
        root ->key = key;
        return 1;
    }

    if (root ->key == key) {
        return 0;
    } else if (root ->key > key) {
        return BSTInsert(root ->lchild, key);
    } else {
        return BSTInsert(root ->rchild, key);
    }
}

void CreateBST(BTNode* &root, int key[], int n) {
    root = nullptr;
    for (int i = 0; i < n; ++ i) {
        BSTInsert(root, key[i]);
    }
}

int getAVLTreeHeight(AVLNode *node) {
    return node == nullptr ? 0 : node ->height;
}

AVLNode* AVLSearch(AVLNode *root, int key) {
    if (root == nullptr) {
        return nullptr;
    }

    AVLNode *node;
    if (root ->key == key) {
        node = root;
        return node;
    } else if (root ->key > key) {
        node = root ->lchild;
    } else {
        node = root ->rchild;
    }

    while (node != nullptr && node ->key != key) {
        if (node ->key > key) {
            node = node ->lchild;
        } else {
            node = node ->rchild;
        }
    }

    return node;
}

/* 左单旋转 */
AVLNode* llAVLRotate(AVLNode *node) {
    AVLNode *avlNode = node ->lchild;
    node ->lchild = avlNode ->rchild;
    avlNode ->rchild = node;

    node ->height = MAX(getAVLTreeHeight(node ->lchild), getAVLTreeHeight(node ->rchild)) + 1;
    avlNode ->height = MAX(getAVLTreeHeight(avlNode ->lchild), getAVLTreeHeight(avlNode ->rchild)) + 1;
    return avlNode;
}

/* 右单旋转 */
AVLNode* rrAVLRotate(AVLNode *node) {
    AVLNode *avlNode = node ->rchild;
    node ->rchild = avlNode ->lchild;
    avlNode ->lchild = node;

    node ->height = MAX(getAVLTreeHeight(node ->lchild), getAVLTreeHeight(node ->rchild)) + 1;
    avlNode ->height = MAX(getAVLTreeHeight(avlNode ->lchild), getAVLTreeHeight(avlNode ->rchild)) + 1;
    return avlNode;
}

/* 左双旋转 */
AVLNode* lrAVLRotate(AVLNode *node) {
    node ->lchild = rrAVLRotate(node ->lchild);

    return llAVLRotate(node);
}

AVLNode* rlAVLRotate(AVLNode *node) {
    node ->rchild = llAVLRotate(node ->rchild);

    return rrAVLRotate(node);
}

AVLNode* AVLInsert(AVLNode* &root, int key, char data) {
    if (root == nullptr) {
        root = (AVLNode *)(malloc(sizeof(AVLNode)));
        root ->key = key;
        root ->data = data;
        root ->height = 1;
    } else if (key < root ->key) {
        root -> lchild = AVLInsert(root ->lchild, key, data);
        if (getAVLTreeHeight(root ->lchild) - getAVLTreeHeight(root ->rchild) >= 2) {
            if (key < root ->lchild ->key) {
                root = llAVLRotate(root);
            } else {
                root = lrAVLRotate(root);
            }
        }
    } else if (key > root ->key) {
        root ->rchild = AVLInsert(root ->rchild, key, data);
        if (getAVLTreeHeight(root ->rchild) - getAVLTreeHeight(root ->lchild) >= 2) {
            if (key > root ->rchild ->key) {
                root = rrAVLRotate(root);
            } else {
                root = rlAVLRotate(root);
            }
        }
    } else { //key == root ->key
        //printf("添加失败：不允许添加相同的节点！\n");
    }
    root ->height = MAX(root ->lchild ->height, root ->rchild ->height) + 1;

    return root;
}

/* 获取AVL树最大点 */
AVLNode* getMaxNode(AVLNode *node) {
    AVLNode *rchild = node;
    while (node ->rchild != nullptr) {
        node = node ->rchild;
    }
    return node;
}

/* 获取AVL树最小点 */
AVLNode* getMinNode(AVLNode *node) {
    AVLNode *rchild = node;
    while (node ->lchild != nullptr) {
        node = node ->lchild;
    }
    return node;
}

/* 删除AVL树结点 */
AVLNode* avlDeleteNode(AVLNode* &root, AVLNode *node) {

    ///根为空 或者 没有要删除的节点，直接返回NULL。
    if (root == nullptr || node == nullptr) {
        return nullptr;
    }

    if (node ->key < root ->key) {
        root ->lchild = avlDeleteNode(root ->lchild, node);
        /// 删除节点后，若AVL树失去平衡，则进行相应的调节。
        if (getAVLTreeHeight(root ->rchild) - getAVLTreeHeight(root ->lchild) >= 2) {
            if (getAVLTreeHeight(root ->rchild ->rchild) > getAVLTreeHeight(root ->rchild ->lchild)) {
                rrAVLRotate(root);
            } else {
                rlAVLRotate(root);
            }
        }
    } else if (node ->key > root ->key) {
        root ->rchild = avlDeleteNode(root ->rchild, node);
        /// 删除节点后，若AVL树失去平衡，则进行相应的调节。
        if (getAVLTreeHeight(root ->lchild) - getAVLTreeHeight(root ->rchild) >= 2) {
            if (getAVLTreeHeight(root ->lchild ->lchild) > getAVLTreeHeight(root ->lchild ->rchild)) {
                llAVLRotate(root);
            } else {
                lrAVLRotate(root);
            }
        }
    } else {
        if (root ->lchild == nullptr || root ->rchild == nullptr) {
            root = root ->lchild != nullptr ? root ->lchild : root ->rchild;
        } else {
            if (getAVLTreeHeight(root ->lchild) > getAVLTreeHeight(root ->rchild)) {
                // 如果tree的左子树比右子树高；
                // 则(01)找出tree的左子树中的最大节点
                //   (02)将该最大节点的值赋值给tree。
                //   (03)删除该最大节点。
                // 这类似于用"tree的左子树中最大节点"做"tree"的替身；
                // 采用这种方式的好处是：删除"tree的左子树中最大节点"之后，AVL树仍然是平衡的。
                AVLNode *maxNode = getMaxNode(root ->lchild);
                root ->key = maxNode ->key;
                root ->data = maxNode ->data;
                root ->lchild = avlDeleteNode(root ->lchild, maxNode);
            } else {
                // 如果tree的左子树不比右子树高(即它们相等，或右子树比左子树高1)
                // 则(01)找出tree的右子树中的最小节点
                //   (02)将该最小节点的值赋值给tree。
                //   (03)删除该最小节点。
                // 这类似于用"tree的右子树中最小节点"做"tree"的替身；
                // 采用这种方式的好处是：删除"tree的右子树中最小节点"之后，AVL树仍然是平衡的。
                AVLNode *minNode = getMinNode(root ->rchild);
                root ->key = minNode ->key;
                root ->data = minNode ->data;
                root ->rchild = avlDeleteNode(root ->rchild, minNode);
            }
        }
    }

    return root;
}

AVLNode* AVLDelete(AVLNode* &root, int key) {
    AVLNode *node;
    if ((node = AVLSearch(root, key)) != nullptr) {
        root = avlDeleteNode(root, node);
    }
    return root;
}