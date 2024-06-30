#include "app_linklist.h"

#include <limits.h>
#include <stddef.h>


#if defined(DataStructApplicationLinkList) && (DataStructApplicationLinkList == 1)
/****************************************************************************
 * MACRO
 ****************************************************************************/

/****************************************************************************
 * PRIVATE FUNCTION
 ****************************************************************************/
/**
 * @brief 节点数据为 ElemType 类型, 
 *        ElemType data 中保存字符串, len save length include '\0';
 *
 * @param[in] pNode
*/
static void visit(ElemType *elem)
{
    printf("[%s](%d)", elem->p_data, elem->len);
}

/**
 * @brief 从小到大排序, a,b 满足从小到大, 返回 true; 否则返回 false
 * 
 * @param[in] a
 * @param[in] b
 * @return -1 when a > b, 0 when a == b, 1 when a< b;
*/
static int InOrderCompare(ElemType *a, ElemType *b)
{
    if (!a || !b || !a->p_data || !b->p_data) {
        LOG_E("null ptr");
        return -1;
    }

    if (a->len <= 0 || b->len <= 0) {
        LOG_E("len:0");
        return -1;
    }

    return COMPARE_ELEM_DATA(a, b);
}

/**
 * @brief 从大到小排序, a,b 满足从大到小, 返回 true; 否则返回 false
 * 
 * @param[in] a
 * @param[in] b
 * @return
*/
static int ReverseOrderCompare(ElemType *a, ElemType *b)
{
    int ret;

    if (!a || !b || !a->p_data || !b->p_data) {
        LOG_E("null ptr");
        return -1;
    }

    if (a->len <= 0 || b->len <= 0) {
        LOG_E("len:0");
        return -1;
    }

    ret = COMPARE_ELEM_DATA(a, b);

    if (ret < 0) {
        return 1;
    } else if (ret > 0) {
        return -1;
    }
    // else {
    return 0;
    // }
}

/**
 * @brief 找相等的元素节点, 相同即满足条件, 返回 true; 不相等, 不满足条件， 返回 false
 * 
 * @param[in] a
 * @param[in] b
 * @return return true(1) when equal, false(0) when not equal
*/
static int EqualCompare(ElemType *a, ElemType *b)
{
    if (!a || !b || !a->p_data || !b->p_data) {
        LOG_E("null ptr");
        return -1;
    }

    if (a->len <= 0 || b->len <= 0) {
        LOG_E("len:0");
        return -1;
    }

    return COMPARE_ELEM_DATA(a, b) == 0;
}
/****************************************************************************
 * PUBLIC FUNCTIONS
 ****************************************************************************/
void struct_member_size_test(void)
{
    Node *pTemp;

    printf("struct size:%d = %d(node) + %d(data) offset:%d\n", 
            sizeof(Node), sizeof(pTemp->next), sizeof(pTemp->data),
            offsetof(Node, data));
}

/**
 * @brief create a string element and allocate memory for the elem
 *        node's data field save string element
 *
 * @param[in] string include '\0'
*/
Status MakeStringElem(ElemType *p_elem, const char *str)
{
    if (!p_elem || !str) {
        LOG_E("null ptr");
        return ERROR;
    }

    p_elem->p_data = malloc(strlen(str) + 1);
    if (!p_elem ->p_data) {
        LOG_E("malloc failed");
        return ERROR;
    }
    LOG_D("malloc elem:%08x", p_elem->p_data);
    strcpy(p_elem->p_data, str);
    p_elem->len = strlen(str) + 1;

    return OK;
}

/**
 * @brief free a node allocated memory
 * 
 * @param[in/out] p
*/
Status FreeStringElem(ElemType *p_elem)
{
    if (!p_elem) {
        LOG_E("null ptr");
        return ERROR;
    }

    if (!p_elem->p_data) {
        return OK;
    }
    LOG_D("free elem:%08x", p_elem->p_data);
    free(p_elem->p_data);
    p_elem->p_data = NULL;
    p_elem->len = 0;

    return OK;
}

