/**
 * @file DoubleCircleLinkList.c
 * @author your name (you@domain.com)
 * @brief double direction linklist
 * @version 0.1
 * @date 2022-11-03
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "DoubleCircleLinkList.h"


#if defined(DOUBLE_CIRCLE_LINKLIST) && (DOUBLE_CIRCLE_LINKLIST == 1)

#if HAVE_TAIL_POINTER

/**
 * @brief 包含头结点
 *        空链表, 仅有头结点
 *
 * @param dcl
 * @return Status
 */
Status InitLinkList_DCL(LinkList_DCL_v2 *dcl)
{
    if (!dcl) {
        return ERROR;
    }
    // head node
    Node_DCL *pHead = (Node_DCL*)malloc(sizeof(Node_DCL) * 1);
    if(!pHead){
        return ERROR;
    }
    pHead->data = INVALID_VAL;
    pHead->next = pHead;
    pHead->prev = pHead;

    dcl->pHead = pHead;
    dcl->pTail = pHead;
    dcl->len = 0;

    return OK;
}

/**
 * @brief 后向遍历
 *
 * @param dcl
 * @return Status
 */
Status TraverseNext_DCL(const LinkList_DCL_v2 *dcl, const char *p_info)
{
    if (!dcl) {
        return ERROR;
    }

    Node_DCL *pCurr = dcl->pHead->next;
    int jx = 0;

    printf("next traverse(%s):\r\n", p_info);
    while (pCurr != dcl->pHead) {
        printf("[%d]:%d -> ", jx, pCurr->data);
        pCurr = pCurr->next;
        ++jx;
    }
    printf("\r\n\r\n");

    return OK;
}

/**
 * @brief 前向遍历
 *
 * @param dcl
 * @return Status
 */
Status TraversePrev_DCL(const LinkList_DCL_v2 *dcl, const char *p_info)
{
    if(!dcl){
        return ERROR;
    }

    // 尾部没有多余的结点
    Node_DCL *temp = dcl->pTail;
    int jx = 0;

    printf("prev traverse(%s):\r\n", p_info);
    while (temp->prev != dcl->pHead) { // 包含头节点, 终止条件:temp->prev != dcl->pHead
        printf("[%d]:%d -> ", jx, temp->data);
        temp = temp->prev;
        ++jx;
    }
    printf("\r\n\r\n");

    return OK;
}

/**
 * @brief create a new node; pointer to itself
 *
 * @param[out] pNode node pointer
 * @param data node value
 * @return Status
 */
Status MakeNode_DCL(Node_DCL **pNode, ElemType data)
{
    if (!pNode) {
        return ERROR;
    }
    Node_DCL *temp = (Node_DCL*)malloc(sizeof(Node_DCL) * 1);
    if (!temp) {
        return ERROR;
    }
    temp->data = data;
    temp->next = temp;
    temp->prev = temp;

    *pNode = temp;

    return OK;
}

/**
 * @brief free a node
 *
 * @param pNode
 * @return Status
 */
Status FreeNode_DCL(Node_DCL **pNode)
{
    if (!pNode || !(*pNode)) {
        return ERROR;
    }

    free(*pNode);
    *pNode = NULL;

    return OK;
}

/**
 * @brief get idx node
 *
 * @param dcl
 * @param idx index start from 0
 * @param[out] pNode Node_DCL** type
 * @return Status
 */
Status GetNode_DCL(const LinkList_DCL_v2 *dcl, size_t idx, Node_DCL **pNode)
{
    // 短路法则
    if(!dcl || !pNode || idx >= dcl->len){
        return ERROR;
    }

    Node_DCL * pCurr = dcl->pHead->next;
    size_t jx = 0;

    while (jx < idx && pCurr != dcl->pHead) {
        pCurr = pCurr->next;
        ++jx;
    }

    if(jx > idx || pCurr == dcl->pHead){
        return ERROR;
    }

    *pNode = pCurr;

    return OK;
}

/**
 * @brief 已经找到结点直接插入即可
 *        (1) 不可以传入空节点
 *
 * @param dcl
 * @param pNode 要插入的位置
 * @param pInsert 要插入的结点
 * @return Status
 */
