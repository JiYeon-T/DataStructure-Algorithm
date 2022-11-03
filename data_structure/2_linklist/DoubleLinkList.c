/**
 * @file DoubleLinkList.c
 * @author your name (you@domain.com)
 * @brief 双向链表
 * @version 0.1
 * @date 2022-03-26
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "./DoubleLinkList.h"
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>


// 不保存尾指针的双向链表的操作与单向链表相比没有什么优势, 且写法差别不大, 还是需要保存尾指针
// typedef struct
// {
//     LinkList_DL head, tail;
//     size_t size;
// } LinkList_DL_v2;

#if WITHOUT_TAIL_POINTER
/**
 * @brief initialize
 *        (1) 头结点的 prev = NULL, next = NULL;
 *        (2) 仅仅从 prev 方向或者 next 方向来看是一个单向链表;
 *        (3) 包含头结点, 头结点不保存数据;
 * @param dl
 * @return Status
 */
Status InitLinkList_DL(LinkList_DL *dl)
{
    if(!dl){
        return ERROR;
    }

    Node_DL *head = (Node_DL*)malloc(sizeof(Node_DL) * 1);
    if(!head){
        printf("memory allocate failed\r\n");
        return ERROR;
    }
    head->data = INT_MAX;
    head->prev = NULL;
    head->next = NULL;

    *dl = head;

    return OK;
}

/**
 * @brief initialize with array
 *
 * @param dl
 * @param arr
 * @param len
 * @return Status
 */
Status InitLinkListWithArray_DL(LinkList_DL *dl, ElemType *arr, size_t len)
{
    if(InitLinkList_DL(dl) != OK || !arr || len < 0){
        return ERROR;
    }

    for(size_t ix = 0; ix < len; ++ix){
        // head/tail insert
    }

    return OK;
}

/**
 * @brief head insert
 *        时间复杂度:O(1)
 *
 * @param dl
 * @param data
 * @return Status
 */
Status InsertHead_DL(LinkList_DL dl, ElemType data)
{
    if(!dl){
        return ERROR;
    }

    Node_DL *temp = (Node_DL*)malloc(sizeof(Node_DL) * 1);
    if(!temp){
        printf("memory allocate failed\r\n");
        return ERROR;
    }
    temp->data = data;
    temp->prev = dl; // prev point to head ndoe
    temp->next = dl->next;
    dl->next = temp; // update head node

    return OK;
}

/**
 * @brief tail insert
 *
 * @param dl
 * @param data
 * @return Status
 */
Status InsertTail_DL(LinkList_DL dl, ElemType data)
{
    if(!dl){
        return ERROR;
    }

    Node_DL *temp = dl->next, *prev = temp;
    // get tail ndoe
    while(temp != NULL){
        prev = temp;
        temp = temp->next;
    }

    // create a new node
    temp = (Node_DL*)malloc(sizeof(Node_DL) * 1);
    temp->data = data;
    temp->next = NULL;
    temp->prev = prev;
    prev->next = temp;

    return OK;
}

/**
 * @brief remove node
 *
 * @param dl
 * @param idx index start from 0
 * @param data
 * @return Status
 */
Status RemoveElem_DL(LinkList_DL dl, size_t idx, ElemType *data)
{
    if(!dl || idx < 0 || !data){
        return ERROR;
    }

    size_t jx = 0;
    Node_DL *temp = dl->next, *prior = temp;

    while (temp != NULL && jx < idx)
    {
        prior = temp;
        temp = temp->next;
        ++jx;
    }

    if(temp == NULL || jx > idx){
        return ERROR;
    }

    prior->next = temp->next;

    // 这里能有什么问题呢? 没有想明白
    // temp->next->prev = prior; // ?????????????????????????????????????????????????????

    // copy data
    *data = temp->data;
    free(temp);

    return OK;
}

/**
 * @brief Modify element
 *
 * @param dl
 * @param idx
 * @param data
 * @return Status
 */
Status ModifyElem_DL(LinkList_DL dl, size_t idx, ElemType *data)
{
    if(!dl || idx < 0 || !data){
        return ERROR;
    }

    size_t jx = 0;
    Node_DL *temp = dl->next;

    while(temp != NULL && jx < idx){
        ++jx;
        temp = temp->next;
    }

    if(temp == NULL || jx > idx){
        return ERROR;
    }

    temp->data = *data;

    return OK;
}

