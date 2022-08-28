#ifndef __SERVICE_BT_LIST_H__
#define __SERVICE_BT_LIST_H__

#include <stdint.h>
#include <stdlib.h>

//#ifndef __cplusplus
//extern "C" {
//#endif // __cplusplus

// macro
// ͨ���ṹ���Ա��ȡ�ṹ����׵�ַ
#define bt_list_container_of(node, type, member) (type*)((uint32_t)node - (uint32_t)&((type*)0)->member)


// typedef
typedef struct bt_node
{
    struct bt_node *p_prev;
    struct bt_node *p_next;
} bt_node_t; // list node, ˫��ѭ������

typedef struct bt_list
{
    // struct_bt_node_t *p_prev;
    // struct_bt_node_t *p_next;
    bt_node_t head_node;    // ����ָ��, �ǽṹ��, �ṹ���Ա��ָ��
    uint32_t node_count;    //
} bt_list_t;

void bt_node_init(bt_node_t *node);

void bt_list_init(bt_list_t *list);

uint32_t bt_list_count(bt_list_t *list);

bt_node_t* bt_list_head(bt_list_t *list);

// ��һ���ڵ�(������ͷ�ڵ�)
bt_node_t* bt_list_first(bt_list_t *list);

//���һ���ڵ�(ͷ�ڵ��ǰһ���ڵ�)
bt_node_t* bt_list_last(bt_list_t *list);

// ��ȡǰһ���ڵ�
bt_node_t* bt_list_prev(bt_list_t *list, bt_node_t *node);

// ��ȡ��һ���ڵ�
bt_node_t* bt_list_next(bt_list_t *list, bt_node_t *node);

// ɾ���ͷ����нڵ�
void bt_list_remove_all(bt_list_t *list);

// �����һ���ڵ�(������ͷ�ڵ�)
void bt_list_add_first(bt_list_t *list, bt_node_t *node);

// �������һ���ڵ�(β������)
void bt_list_add_last(bt_list_t *list, bt_node_t *node);

// ɾ����һ��Ԫ��, ������ͷ�ڵ�
// ����ָ���һ���ڵ��ָ��
bt_node_t* bt_list_remove_first(bt_list_t *list);

// (��)����ڵ�
void bt_list_insert(bt_list_t *list, bt_node_t *node, bt_node_t *insertNode);

// ɾ��һ���ڵ�(Ϊʲô���ͷ��ڴ�, �ѵ�ʹ��ջ�ڴ�???)
void bt_list_remove_node(bt_list_t *list, bt_node_t *node);

void test();

#endif // __SERVICE_BT_LIST_H__
