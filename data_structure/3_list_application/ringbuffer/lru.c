#include "lru.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* Least Recently Used 最近最少使用）缓存算法
LRU算法是一种缓存淘汰策略，其核心思想是：
如果一个数据项在最近一段时间内未被访问过，那么在将来它被访问的概率也不大。因此，当缓存空间不足时，LRU算法会选择最近最少使用的数据项进行淘汰。


 实现原理:
 为了高效地实现LRU算法，我们需要两种主要的数据结构：哈希表和双向链表。
 哈希表用于快速查找缓存中的数据项， O(1), ‌哈希表‌：键为缓存项的键，值为指向双向链表中对应节点的指针。
 而双向链表则用于维护缓存中数据项的访问顺序。每个节点包含键、值、前驱指针和后继指针。"链表头指向最近访问的节点，链表尾指向最久未访问的节点"

----------------------------------------------------------------------
[] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] [] []
----------------------------------------------------------------------
链表头部:最近使用的                             链表尾部, 最长时间未使用的
*/


// TODO: 这篇文章的代码有很多问题, 停留在画马第 2 步!!!!!!
// https://yr7ywq.smartapps.baidu.com/?content_id=26a031b&word=LRU%2Bc%2B%E5%AE%9E%E7%8E%B0&_chatQuery=LRU%20c%20%E5%AE%9E%E7%8E%B0&searchid=15423938840904662945&_chatParams=%7B%22content_build_id%22%3A%2226a031b%22%2C%22from%22%3A%22q2c%22%2C%22token%22%3A%22H9b1KvmKNDnoEuSAx9VGVMcqasqBvuslDkUwlaZp0wsXTjEx4yVXndyK1eb%2FTMh4V1g%2Bjog2P%2FeIll2hnaQ2xTCdA9l%2B7lla1YEPh0v5Ix4%3D%22%2C%22chat_no_login%22%3Atrue%2C%22agent_id%22%3A%22c816%22%7D&_swebScene=3711000610000000


#define CAPACITY        100




/**
 * @brief Create a lru cache object
 *        初始化函数负责创建哈希表和双向链表，并设置缓存的容量。
 * 
 * @param capacity 
 * @return LRUCache* 
 */
LRUCache *create_lru_cache(int capacity)
{
    LRUCache *cache = (LRUCache*)malloc(sizeof(LRUCache));
    if (!cache) {
        printf("malloc failed");
        return NULL;
    }

    cache->head = (Node*)malloc(sizeof(Node)); // 空闲的头结点和空闲的尾节点, 这里的实现和之前有点不一样
    cache->tail =  (Node*)malloc(sizeof(Node));
    cache->head->next = cache->tail; // 没有初始化 prev
    cache->tail->next = cache->head;
    cache->cache = (Node**)calloc(capacity, sizeof(Node*)); // 存储指向节点的指针
    cache->capacity = capacity;

    return cache;
}

/**
 * @brief 插入操作函数负责在缓存中插入新的数据项，或在数据项已存在时更新其值。
 *        如果缓存已满，则需要删除最久未使用的数据项。
 * 
 * @param cache 
 * @param key 键为缓存项的键，
 * @param value 值为指向双向链表中对应节点的指针。
 */
void insert(LRUCache *cache, int key, int value)
{
    int index = key % cache->capacity; // hash
    if (cache->cache[index] != NULL) { // 更新已存在的数据项
        Node *node = cache->cache[index];
        node->value = value;
        move_to_head(cache, node);
    } else { // 插入新的数据项
        if (cache->head->next == cache->tail) { // 缓存已满，删除最久未使用的数据项, TODO:这里是空链表把?
            Node *tailNode = cache->tail->prev; // 倒数第一个节点
            int tailIndex = tailNode->key % cache->capacity; // key 不是已经 hash 过了？
            cache->cache[tailIndex] = NULL;
            remove_from_list(cache, tailNode);
        }

        Node *newNode = (Node*)malloc(sizeof(Node)); // 插入到第一个节点
        newNode->key = key;
        newNode->value = value;
        newNode->prev = cache->head;
        newNode->next = cache->head->next;
        cache->head->next->prev = newNode;
        cache->head->next = newNode;
        cache->cache[key % cache->capacity] = newNode;
    }
}

/**
 * @brief 获取操作函数负责根据键查找缓存中的数据项，并更新该数据项为最近访问。
 *        如果数据项不存在，则返回-1。
 * 
 * @param cache 
 * @param key 
 * @return int value
 */
int get(LRUCache *cache, int key)
{
    int index = key % cache->capacity;
    if (cache->cache[index] != NULL) {
        Node *node = cache->cache[index];
        move_to_head(cache, node); // 这里只要访问了就移动到最前面的位置
        return node->value;
    }

    return -1;
}

/**
 * @brief 移动到第一个节点
 * 
 * @param cache 
 * @param node 
 */
void move_to_head(LRUCache *cache, Node *node)
{
    remove_from_list(cache, node);
    node->prev = cache->head;
    node->next = cache->head->next;
    cache->head->next->prev = node;
    cache->head->next = node;
}

/**
 * @brief 删除节点
 * 
 * @param cache 
 * @param node 
 */
void remove_from_list(LRUCache *cache, Node *node)
{
    node->prev->next = node->next;
    node->next->prev = node->prev;
}


int main(int argc, char *argv[])
{
    LRUCache *cache = create_lru_cache(3);

    insert(cache, 1, 1);
    insert(cache, 2, 2);
    insert(cache, 2, 2);
    printf("Get key 2:%d", get(cache, 2));

    insert(cache, 4, 4); // 缓存已满，应删除 key 1
    printf("get key 1:%d", get(cache, 1));
    printf("get key 2:%d", get(cache, 2));
    printf("get key 3:%d", get(cache, 3));
    printf("get key 4:%d", get(cache, 4));
}