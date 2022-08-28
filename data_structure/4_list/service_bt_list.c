/*
* @file
* @date:
* @author:
*/
#include "service_bt_list.h"

#define FIRSTNODE   head_node.p_next
#define LASTNODE    head_node.p_prev

#if 0
void bt_node_init(bt_node_t *node)
{
    node->p_next = node;
    node->p_prev = node;
    return;
}

void bt_list_init(bt_list_t *list)
{
    list->FIRSTNODE = &(list->head_node);
    list->LASTNODE = &(list->head_node);
    list->node_count = 0;
    return;
}

uint32_t bt_list_count(bt_list_t *list)
{
    return list->node_count;
}

bt_node_t* bt_list_head(bt_list_t *list)
{
    return &(list->head_node); // head_node bt_node_t type
}

/*
* @fun: 第一个节点(不包括头节点)
*/
bt_node_t* bt_list_first(bt_list_t *list)
{
    if(list->node_count == 0){
        return NULL;
    }
    return list->FIRSTNODE;
}

/*
* @fun: 最后一个节点(头节点的前一个节点)
*/
bt_node_t* bt_list_last(bt_list_t *list)
{
    if(list->node_count == 0){
        return NULL;
    }
    return list->LASTNODE;
}

// 获取前一个节点
bt_node_t* bt_list_prev(bt_list_t *list, bt_node_t *node)
{
    if(node->p_prev == node){
        return NULL;
    }
    return node->p_prev;
}

// 获取后一个节点
bt_node_t* bt_list_next(bt_list_t *list, bt_node_t *node)
{
    if(node->p_next == node){
        return NULL;
    }
    return node->p_next;
}

// 删除释放所有节点
void bt_list_remove_all(bt_list_t *list)
{
    uint32_t count;
    bt_node_t *p_next;

    p_next = list->FIRSTNODE; // 不是头节点的第一个节点
    for(count = list->node_count; count != 0; --count){
        bt_node_t *currNode = p_next;
        currNode->p_next = currNode; // 申请的内存不释放吗？
        currNode->p_prev = currNode;
    }
    list->FIRSTNODE = &(list->head_node)；
    list->LASTNODE = &(list->head_node);
    list->node_count = 0;
    return;
}

// 插入第一个节点(不包括头节点)
void bt_list_add_first(bt_list_t *list, bt_node_t *node)
{
    node->p_prev = list->FIRSTNODE->p_prev;
    node->p_next = list->FIRSTNODE;
    list->FIRSTNODE->p_prev = node;
    list->FIRSTNODE = node;
    ++list->node_count;
    return;
}

// 插入最后一个节点(尾部插入)
void bt_list_add_last(bt_list_t *list, bt_node_t *node)
{
    node->p_prev = list->LASTNODE;
    node->p_next = list->LASTNODE->p_next;
    list->LASTNODE->p_next = node;
    list->LASTNODE = node;
    ++list->node_count;
    return;
}

// 删除第一个元素, 不包括头节点
// 返回指向第一个节点的指针
bt_node_t* bt_list_remove_first(bt_list_t *list)
{
    bt_node_t *node = NULL; // bt_node_t *node = (bt_node_t*)0;
    if(list->node_count == 0){
        return NULL;
    }

    node = list->FIRSTNODE;
    node->p_next->p_prev = &(list->head_node);
    list->FIRSTNODE = node->p_next;
    --list->node_count;
    return node;
}

// (后)插入节点
void bt_list_insert(bt_list_t *list, bt_node_t *node, bt_node_t *insertNode)
{
    insertNode->p_next = node->p_next;
    insertNode->p_prev = node;
    node->p_next->p_prev = insertNode;
    node->p_next = insertNode; // 最后更新要插入的节点
    ++list->node_count;
}

// 删除一个节点(为什么不释放内存, 难道使用栈内存???)
void bt_list_remove_node(bt_list_t *list, bt_node_t *node)
{
    node->p_prev->p_next = node->p_next;
    node->p_next->p_prev = node->p_prev;
    --list->node_count;
    return;
}

void test()
{


}
#endif