Status InsertBefore_DCL(LinkList_DCL_v2 *dcl, Node_DCL *pNode, Node_DCL *pInsert)
{
    if (!dcl || !pNode || !pInsert) {
        return ERROR;
    }

    // empty linklist(only have a head node):pNode == dcl->pHead;
    // 空链表:传入 pNode 的为头指针, 则插入的 pInsert 为第一个节点, 也是尾指针
    if(pNode->next == pNode){
        pInsert->next = pNode;
        pInsert->prev = pNode;
        pNode->next = pInsert;
        pNode->prev = pInsert;

        // update tail ndoe
        dcl->pTail = pInsert;

        dcl->len++;

        return OK;
    }

    // 非空链表, 不允许在头节点前插入
    // if (pNode == dcl->pHead) {
    //     return ERROR;
    // }

    Node_DCL *pPrev = pNode->prev, *pNext = pNode->next;
    pInsert->next = pNode;
    pInsert->prev = pNode->prev;
    // ??????????????????
    // 为什么双重解引用会报错: dereferencing pointer to incomplete type 'struct Node_DCL'
    // pNode->prev->next = pInsert;
    // pNode->next->prev = pInsert;
    pPrev->next = pInsert;
    pNext->prev = pInsert;

    // 只要在头指针前插入, 就要更新尾指针(因为是循环链表)
    // if(pNode == dcl->pHead){
    //     // update tail ndoe
    //     dcl->pTail = pInsert;
    // }
    dcl->len++;

    return OK;
}

/**
 * @brief 结点后插入
 *
 * @param dcl
 * @param pNode 插入位置
 * @param pInsert 要插入的节点
 * @return Status
 */
Status InsertAfter_DCL(LinkList_DCL_v2 *dcl, Node_DCL *pNode, Node_DCL *pInsert)
{
    if(!dcl || !pNode || !pInsert){
        return ERROR;
    }

    // empty linklist
    if(pNode->next == pNode){
        pInsert->next = pNode;
        pInsert->prev = pNode;
        pNode->next = pInsert;
        pNode->prev = pInsert;

        // update tail ndoe
        dcl->pTail = pInsert;

        dcl->len++;

        return OK;
    }

    Node_DCL *next = pNode->next;

    pInsert->next = pNode->next;
    pInsert->prev = pNode;
    // 为什么双重解引用会报错: dereferencing pointer to incomplete type 'struct Node_DCL'
    // pNode->next->prev = pInsert;
    // pNode->prev->next = pInsert;
    next->prev = pInsert;
    pNode->next = pInsert;

    // 最后一个节点后插入, 也要更新尾指针
    if(pNode == dcl->pTail){
        dcl->pTail = pInsert;
    }
    dcl->len++;

    return OK;
}

/**
 * @brief modify node value
 *
 * @param dcl
 * @param idx
 * @param data
 * @return Status
 */
Status ModifyNode_DCL(LinkList_DCL *dcl, size_t idx, ElemType data)
{
    if(!dcl || idx < 0){
        return ERROR;
    }

    Node_DCL *pNodeIdx;
    if(GetNode_DCL(dcl, idx, &pNodeIdx) != OK){
        return ERROR;
    }

    // if(MakeNode_DCL(&pNodeInsert, data) != OK){
    //     return ERROR;
    // }

    pNodeIdx->data = data;

    return OK;
}

/**
 * @brief Delete node
 *
 * @param dcl
 * @param idx
 * @return Status
 */
Status DeleteNode_DCL(LinkList_DCL *dcl, size_t idx)
{
    if(!dcl || idx < 0){
        return ERROR;
    }

    Node_DCL *temp, *prev, *next;
    if(GetNode_DCL(dcl, idx, &temp) != OK){
        return ERROR;
    }

    prev = temp->prev;
    next = temp->next;

    prev->next = temp->next;
    next->prev = temp->prev;

    FreeNode_DCL(&temp);

    return OK;
}

/**
 * @brief clear
 *
 * @param dcl
 * @return Status
 */
Status Clear_DCL(LinkList_DCL *dcl)
{

}

/**
 * @brief deinit
 *
 * @param dcl
 * @return Status
 */