Status GetElem_DL(LinkList_DL dl, size_t idx, ElemType *data)
{

}

Status GetPriorElem_DL(LinkList_DL dl, Node_DL *node, Node_DL *prior)
{

}

Status GetNextElem_DL(LinkList_DL dl, Node_DL *node, Node_DL *next)
{

}

/**
 * @brief 前向遍历
 *        适用于尾指针也保存的情况
 *
 * @param dl
 * @return Status
 */
Status TraversePrior_DL(LinkList_DL dl)
{

}

/**
 * @brief 后向遍历
 *
 * @param dl
 * @return Status
 */
Status TraverseNext_DL(LinkList_DL dl)
{
    if(!dl){
        return ERROR;
    }
    Node_DL *temp = dl->next; // from first node to tail node

    printf("Traverse:\r\n");
    while (temp != NULL)
    {
        printf("%d ->", temp->data);
        temp = temp->next;
    }
    printf("\r\n\r\n");

    return OK;
}

Status Clear_DL(LinkList_DL dl)
{

}

Status Deinit_DL(LinkList_DL dl)
{

}

void DoubleListTest()
{
    LinkList_DL dl; // 头指针
    ElemType data;
    size_t idx;

    InitLinkList_DL(&dl);
    TraverseNext_DL(dl);

    data = 100;
    InsertHead_DL(dl, data);
    printf("add head:%d\r\n", data);
    TraverseNext_DL(dl);

    data = 58;
    InsertHead_DL(dl, data);
    printf("add head:%d\r\n", data);
    TraverseNext_DL(dl);

    data = 123;
    InsertTail_DL(dl, data);
    printf("insert tail:%d\r\n", data);
    TraverseNext_DL(dl);

    idx = 1;
    RemoveElem_DL(dl, idx, &data);
    printf("remove index:%d val:%d\r\n", idx, data);
    TraverseNext_DL(dl);

    idx = 0;
    data = 12345;
    ModifyElem_DL(dl, idx, &data);
    printf("Modify idx:%d value:%d", idx, data);
    TraverseNext_DL(dl);
}
#else // #ifdef WITHOUT_TAIL_POINTER

/*********************************** 2.包含尾指针 ********************************************/
/**
 * @brief initialize

 * @param dl
 * @return Status
 */
Status InitLinkList_DL(LinkList_DL_v2 *dl)
{
    if(!dl){
        return ERROR;
    }

    Node_DL *head = (Node_DL*)malloc(sizeof(Node_DL) * 1);
    head->data = INT_MAX;
    head->prev = NULL;
    head->next = NULL;

    dl->len = 0;
    dl->pHead = head; // 空链表:头指针, 尾指针都指向头结点
    dl->pTail = head;

    return OK;
}

/**
 * @brief initialize with array
 *
 * @param dl
 * @param arr
 * @param len
 * @return Status
 */
Status InitLinkListWithArray_DL(LinkList_DL_v2 *dl, ElemType *arr, size_t len)
{

}

/**
 * @brief head insert
 *        时间复杂度:O(1)
 *
 * @param dl
 * @param data
 * @return Status
 */
Status InsertHead_DL(LinkList_DL_v2 *dl, ElemType data)
{
    if(!dl){
        return ERROR;
    }

    Node_DL *temp = (Node_DL*)malloc(sizeof(Node_DL) * 1);
    if(!temp){
        printf("malloc failed\r\n");
        return ERROR;
    }
    
    // 这里必须引入第三个变量保存 pFirst
    Node_DL *pFirst = dl->pHead->next;
    temp->data = data;
    temp->next = dl->pHead->next; // NULL, empty linklist
    temp->prev = dl->pHead; //  前驱节点
    dl->pHead->next = temp;
    if(pFirst) // 非空链表
        // 为什么这里不引入第三个变量就会报错????????????????????????????????????????????
        pFirst->prev = temp;

    if(!pFirst) // 空链表, 则更新尾节点, 否则不更新
        dl->pTail = temp; // 更新尾节点

    ++dl->len;

    return OK;
}

/**
 * @brief tail insert
 *
 * @param dl
 * @param data
 * @return Status
 */
