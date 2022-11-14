#include "LinkList.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


// declaration
static void PolynomailPrinfInfo(void *poly);

// static pPrintInfo printInfo = PolynomailPrinfInfo;

/**
 * @brief
 *
 * @param poly
 */
static void PolynomailPrinfInfo(void *poly)
{
    ElemType *temp = (ElemType*)poly;
    printf("%2.1fx^%d ->", temp->coef, temp->expn);

    return;
}

/**
 * @brief initialize a linklist
 *        (1) 包含头结点;
 *
 * @param l Node ** 头指针
 * @return Status
 */
Status InitLinkList(LinkList *l)
{
    if(!l){
        return ERROR;
    }

    Node *pHead = (Node*)malloc(sizeof(Node) * 1); // head node
    // temp->data.coef = INT_MAX;
    // temp->data.expn = INT_MAX;
    pHead->next = NULL;

    *l = pHead;

    return OK;
}

/**
 * @brief initialize linklist with array
 *
 * @param l
 * @param arr
 * @param len
 * @return Status
 */
Status InitLinkListWithArray(LinkList *l, ElemType *arr, size_t len)
{
    if(!l || !arr || len < 0){
        return ERROR;
    }

    for(size_t ix = 0; ix < len; ++ix){
        // InsertBefore(*l, 0, arr[ix]);
        InsertTail(*l, arr[ix]);
    }

    return OK;
}

/**
 * @brief only reserve head node
 *
 * @param l
 * @return Status
 */
Status ClearLinkList(LinkList l)
{
    if(!l){
        return ERROR;
    }

    Node *temp = l->next;

    while(temp){
        Node *pFree = temp;
        temp = temp->next;
        FreeNode(&pFree);
    }

    l->next = NULL;

    return OK;
}

/**
 * @brief Destroy LinkList, Clear linklist and Delete head node
 *
 * @param l
 * @return Status
 */
Status DestroyLinkList(LinkList *l)
{
    if(!l){
        return ERROR;
    }

    ClearLinkList(*l);

    FreeNode(l); // free head node

    return OK;
}

/**
 * @brief Create a new node and allocate memory
 *
 * @param[out] node Node ** type,
 * @param data
 * @return Status
 */
Status MakeNode(Node **pNode, ElemType data)
{
    if(!pNode){
        return ERROR;
    }

    Node *temp = (Node*)malloc(sizeof(Node) * 1);
    temp->next = NULL;
    temp->data = data;

    *pNode = temp;

    return OK;
}

/**
 * @brief Free Node memory
 *
 * @param pNode
 * @return Status
 */
Status FreeNode(Node **pNode)
{
    if(!pNode){
        return ERROR;
    }

    free(*pNode);
    *pNode = NULL; // *pNode -> Node * type

    return OK;
}

/**
 * @brief traverse linklist
 *
 * @param l
 * @param printFun
 * @return Status
 */
Status Traverse(const LinkList l, pPrintInfo printFun)
{
    if(!l){
        return ERROR;
    }

    Node *temp = l->next;

    printf("Traverse:\r\n");
    while(temp != NULL){
        (*printFun)(temp);
        temp = temp->next;
    }
    printf("\r\n\r\n");

    return OK;
}

/**
 * @brief Get the Node object
 *
 * @param l
 * @param idx from 0 to len-1
 * @param[out] pNode
 * @return Status
 */
Status GetNode(const LinkList l, size_t idx, Node **pNode)
{
    if(!l || idx < 0 || !pNode){
        return ERROR;
    }

    size_t jx = 0;
    Node *temp = l->next;

    while(temp && jx < idx){
        temp = temp->next;
        ++jx;
    }

    if(!temp || jx > idx){ // 没有遍历搜索到
        return ERROR;
    }

    *pNode = temp; // output parameter

    return OK;
}

/**
 * @brief Get the Tail Node object
 * 
 * @param l 
 * @param pNode 
 * @return Status 
 */
Status GetTailNode(const LinkList l, Node **pNode)
{
    if(!l || !pNode){
        return ERROR;
    }

    Node *temp = l->next, *prev = temp;

    if(!temp){
        *pNode = NULL;
        return OK;
    }

    // traverse
    while (temp)
    {
        prev = temp;
        temp = temp->next;
    }

    // get tail node
    *pNode = prev;
    
    return OK;
}

/**
 * @brief Insert a node before idx
 *        InsertBefore(l, 0, node); // 插入一个第一个节点
 * @param l
 * @param idx
 * @param data
 * @return Status
 */
