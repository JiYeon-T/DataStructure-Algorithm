#include "list.h"
#include "string.h"
#include "stdlib.h"


// 双向链表的头结点的下一个节点指向头结点; 头结点的上一个节点指向最后一个节点
// head node 是结构体类型, 而不是结构体指针
// 返回的是指针类型
#define P_FIRSTNODE   head_node.p_next
#define P_LASTNODE    head_node.p_prev

#define UNUSED_PARAM(x)     ((void)x)


/**
* @fun: 初始化一个节点
* @desc: 指向自己
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
* @fun: 双向链表初始化
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
    return &p_list->head_node; // 都是单目运算符, 计算顺序从右向左
}

/**
* @fun: 第一个节点(不包括头节点)
* @desc: 头结点的 p_next 指向第一个节点
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
* @fun: 最后一个节点(头节点的前一个节点)
* @desc: 头结点的 p_prev 指向最后一个节点
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
* @fun: 获取前一个节点
* @desc: 头结点的 p_prev 指向最后一个节点
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
* @fun: 获取后一个节点
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
* @fun: 删除所有节点
* @desc: 这里没有释放资源, 仅仅是将链表的每个节点都拆开
*/
void list_remove_all(list_t *p_list)
{
    uint32_t count;
    node_t *p_temp;

    p_temp = p_list->P_FIRSTNODE; // 第一个节点(包含头结点)
    for(count = p_list->node_count; count != 0; --count){
        node_t *curr_node = p_temp;
        p_temp = p_temp->p_next;
        curr_node->p_next = curr_node; // 申请的内存不释放吗？让每一个节点都指向自己
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
* @fun: 头部插入第一个节点(不包括头节点)
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
* @fun: 插入最后一个节点(尾部插入)
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
* @fun: 删除第一个节点(不包括头节点)
* @desc:
* @ret: 返回指向第一个节点的指针
*/
node_t* list_remove_first(list_t *p_list)
{
    node_t *p_temp = NULL; // bt_node_t *node = (bt_node_t*)0;
    if(p_list->node_count == 0){
        return NULL;
    }

    p_temp = p_list->P_FIRSTNODE; // 取出第一个节点
    p_temp->p_next->p_prev = &(p_list->head_node);
    p_list->P_FIRSTNODE = p_temp->p_next;
    --p_list->node_count;
    return p_temp;
}

/**
* @fun: (后)插入节点
* @param: p_pos_node 在 p_pos_node 后插入节点
* @param: p_node 要插入的节点
* @desc:
*/
void list_insert(list_t *p_list, node_t *p_pos_node, node_t *p_node)
{
    p_node->p_next = p_pos_node->p_next;
    p_node->p_prev = p_pos_node;
    p_pos_node->p_next->p_prev = p_node;
    p_pos_node->p_next = p_node; // 最后更新要插入的节点
    ++p_list->node_count;
    return;
}

/**
* @fun: 删除一个节点
* @desc: 没有释放内存, 内存由使用该队列的一起申请和释放
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
* @fun: 遍历链表, 测试使用
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








