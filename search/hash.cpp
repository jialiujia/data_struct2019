//
// Created by 贾屹伦 on 2018/7/11.
//

#include "hash.hpp"
#include <string.h>
#ifdef __APPLE__
#include "mm_malloc.h"
#else
#include "malloc.h"
#endif

/* ELF Hash算法 */
unsigned int elfHash(char *key) {
    int hash = 0;
    int x = 0;
    while (*key) {
        //hash左移4位，当前字符ASCII存入hash
        hash = (hash << 4);
        hash += (*key);
        *key ++;
        //如果最高的四位不为0，则说明字符多余7个，如果不处理，再加第九个字符时，
        //第一个字符会被移出，因此要有如下处理。
        if (( x = hash & 0xF0000000L) != 0) {
           hash ^= x >> 24;
           //清空28-31位
           hash &= ~x;
        }
        //返回一个符号位为0的数
        return (hash & 0x7FFFFFFF);
    }
}

/* BKDR Hash算法 */
unsigned int bkdrHash(char *key) {
    unsigned int seed = 131;
    unsigned int hash = 0;
    while (*key) {
        hash = hash * seed + (*key);
        *key ++;
    }
    return (hash % 0x7FFFFFFF);
}

/* 二次Hash */
unsigned int hash(int hash) {
    hash ^= (hash >> 20) ^ (hash >> 12);
    return (hash >> 7) ^ (hash >> 4);
}

/* 获取hash所在位置 */
int indexOfHash(HashTable *table, int hash) {
    return hash & (table ->capacity - 1);
}

/* Hash表扩容 */
void resizeHash(HashTable* &table) {
    int oldCap = table ->size;
    int oldThr = table ->threshold;
    int newCap = 0, newThr = 0;

    if(oldCap >= MAX_CAPACITY) {
        table ->threshold = 0x7FFFFFFF;
        return;
    } else if ((newCap = oldCap << 1) < MAX_CAPACITY
            && oldCap >= DEFAULT_INIT_CAPACITY) {
        newThr = oldThr << 1;
    }

    if (newThr == 0) {
        newThr = (int)(newCap * table ->loadFacor);
        newThr = (newCap < MAX_CAPACITY && newThr < MAX_CAPACITY) ?
                newThr : 0xFFFFFFF;
    }

    HashTable *newTable = (HashTable *)malloc(sizeof(HashTable));
    if (newTable == nullptr)
        return;
    newTable ->table = (KV **)malloc(sizeof(KV) * newCap);
    if (newTable ->table == nullptr)
        return;
    newTable ->loadFacor = table ->loadFacor;
    newTable ->threshold = newThr;
    newTable ->capacity = newCap;
    newTable ->size = 0;
    for (int i = 0; i < table ->capacity; ++i) {
        KV *entry = table ->table[i];
        while (entry != nullptr) {
            PutHashKV(newTable, entry ->key, entry ->value);
            entry = entry ->next;
        }
    }
    table = newTable;
}

/* 添加键值对 */
int addEntry(HashTable* &table, KV *kv, int index) {
    if (table == nullptr || table ->table == nullptr || kv == nullptr || index < 0) {
        return 0;
    }

    KV *entry = table ->table[index];
    kv ->next = entry;
    table ->table[index] = kv;
    ///如果超过Hash表的极限，则进行扩容
    if ((++ table ->size) > table ->threshold) {
        resizeHash(table);
    }

    return 1;
}

void InitKV(KV* &kv, char *key, char *value) {
    kv = (KV *)malloc(sizeof(KV));
    if (kv == nullptr) {
        return;
    }
    kv ->key = key;
    kv ->next = nullptr;
    kv ->value = value;
    kv ->hash = bkdrHash(key);
}

void FreeKV(KV* &kv) {
    if (kv != nullptr) {
        if (kv ->key != nullptr) {
            kv ->key = nullptr;
            free(kv ->key);
        }

        if (kv ->value != nullptr) {
            kv ->value = nullptr;
            free(kv ->value);
        }

        if (kv ->next != nullptr) {
            kv ->next = nullptr;
        }
        free(kv);
    }
}