/**
 * @brief allocatet a node space and init it
 *        reuse memory allocated by @fun {MakeStringElem}
 * 
 * @param[in/out] p Node **type
 * @param[in] e reuse memory allocated by @fun {MakeStringElem}, NULL is allowed
 * @return success return OK, otherwise return ERROR
*/
Status MakeNode(Node **p, ElemType *e)
{
    if (!p) {
        LOG_E("null ptr");
        return ERROR;
    }

    // if (e)
    //     LOG_D("e->len:%d e->data:%s", e->len, e->p_data);

    Status ret;
    Node *temp = malloc(sizeof(Node));
    if (!temp) {
        LOG_E("allocate failed");
        return ERROR;
    }
    LOG_D("malloc node:%08x", temp);
    memset(temp, 0, sizeof(Node));
    if (e) {
        // reuse var ${e}'s memory allocated by @fun {MakeStringElem}
        memcpy(&temp->data, e, sizeof(ElemType));
        // LOG_D("e->len:%d e->data:%s", temp->data.len, temp->data.p_data);
    }
    temp->next = NULL;

    *p = temp;

    return OK;
}

/**
 * @brief free a node allocated memory
 * 
 * @param[in/out] p
*/
void FreeNode(Node *p)
{
    if (!p) {
        LOG_E("null ptr");
        return;
    }
    FreeStringElem(&p->data);
    free(p);
    LOG_D("free node:%08x", p);

    return;
}


// oblete:
/**
 * @fun 交换链表中的两个节点
 * @brief 1.对于单向链表, 交换链表中的两个节点, 需要传入节点的前一个节点, 否则又要遍历一遍链表, 找前一个节点
 *        2. 双向链表:
 *        不可以传入头节点, 只能传入链表的中间节点 
 *
 * @param[in] pPrev1 节点1 的前一个节点
 * @param[in] p1 节点1
 * @param[in] pPrev2 节点2
 * @param[in] p2 节点2的前一个节点
 * 
*/
// static Status SwapNode(Node *pPrev1, Node *p1, Node *pPrev2, Node *p2)
// {
//     if (!pPrev1 || !p1 || !pPrev2 || !p2)
//         return ERROR;

//     // 如果 p1, p2 为相邻节点则需要特殊处理
//     if (pPrev2 == p1) { // p1, p2 相邻, p1 在前
//         Node *temp = p2->next;
//         p2->next = p1;
//         pPrev1->next = p2;
//         p1->next = temp;
//         return OK;
//     } else if (pPrev1 == p2) { // p1, p2 相邻, p2 在前
//         Node *temp = p1->next;
//         p1->next = p2;
//         pPrev2->next = p1;
//         p2->next = temp;
//         return OK;
//     }
//     // else { // p1, p2 不相邻
//     Node *temp = p2->next;

//     p2->next = p1->next; // 保证所有被赋值的节点都没有被修改过
//     p1->next = temp;
//     pPrev1->next = p2;
//     pPrev2->next = p1;
//     // }

//     return OK;
// }

/**
 * @brief initialize a empty linklist, only a head node
 *
 * @param ll struct Node **L, 头指针, 
 *          初始化一个头指针指向头节点(头节点不保存数据)
 *          传入一个指向头节点的指针, 初始化后, 将该指针改为指向头节点(值为头节点的地址)
 * @return Status
 */
Status InitLinkList(LinkList *ll)
{
    if (!ll) {
        LOG_E("null ptr");
        return ERROR;
    }

    Status ret;
    Node *p_head_node;

    ret = MakeNode(&p_head_node, NULL);
    CHECK_RET(ret);

    p_head_node->next = NULL;
    LOG_D("head node data:%s len:%d next:%p", p_head_node->data.p_data,
            p_head_node->data.len, p_head_node->next);

    *ll = p_head_node;

    return OK;
}

