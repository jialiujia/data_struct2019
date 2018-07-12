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
    unsigned int hash = 0;
    unsigned int x = 0;
    while (*key) {
        //hash左移4位，当前字符ASCII存入hash
        hash = (hash << 4) + (*key) ++;
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

void InitKV(KV* &kv) {
    kv = (KV *)malloc(sizeof(KV));
    if (kv == nullptr) {
        return;
    }
    kv ->key = nullptr;
    kv ->next = nullptr;
    kv ->value = nullptr;
}

void FreeKV(KV* &kv) {
    if (kv != nullptr) {
        if (kv ->key != nullptr) {
            free(kv ->key);
            kv ->key = nullptr;
        }

        if (kv ->value != nullptr) {
            free(kv ->value);
            kv ->value = nullptr;
        }

        if (kv ->next != nullptr) {
            kv ->next = nullptr;
        }
        free(kv);
    }
}

void InitHashTable(HashTable* &table) {
    table = (HashTable *)malloc(sizeof(HashTable));
    if (table == nullptr) {
        DeleteHashTable(table);
        return;
    }

    table ->table = (KV **)malloc(sizeof(KV) * MAXSIZE);
    if (table ->table == nullptr) {
        DeleteHashTable(table);
        return;
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
        for (int i = 0; i < MAXSIZE; ++ i) {
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
    if (table == nullptr) {
        return 0;
    }

    int hash = elfHash(key);
    if (table ->table[hash] == nullptr) {
        KV *kv;
        InitKV(kv);
        kv ->key = key;
        kv ->value = value;

        table ->table[hash] = kv;
        ++ table ->size;
    } else {
        KV *p = table ->table[hash];
        while (p ->next != nullptr) {
            if (strcmp(p ->key, key) == 0) {
                p ->value = value;
                return 1;
            }
            p = p ->next;
        }
        if (strcmp(p ->key, key) == 0) {
            p ->value = value;
        } else {
            KV *kv;
            InitKV(kv);
            kv ->key = key;
            kv ->value = value;
            p ->next = kv;
            ++ table ->size;
        }
    }

    return 1;
}

char* GetHashValue(HashTable *table, char *key) {
    if (table == nullptr || table ->size == 0) {
        return nullptr;
    }

    int hash = elfHash(key);
    if (table ->table[hash] == nullptr) {
        return nullptr;
    } else {
        KV *kv = table ->table[hash];
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

    int hash = elfHash(key);
    if (table ->table[hash] == nullptr) {
        return nullptr;
    } else {
        char *value = nullptr;
        KV *kv = table ->table[hash];
        if (kv ->key == key) {
            table ->table[hash] = kv ->next;
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
                table ->table[hash] = kv ->next;
                value = kv ->value;
                FreeKV(kv);
                -- table ->size;
            }
        }

        return value;
    }
}