void InitHashTable(HashTable* &table) {
    InitHashTable(table, DEFAULT_INIT_CAPACITY, DEFAULT_LOAD_FACTOR);
}

void InitHashTable(HashTable* &table, int size) {
    InitHashTable(table, size, DEFAULT_LOAD_FACTOR);
}

void InitHashTable(HashTable* &table, int size, float loadFactor) {
    if (size < 0) {
        return;
    }

    if (loadFactor <= 0) {
        return;
    }

    if (size > MAX_CAPACITY) {
        size = MAX_CAPACITY;
    }

    table = (HashTable *)malloc(sizeof(HashTable));
    if (table == nullptr) {
        DeleteHashTable(table);
        return;
    }

    int capacity = 1;
    while (capacity < size) {
        capacity <<= 1;
    }

    table ->table = (KV **)malloc(sizeof(KV) * capacity);
    if (table ->table == nullptr) {
        DeleteHashTable(table);
        return;
    }
    table ->capacity = capacity;
    //设置容量极限，当HashMap的容量达到该极限时就会进行扩容操作
    table ->loadFacor = loadFactor;
    table ->threshold = (int)(loadFactor * table ->capacity);
    for (int i = 0; i < table ->capacity; ++ i) {
        table ->table[i] = nullptr;
    }
    table ->size = 0;
}

void DeleteHashTable(HashTable* &table) {
    if (table == nullptr) {
        return;
    }

    if (table ->size == 0) {
        free(table ->table);
        table ->table = nullptr;
    } else {
        for (int i = 0; i < table ->capacity; ++ i) {
            KV *p = table ->table[i];
            KV *q = nullptr;
            while (p != nullptr) {
                q = p ->next;
                FreeKV(p);
                p = q;
            }
        }
    }
    free(table);
}

int PutHashKV(HashTable* &table, char *key, char *value) {
    if (table == nullptr || table ->table == nullptr || key == nullptr) {
        return 0;
    }

    int hash = bkdrHash(key);
    int index = indexOfHash(table, hash);
    kv *e = table ->table[index];
    if (e != nullptr) {
        for (KV *e = table ->table[index]; e != nullptr; e = e ->next) {
            if (e ->hash == hash && (strcmp(e ->key, key) == 0)) {
                e ->value = value;
                return 1;
            }
        }
    }
    KV *kv;InitKV(kv, key, value);
    if (kv == nullptr) {
        return 0;
    }
    return addEntry(table, kv, index);
}

char* GetHashValue(HashTable *table, char *key) {
    if (table == nullptr || table ->size == 0) {
        return nullptr;
    }

    int hash = bkdrHash(key);
    int index = indexOfHash(table, hash);
    if (table ->table[index] == nullptr) {
        return nullptr;
    } else {
        KV *kv = table ->table[index];
        while (kv != nullptr) {
            if (kv ->key == key) {
                return kv ->value;
            }
            kv = kv ->next;
        }
    }
    return nullptr;
}

char* RemoveHashKV(HashTable* &table, char *key) {
    if (table == nullptr || table ->size == 0) {
        return nullptr;
    }

    int hash = bkdrHash(key);
    int index = indexOfHash(table, hash);
    if (table ->table[index] == nullptr) {
        return nullptr;
    } else {
        char *value = nullptr;
        KV *kv = table ->table[index];
        if (kv ->key == key) {
            table ->table[index] = kv ->next;
            value = kv ->value;
            FreeKV(kv);
            -- table ->size;
        } else {
            while (kv ->next != nullptr) {
                if (kv ->next ->key == key) {
                    KV *n = kv ->next;
                    kv ->next = n ->next;
                    value = n ->value;
                    -- table ->size;
                    break;
                }
                kv = kv ->next;
            }
            if (kv ->key == key) {
                table ->table[index] = kv ->next;
                value = kv ->value;
                FreeKV(kv);
                -- table ->size;
            }
        }

        return value;
    }
}