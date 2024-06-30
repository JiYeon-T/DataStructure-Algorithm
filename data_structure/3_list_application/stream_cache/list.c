#include "list.h"
#include "string.h"
#include "stdlib.h"

#if defined(DATA_STRUCTURE_STREAM_CACHE) && (DATA_STRUCTURE_STREAM_CACHE == 1)

// ˫��������ͷ������һ���ڵ�ָ��ͷ���; ͷ������һ���ڵ�ָ�����һ���ڵ�
// head node �ǽṹ������, �����ǽṹ��ָ��
// ���ص���ָ������
#define P_FIRSTNODE   head_node.p_next
#define P_LASTNODE    head_node.p_prev

#define UNUSED_PARAM(x)     ((void)x)


/**
* @fun: ��ʼ��һ���ڵ�
* @desc: ָ���Լ�
*/
void node_init(node_t *p_node, int data)
{
    p_node->p_next = p_node;
    p_node->p_prev = p_node;
#if INNER_LIST_TEST
    p_node->elem = data;
#else
    UNUSED_PARAM(data);
#endif
    return;
}

/**
* @fun: ˫��������ʼ��
* @desc:
*/
void list_init(list_t *p_list)
{
//    node_init(p_list->P_FIRSTNODE, 0);
//    node_init(p_list->P_LASTNODE, 0);
    p_list->P_FIRSTNODE = &(p_list->head_node);
    p_list->P_LASTNODE = &(p_list->head_node);
    p_list->node_count = 0;
    return;
}

/**
* @fun: get list node count
*/
uint32_t list_node_count_get(list_t *p_list)
{
    return p_list->node_count;
}

node_t* list_head(list_t *p_list)
{
    return &p_list->head_node; // ���ǵ�Ŀ�����, ����˳���������
}

/**
* @fun: ��һ���ڵ�(������ͷ�ڵ�)
* @desc: ͷ���� p_next ָ���һ���ڵ�
*/
node_t* list_first(list_t *p_list)
{
    if(p_list->node_count == 0){
        return NULL;
    }
    // return p_list->head_node.p_next;
    return p_list->P_FIRSTNODE;
}

/**
* @fun: ���һ���ڵ�(ͷ�ڵ��ǰһ���ڵ�)
* @desc: ͷ���� p_prev ָ�����һ���ڵ�
*/
node_t* list_last(list_t *p_list)
{
    if(p_list->node_count == 0){
        return NULL;
    }
    // return p_list->head_node.p_prev;
    return p_list->P_LASTNODE;
}

/**
* @fun: ��ȡǰһ���ڵ�
* @desc: ͷ���� p_prev ָ�����һ���ڵ�
*/
node_t* list_prev(list_t *p_list, node_t *p_node)
{
    UNUSED_PARAM(p_list);
    if(p_node->p_prev == p_node){
        return NULL;
    }
    return p_node->p_prev;
}

/**
* @fun: ��ȡ��һ���ڵ�
* @desc:
*/
node_t* list_next(list_t *p_list, node_t *p_node)
{
    if(p_node->p_next == p_node){
        return NULL;
    }
    return p_node->p_next;
}

/**
* @fun: ɾ�����нڵ�
* @desc: ����û���ͷ���Դ, �����ǽ�������ÿ���ڵ㶼��
*/
void list_remove_all(list_t *p_list)
{
    uint32_t count;
    node_t *p_temp;

    p_temp = p_list->P_FIRSTNODE; // ��һ���ڵ�(����ͷ���)
    for(count = p_list->node_count; count != 0; --count){
        node_t *curr_node = p_temp;
        p_temp = p_temp->p_next;
        curr_node->p_next = curr_node; // ������ڴ治�ͷ�����ÿһ���ڵ㶼ָ���Լ�
        curr_node->p_prev = curr_node;
    }
    p_list->P_FIRSTNODE = &(p_list->head_node);
    p_list->P_LASTNODE = &(p_list->head_node);
//    p_list->head_node.p_prev = &(p_list->head_node);
//    p_list->head_node.p_next = &(p_list->head_node);
    p_list->node_count = 0;
    return;
}