/**
* @brief: clear linklist,
*       does not delte head node, becomde a empty linklist
*
* @param[in]  L Node * type, pointer to head node
* @retval Status
*/
Status ClearLinkList(LinkList L)
{
    Node *pCurr = L->next; // first node, Node *pFirstNode = L->next;

    while (pCurr != NULL) {
        Node *pFree = NULL;
        pFree = pCurr;
        pCurr = pCurr->next;
        FreeNode(pFree);
        // pFree = NULL; // 释放内存并且修改为 NULL, 要不然下次遍历会出问题
    }

    L->next = NULL; // include a head node

    return OK;
}

/**
* @brief: free heap memory(include head node)
*
* @param[in]  L pointer to head node
* @retval Status
*/
Status DestroyLinkList(LinkList *L)
{
    Node *pCurr = *L; // Node* type

    while (pCurr != NULL) {
        Node *pFree = NULL;
        pFree = pCurr;
        pCurr = pCurr->next;
        FreeNode(pFree);
    }

    *L = NULL;

    return OK;
}

/**
 * @brief: init liklist with array, include head node
 * 
 * @param[in] pHead head pointer, 头指针指向头结点, 头结点不保存数据
 * @param[in] pElemArr ElemType *
 * @param[in] len
 **/
Status InitLinkListWithArray(LinkList *L, ElemType **pElemArr, size_t len)
{
    if (!L || !pElemArr || !len) {
        fprintf(stderr, "null ptr\n");
        return ERROR;
    }

    Status ret;
    Node *pHead;
    ElemType elem;

    // initialize head node
    ret = MakeNode(&pHead, NULL);
    CHECK_RET(ret);

    pHead->next = NULL;
    *L = pHead;  // 头指针指向头结点, 保存地址; LinkList = struct Node *
    // LinkList *L;  // struct Node **L; // 解引用一层变成 Node * 类型

    // other node, tail insert
    Node *pTail = pHead; // 尾指针

    for (int ix = 0; ix < len; ++ix) {
        Node *pNew;

        ret = MakeNode(&pNew, pElemArr[ix]);
        CHECK_RET(ret);
        pNew->next = NULL;
        // LOG_D("len:%d data:%s", pNew->data.len, pNew->data.p_data);

        /* 头插法 */
        // pNew->next = pHead;
        // pHead = pNew;
        /*  尾插法 */
        pTail->next = pNew;

        pTail = pNew;
    }

    return OK;

EXIT:
    // 释放已经分配内存
    // deinit 链表或者保留已经初始化的部分
    // 返回 ERROR
    // LinkListDestroy();
    return ERROR;
}

/**
* @brief: traverse linklist
*
* @param[in] head pointer to head node, Node * type
* @param[in] p_op_info traverse operation inforamtion
* @param[in] p_print_node_fun print node_information
* @ret Status
*/
Status Traverse(const LinkList L, void (*visit)(ElemType *data))
{
    if (!L || !visit) {
        fprintf(stderr, "null ptr\n");
        return ERROR;
    }
    size_t idx = 0;

    printf("traverse:\n");
    Node *pCurr = L->next; // first node
    while (pCurr) {
        printf("{[%d]:", idx++);
        visit(&pCurr->data);
        printf("} -> ");
        pCurr = pCurr->next;
    }
    printf("\n\n");

    return OK;
}

#if 0
/**
* @brief: get linklist element
*
* @param[in]  L pointer to head node
* @param[in]  i index start from 0
* @param[out] e save value of index ix
*/
Status GetElem(const LinkList L, position_t i, ElemType *e)
{
    if (!L) {
        fprintf(stderr, "null ptr\n");
        return ERROR;
    }
    Node *pCurr = L->next; // head node
    position_t j = 0;

    while (pCurr && j < i) {
        pCurr = pCurr->next;
        ++j;
    }

    if (!pCurr || j > i) {
        fprintf(stderr, "can't find node idx:%d\n", i);
        return ERROR;
    }

    memcpy(e, &pCurr->data, sizeof(ElemType));

    return OK;
}