Status InsertTail_DL(LinkList_DL_v2 *dl, ElemType data)
{
    if(!dl){
        return ERROR;
    }

    Node_DL *temp = (Node_DL*)malloc(sizeof(Node_DL) * 1);
    if(!temp){
        printf("malloc failed\r\n");
        return ERROR;
    }
    temp->data = data;
    temp->next = NULL;
    temp->prev = dl->pTail;
    dl->pTail->next = temp;
    dl->pTail = temp;

    ++dl->len;

    return OK;
}

/**
 * @brief 在节点前插入一个节点
 *
 * @param dl
 * @param idx from 0 to len-1
 * @param data
 * @return Status
 */
Status InsertBefore_DL(LinkList_DL_v2 *dl, size_t idx, ElemType data)
{
    if(!dl || idx > dl->len){
        return ERROR;
    }

    Node_DL *temp = NULL;
    Node_DL *pInsert = (Node_DL*)malloc(sizeof(Node_DL) * 1);
    Node_DL *prev_node;
    if(GetNode_DL(dl, idx, &temp) != OK){ // 获取节点指针
        return ERROR;
    }
    prev_node = temp->prev; 
    // printf("get node:%d\r\n", temp->data);

    pInsert->data = data;
    pInsert->prev = prev_node;
    // 为什么一定要引入一个变量才不会编译报错???????????????????????????????????????????????????
    prev_node->next = pInsert; // temp->rpev->next = pInsert
    pInsert->next = temp;
    temp->prev = pInsert;

    ++dl->len;

    return OK;
}

/**
 * @brief remove node
 *
 * @param dl
 * @param idx index start from 0
 * @param data
 * @return Status
 */
Status RemoveElem_DL(LinkList_DL_v2 *dl, size_t idx, ElemType *data)
{

}

/**
 * @brief Modify element
 *
 * @param dl
 * @param idx from 0 to len-1
 * @param data
 * @return Status
 */
Status ModifyElem_DL(LinkList_DL_v2 *dl, size_t idx, ElemType *data)
{
    if(!dl || idx > dl->len || !data){
        return ERROR;
    }

    size_t jx = 0;
    Node_DL *temp = dl->pHead->next;
    while(temp != NULL && jx < idx){
        temp = temp->next;
        ++jx;
    }

    if(!temp || jx > idx){
        return ERROR;
    }

    temp->data = *data;

    return OK;
}

/**
 * @brief 获取数据
 * 
 * @param dl 
 * @param idx from 0 to len-1
 * @param[out] data 
 * @return Status 
 */
Status GetElem_DL(LinkList_DL_v2 *dl, size_t idx, ElemType *data)
{
    if(!dl || idx > dl->len || !data){
        return ERROR;
    }

    size_t jx = 0;
    Node_DL *temp = dl->pHead->next;
    while(temp != NULL && jx < idx){
        temp = temp->next;
        ++jx;
    }

    if(!temp || jx > idx){
        return ERROR;
    }

    *data = temp->data;

    return OK;
}

/**
 * @brief get Node pointer
 * 
 * @param dl 
 * @param idx from 0 to len-1
 * @param[out] node 传递一个指针出去, 这里加上 const 外接仍然可以修改这个地址的值; const 的作用是不让形参修改传入的实参
 * @return Status 
 */
Status GetNode_DL(const LinkList_DL_v2 *dl, size_t idx, const Node_DL **node)
{
    if(!dl || idx > dl->len || !node){
        return ERROR;
    }

    size_t jx = 0;
    Node_DL *temp = dl->pHead->next;
    // 后向遍历
    while(temp != NULL && jx < idx)
    {
        temp = temp->next;
        ++jx;
    }

    if(temp == NULL || jx > idx){
        return ERROR;
    }

    *node = temp;
    
    return OK;
}

/**
 * @brief get previous node
 *        O(1)
 * 
 * @param dl 
 * @param node 
 * @param[out] prior Node_DL ** type
 * @return Status 
 */
Status GetPriorElem_DL(LinkList_DL_v2 *dl, const Node_DL *node, Node_DL **prior)
{
    if(!dl || !node || !prior){
        return ERROR;
    }

    *prior = node->prev;

    return OK;
}

