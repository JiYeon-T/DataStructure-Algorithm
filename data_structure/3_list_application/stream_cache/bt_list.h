#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED


#if defined(DATA_STRUCTURE_STREAM_CACHE) && (DATA_STRUCTURE_STREAM_CACHE == 1)

// call by outer class object
#define bt_list_container_offset(node, type, member)            (type*)((uint32_t)node - (uint32_t)((type*)0)->member)


// node
typedef struct bt_node {
    struct bt_node_t *p_prev;
    struct bt_node_t *p_next;
} bt_node_t;

// list
typedef struct bt_list
{
    bt_node_t head_node;
    uint32_t node_count;
} bt_list_t;


void bt_node_init(bt_node_t *p_node);
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

#endif // DATA_STRUCTURE_STREAM_CACHE

#endif // LIST_H_INCLUDED