Status Deinit_DCL(LinkList_DCL *dcl)
{

}
void LinkListTest_DCL1()
{
    LinkList_DCL_v2 dcl1, dcl2;
    Node_DCL *temp = NULL;
    ElemType data;
    size_t idx;

    printf("Init dcl1:\r\n");
    InitLinkList_DCL(&dcl1);
    TraverseNext_DCL(&dcl1);
    TraversePrev_DCL(&dcl1);

    data = 100;
    printf("before insert %d\r\n", data);
    if(MakeNode_DCL(&temp, data) != OK){
        printf("ERROR\r\n");
        return;
    }
    InsertBefore_DCL(&dcl1, dcl1.pHead, temp);
    TraverseNext_DCL(&dcl1);
    TraversePrev_DCL(&dcl1);

    data = 5;
    printf("before insert %d\r\n", data);
    if(MakeNode_DCL(&temp, data) != OK){
        printf("ERROR\r\n");
        return;
    }
    InsertBefore_DCL(&dcl1, dcl1.pHead, temp); // 在头结点前插入 5 相当于在尾部插入 5
    TraverseNext_DCL(&dcl1);
    TraversePrev_DCL(&dcl1);


    printf("Init dcl2:\r\n");
    InitLinkList_DCL(&dcl2);
    TraverseNext_DCL(&dcl2);
    TraversePrev_DCL(&dcl2);
    data = -999;
    if(MakeNode_DCL(&temp, data) != OK){
        printf("ERROR\r\n");
        return;
    }
    printf("after insert %d\r\n", data);
    InsertAfter_DCL(&dcl2, dcl2.pHead, temp);
    TraverseNext_DCL(&dcl2);
    TraversePrev_DCL(&dcl2);

    data = -888;
    if(MakeNode_DCL(&temp, data) != OK){
        printf("ERROR\r\n");
        return;
    }
    printf("after insert %d\r\n", data);
    InsertAfter_DCL(&dcl2, dcl2.pHead, temp);
    TraverseNext_DCL(&dcl2);
    TraversePrev_DCL(&dcl2);

    data = 333;
    idx = 1;
    printf("modify idx:%d data:%d\r\n", idx, data);
    if(ModifyNode_DCL(&dcl2, idx, data) != OK){
        printf("modify error\r\n");
        return ;
    }
    TraverseNext_DCL(&dcl2);
    TraversePrev_DCL(&dcl2);

    idx = 0;
    printf("delete node idx:%d\r\n", idx);
    if(DeleteNode_DCL(&dcl2, idx) != OK){
        printf("ERROR\r\n");
    }
    TraverseNext_DCL(&dcl2);
    TraversePrev_DCL(&dcl2);

}

#else
/**
 * @fun 空双向循环链表, 仅有头节点
*/
Status InitLinkList_DCL(Node_DCL **dcl)
{
    if (!dcl) {
        return ERROR;
    }

    Node_DCL *pHead = (Node_DCL*)malloc(sizeof(Node_DCL));
    if (!pHead)
        return ERROR;
    pHead->data = INVALID_VAL;
    pHead->next = pHead;
    pHead->prev = pHead;
    *dcl = pHead;

    return OK;
}

/**
 * @fun 后向遍历
*/
Status TraverseNext_DCL(const Node_DCL *dcl, const char *pInfo)
{
    if (!dcl)
        return ERROR;

    const Node_DCL *pCurr = dcl->next;
    int jx = 0;

    printf("TraverseNext(%s):\n", pInfo);
    while (pCurr != dcl) {
        printf("[%d]:%d -> ", jx, pCurr->data);
        pCurr = pCurr->next;
        ++jx;
    }
    printf("\n\n");

    return OK;
}

/**
 * @fun 前向遍历, 仅保存尾节点的双向链表支持
*/
Status TraversePrev_DCL(const Node_DCL *dcl, const char *pInfo)
{

}

/**
 * @fun 插入第一个节点
*/
Status InsertHead_DCL(Node_DCL *dcl, ElemType data)
{
    if (!dcl)
        return ERROR;
    
    Node_DCL *pFirst = dcl->next;
    Node_DCL *pInsert = (Node_DCL*)malloc(sizeof(Node_DCL));
    if (!pInsert)
        return ERROR;
    pInsert->data = data;
    pInsert->next = pFirst;
    pInsert->prev = dcl;
    pFirst->prev = pInsert;
    // dcl->next->prev = pInsert;
    dcl->next = pInsert;

    return OK;
}

/**
 * @fun 插入尾节点
*/
Status InsertTail_DCL(Node_DCL *dcl, ElemType data)
{
    if (!dcl)
        return ERROR;

    Node_DCL *pInsert;
    Node_DCL *pPrev = dcl, *pCurr = dcl->next;
    Node_DCL *pTail;

    while (pCurr != dcl) {
        pPrev = pCurr;
        pCurr = pCurr->next;
    }
    pTail = pPrev; // 直到 pPrev 指向尾节点
    pInsert = (Node_DCL*)malloc(sizeof(Node_DCL));
    if (!pInsert)
        return ERROR;
    pInsert->data = data;
    pInsert->next = dcl;
    pInsert->prev = pTail;
    pTail->next = pInsert;
    // pPrev->next->prev = pInsert;
    dcl->prev = pInsert;
    
    return OK;
}

