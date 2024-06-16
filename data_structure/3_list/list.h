/**
* @file:listh.h
* @desc: 通过双向链表实现的一个缓存队列
*
*/
#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <stdint.h>

// 通过结构图体成员获取该结构体的地址
// <Linux 内核设计与实现> p69, 应用举例:
// #include <linux/list.h>
// #include <nuttx/list.h>
#define bt_list_container_of(node, type, member) (type*)((uint32_t)node - (uint32_t)&((type*)0)->member)


// 通过结构体成员获取结构体的首地址
//#define offsetof(type, member)      ((uint32_t)&((type*)0)->member)
//#define bt_list_container_of(node, type, member) (type*)((uint32_t)node - offsetof(type, member))

// 双向链表内部测试使用
#define INNER_LIST_TEST         0

// typedef
typedef struct node
{
    struct node *p_prev;
    struct node *p_next;
#if INNER_LIST_TEST
    int elem;
#endif
} node_t; // list node, 双向链表

typedef struct list
{
    node_t head_node;       // 不是指针, 是结构体, 结构体成员是指针
    uint32_t node_count;    // 双向链表包含头结点, 但是头结点不保存数据
} list_t;


/**
* @fun: 初始化一个节点
* @desc: 指向自己
*/
void node_init(node_t *p_node, int data);

/**
* @fun: 双向链表初始化
* @desc:
*/
void list_init(list_t *p_list);

/**
* @fun: get list node count
*/
uint32_t list_node_count_get(list_t *p_list);

/**
* @fun: 第一个节点(不包括头节点)
* @desc: 头结点的 p_next 指向第一个节点
*/
node_t* list_first(list_t *p_list);

/**
* @fun: 最后一个节点(头节点的前一个节点)
* @desc: 头结点的 p_prev 指向最后一个节点
*/
node_t* list_last(list_t *p_list);

/**
* @fun: 获取前一个节点
* @desc: 头结点的 p_prev 指向最后一个节点
*/
node_t* list_prev(list_t *p_list, node_t *p_node);

/**
* @fun: 获取后一个节点
* @desc:
*/
node_t* list_next(list_t *p_list, node_t *p_node);

/**
* @fun: 删除所有节点
* @desc: 这里没有释放资源, 仅仅是将链表的每个节点都拆开
*/
void list_remove_all(list_t *p_list);

/**
* @fun: 头部插入第一个节点(不包括头节点)
* @desc:
*/
void list_add_first(list_t *p_list, node_t *p_node);

/**
* @fun: 插入最后一个节点(尾部插入)
* @desc:
*/
void list_add_last(list_t *p_list, node_t *p_node);

/**
* @fun: 删除第一个节点(不包括头节点)
* @desc:
* @ret: 返回指向第一个节点的指针
*/
node_t* list_remove_first(list_t *p_list);

/**
* @fun: (后)插入节点
* @param: p_pos_node 在 p_pos_node 后插入节点
* @param: p_node 要插入的节点
* @desc:
*/
void list_insert(list_t *p_list, node_t *p_pos_node, node_t *p_node);

/**
* @fun: 删除一个节点
* @desc: 没有释放内存, 内存由使用该队列的一起申请和释放
*/
void list_remove_node(list_t *p_list, node_t *p_node);


void list_test_raw();


#endif // LIST_H_INCLUDED