Status InsertBefore(LinkList l, size_t idx, ElemType data)
{
    if(!l || idx < 0){
        return ERROR;
    }

    size_t jx = 0;
    Node *pInsertNode, *temp = l->next, *prev = temp;

    if(temp == NULL && idx == 0){ // 空链表, 插入第一个节点
        if(MakeNode(&pInsertNode, data) != OK){
            return ERROR;
        }
        l->next = pInsertNode;
        return OK;
    }
    else
        prev = l; // 前一个节点是头结点

    while(temp && jx < idx){
        prev = temp;
        temp = temp->next;
        ++jx;
    }

    if(!temp || jx > idx){ // 没有遍历搜索到/空链表
        return ERROR;
    }

    if(MakeNode(&pInsertNode, data) != OK){
        return ERROR;
    }

    pInsertNode->next = temp; // temp node 前面插入
    prev->next = pInsertNode;

    return OK;
}

/**
 * @brief Insert node after idx
 *
 * @param l
 * @param idx
 * @param data
 * @return Status
 */
Status InsertAfter(LinkList l, size_t idx, ElemType data)
{
    if(!l || idx < 0){
        return ERROR;
    }

    Node *pInsertPos, *pInsertNode;

    if(GetNode(l, idx, &pInsertPos) != OK){
        return ERROR;
    }


    if(MakeNode(&pInsertNode, data) != OK){
        return ERROR;
    }

    pInsertNode->next = pInsertPos->next;
    pInsertPos->next = pInsertNode;

    return OK;
}

/**
 * @brief 在 node 后插入一个节点
 *
 * @param l
 * @param node
 * @param data
 * @return Status
 */
Status InsertAfterNode(LinkList l, Node *node, ElemType data)
{

}

/**
 * @brief 在最后一个节点后插入一个节点
 *
 * @param l
 * @param data 传入节点数据
 * @return Status
 */
Status InsertTail(LinkList l, ElemType data)
{
    if(!l){
        return ERROR;
    }

    Node *prev, *temp = l->next;
    Node *pTail = NULL;

    if(!temp){ // 空链表, 插入第一个节点
        InsertBefore(l, 0, data);
        return OK;
    }

    // find tail node
    while(temp){
        prev = temp;
        temp = temp->next;
    }

    // create node
    if(MakeNode(&pTail, data) != OK){
        return ERROR;
    }

    // insert
    pTail->next = NULL;
    prev->next = pTail;

    return OK;
}

/**
 * @brief 尾部插入一个节点
 * 
 * @param l 
 * @param node 传入一个节点指针
 * @return Status 
 */
Status InsertTailWithNode(LinkList l, Node *node)
{
    if(!l || !node){
        return ERROR;
    }

    Node *pTail = NULL;

    if(GetTailNode(l, &pTail) != OK){
        return ERROR;
    }

    // 将尾结点的 next = NULL
    node->next = NULL;
    pTail->next = node;

    return;
}

/**
 * @brief modify node data
 *
 * @param l
 * @param idx
 * @param data
 * @return Status
 */
Status ModifyNode(LinkList l, size_t idx, ElemType data)
{
    if(!l || idx < 0){
        return ERROR;
    }

    Node *temp;
    if(GetNode(l, idx, &temp) != OK){
        return ERROR;
    }

    temp->data = data;

    return OK;
}

/**
 * @brief Delete a node
 *
 * @param l
 * @param idx
 * @return Status
 */
Status DeleteNode(LinkList l, size_t idx)
{
    if(!l || idx < 0){
        return ERROR;
    }

    size_t jx = 0;
    Node *temp = l->next, *prev = temp;

    while(temp && jx < idx){
        prev = temp;
        temp = temp->next;
        ++jx;
    }

    if(!temp || jx > idx){
        return ERROR;
    }

    prev->next = temp->next;

    if(FreeNode(&temp) != OK){
        return ERROR;
    }

    return OK;
}

/**
 * @brief get linklist length
 * 
 * @param l 
 * @param len 
 * @return Status 
 */
Status LinkListLength(LinkList l, size_t *len)
{
    if(!l || !len){
        return ERROR;
    }

    Node *temp = l->next;
    size_t tempLen = 0;

    while(temp){
        ++tempLen;
        temp = temp->next;
    }

    *len = tempLen;

    return OK;
}

/**
 * @brief append a linklist at the end of l
 * 
 * @param l 
 * @param listToAppend 不包含头结点; 最后以 NULL 结尾
 * @return Status 
 */
Status LinkListAppend(LinkList l, LinkList listToAppend)
{
    if(!l || !listToAppend){
        return ERROR;
    }

    Node *temp = l->next, *prev = temp;
    if(!temp){ // empty lilnklist
        l->next = listToAppend;
        return OK;
    }
    
    while(temp){
        prev = temp;
        temp = temp->next;
    }

    prev->next = listToAppend;

    return OK;
}

/**
 * @brief 两个链表节点的位置交换
 *        (1) 不相邻的两个节点都可以交换
 *
 * @param a
 * @param b
 * @return Status
 */
static Status SwapNode(Node *a, Node *b)
{

}

/**
 * @brief 冒泡排序
 *
 * @param l
 * @return Status
 */
