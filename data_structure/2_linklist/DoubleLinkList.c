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
#include "DoubleLinkList.h"


#if defined(DataStructDoubleLinkListV1) && (DataStructDoubleLinkListV1 == 1)


/**
 * @brief initialize
 *        (1) 头结点的 prev = NULL, next = NULL;
 *        (2) 仅仅从 prev 方向或者 next 方向来看是一个单向链表;
 *        (3) 包含头结点, 头结点不保存数据;
 *
 * @param dl
 * @return Status
 */
Status InitLinkList_DL(LinkList_DL *dl)
{
    if (!dl) {
        return ERROR;
    }

    Node_DL *head = (Node_DL*)malloc(sizeof(Node_DL) * 1);
    if (!head) {
        printf("memory allocate failed\r\n");
        return ERROR;
    }
    head->data = INVALID_VAL;
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
Status InitLinkListWithArray_DL(LinkList_DL *dl, ElemType *pArr, size_t len)
{
    if(InitLinkList_DL(dl) != OK || !pArr || len < 0){
        return ERROR;
    }

    Node_DL *pFirst;
    Node_DL *pTail;
    for(size_t ix = 0; ix < len; ++ix){
        pFirst = (*dl)->next;
        Node_DL *pInsert = (Node_DL*)malloc(sizeof(Node_DL));
        if (!pInsert) {
            // got ERROR;
            return ERROR;
        }
        pInsert->data =  pArr[ix];
        // head insert
        pInsert->next = pFirst;
        pInsert->prev = *dl;
        pFirst->prev = pInsert;
        (*dl)->next = pInsert;
        
        // tail insert
        // pTail = (*dl);
        // pInsert->next = NULL;
        // pInsert->prev = pTail;
        // pTail->next = pInsert;
        // pTail = pInsert;
    }

    return OK;
}

/**
 * @brief head insert
 *        时间复杂度:O(1)
 *
 * @param dl 头节点的值不用更新, 所以传入 Node_DL * 类型
 * @param data
 * @return Status
 */
Status InsertHead_DL(LinkList_DL dl, ElemType data)
{
    if (!dl) {
        return ERROR;
    }

    Node_DL *pInsert = (Node_DL*)malloc(sizeof(Node_DL) * 1);
    Node_DL *pFirst = dl->next;
    if(!pInsert){
        printf("memory allocate failed\r\n");
        return ERROR;
    }
    pInsert->data = data;
    pInsert->prev = dl; // prev point to head ndoe
    pInsert->next = dl->next;
    if (pFirst) // 空链表:pFirst == NULL
        pFirst->prev = pInsert;
    // dl->next->prev = pInsert; // 编译报错,等价
    dl->next = pInsert; // update head node

    return OK;
}

/**
 * @brief tail insert, 插入尾节点
 *
 * @param dl
 * @param data
 * @return Status
 */
Status InsertTail_DL(LinkList_DL dl, ElemType data)
{
    if (!dl) {
        return ERROR;
    }

    Node_DL *pInsert;
    Node_DL *pCurr = dl->next, *pPrev = dl;
    // get tail ndoe
    while(pCurr != NULL){
        pPrev = pCurr;
        pCurr = pCurr->next;
    }

    // create a new node
    pInsert = (Node_DL*)malloc(sizeof(Node_DL) * 1);
    if (!pInsert)
        return ERROR;
    pInsert->data = data;
    pInsert->next = NULL;
    pInsert->prev = pPrev;
    pPrev->next = pInsert;

    return OK;
}

/**
 * @brief remove idx node
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
    Node_DL *pCurr = dl->next, *pPrev = dl;
    Node_DL *pNext;

    while (pCurr != NULL && jx < idx) {
        pPrev = pCurr;
        pCurr = pCurr->next;
        ++jx;
    }

    if(pCurr == NULL || jx > idx){
        return ERROR;
    }

    pPrev->next = pCurr->next;
    pNext = pCurr->next;
    pNext->prev = pPrev;
    // pCurr->next->prev = pPrev;
    // 这里能有什么问题呢? 为什么编译报错???
    // temp->next->prev = prior; // ?????????????????????????????????????????????????????

    // copy data
    *data = pCurr->data;
    free(pCurr);

    return OK;
}

/**
 * @brief Modify index element
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
    Node_DL *pCurr = dl->next;

    while(pCurr != NULL && jx < idx){
        ++jx;
        pCurr = pCurr->next;
    }

    if(pCurr == NULL || jx > idx){
        return ERROR;
    }

    pCurr->data = *data;

    return OK;
}

/**
 * @fun Get index element
 * 
 * @param[in] dl
 * @param[in] idx index start from 0
 * @param[out] pData
 * @ret
*/
Status GetElem_DL(LinkList_DL dl, size_t idx, ElemType *pData)
{
    if (!dl || idx < 0 || !pData)
        return ERROR;
    
    Node_DL *pCurr = dl->next;
    int jx = 0;

    while (pCurr != NULL && jx < idx) {
        pCurr = pCurr->next;
        ++jx;
    }

    if (pCurr == NULL || jx > idx)
        return ERROR;
    
    *pData = pCurr->data;

    return OK;
}

/**
 * @fun Get index node
 * 
 * @param[in] dl
 * @param[in] idx start from 0
 * @param[out] pNode return a pointer point to idx Node
*/
Status GetNode_DL(LinkList_DL dl, size_t idx, Node_DL **pNode)
{
    if (!dl || idx < 0 || !pNode)
        return ERROR;
    
    Node_DL *pCurr = dl->next;
    int jx = 0;

    while (pCurr != NULL && jx < idx) {
        pCurr = pCurr->next;
        ++jx;
    }

    if (pCurr == NULL || jx > idx)
        return ERROR;
    
    *pNode = pCurr; // return a pointer's value

    return OK;
}

/**
 * @fun Get previous node's value, 可以直接通过知道操作实现
*/
Status GetPriorElem_DL(LinkList_DL dl, Node_DL *node, Node_DL *prior)
{

}

/**
 * @fun Get Next Node's value, 可以直接通过知道操作实现
*/
Status GetNextElem_DL(LinkList_DL dl, Node_DL *node, Node_DL *next)
{

}

/**
 * @brief 前向遍历
 *        适用于尾指针也保存的情况, 否则不知道尾指针, 从哪里开始遍历
 *
 * @param dl
 * @return Status
 */
Status TraversePrior_DL(LinkList_DL dl)
{
    return ERROR;
}

/**
 * @brief 后向遍历
 *
 * @param dl
 * @return Status
 */
Status TraverseNext_DL(LinkList_DL dl, const char *pInfo)
{
    if(!dl){
        return ERROR;
    }
    Node_DL *pCurr = dl->next; // from first node to tail node
    int jx = 0;

    printf("Traverse(%s):\r\n", pInfo);
    while (pCurr != NULL) {
        printf("[%d]:%d -> ", jx, pCurr->data);
        pCurr = pCurr->next;
        ++jx;
    }
    printf("\r\n\r\n");

    return OK;
}

/**
 * @fun clear all node except head node
*/
Status Clear_DL(LinkList_DL dl)
{
    if (!dl)
        return ERROR;
    Node_DL *pCurr = dl->next;
    
    while (pCurr != NULL) {
        Node_DL *temp = pCurr;
        Node_DL *pNext = pCurr->next, *pPrev = pCurr->prev;
        if (pPrev)
            pPrev->next = pNext;
        // 这么写为什么会编译报错???????
        // pCurr->next.prev = pPrev;
        if (pNext)
            pNext->prev = pPrev;
        pCurr = pCurr->next;
        free(temp);
        printf("free:0x%08X\n", temp);
    }

    return OK;
}

/**
 * @fun clear all ndoe include head node
*/
Status Deinit_DL(LinkList_DL *dl)
{
    if (!dl)
        return ERROR;
    Node_DL *pCurr = (*dl)->next;
    
    while (pCurr != NULL) {
        Node_DL *temp = pCurr;
        Node_DL *pNext = pCurr->next, *pPrev = pCurr->prev;
        if (pPrev)
            pPrev->next = pNext;
        // 这么写为什么会编译报错???????
        // pCurr->next.prev = pPrev;
        if (pNext)
            pNext->prev = pPrev;
        pCurr = pCurr->next;
        free(temp);
        printf("free:0x%08X\n", temp);
    }

    free(*dl); // free head node
    printf("free head:0x%08X\n", *dl);

    *dl = NULL;

    return OK;
}

void DoubleListTest(void)
{
    LinkList_DL dl; // 头指针
    ElemType data;
    size_t idx;
    Status ret;
    Node_DL *pNode, *pPrev, *pNext;

    ret = InitLinkList_DL(&dl);
    CHECK_RET_OP(ret, "init double linklist");
    ret = TraverseNext_DL(dl, "init double linklist");
    CHECK_RET_OP(ret, "init double linklist");

    data = 100;
    ret = InsertHead_DL(dl, data);
    CHECK_RET_OP(ret, "insert head:100");
    ret = TraverseNext_DL(dl, "insert head:100");
    CHECK_RET_OP(ret, "insert head:100");

    data = 58;
    ret = InsertHead_DL(dl, data);
    CHECK_RET_OP(ret, "insert head:58");
    ret = TraverseNext_DL(dl, "insert head:58");
    CHECK_RET_OP(ret, "insert head:58");

    data = 99;
    ret = InsertHead_DL(dl, data);
    CHECK_RET_OP(ret, NULL);
    ret = TraverseNext_DL(dl, "insert head:99");
    CHECK_RET_OP(ret, NULL);

    data = 123;
    ret = InsertTail_DL(dl, data);
    CHECK_RET_OP(ret, NULL);
    ret = TraverseNext_DL(dl, "insert tail:123");
    CHECK_RET_OP(ret, NULL);

    data = 456;
    ret = InsertTail_DL(dl, data);
    CHECK_RET_OP(ret, NULL);
    ret = TraverseNext_DL(dl, "insert tail:456");
    CHECK_RET_OP(ret, NULL);

    idx = 0;
    ret = RemoveElem_DL(dl, idx, &data);
    CHECK_RET_OP(ret, NULL);
    printf("remove index:%d val:%d\r\n", idx, data);
    ret = TraverseNext_DL(dl, "remove idx:0");
    CHECK_RET_OP(ret, NULL);

    idx = 2;
    ret = RemoveElem_DL(dl, idx, &data);
    CHECK_RET_OP(ret, NULL);
    printf("remove index:%d val:%d\r\n", idx, data);
    ret = TraverseNext_DL(dl, "remove idx:2");
    CHECK_RET_OP(ret, NULL);

    idx = 0;
    data = 12345;
    ret = ModifyElem_DL(dl, idx, &data);
    CHECK_RET_OP(ret, NULL);
    ret = TraverseNext_DL(dl, "modify idx:0 val:12345");
    CHECK_RET_OP(ret, NULL);

    idx = 1;
    ret = GetElem_DL(dl, idx, &data);
    CHECK_RET_OP(ret, NULL);
    printf("get elem idx:%d data:%d\n", idx, data);
    ret = TraverseNext_DL(dl, "get elem");
    CHECK_RET_OP(ret, NULL);

    ret = GetNode_DL(dl, 1, &pNode);
    CHECK_RET_OP(ret, "get node");
    pPrev = pNode->prev;
    pNext = pNode->next;
    // 这么写为什么会报错????
    // printf("get node's val:%d prev:%d next:%d\n", pNode->data, pNode->prev->data, pNode->next->data);
    printf("get node's val:%d prev:%d next:%d\n", pNode->data, pPrev->data, pNext->data);
    ret = TraverseNext_DL(dl, "get node");
    CHECK_RET_OP(ret, "get node");

    ret = Clear_DL(dl);
    CHECK_RET_OP(ret, NULL);
    ret = TraverseNext_DL(dl, "clear");
    CHECK_RET_OP(ret, NULL);

    ret = Deinit_DL(&dl);
    CHECK_RET_OP(ret, "deinit");
    ret = TraverseNext_DL(dl, "Deinit_DL");
    CHECK_RET_OP(ret, "deinit traverse");
}


/*********************************** 2.包含尾指针 ********************************************/
// 不保存尾指针的双向链表的操作与单向链表相比没有什么优势, 且写法差别不大, 还是需要保存尾指针
// 保存尾指针可以反向遍历
// typedef struct
// {
//     LinkList_DL head, tail;
//     size_t size;
// } LinkList_DL_v2;
#if HAVE_TAIL_POINTER
/**
 * @brief initialize
 *        (1) 头结点的 prev = NULL, 尾节点的 next = NULL;
 *        (2) 链表保存头结点和尾节点;
 * 
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
    if(!dl || !arr || len < 0){
        return ERROR;
    }

    for(size_t ix = 0; ix < len; ++ix){
        InsertTail_DL(dl, arr[ix]);
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
    if(!dl || idx>dl->len ||!data){
        return ERROR;
    }

    Node_DL *temp = NULL;
    if(GetNode_DL(dl, idx, &temp) != OK){
        return ERROR;
    }

    // 为什么会报错??????????????????????????????????????
    // temp->prev->next = temp->next;
    // temp->next->prev = temp->prev;
    Node_DL *prev = temp->prev;
    Node_DL *next = temp->next;
    prev->next = temp->next;
    next->prev = temp->prev;

    *data = temp->data;

    --dl->len;

    return OK;
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

/**
 * @brief clear linklist, save head node
 * 
 * @param dl 
 * @return Status 
 */
Status Clear_DL(LinkList_DL_v2 *dl)
{
    if(!dl){
        return ERROR;
    }

    Node_DL *temp = dl->pHead->next;

    while(temp != NULL){
        Node_DL *pFree = temp;
        temp = temp->next;
        free(pFree);
    }

    dl->pTail = dl->pHead; // tail pointer
    dl->pHead->next = NULL; // 头结点的后继节点为 NULL
    dl->len = 0;

    return OK;
}

/**
 * @brief Clear linklist and remove head node
 * 
 * @param dl 
 * @return Status 
 */
Status Deinit_DL(LinkList_DL_v2 *dl)
{
    if(!dl){
        return ERROR;
    }
    
    if(Clear_DL(dl) != OK){
        return ERROR;
    }

    free(dl->pHead);

    dl->pHead = NULL;
    dl->pTail = NULL;
    dl->len = 0;

    return OK;
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

    idx = 1;
    RemoveElem_DL(&dl, idx, &data);
    printf("remove idx:%d val:%d\r\n", idx, data);
    TraverseNext_DL(&dl);
    TraversePrior_DL(&dl);

    Clear_DL(&dl);
    printf("clear double linklist:\r\n");
    TraverseNext_DL(&dl);
    TraversePrior_DL(&dl);

    Deinit_DL(&dl);
    printf("deinit double linklist:\r\n");
    // TraverseNext_DL(&dl);
    // TraversePrior_DL(&dl);
}

void DoubleLinkListTest3()
{
    LinkList_DL_v2 dl;
    ElemType arr[] = {1, 333, 444, 22243, 2134556};
    InitLinkList_DL(&dl);
    InitLinkListWithArray_DL(&dl, arr, sizeof(arr) / sizeof(ElemType));
    TraverseNext_DL(&dl);
    TraversePrior_DL(&dl);
}


#endif

#endif