/**
 * @fun get index node's value
 * @param[in] dcl
 * @param[in] idx start from 0
 * @param[out] pData save node's value
 * @ret
*/
Status GetElem_DCL(Node_DCL *dcl, size_t idx, ElemType *pData)
{
    if (!dcl || idx <= 0 || !pData)
        return ERROR;
    int jx = 0;
    Node_DCL *pCurr = dcl->next;

    while (pCurr != dcl && jx < idx) {
        pCurr = pCurr->next;
        ++jx;
    }
    if (pCurr == dcl || jx > idx)
        return ERROR;
    *pData = pCurr->data;

    return OK;
}

// set idx node's value
Status SetElem_DCL(Node_DCL *dcl, size_t idx, ElemType *pData)
{
    if (!dcl || idx <= 0 || !pData)
        return ERROR;
    int jx = 0;
    Node_DCL *pCurr = dcl->next;

    while (pCurr != dcl && jx < idx) {
        pCurr = pCurr->next;
        ++jx;
    }
    if (pCurr == dcl || jx > idx)
        return ERROR;
    pCurr->data = *pData;

    return OK;
}

/**
 * @fun Insert before idx node
*/
Status InsertBefore_DCL(Node_DCL *dcl, size_t idx, ElemType *pData)
{
    if (!dcl || idx < 0 || !pData)
        return ERROR;
    
    int jx = 0;
    Node_DCL *pInsert;
    Node_DCL *pPrev = dcl;
    Node_DCL *pCurr = dcl->next;

    while (pCurr != dcl && jx < idx) {
        pPrev = pCurr;
        pCurr = pCurr->next;
        ++jx;
    }
    if (pCurr == dcl || jx > idx)
        return ERROR;

    pInsert = (Node_DCL*)malloc(sizeof(Node_DCL));
    if (!pInsert)
        return ERROR;
    pInsert->data = *pData;
    pInsert->next = pCurr;
    pInsert->prev = pCurr->prev;
    pCurr->prev = pInsert;
    // pCurr->prev->next = pInsert;
    pPrev->next = pInsert;

    return OK;
}

/**
 * @fun Remove idx node
*/
Status RemoveElem_DCL(Node_DCL *dcl, size_t idx, ElemType *pData)
{
    if (!dcl || idx < 0 || !pData)
        return ERROR;
    
    int jx = 0;
    Node_DCL *pCurr = dcl->next;
    Node_DCL *pPrev, *pNext;

    while (pCurr != dcl && jx < idx) {
        pCurr = pCurr->next;
        ++jx;
    }
    if (pCurr == dcl || jx > idx)
        return ERROR;

    *pData = pCurr->data;
    pPrev = pCurr->prev;
    pNext = pCurr->next;
    // pCurr->next->prev = pCurr->prev;
    pNext->prev = pCurr->prev;
    // pCurr->prev->next = pCurr->next;
    pPrev->next = pCurr->next;
    free(pCurr);

    return OK;
}

// get first node
Status GetHead_DCL(Node_DCL *dcl, Node_DCL **pHead)
{
    if (!dcl || !pHead)
        return ERROR;
    if (dcl->next == dcl) { // empty linklist
        *pHead = NULL;
        return ERROR;
    }
    *pHead = dcl->next;

    return OK;
}

// get last node
Status GetTail_DCL(Node_DCL *dcl, Node_DCL **pTail)
{
    if (!dcl || !pTail || dcl->prev == dcl)
        return ERROR;
    *pTail = dcl->prev;

    return OK;
}

// get idx node's pointer
Status GetNode_DCL(Node_DCL *dcl, size_t idx, Node_DCL **pNode)
{
    if (!dcl || idx < 0 || !pNode)
        return ERROR;
    
    Node_DCL *pCurr = dcl->next;
    int jx = 0;

    while (pCurr != dcl && jx < idx) {
        pCurr = pCurr->next;
        ++jx;
    }
    if (pCurr == dcl || jx > idx)
        return ERROR;
    *pNode = pCurr;

    return OK;
}