/**
 * @brief 若链表中存在与 nodeVal 进行 compare 操作结果 == 0 的元素, 则 pos 返回该结果, 并返回 false
 *      否则, 返回 false
 * 
 *      仅仅判断 ElemType 是否指向相同的内存, 而不判断字符串的内容是否相同
 * 
 * @param[in] L
 * @param[in] nodeval
 * @param[out] pos 节点下标索引 start from 0
 * @return OK/ERROR
*/
Status LocateElem(const LinkList L, ElemType *pNodeVal, position_t *pos)
{
    if (!L || !pos) {
        fprintf(stderr, "null ptr\n");
        return false;
    }
    
    position_t idx = 0;
    Node *pCurr = L->next;

    // 仅仅判断 ElemType 是否指向相同的内存, 而不判断字符串的内容是否相同
    while (pCurr && (COMPARE_ELEM_PTR(pNodeVal, &pCurr->data) == 0)) {
        pCurr = pCurr->next;
        ++idx;
    }

    if (!pCurr) { // can't find this node
        *pos = -1;
        LOG_E("can't find node data:");
        visit(pNodeVal);
        return ERROR;
    }
    *pos = idx;

    return OK;
}

/**
 * @fun 按照有序链表的约定, 将一个节点的值插入到指定的位置, sort with param@{pCompareFun}
 * 
 * @param[in] L 有序链表
 * @param[in] nodeVal 待插入的值, 需要创建新结点
 * @param[in] pCompareFun
 * @ret
*/
#if 0
Status OrderInsert(LinkList *L, ElemType nodeVal, compare_t p_compare)
{
    if (!L || !p_compare) {
        LOG_E("null ptr");
        return ERROR;
    }
    
    Node *pCurr = (*L)->next, *pPrev = (*L);
    Status ret;
    size_t idx = 0;

    while ((pCurr) && (p_compare(&nodeVal, &pCurr->data) == 0)) { // 例如: 不满足插入条件,不需要插入, nodeVal > pCurr->data, 下一个节点
        pPrev = pCurr;
        pCurr = pCurr->next;
        ++idx;
    }

    if (!pCurr) { // 直到尾部都没有找到符合插入条件的节点,插入到末尾
        ret = InsertAtTail(*L, &nodeVal);
        if (ret != OK) {
            return ERROR;
        }
        return OK;
    }
    // else { // 找到了插入符合条件的节点,插入到当前节点前
        ret= InsertBeforePosIdx(L, idx, &nodeVal);
        CHECK_RET(ret);
    // }

    return OK;
}

/**
 * @fun 按照有序链表的约定, 将一个节点的值插入到指定的位置, 从大到大排序
 * 
 * @param[in] L 有序链表
 * @param[in] nodeVal 待插入的值, 需要创建新结点
 * @param[in] pCompareFun
 * @ret
*/
Status ReverseOrderInsert(LinkList *L, ElemType nodeVal, compare_t pCompareFun)
{
    if (!L || !pCompareFun)
        return ERROR;
    
}
#endif

/**
 * @fun get linklist elem number
 * 
 * @param[in] ll
 * @param[out] linklist size pointer
 * @ret linklist size on success, -1 on error
*/
Status LinkListLength(const LinkList ll, size_t *pLen)
{
    if (!ll) {
        LOG_E("null ptr");
        return ERROR;
    }
    
    Node *pCurr = ll->next;
    size_t size = 0;
    while (pCurr) {
        pCurr = pCurr->next;
        ++size;
    }
    *pLen = size;

    return OK;
}

