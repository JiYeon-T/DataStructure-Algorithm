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
* @fun: ��һ���ڵ�(������ͷ�ڵ�)
*/
bt_node_t* bt_list_first(bt_list_t *list)
{
    if(list->node_count == 0){
        return NULL;
    }
    return list->FIRSTNODE;
}

/*
* @fun: ���һ���ڵ�(ͷ�ڵ��ǰһ���ڵ�)
*/
bt_node_t* bt_list_last(bt_list_t *list)
{
    if(list->node_count == 0){
        return NULL;
    }
    return list->LASTNODE;
}

// ��ȡǰһ���ڵ�
bt_node_t* bt_list_prev(bt_list_t *list, bt_node_t *node)
{
    if(node->p_prev == node){
        return NULL;
    }
    return node->p_prev;
}

// ��ȡ��һ���ڵ�
bt_node_t* bt_list_next(bt_list_t *list, bt_node_t *node)
{
    if(node->p_next == node){
        return NULL;
    }
    return node->p_next;
}

// ɾ���ͷ����нڵ�
void bt_list_remove_all(bt_list_t *list)
{
    uint32_t count;
    bt_node_t *p_next;

    p_next = list->FIRSTNODE; // ����ͷ�ڵ�ĵ�һ���ڵ�
    for(count = list->node_count; count != 0; --count){
        bt_node_t *currNode = p_next;
        currNode->p_next = currNode; // ������ڴ治�ͷ���
        currNode->p_prev = currNode;
    }
    list->FIRSTNODE = &(list->head_node)��
    list->LASTNODE = &(list->head_node);
    list->node_count = 0;
    return;
}

// �����һ���ڵ�(������ͷ�ڵ�)
void bt_list_add_first(bt_list_t *list, bt_node_t *node)
{
    node->p_prev = list->FIRSTNODE->p_prev;
    node->p_next = list->FIRSTNODE;
    list->FIRSTNODE->p_prev = node;
    list->FIRSTNODE = node;
    ++list->node_count;
    return;
}

// �������һ���ڵ�(β������)
void bt_list_add_last(bt_list_t *list, bt_node_t *node)
{
    node->p_prev = list->LASTNODE;
    node->p_next = list->LASTNODE->p_next;
    list->LASTNODE->p_next = node;
    list->LASTNODE = node;
    ++list->node_count;
    return;
}

// ɾ����һ��Ԫ��, ������ͷ�ڵ�
// ����ָ���һ���ڵ��ָ��
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

// (��)����ڵ�
void bt_list_insert(bt_list_t *list, bt_node_t *node, bt_node_t *insertNode)
{
    insertNode->p_next = node->p_next;
    insertNode->p_prev = node;
    node->p_next->p_prev = insertNode;
    node->p_next = insertNode; // ������Ҫ����Ľڵ�
    ++list->node_count;
}

// ɾ��һ���ڵ�(Ϊʲô���ͷ��ڴ�, �ѵ�ʹ��ջ�ڴ�???)
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