/**
 * @fun free all node except head node
*/
Status ClearLinkList_DCL(Node_DCL *dcl)
{

}

/**
 * @fun free all node include head node
*/
Status DeinitLinkList_DCL(Node_DCL *dcl)
{

}



void LinkListTest_DCL2(void)
{
    Node_DCL *dcl;
    ElemType data;
    int ix;
    Status ret;
    Node_DCL *pNode;

    ret = InitLinkList_DCL(&dcl);
    CHECK_RET_OP(ret, "init double circle linklist");
    ret = TraverseNext_DCL(dcl, "init dcl");
    CHECK_RET_OP(ret, "traverse dcl");

    data = 2;
    ret = InsertHead_DCL(dcl, data);
    CHECK_RET_OP(ret, "insert head:2");
    ret = TraverseNext_DCL(dcl, "insert head:2");
    CHECK_RET_OP(ret, "insert traverse");

    data = 3;
    ret = InsertHead_DCL(dcl, data);
    CHECK_RET_OP(ret, "insert head:3");
    ret = TraverseNext_DCL(dcl, "insert head:3");
    CHECK_RET_OP(ret, "insert traverse");

    data = 5;
    ret = InsertHead_DCL(dcl, data);
    CHECK_RET_OP(ret, "insert head:5");
    ret = TraverseNext_DCL(dcl, "insert head:5");
    CHECK_RET_OP(ret, "insert traverse");

    data = 99;
    ret = InsertTail_DCL(dcl, data);
    CHECK_RET_OP(ret, "insert tail:99");
    ret = TraverseNext_DCL(dcl, "insert tail:99");
    CHECK_RET_OP(ret, "insert tail traverse");

    data = 199;
    ret = InsertTail_DCL(dcl, data);
    CHECK_RET_OP(ret, "insert tail:199");
    ret = TraverseNext_DCL(dcl, "insert tail:199");
    CHECK_RET_OP(ret, "insert tail traverse");

    ix = 2;
    ret = GetElem_DCL(dcl, ix, &data);
    CHECK_RET_OP(ret, "get elem");
    printf("get elem idx:%d data:%d\n", ix, data);
    ret = TraverseNext_DCL(dcl, "get elem");
    CHECK_RET_OP(ret, "get elem");

    ix = 3;
    data = 500;
    ret = SetElem_DCL(dcl, ix, &data);
    CHECK_RET_OP(ret, "set elem");
    ret = TraverseNext_DCL(dcl, "set elem idx:3 data:500");
    CHECK_RET_OP(ret, "set elem");

    ix = 1;
    data = 23;
    ret = InsertBefore_DCL(dcl, ix, &data);
    CHECK_RET_OP(ret, "insert elem");
    ret = TraverseNext_DCL(dcl, "insert before idx:1 data:23");
    CHECK_RET_OP(ret, "insert elem");

    ix = 0;
    data = 0;
    ret = InsertBefore_DCL(dcl, ix, &data);
    CHECK_RET_OP(ret, "insert elem");
    ret = TraverseNext_DCL(dcl, "insert before idx:0 data:0");
    CHECK_RET_OP(ret, "insert elem");

    ix = 1;
    ret = RemoveElem_DCL(dcl, ix, &data);
    CHECK_RET_OP(ret, "remove elem");
    printf("remove idx:%d data:%d", ix, data);
    ret = TraverseNext_DCL(dcl, "remove idx:1");
    CHECK_RET_OP(ret, "remove elem");

    ret = GetHead_DCL(dcl, &pNode);
    CHECK_RET_OP(ret, "get head");
    printf("get head value:%d\n", pNode->data);
    ret = TraverseNext_DCL(dcl, "get head");
    CHECK_RET_OP(ret, "get head");

    ret = GetTail_DCL(dcl, &pNode);
    CHECK_RET_OP(ret, "get tail");
    printf("get tail value:%d\n", pNode->data);
    ret = TraverseNext_DCL(dcl, "get tail");
    CHECK_RET_OP(ret, "get tail");

    ix = 1;
    ret = GetNode_DCL(dcl, ix, &pNode);
    CHECK_RET_OP(ret, "get node");
    printf("get node idx:%d val:%d\n", ix, pNode->data);
    ret = TraverseNext_DCL(dcl, "get node");
    CHECK_RET_OP(ret, "get node");

    // TODO:
    // clear & deinit
}

#endif // HAVE_TAIL_POINTER

#endif