/**
* @brief: Insert a number
* @desc: 有头节点的链表对于第一个节点的插入和删除操作和中间节点的操作一致, 
*       不需要区分是否在第一个节点前插入/删除, 如果要插入的为第 0 个元素, 就需要修改头指针, 所以传入 Node** 类型
*
* @param[in]  L pointer to head node
* @param[in]  i index start from 0
* @param[in] elem node value pointer
*/
Status InsertBeforePosIdx(LinkList *L, size_t idx, ElemType *pElem)
{
    if (!L || idx < 0) {
        LOG_E("null ptr");
        return ERROR;
    }
    
    Status ret;
    Node *pCurr = *L; // LinkList * == struct Node **
    Node *pInsert;
    size_t jx = 0;

    while (pCurr != NULL && jx < idx) { // 寻找第 i-1 个节点
        pCurr = pCurr->next;
        jx++;
    }

    if (!pCurr || jx > idx) {
        LOG_E("can't finde node idx:%d", idx);
        return ERROR;
    }

    ret = MakeNode(&pInsert, pElem);
    CHECK_RET(ret);

    pInsert->next =pCurr->next;
    pCurr->next = pInsert;

    return OK;   
}

/**
 * @brief Insert a node before node "elem"
 * @param[in] L LinkList
 * @param[in] pElem node value piniter
 * @param[in] pInsertElem
 * @retval
 */
Status InsertBeforeElem(LinkList L, ElemType *pElem, ElemType *pInsertElem)
{
    if (!L || !pElem || !pInsertElem) {
        LOG_E("null ptr");
        return ERROR;
    }
    // insert insertElem before elem
    Status ret;
    Node *pPrev = L, *pCurr = L->next;
    Node *pInsert = NULL;

    while (pCurr && (COMPARE_ELEM_PTR(&pCurr->data, pElem) != 0)) {
        pPrev = pCurr;
        pCurr = pCurr->next;
    }

    // can't find node elem
    if(!pCurr){
        LOG_E("can't find node data:%s", pElem->p_data);
        return ERROR;
    }

    // inser node
    ret = MakeNode(&pInsert, pInsertElem);
    CHECK_RET(ret);

    pInsert->next = pCurr;
    pPrev->next = pInsert;

    return OK;
}

/**
 * @brief Insert a node before first node
 * @param[in] L head pointer
 * @param[in] data insert node value pointer
 * @retval
 */
Status InsertAtFirst(LinkList L, ElemType *pElem)
{
    if (!L || !pElem) {
        LOG_E("null ptr");
        return ERROR;
    }
    Status ret;
    Node *pInsert;

    ret = MakeNode(&pInsert, pElem);
    
    pInsert->next = L->next; // first node
    L->next = pInsert; // update first node

    return OK;
}

/**
 * @brief Insert a node after last node
 * @param[in] L LinkList
 * @param[in] pVal node val pointer
 * @retval
 */
Status InsertAtTail(LinkList L, ElemType *pElem)
{
    if(!L || !pElem){
        LOG_E("null ptr");
        return ERROR;
    }
    Status ret;
    Node *pTail = L->next;
    Node *pTemp = L->next;
    Node *pInsert;
    
    ret= MakeNode(&pInsert, pElem);
    CHECK_RET(ret);
    pInsert->next = NULL;


    while(pTemp){
        pTail = pTemp;
        pTemp = pTemp->next;
    }

    pTail->next = pInsert;

    return OK;
}

/**
 * @brief delete a node
 * @param[in] L LinkList
 * @param[in] pDeleteVal
 * @retval
 */
Status DeleteElem(LinkList L, ElemType *pDeleteElem)
{
    if (!L || !pDeleteElem) {
        LOG_E("null ptr");
        return ERROR;
    }
    Node *pPrev = L, *pCurr = L->next;

    while(pCurr && (COMPARE_ELEM_PTR(&pCurr->data, pDeleteElem) != 0)) {
        pPrev = pCurr;
        pCurr = pCurr->next;
    }

    if (!pCurr) { // can't find deleteElem
        LOG_E("can't find node data:");
        visit(pDeleteElem);
        return ERROR;
    }
    // delete ndoe
    pPrev->next = pCurr->next;
    FreeNode(pCurr);

    return OK;
}

/**
 * @fun 删除第 idx 个元素
 *      这里为什么一定要使用 Node ** 类型呢???????
 *      不需要修改头指针的值, 好像没必要使用 Node** 类型吖, 在 LinkList_v3 中实现
 * 
 * @param[in] L LinkList
 * @param[in] idx start from 0
 * @param[out] e element, data memory space allocated by linklist, need free???
 * @retval
 */
