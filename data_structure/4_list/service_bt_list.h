#ifndef __SERVICE_BT_LIST_H__
#define __SERVICE_BT_LIST_H__

#include <stdint.h>
#include <stdlib.h>

//#ifndef __cplusplus
//extern "C" {
//#endif // __cplusplus

// macro
// 通过结构体成员获取结构体的首地址
#define bt_list_container_of(node, type, member) (type*)((uint32_t)node - (uint32_t)&((type*)0)->member)


// typedef
typedef struct bt_node
{
    struct bt_node *p_prev;
    struct bt_node *p_next;
} bt_node_t; // list node, 双向循环链表

typedef struct bt_list
{
    // struct_bt_node_t *p_prev;
    // struct_bt_node_t *p_next;
    bt_node_t head_node;    // 不是指针, 是结构体, 结构体成员是指针
    uint32_t node_count;    //
} bt_list_t;

void bt_node_init(bt_node_t *node);

void bt_list_init(bt_list_t *list);

uint32_t bt_list_count(bt_list_t *list);

bt_node_t* bt_list_head(bt_list_t *list);

// 第一个节点(不包括头节点)
bt_node_t* bt_list_first(bt_list_t *list);

//最后一个节点(头节点的前一个节点)
bt_node_t* bt_list_last(bt_list_t *list);

// 获取前一个节点
bt_node_t* bt_list_prev(bt_list_t *list, bt_node_t *node);

// 获取后一个节点
bt_node_t* bt_list_next(bt_list_t *list, bt_node_t *node);

// 删除释放所有节点
void bt_list_remove_all(bt_list_t *list);

// 插入第一个节点(不包括头节点)
void bt_list_add_first(bt_list_t *list, bt_node_t *node);

// 插入最后一个节点(尾部插入)
void bt_list_add_last(bt_list_t *list, bt_node_t *node);

// 删除第一个元素, 不包括头节点
// 返回指向第一个节点的指针
bt_node_t* bt_list_remove_first(bt_list_t *list);

// (后)插入节点
void bt_list_insert(bt_list_t *list, bt_node_t *node, bt_node_t *insertNode);

// 删除一个节点(为什么不释放内存, 难道使用栈内存???)
void bt_list_remove_node(bt_list_t *list, bt_node_t *node);

void test();

#endif // __SERVICE_BT_LIST_H__
