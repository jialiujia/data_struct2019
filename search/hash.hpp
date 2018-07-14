//
// Created by 贾屹伦 on 2018/7/11.
//

#ifndef DATA_STRUCT2019_HASH_HPP
#define DATA_STRUCT2019_HASH_HPP

#define MAXSIZE 1024 * 1024

///键值对
typedef struct kv {
    kv *next;
    char *key;
    char *value;
} KV;

///哈希表
typedef struct hash_table {
    KV *table[];
    int size;
} HashTable;

/* 初始化键值对 */
void InitKV(KV* &kv);

/* 释放键值对 */
void FreeKV(KV* &kv);

/* 初始化哈希表 */
void InitHashTable(HashTable* &table);

/* 清空哈希表 */
void DeleteHashTable(HashTable* &table);

/* 添加Hash键值对 */
int PutHashKV(HashTable* &table, char *key, char *value);

/* 获取键值 */
char* GetHashValue(HashTable *table, char *key);

/* 删除键值对 */
char* RemoveHashKV(HashTable* &table, char *key);


#endif //DATA_STRUCT2019_HASH_HPP