Status DeleteByIdx(LinkList *L, size_t idx, ElemType *e)
{
    if (!L || idx < 0 || !e) {
        LOG_E("null ptr");
        return ERROR;
    }
    
    Node *pTemp = *L;
    Node *pDelete;
    size_t jx = 0;

    while (pTemp && jx < idx) { // 寻找第 idx-1 个节点
        ++jx;
        pTemp = pTemp->next;
    }
    if (!pTemp || jx > idx) {
        LOG_E("can't finde node idx:%d", idx);
        return ERROR;
    }
    pDelete = pTemp->next;
    pTemp->next = pDelete->next;
    COPY_ELEM(e, &pDelete->data, sizeof(ElemType)); // copy element
    FreeNode(pDelete);

    return OK;
}

/**
 * @fun 删除链表中第一个节点, 但是不释放内存,以 pDelNode 返回
 * 
 * @param[in] L linklist
 * @param[out] pDelNode 返回指向该节点的指针
 * @ret
*/
Status DelFirst(LinkList L, Node **pDelNode)
{
    if (!L || !pDelNode)
        return ERROR;

    Node *pFirst = L->next;
    L->next = pFirst->next;
    *pDelNode = pFirst;

    return OK;
}

/**
 * @fun Append a new node at tail
 * 
 * @param[in] L
 * @param[in] pNew point to new node
 * @ret
*/
Status Append(LinkList L, Node *pNew)
{
    if (!L || !pNew)
        return ERROR;

    Node *pCurr = L->next, *pPrev = L;

    while (pCurr) {
        pPrev = pCurr;
        pCurr = pCurr->next;
    }
    pPrev->next = pNew;

    return OK;
}

/**
 * @fun 删除最后一个节点并返回该链表指针 pDelNode
 * 
 * @param[in] L
 * @param[out] pDelNode
*/
Status RemoveTail(LinkList L, Node **pDelNode)
{
    if (!L || !pDelNode)
        return ERROR;
    
    Node *pCurr = L->next, *pPrev = L;

    while (pCurr) {
        pPrev = pCurr;
        pCurr = pCurr->next;
    }
    pPrev->next = NULL;
    *pDelNode = pCurr;

    return OK;
}

/**
 * @fun 将 s 插入 p 所指节点前, s->p
 * 
 * @param[in] p
 * @param[in] s
 * @ret
*/
Status InsertBefore(LinkList L, Node *p, Node *s)
{
    if (!L || !p || !s)
        return ERROR;

    Node *pCurr = L->next, *pPrev = L;    

    while (pCurr && (pCurr != p)) {
        pPrev = pCurr;
        pCurr = pCurr->next;
    }
    if (!pCurr) // can't find this node
        return ERROR;
    s->next = p;
    pPrev->next = s;

    return OK;
}

/**
 * @fun 将 s 插入 p 所指节点后 p->s
 * 
 * @param[in] p
 * @param[in] s
 * @ret
*/
Status InsertAfter(LinkList L, Node *p, Node *s)
{
    if (!L || !p || !s)
        return ERROR;

    Node *pCurr = L->next, *pPrev = L;    

    while (pCurr && (pCurr != p)) {
        pPrev = pCurr;
        pCurr = pCurr->next;
    }
    if (!pCurr) // can't find this node
        return ERROR;
    s->next = p->next;
    p->next = s;

    return OK;
}

/**
 * @fun 已知 p 为链表中的一个节点, 设置节点的新值
 * 
 * @param[in] L
 * @param[in] p
 * @param[in] nodeNewVal
 * @ret
*/
Status SetCurrElem(LinkList L, Node *p, ElemType nodeNewVal)
{
    if (!L || !p)
        return ERROR;
    
    Node *pCurr = L->next;

    while (pCurr && (pCurr != p)) {
        pCurr = pCurr->next;
    }
    if (!pCurr) // p is not this linklist's node
        return ERROR;
    COPY(&pCurr->data, &nodeNewVal, sizeof(ElemType));

    return OK;
}