/**
* @fun: ͷ�������һ���ڵ�(������ͷ�ڵ�)
* @desc:
*/
void list_add_first(list_t *p_list, node_t *p_node)
{
    p_node->p_prev = p_list->P_FIRSTNODE->p_prev;
    p_node->p_next = p_list->P_FIRSTNODE;
    p_list->P_FIRSTNODE->p_prev = p_node;
    p_list->P_FIRSTNODE = p_node;
    ++p_list->node_count;
    return;
}

/**
* @fun: �������һ���ڵ�(β������)
* @desc:
*/
void list_add_last(list_t *p_list, node_t *p_node)
{
    p_node->p_prev = p_list->P_LASTNODE;
    p_node->p_next = p_list->P_LASTNODE->p_next;
    p_list->P_LASTNODE->p_next = p_node;
    p_list->P_LASTNODE = p_node;
    ++p_list->node_count;
    return;
}

/**
* @fun: ɾ����һ���ڵ�(������ͷ�ڵ�)
* @desc:
* @ret: ����ָ���һ���ڵ��ָ��
*/
node_t* list_remove_first(list_t *p_list)
{
    node_t *p_temp = NULL; // bt_node_t *node = (bt_node_t*)0;
    if(p_list->node_count == 0){
        return NULL;
    }

    p_temp = p_list->P_FIRSTNODE; // ȡ����һ���ڵ�
    p_temp->p_next->p_prev = &(p_list->head_node);
    p_list->P_FIRSTNODE = p_temp->p_next;
    --p_list->node_count;
    return p_temp;
}

/**
* @fun: (��)����ڵ�
* @param: p_pos_node �� p_pos_node �����ڵ�
* @param: p_node Ҫ����Ľڵ�
* @desc:
*/
void list_insert(list_t *p_list, node_t *p_pos_node, node_t *p_node)
{
    p_node->p_next = p_pos_node->p_next;
    p_node->p_prev = p_pos_node;
    p_pos_node->p_next->p_prev = p_node;
    p_pos_node->p_next = p_node; // ������Ҫ����Ľڵ�
    ++p_list->node_count;
    return;
}

/**
* @fun: ɾ��һ���ڵ�
* @desc: û���ͷ��ڴ�, �ڴ���ʹ�øö��е�һ��������ͷ�
*/
void list_remove_node(list_t *p_list, node_t *p_node)
{
    p_node->p_prev->p_next = p_node->p_next;
    p_node->p_next->p_prev = p_node->p_prev;
    --p_list->node_count;
    return;
}

#if INNER_LIST_TEST
/**
* @fun: ��������, ����ʹ��
* @desc:
*/
static void list_traverse(list_t *p_list)
{
    if(!p_list){
        printf("null\r\n");
        return;
    }
    node_t *p_temp = p_list->P_FIRSTNODE;
    //printf("%d-> ", p_temp->elem);

    do{
        printf("%d-> ", p_temp->elem);
        p_temp = p_temp->p_next;
    }
    while(p_temp != &p_list->head_node);
    printf("\r\n");
    return;
}
#endif


void list_test_raw()
{
#if INNER_LIST_TEST
    list_t list;
    node_t temp_node, temp_node2, temp_node3;

    printf("list:%p temp_node:%p temp_node2:%p\r\n", &list, &temp_node, &temp_node2);
    node_init(&temp_node, 123);
    list_init(&list);
    list_traverse(&list);

    list_add_first(&list, &temp_node);
    list_traverse(&list);

    node_init(&temp_node2, 3445);
    list_add_last(&list, &temp_node2);
    list_traverse(&list);

    printf("element:%d\r\n", list_node_count_get(&list));

    printf("first:%d\r\n", list_first(&list)->elem);

    printf("last:%d\r\n", list_last(&list)->elem);

    printf("prev:%d\r\n", list_prev(&list, &temp_node2)->elem);

    printf("next:%d\r\n", list_next(&list, &temp_node)->elem);

    node_init(&temp_node3, 789);
    list_insert(&list, &temp_node, &temp_node3);
    list_traverse(&list);

    list_remove_node(&list, &temp_node2);
    list_traverse(&list);

    list_remove_all(&list);
    list_traverse(&list);

    list_add_first(&list, &temp_node);
    list_traverse(&list);
#endif
}

#endif // DATA_STRUCTURE_STREAM_CACHE