/**
 * @brief get next node
 * 
 * @param dl 
 * @param node 
 * @param[out] next 
 * @return Status 
 */
Status GetNextElem_DL(LinkList_DL_v2 *dl, Node_DL *node, Node_DL **next)
{
    if(!dl || !node || !next){
        return ERROR;
    }

    *next = node->next;

    return OK;
}

/**
 * @brief 前向遍历
 *        (1) 适用于尾指针也保存的情况
 *        (2) 相当于没有头结点的单向链表
 *        (3) O(1)
 *
 * @param dl
 * @return Status
 */
Status TraversePrior_DL(const LinkList_DL_v2 *dl)
{
    if(!dl){
        return ERROR;
    }
    Node_DL *temp = dl->pTail; // 没有头结点

    printf("Prior Traverse:\r\n");
    while(temp != dl->pHead){ // 终止条件不包括头结点
        printf("%d ->", temp->data);
        temp = temp->prev;
    }
    printf("\r\n\r\n");

    return OK;
}

/**
 * @brief 后向遍历
 *        O(1)
 *
 * @param dl
 * @return Status
 */
Status TraverseNext_DL(const LinkList_DL_v2 *dl)
{
    if(!dl){
        return ERROR;
    }
    Node_DL *temp = dl->pHead->next;

    printf("next Traverse:\r\n");
    while(temp != NULL){
        printf("%d ->", temp->data);
        temp = temp->next;
    }
    printf("\r\n\r\n");

    return OK;
}

Status Clear_DL(LinkList_DL_v2 *dl)
{

}

Status Deinit_DL(LinkList_DL_v2 dl)
{

}

void DoubleListTest_v2()
{
    LinkList_DL_v2 dl;
    ElemType data;
    size_t idx = 1;
    Node_DL *pTest, *prevElem, *nextElem;

    InitLinkList_DL(&dl);
    TraverseNext_DL(&dl);
    TraversePrior_DL(&dl);

    data = 101;
    InsertHead_DL(&dl, data);
    printf("insert head:%d\r\n", data);
    TraverseNext_DL(&dl);
    TraversePrior_DL(&dl);

    data = 185;
    InsertHead_DL(&dl, data);
    printf("insert head:%d\r\n", data);
    TraverseNext_DL(&dl);
    TraversePrior_DL(&dl);

    data = 987;
    InsertTail_DL(&dl, data);
    printf("insert tail:%d\r\n", data);
    TraverseNext_DL(&dl);
    TraversePrior_DL(&dl);

    data = 654;
    InsertTail_DL(&dl, data);
    printf("insert tail:%d\r\n", data);
    TraverseNext_DL(&dl);
    TraversePrior_DL(&dl);

    idx = 1;
    GetNode_DL(&dl, idx, &pTest);
    printf("Get Elem idx:%d value:%d\r\n", idx, pTest->data);
    TraverseNext_DL(&dl);
    TraversePrior_DL(&dl);
    pTest->data = 1233;
    TraverseNext_DL(&dl);
    TraversePrior_DL(&dl);

    idx = 1;
    data = 222;
    InsertBefore_DL(&dl, idx, data);
    printf("insert before idx:%d value:%d\r\n", idx, data);
    TraverseNext_DL(&dl);
    TraversePrior_DL(&dl);

    idx = 2;
    GetNode_DL(&dl, idx, &data);
    printf("get idx:%d value:%d\r\n", idx, data);
    TraverseNext_DL(&dl);
    TraversePrior_DL(&dl);

    idx = 3;
    data = 9987;
    ModifyElem_DL(&dl, idx, &data);
    printf("modify idx:%d data:%d\r\n", idx, data);
    TraverseNext_DL(&dl);
    TraversePrior_DL(&dl);

    idx = 2;
    GetNode_DL(&dl, idx, &pTest);
    printf("get elem idx:%d value:%d\r\n", idx, pTest->data);
    GetNextElem_DL(&dl, pTest, &nextElem);
    printf("get next elem idx:%d value:%d\r\n", idx, nextElem->data);
    GetPriorElem_DL(&dl, pTest, &prevElem);
    printf("get prior elem idx:%d value:%d\r\n", idx, prevElem->data);
    TraverseNext_DL(&dl);
    TraversePrior_DL(&dl);
}

#endif