/**
 * @fun 获取节点的值
 * 
 * @param[in] L
 * @param[in] p
 * @param[out] nodeNewVal
 * @ret
*/
Status GetCurrElem(LinkList L, Node *p, ElemType *pNode)
{
    if (!L || !p)
        return ERROR;
    
    Node *pCurr = L->next;

    while (pCurr && (pCurr != p)) {
        pCurr = pCurr->next;
    }
    if (!pCurr) // p is not this linklist's node
        return ERROR;
    COPY(pNode, &pCurr->data, sizeof(ElemType));

    return OK;
}

/**
 * @fun: 删除节点, 不释放内存
*/
Status DeleteNode(LinkList L, Node **pDelete)
{
    if (!L || !pDelete)
        return ERROR;
    
    Node *pPrev = L, *pCurr = L->next;
    while (pCurr && (pCurr != *pDelete)) {
        pPrev = pCurr;
        pCurr = pCurr->next;
    }
    if (!pCurr) // can't find pDelete in this linklist
        return ERROR;
    
    pPrev->next = pCurr->next;

    return OK;
}


/**
 * @fun 
*/
bool ListEmpty(LinkList L)
{
    size_t len = 0;
    LinkListLength(L, &len);
    return (len == 0 ? true : false);
}

/**
 * @fun 链表排序, 冒泡排序, swap 方法已经实现
 *
 * @param[in] L
 * @param[in] pCompareFun 满足交换要求返回 true, 不满足返回 false：根据传入的函数, 有上层决定是从小到大排序还是从大到小等等其他排序方式, 
 * @ret 
*/
Status BubbleSortLinkList(LinkList L, compare_t pCompareFun)
{
    if (!L)
        return ERROR;

    Node *pI = L->next, *pPrevI = L;

    for (; pI != NULL; pPrevI = pI, pI = pI->next) {
        Node *pJ = pI->next, *pPrevJ = pI;
        for (; pJ != NULL; pPrevJ = pJ, pJ = pJ->next) {
            if (pCompareFun(pI->data, pJ->data) == 0) { // 满足 pCompareFun 规定的交换要求
                if(SwapNode(pPrevI, pI, pPrevJ, pJ) != OK) // {
                    return ERROR;
                // } else { // 交换后交换 pi, pj 指针
                //     Node *temp = pJ, *prev = pPrevJ;
                //     pJ = pI;
                //     pPrevJ = pPrevI;
                //     pI = temp;
                //     pPrevI = prev;
                // }
                // TODO:
                // pj, pj 交换后, 链表的遍历出现异常
            }
        }
    }

    return OK;
}
#endif

void app_linklist_api_test1(void)
{
    Status ret;
    LinkList list;
    ElemType elem;
    position_t idx;
    ElemType elem1, elem2, elem3;
    ElemType *elem_ptr_array[3];

    // ret = InitLinkList(&list);
    // CHECK_RET(ret);
    // ret = Traverse(list, visit);
    // CHECK_RET(ret);

    ret = MakeStringElem(&elem1, "This is Node -1-");
    CHECK_RET(ret);
    elem_ptr_array[0] = &elem1;

    ret = MakeStringElem(&elem2, "This is Node +2++");
    CHECK_RET(ret);
    elem_ptr_array[1] = &elem2;

    ret = MakeStringElem(&elem3, "This is Node *3***");
    CHECK_RET(ret);
    elem_ptr_array[2] = &elem3;

    ret = InitLinkListWithArray(&list, elem_ptr_array, ARRAY_SIZE(elem_ptr_array));
    CHECK_RET(ret);
    ret = Traverse(list, visit);
    CHECK_RET(ret);





    ret = ClearLinkList(list);
    CHECK_RET(ret);
    ret = Traverse(list, visit);
    CHECK_RET(ret);

    ret = DestroyLinkList(&list);
    CHECK_RET(ret);
    ret = Traverse(list, visit);
    CHECK_RET(ret);


}


#endif