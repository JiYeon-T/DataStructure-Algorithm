#include "bt_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// TODO: 通过链表实现的一个音乐播放器数据缓存的功能
// 音频数据流队列

#if defined(DATA_STRUCTURE_STREAM_CACHE) && (DATA_STRUCTURE_STREAM_CACHE == 1)

/*
* @fun:
* @desc:
*/
void bt_node_init(bt_node_t *p_node)
{
        p_node->p_next = p_node;
        p_node->p_prev = p_node;
}

void bt_list_init(bt_list_t *p_list);
bt_node_t* bt_list_head(bt_list_t *p_list);
bt_node_t* bt_list_first(bt_list_t *p_list);
uint32_t bt_list_count(bt_list_t *p_list);
bt_node_t* bt_list_last(bt_list_t *p_list);
bt_node_t* bt_list_prev(bt_list_t *p_list, bt_node_t *p_node);
bt_node_t* bt_list_next(bt_list_t *p_list, bt_node_t *p_node);
void bt_list_add_first(bt_list_t *p_list, bt_node_t *node);
void bt_list_add_last(bt_list_t *p_list, bt_node_t *node);
bt_node_t *bt_list_remove_first(bt_list_t *p_list);
bt_node_t *bt_list_remove_last(bt_list_t *p_list);
void bt_list_remove_all(bt_list_t *p_list);
void bt_list_insert(bt_list_t *p_list, bt_node_t *p_insert_node, bt_node_t *p_insert_pos_node);
void bt_list_remove(bt_list_t *p_list, bt_node_t *p_node);

#endif