Status SortLinkList(LinkList l)
{

}

void LinkListTest()
{
    LinkList l;
    Node *pTempNode;
    ElemType data;
    size_t pos;

    data.coef = 1;
    data.expn = 2;
    MakeNode(&pTempNode, data);
    printf("pTempNode data:%f %d next:%d\r\n", pTempNode->data.coef, pTempNode->data.expn, pTempNode->next);
    FreeNode(&pTempNode);
    if(pTempNode)
        printf("pTempNode data:%d %d next:%d\r\n", pTempNode->data.coef, pTempNode->data.expn, pTempNode->next);
    else
        printf("null ptr\r\n");

    // InitLinkList(&l);
    // Traverse(l, PolynomailPrinfInfo);

    // ClearLinkList(l);
    // Traverse(l, PolynomailPrinfInfo);

    // DestroyLinkList(&l);
    // Traverse(l, PolynomailPrinfInfo);

    InitLinkList(&l);
    printf("init:\r\n");
    Traverse(l, PolynomailPrinfInfo);

    pos = 0;
    InsertBefore(l, 0, data);
    printf("insert before idx:%d data:%2.2f %d\r\n", pos, data.coef, data.expn);
    Traverse(l, PolynomailPrinfInfo);

    pos = 0;
    data.coef = 3;
    InsertBefore(l, pos, data);
    printf("insert before idx:%d data:%2.2f %d\r\n", pos, data.coef, data.expn);
    Traverse(l, PolynomailPrinfInfo);

    pos = 1;
    data.coef = 999;
    InsertBefore(l, pos, data);
    printf("insert before idx:%d data:%2.2f %d\r\n", pos, data.coef, data.expn);
    Traverse(l, PolynomailPrinfInfo);

    pos = 2;
    InsertAfter(l, pos, data);
    printf("insert after idx:%d data:%2.2f %d\r\n", pos, data.coef, data.expn);
    Traverse(l, PolynomailPrinfInfo);

    pos = 1;
    data.expn = 222;
    ModifyNode(l, pos, data);
    printf("modify idx:%d data:%2.2f %d\r\n", pos, data.coef, data.expn);
    Traverse(l, PolynomailPrinfInfo);

    DeleteNode(l, pos);
    printf("delete node idx:%d\r\n", pos);
    Traverse(l, PolynomailPrinfInfo);

    InsertTail(l, data);
    data.coef = 345;
    data.expn = 33;
    printf("insert tail idx:%d data:%2.1f %d\r\n", pos, data.coef, data.expn);
    Traverse(l, PolynomailPrinfInfo);

    LinkListLength(l, &pos);
    printf("list len:%d\r\n", pos);

    printf("clear linklist:\r\n");
    ClearLinkList(l);
    Traverse(l, PolynomailPrinfInfo);

    printf("Destroy linklist:\r\n");
    DestroyLinkList(&l);
    Traverse(l, PolynomailPrinfInfo);

    if(LinkListLength(l, &pos) != OK){
        printf("get len error\r\n");
    }
    else
        printf("list len:%d\r\n", pos);

    return;
}

void LinkListTest2()
{
    LinkList l, l2;
    ElemType arr[] = {{1, 2}, {1, 3}, {1, 4}};
    size_t idx = 0;
    ElemType data = {99, 88};
    Node *pTemp = NULL;
    Node *pInsert;

    printf("init l1:\r\n");
    if(InitLinkList(&l) != OK){
        printf("init failed\r\n");
    }
    Traverse(l, PolynomailPrinfInfo);

    InitLinkListWithArray(&l, arr, 3);
    printf("init l1 with array:\r\n");
    Traverse(l, PolynomailPrinfInfo);

    printf("init l2:\r\n");
    if(InitLinkList(&l2) != OK){
        printf("init failed\r\n");
    }
    Traverse(l2, PolynomailPrinfInfo);

    InitLinkListWithArray(&l2, arr, 3);
    printf("init l2 with array:\r\n");
    Traverse(l2, PolynomailPrinfInfo);

    if(InsertAfter(l, idx, data) != OK){
        printf("insert failed\r\n");
        return;
    }
    printf("insert after idx:%d data:%2.1f %d\r\n", idx, data.coef, data.expn);
    Traverse(l, PolynomailPrinfInfo);

    printf("append:\r\n");
    LinkListAppend(l, l2->next);
    Traverse(l, PolynomailPrinfInfo);

    GetTailNode(l, &pTemp);
    printf("Get tail node:%2.1f %d\r\n", pTemp->data.coef, pTemp->data.expn);
    Traverse(l, PolynomailPrinfInfo);

    data.coef = 1122;
    if(MakeNode(&pInsert, data) != OK){
        return ERROR;
    }
    InsertTailWithNode(l, pInsert);
    Traverse(l, PolynomailPrinfInfo);

    return;
}
