#ifndef __LRU_H__
#define __LRU_H__

typedef struct Node {
    int key; // 键为缓存项的键
    int value; // 值为指向双向链表中对应节点的指针
    struct Node *prev; // 双向链表
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    Node **cache; // 哈希表，存储指向节点的指针
    int capacity; // cache 容量
} LRUCache;

LRUCache *create_lru_cache(int capacity);
void insert(LRUCache *cache, int key, int value);
int get(LRUCache *cache, int key);
void move_to_head(LRUCache *cache, Node *node);
void remove_from_list(LRUCache *cache, Node *node);


#endif