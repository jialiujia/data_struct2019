//
// Created by 贾屹伦 on 2018/7/11.
//

#ifndef DATA_STRUCT2019_HASH_HPP
#define DATA_STRUCT2019_HASH_HPP

#define MAX_CAPACITY 1 << 30          ///最大数组大小为2 ^ 30
#define DEFAULT_INIT_CAPACITY 1 << 4  ///默认数组大小
#define DEFAULT_LOAD_FACTOR 0.75f     ///默认装载因子

///键值对
typedef struct kv {
    kv *next;
    char *key;
    char *value;
    unsigned int hash; //key的Hash值
} KV;

///哈希表
typedef struct hash_table {
    KV **table;
    int size;
    int capacity;  //容量
    int threshold; //容量极限
    float loadFacor; //装载因子
} HashTable;

/* 初始化键值对 */
void InitKV(KV* &kv, char *key, char *value);

/* 释放键值对 */
void FreeKV(KV* &kv);

/* 初始化哈希表 */
void InitHashTable(HashTable* &table);

/* 初始化哈希表 */
void InitHashTable(HashTable* &table, int size);

/* 初始化哈希表 */
void InitHashTable(HashTable* &table, int size, float loadFactor);

/* 清空哈希表 */
void DeleteHashTable(HashTable* &table);

/* 添加Hash键值对 */
int PutHashKV(HashTable* &table, char *key, char *value);

/* 获取键值 */
char* GetHashValue(HashTable *table, char *key);

/* 删除键值对 */
char* RemoveHashKV(HashTable* &table, char *key);


#endif //DATA_STRUCT2019_HASH_HPP
