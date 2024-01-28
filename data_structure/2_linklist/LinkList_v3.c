#include "LinkList_v3.h"
#include <limits.h>

// TODO:
// (2) 传参传 Node * 类型, 不使用 Node ** 类型可以吗?

#if defined(DataStructLinkListV3) && (DataStructLinkListV3 == 1)
/**
 * @fun 初始化一个链表, 要修改指针的值, 所以传递 Node** 类型
 *      没有头节点的链表, 空链表头指针为空即可
 *      非必要的一个接口
 * 
 * @param p_first 头指针
*/
Status InitLinkList(Node **p_first)
{
    *p_first = NULL;

    return OK;
}

// insert at tail
Status PutElem(Node **p_first, ElemType data)
{
    Node *p_prev, *p_curr, *p_insert;

    p_insert = (Node*)malloc(sizeof(Node) * 1);
    if (!p_insert)
        return ERROR;
    p_insert->data = data;
    p_insert->next = NULL;

    if (!(*p_first)) { // 空链表:要插入的节点是头节点
        // set head pointer
        *p_first = p_insert;
        return OK;
    }
    // else { // 非空链表:中间节点
    p_curr = *p_first;
    p_prev = p_curr;

    while (p_curr) { // 寻找尾节点, 保存前一个节点
        p_prev = p_curr;
        p_curr = p_curr->next;
    }
    
    p_prev->next = p_insert;

    return OK;
}

/**
 * @fun insert before position idx
 * 
 * @param[in] p_first head pointer
 * @param[in] idx start from 0
 * @param[in] data element data
 * @ret
*/
Status InsertElemBeforeIdx(Node **p_first, size_t idx, ElemType data)
{
    if (!(*p_first) && idx != 0) // 空链表还不插入第一个节点
        return ERROR;
    Node *p_insert, *p_curr, *p_prev;
    size_t jx = 0;

    p_insert = (Node*)malloc(sizeof(Node));
    if (!p_insert) {
        return ERROR;
    }
    p_insert->data = data;
    p_insert->next = NULL;
    if (!(*p_first)) { // 空链表:要插入的节点是头节点
        *p_first = p_insert;
        return OK;
    } else if (idx == 0) { // 非空链表:插入头节点
        p_insert->next = *p_first;
        *p_first = p_insert;
        return OK;
    }

    // else {} // 非空链表:中间节点
    p_curr = *p_first;
    p_prev = p_curr;
    while (p_curr && jx < idx) {
        p_prev = p_curr;
        p_curr = p_curr->next;
        ++jx;
    }

    if (!p_curr || jx > idx) {
        free(p_insert);
        return ERROR;
    }

    p_insert->next = p_curr;
    p_prev->next = p_insert;

    return OK;
}

/**
 * @fun insert before idx position
 * @param[in] p_first head pointer
 * @param[in] idx start from 0
 * @param[in] data element data
 * @ret
*/
Status DeleteElem(Node **p_first, size_t idx, ElemType *p_data)
{
    if (!p_first || !(*p_first) || idx < 0 || !p_data)
        return ERROR;

    Node *p_curr, *p_prev;
    size_t jx;

    p_curr = *p_first;
    if (idx == 0) { // delete first node
        *p_first = p_curr->next; // 更新头节点
        free(p_curr); // 删除节点
        return OK;
    }
    // else {} // 删除中间节点
    p_prev = p_curr;
    while (p_curr && jx < idx) {
        p_prev = p_curr;
        p_curr = p_curr->next;
        ++jx;
    }
    if (!p_curr || jx > idx) {
        return ERROR;
    }

    p_prev->next = p_curr->next;
    *p_data = p_curr->data;
    free(p_curr);

    return OK;
}

/**
 * @fun set
 * 
 * @param[in] p_first head pointer
 * @param[in] idx start from 0
 * @param[in] data element data
 * @ret
 **/
Status SetElem(Node *p_first, size_t idx, ElemType data)
{
    if (!p_first || idx < 0)
        return ERROR;
    Node *p_curr = p_first;
    size_t jx;

    while (p_curr && jx < idx) {
        p_curr = p_curr->next;
        ++jx;
    }
    if (!p_curr || jx > idx)
        return ERROR;
    
    p_curr->data = data;

    return OK;
}

/**
 * @fun get
 *
 * @param[in] p_first head pointer
 * @param[in] idx start from 0
 * @param[in] data element data
 * @ret
 **/
Status GetElem(const Node *p_first, size_t idx, ElemType *p_data)
{
    if (!p_first || idx < 0 || !p_data)
        return ERROR;
    Node *p_curr = p_first;
    size_t jx;

    while (p_curr && jx < idx) {
        p_curr = p_curr->next;
        ++jx;
    }
    if (!p_curr || jx > idx)
        return ERROR;
    
    *p_data = p_curr->data;

    return OK;
}

// 没有头节点
Status Traverse(const Node *p_first, const char *p_op_info)
{
    if (!p_first)
        return ERROR;
    size_t idx = 0;

    printf("traverse(%s):\n", p_op_info);
    Node *pTemp = p_first; // first node
    while (pTemp) {
        printf("[%d]:%d ->", idx++, pTemp->data);
        pTemp = pTemp->next;
    }
    printf("\n\n");

    return OK;
}

void linklist_api_test_v3(void)
{
    Node *p_head = NULL;
    Status ret;
    ElemType data;

    ret = InitLinkList(&p_head);
    CHECK_RET_OP(ret, "Init");

    ret = PutElem(&p_head, 0);
    CHECK_RET_OP(ret, "put");
    ret = Traverse(p_head, "put:0");
    CHECK_RET_OP(ret, "put:0");

    ret = PutElem(&p_head, 1);
    CHECK_RET_OP(ret, "put");
    ret = Traverse(p_head, "put：1");
    CHECK_RET_OP(ret, "put");

    ret = InsertElemBeforeIdx(&p_head, 0, 123);
    CHECK_RET_OP(ret, "insert:123 at head");
    ret = Traverse(p_head, "insert at head");
    CHECK_RET_OP(ret, "insert at head");

    ret = DeleteElem(&p_head, 0, &data);
    CHECK_RET_OP(ret, "delete");
    printf("delte idx:%d elem:%d\n", 0, data);
    ret = Traverse(p_head, "delete head node");
    CHECK_RET_OP(ret, "delete");

    ret = SetElem(p_head, 1, 111);
    CHECK_RET_OP(ret, "set");
    ret = Traverse(p_head, "set idx:1 val:111");
    CHECK_RET_OP(ret, "set");

    ret = GetElem(p_head, 1, &data);
    CHECK_RET_OP(ret, "get");
    printf("get idx:%d val:%d\n", 1, data);
    ret = Traverse(p_head, "get");
    CHECK_RET_OP(ret, "get");
}

#endif