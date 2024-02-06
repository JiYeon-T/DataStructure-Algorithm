#include "LinkList_v4.h"
#include <limits.h>
#include <stddef.h>


#if defined(DataStructLinkListV4) && (DataStructLinkListV4 == 1)

#define COPY(DEST, SRC, LEN)             memcpy(DEST, SRC, LEN) // 拷贝数据域
// 比较数据域内容:相同返回 true, 不同返回 false
// #define COMPARE(VALADDR1, VALADDR2, LEN) \
//     do \
//     { \
//         if (memcmp(VALADDR1, VALADDR2, LEN) == 0) \
//             return true; \
//         else \
//             return false; \
//     } \
//     while(0)
#define COMPARE(VALADDR1, VALADDR2, LEN) \
    (memcmp((VALADDR1), (VALADDR2), (LEN)) == 0 ? true : false)


void struct_member_size_test(void)
{
    Node *pTemp;

    printf("data size:%d offset:%d\n", 
            sizeof(pTemp->data), offsetof(Node, data));
}

/**
 * @fun 节点数据为 int 类型
 * @param[in] pNode
*/
// static void print_general_node_info(Node *pNode)
// {
//     printf("%d -> ", pNode->data);
// }

/**
 * @fun 从小到大排序, a,b 满足从小到大, 返回 true; 否则返回 false
 * 
 * @param[in] a
 * @param[in] b
 * @ret
*/
// static int InOrderCompare(ElemType a, ElemType b)
// {
//     return (a <= b ? 1 : 0);
// }

/**
 * @fun 从大到小排序, a,b 满足从大到小, 返回 true; 否则返回 false
 * 
 * @param[in] a
 * @param[in] b
 * @ret
*/
// static int ReverseOrderCompare(ElemType a, ElemType b)
// {
//     return (a >= b ? 1 : 0);
// }

/**
 * @fun 找相等的元素节点, 相同即满足条件, 返回 true; 不相等, 不满足条件， 返回 false
 * 
 * @param[in] a
 * @param[in] b
 * @ret
*/
// static int EqualCompare(ElemType a, ElemType b)
// {
//     return (a == b ? 1 : 0);
// }

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
static Status SwapNode(Node *pPrev1, Node *p1, Node *pPrev2, Node *p2)
{
    if (!pPrev1 || !p1 || !pPrev2 || !p2)
        return ERROR;

    // 如果 p1, p2 为相邻节点则需要特殊处理
    if (pPrev2 == p1) { // p1, p2 相邻, p1 在前
        Node *temp = p2->next;
        p2->next = p1;
        pPrev1->next = p2;
        p1->next = temp;
        return OK;
    } else if (pPrev1 == p2) { // p1, p2 相邻, p2 在前
        Node *temp = p1->next;
        p1->next = p2;
        pPrev2->next = p1;
        p2->next = temp;
        return OK;
    }
    // else { // p1, p2 不相邻
    Node *temp = p2->next;

    p2->next = p1->next; // 保证所有被赋值的节点都没有被修改过
    p1->next = temp;
    pPrev1->next = p2;
    pPrev2->next = p1;
    // }

    return OK;
}

/**
 * @brief initialize a empty linklist, only a head node
 *
 * @param ll struct Node **L, 头指针, 初始化一个头指针指向头节点(头节点不保存数据)
 *          传入一个指向头节点的指针, 初始化后, 将该指针改为指向头节点(值为头节点的地址)
 * @return Status
 */
Status InitLinkList(LinkList *ll)
{
    if (!ll) {
        return ERROR;
    }

    Node *pTemp = (Node*)malloc(sizeof(Node) * 1);
    if (!pTemp) {
        return ERROR;
    }
    // pTemp->data = INVALID_VAL;
    memset(&pTemp->data, 0, sizeof(pTemp->data));
    pTemp->next = NULL;

    *ll = pTemp;

    return OK;
}

/**
 * @fun: init liklist with array, include head node
 * 
 * @param[in] pHead head pointer, 头指针指向头结点, 头结点不保存数据
 * @param[in] pArr
 * @param[in] len
 **/
Status InitLinkListWithArray(LinkList *L, ElemType *pArr, size_t len)
{
    if(!L || !pArr || !len){
        fprintf(stderr, "null ptr\n");
        return ERROR;
    }

    // initialize head node
    Node *pHead = (Node*)malloc(sizeof(Node) * 1);
    printf("malloc address:%#p\n", pHead);
    if(!pHead)
        return ERROR;
    // pHead->data = INVALID_VAL;
    memset(&pHead->data, 0, sizeof(pHead->data));
    pHead->next = NULL;
    *L = pHead;  // 头指针指向头结点, 保存地址; LinkList = struct Node *
    // LinkList *L;  // struct Node **L; // 解引用一层变成 Node * 类型

    // other node, tail insert
    Node *pTail = pHead; // 尾指针
    for (int ix = 0; ix < len; ++ix) {
        Node *pNew = (Node*)malloc(sizeof(Node) * 1);
        if(!pNew)
            goto EXIT;
        pNew->data = pArr[ix];
        COPY(&pNew->data, &pArr[ix], sizeof(ElemType));
        pNew->next = NULL;

        // 头插法
        // pNew->next = pHead;
        // pHead = pNew;

        // 尾插法
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
* @fun: traverse linklist
* @param[in] head pointer to head node
* @param[in] p_op_info traverse operation inforamtion
* @param[in] p_print_node_fun print node_information
* @ret Status
*/
Status Traverse(const LinkList L, char *p_op_info, print_node_info_fun p_print_node_fun)
{
    if (L == NULL || !p_print_node_fun) {
        fprintf(stderr, "null ptr\n");
        return ERROR;
    }
    size_t idx = 0;

    printf("traverse(%s):\n", p_op_info != NULL ? p_op_info : "unamed op");
    Node *pTemp = L->next; // first node
    while (pTemp) {
        printf("[%d]:", idx++);
        p_print_node_fun(pTemp);
        pTemp = pTemp->next;
    }
    printf("\n\n");

    return OK;
}

/**
* @fun: get linklist element
* @param[in]  L pointer to head node
* @param[in]  i index start from 0
* @param[out] e save value of index ix
*/
Status GetElem(const LinkList L, int i, ElemType *e)
{
    if (!L) {
        return ERROR;
    }
    Node *pTemp = L->next; // head node
    int j = 0;

    while (pTemp && j < i) {
        pTemp = pTemp->next;
        ++j;
    }

    if (!pTemp || j > i) {
        return ERROR;
    }
    COPY(e, &pTemp->data, sizeof(ElemType));

    return OK;
}

/**
 * @fun 若链表中存在与 nodeVal 进行 compare 操作结果 == 0 的元素, 则 pos 返回该结果, 并返回 false
 *      否则, 返回 false
 * 
 * @param[in] L
 * @param[in] nodeval
 * @param[out] pos 节点下标索引
 * @param[in] pCompareFun 节点数据域比较函数
 * @ret true/false
*/
Status LocateElem(const LinkList L, ElemType nodeVal, position_t *pos, compare_t pCompareFun)
{
    if (!L || !pos || !pCompareFun)
        return false;
    
    position_t idx = 0;
    Node *pCurr = L->next;

    while (pCurr && (pCompareFun(nodeVal, pCurr->data) == 0)) { // 不满足条件 pCompareFun, 遍历下一个节点
        pCurr = pCurr->next;
        ++idx;
    }
    if (!pCurr) { // can't find this node
        *pos = -1;
        return ERROR;
    }
    *pos = idx;

    return OK;
}

/**
 * @fun 按照有序链表的约定, 将一个节点的值插入到指定的位置, 从小到大排序
 * 
 * @param[in] L 有序链表
 * @param[in] nodeVal 待插入的值, 需要创建新结点
 * @param[in] pCompareFun
 * @ret
*/
Status OrderInsert(LinkList *L, ElemType nodeVal, compare_t pCompareFun)
{
    if (!L || !pCompareFun)
        return ERROR;
    
    Node *pCurr = (*L)->next, *pPrev = (*L);
    Status ret;
    size_t idx = 0;

    while ((pCurr) && (pCompareFun(nodeVal, pCurr->data) == 0)) { // 例如: 不满足插入条件,不需要插入, nodeVal > pCurr->data, 下一个节点
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
        if (ret != OK) {
            return ERROR;
        }
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
// Status ReverseOrderInsert(LinkList *L, ElemType nodeVal, compare_t pCompareFun)
// {
//     if (!L || !pCompareFun)
//         return ERROR;
    

// }

/**
 * @fun get linklist elem number
 * 
 * @param[in] ll
 * @param[out] linklist size pointer
 * @ret linklist size on success, -1 on error
*/
Status LinkListLength(const LinkList ll, size_t *pLen)
{
    if (!ll)
        return ERROR;
    
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
* @fun: Insert a number
* @desc: 有头节点的链表对于第一个节点的插入和删除操作和中间节点的操作一致, 
*       不需要区分是否在第一个节点前插入/删除, 如果要插入的为第 0 个元素, 就需要修改头指针, 所以传入 Node** 类型
*
* @param[in]  L pointer to head node
* @param[in]  i index start from 0
* @param[in] elem node value pointer
*/
Status InsertBeforePosIdx(LinkList *L, size_t idx, ElemType *pElem)
{
    if (!L || idx < 0)
        return ERROR;
    
    Node *pCurr = *L; // LinkList * == struct Node **
    Node *pInsert;
    size_t jx = 0;

    while (pCurr != NULL && jx < idx) { // 寻找第 i-1 个节点
        pCurr = pCurr->next;
        jx++;
    }

    if (!pCurr || jx > idx)
        return ERROR;

    pInsert = (struct Node *)malloc(sizeof(Node) * 1);
    COPY(&pInsert->data, pElem, sizeof(ElemType));
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
    if(!L){
        return ERROR;
    }
    // insert insertElem before elem
    Node *pPrev = L, *pCurr = L->next;
    Node *pInsert = NULL;

    while(pCurr && (COMPARE(pElem, &pCurr->data, sizeof(ElemType)) != true)){
        pPrev = pCurr;
        pCurr = pCurr->next;
    }

    // can't find node elem
    if(!pCurr){
        return ERROR;
    }

    // inser node
    pInsert = (LinkList)malloc(sizeof(Node) * 1);
    COPY(&pInsert->data, pInsertElem, sizeof(ElemType));
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
Status InsertAtFirst(LinkList L, ElemType *pVal)
{
    if (!L) {
        return ERROR;
    }
    Node *pInsert = (Node*)malloc(sizeof(Node) * 1);
    if (!pInsert) {
        perror("malloc failed\n");
        return ERROR;
    }

    COPY(&pInsert->data, pVal, sizeof(ElemType));
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
Status InsertAtTail(LinkList L, ElemType *pVal)
{
    if(!L){
        return ERROR;
    }
    Node *pTail = L->next;
    Node *pTemp = L->next;

    Node *pInsert = (Node*)malloc(sizeof(Node) * 1);
    if(!pInsert){
        perror("malloc failed\n");
        return ERROR;
    }
    COPY(&pInsert->data, pVal, sizeof(ElemType));
    pInsert->next = NULL;

    if(!pTemp){ // empty linklist
        L->next = pInsert;
        return OK;
    }

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
Status DeleteElem(LinkList L, ElemType *pDeleteVal)
{
    if(!L){
        return ERROR;
    }
    Node *pPrev = L, *pCurr = L->next;

    while(pCurr && (COMPARE(&pCurr->data, pDeleteVal, sizeof(ElemType)) != true)) {
        pPrev = pCurr;
        pCurr = pCurr->next;
    }

    if(!pCurr){ // can't find deleteElem
        return ERROR;
    }
    // delete ndoe
    pPrev->next = pCurr->next;
    free(pCurr);

    return OK;
}

/**
 * @fun 删除第 idx 个元素
 *      这里为什么一定要使用 Node ** 类型呢???????
 *      不需要修改头指针的值, 好像没必要使用 Node** 类型吖, 在 LinkList_v3 中实现
 * 
 * @param[in] L LinkList
 * @param[in] idx start from 0
 * @param[out] e element
 * @retval
 */
Status DeleteByIdx(LinkList *L, size_t idx, ElemType *e)
{
    if (!L || idx < 0 || !e)
        return ERROR;
    
    Node *pTemp = *L;
    Node *pDelete;
    size_t jx = 0;

    while (pTemp && jx < idx) { // 寻找第 idx-1 个节点
        ++jx;
        pTemp = pTemp->next;
    }
    if (!pTemp || jx > idx)
        return ERROR;
    pDelete = pTemp->next;
    pTemp->next = pDelete->next;
    COPY(e, &pDelete->data, sizeof(ElemType));
    free(pDelete);

    return OK;
}

/**
 * @fun 分配由 p 指向的值为 e 的节点
 * 
 * @param[out] node ptr
 * @param[in] nodeVal
 * @ret true/false
*/
Status MakeNode(Node **pNode, ElemType nodeVal)
{
    if (!pNode)
        return ERROR;

    Node *pNew = (Node*)malloc(sizeof(Node));
    if (!pNew)
        return ERROR;
    memset(pNew, 0x00, sizeof(Node));
    COPY(&pNew->data, &nodeVal, sizeof(ElemType));
    *pNode = pNew;

    return OK;
}

/**
 * @fun 释放节点
*/
Status FreeNode(Node **pNode)
{
    if (!pNode)
        return ERROR;

    free(*pNode);
    *pNode = NULL;

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

/**
* @fun: clear linklist,
*       does not delte head node, becomde a empty linklist
*
* @param[in]  L pointer to head node
* @retval Status
*/
Status ClearLinkList(LinkList L)
{
    // printf("param:%#p\n", L);
    // printf("head node, pinter:%#p data area:%ld\r\n", (*L).next, (*L).data);
    // printf("INT_MAX:%ld\r\n", INT_MAX);

    Node *pTemp = L->next; // first node, Node *pFirstNode = L->next;
    Node *pFree = NULL;

    while(pTemp != NULL){
        pFree = pTemp;
        pTemp = pTemp->next;
        free(pFree);
        pFree = NULL; // 释放内存并且修改为 NULL, 要不然下次遍历会出问题
    }

    L->next = NULL; // include a head node

    return OK;
}

/**
* @fun: free heap memory(include head node)
* @param[in]  L pointer to head node
* @retval Status
*/
Status DeinitLinkList(LinkList *L)
{
    Node *pTemp = *L; // Node* type
    Node *pFree = NULL;

    while(pTemp != NULL){
        pFree = pTemp;
        pTemp = pTemp->next;
        free(pFree);
    }

    *L = NULL;

    return OK;
}

#if 0


void LinkListTest2()
{
//     LinkList pList; // Node * pList;
//     ElemType arr[5] = {5, 7, 22, 111, 3};

//     InitLinkListWithArray_L(&pList, arr, sizeof(arr)/sizeof(arr[0]));
//     printf("get address:%#p\n", pList);
//     printf("init:\r\n");
//     Traverse_L(pList);

//     Insert_L(pList, 22, 99);
//     printf("insert:99\r\n");
//     Traverse_L(pList);

//     Delete_L(pList, 111);
//     printf("delete:111\r\n");
//     Traverse_L(pList);

// //    printf("arg:%#p\n", pList);
//     Clear_L(pList);
//     printf("clear\r\n");
//     Traverse_L(pList);

//     InserHead_L(pList, 1234);
//     printf("insert head node:1234\r\n");
//     Traverse_L(pList);

//     InsertAtTail(pList, 4568);
//     printf("insert tail node:4568\r\n");
//     Traverse_L(pList);

//     Deinit_L(&pList);
//     printf("deinit\r\n");
//     Traverse_L(pList);
}

void LinkListTest3(void)
{
    printf("Linklist v4 test3\n");
    ElemType data, insertVal;
    Status ret;
    size_t listSize = 10;
    size_t index = 5;
    Node *head;
    ElemType arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1088};
    position_t pos;

    ret = InitLinkListWithArray(&head, arr, sizeof(arr)/sizeof(arr[0]));
    CHECK_RET_OP(ret, "Init with array");
    LinkListLength(head, &listSize);
    printf("List size:%d\n", listSize);
    ret = Traverse(head, "InitLinkList with array", print_general_node_info);
    CHECK_RET_OP(ret, "Init");

    data = 4567;
    ret = InsertAtTail(head, &data);
    CHECK_RET_OP(ret, "insert:4567 at tail");
    LinkListLength(head, &listSize);
    printf("List size:%d\n", listSize);
    ret = Traverse(head, "insert:4567 at tail", print_general_node_info);
    CHECK_RET_OP(ret, "insert at tail");

    data = 0;
    ret = OrderInsert(&head, data, InOrderCompare);
    CHECK_RET_OP(ret, "OrderInsert:0");
    LinkListLength(head, &listSize);
    printf("List size:%d\n", listSize);
    ret = Traverse(head, "OrderInsert:0", print_general_node_info);
    CHECK_RET_OP(ret, "OrderInsert:0");

    data = 258;
    ret = OrderInsert(&head, data, InOrderCompare);
    CHECK_RET_OP(ret, "OrderInsert:258");
    LinkListLength(head, &listSize);
    printf("List size:%d\n", listSize);
    ret = Traverse(head, "OrderInsert:258", print_general_node_info);
    CHECK_RET_OP(ret, "OrderInsert:258");

    data = 9999;
    ret = OrderInsert(&head, data, InOrderCompare);
    CHECK_RET_OP(ret, "OrderInsert:9999");
    LinkListLength(head, &listSize);
    printf("List size:%d\n", listSize);
    ret = Traverse(head, "OrderInsert:9999", print_general_node_info);
    CHECK_RET_OP(ret, "OrderInsert:9999");
}

//链表测试函数
void linklist_api_test4(void)
{
    printf("Linklist v4 test\n");
    ElemType data, insertVal;
    Status ret;
    size_t listSize = 10;
    size_t index = 5;
    Node *head;
    ElemType arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    position_t pos;

    // head = InitHeadInsert_L(listSize);
    ret = InitLinkListWithArray(&head, arr, sizeof(arr)/sizeof(arr[0]));
    CHECK_RET_OP(ret, "Init with array");
    LinkListLength(head, &listSize);
    printf("List size:%d\n", listSize);
    ret = Traverse(head, "InitLinkList with array", print_general_node_info);
    CHECK_RET_OP(ret, "Init");

    ret = GetElem(head, 5, &data);
    CHECK_RET_OP(ret, "Get");
    printf("idx:%d val:%d\n", 5, data);

    ret = GetElem(head, 4, &data);
    CHECK_RET_OP(ret, "Get");
    printf("idx:%d val:%d\n", 4, data);

    data = 1000;
    ret = InsertBeforePosIdx(&head, 1, &data);
    CHECK_RET_OP(ret, "insert:1000 before idx[1]");
    LinkListLength(head, &listSize);
    printf("List size:%d\n", listSize);
    ret = Traverse(head, "insert:1000 before idx[1]", print_general_node_info);
    CHECK_RET_OP(ret, "insert before idx");

    data = 1000;
    insertVal = 2000;
    ret = InsertBeforeElem(head, &data, &insertVal);
    CHECK_RET_OP(ret, "insert:2000 before elem 1000");
    LinkListLength(head, &listSize);
    printf("List size:%d\n", listSize);
    ret = Traverse(head, "insert:2000 before elem 1000", print_general_node_info);
    CHECK_RET_OP(ret, "insert before elem");

    data = 1234;
    ret = InsertAtFirst(head, &data);
    CHECK_RET_OP(ret, "insert:1234 at first");
    LinkListLength(head, &listSize);
    printf("List size:%d\n", listSize);
    ret = Traverse(head, "insert:1234 at first", print_general_node_info);
    CHECK_RET_OP(ret, "insert at first");

    data = 4567;
    ret = InsertAtTail(head, &data);
    CHECK_RET_OP(ret, "insert:4567 at tail");
    LinkListLength(head, &listSize);
    printf("List size:%d\n", listSize);
    ret = Traverse(head, "insert:4567 at tail", print_general_node_info);
    CHECK_RET_OP(ret, "insert at tail");

    data = 4567;
    ret = DeleteElem(head, &data);
    CHECK_RET_OP(ret, "delete elem:4567");
    LinkListLength(head, &listSize);
    printf("List size:%d\n", listSize);
    ret = Traverse(head, "delete elem:4567", print_general_node_info);
    CHECK_RET_OP(ret, "delete elem");


    ret = DeleteByIdx(&head, 5, &data);
    CHECK_RET_OP(ret, "delete elem idx:[5]");
    printf("delte idx:%d val:%d\n", 5, data);
    LinkListLength(head, &listSize);
    printf("List size:%d\n", listSize);
    ret = Traverse(head, "delete elem idx:[5]", print_general_node_info);
    CHECK_RET_OP(ret, "delete elem");

    // data = 1234;
    /* 需要是有序链表 */
    data = 9;
    ret = LocateElem(head, data, &pos, EqualCompare);
    CHECK_RET_OP(ret, "LocateElem");
    printf("elem:%d pos:%d\n", data, pos);
    LinkListLength(head, &listSize);
    printf("List size:%d\n", listSize);
    ret = Traverse(head, "LocateElem", print_general_node_info);
    CHECK_RET_OP(ret, "LocateElem");
}

void LinkListTest5(void)
{
    printf("Linklist v4 test5\n");
    ElemType data, insertVal;
    Status ret;
    size_t listSize = 10;
    size_t index = 5;
    Node *head;
    ElemType arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1088};
    position_t pos;

    ret = InitLinkListWithArray(&head, arr, sizeof(arr)/sizeof(arr[0]));
    CHECK_RET_OP(ret, "Init with array");
    LinkListLength(head, &listSize);
    printf("List size:%d\n", listSize);
    ret = Traverse(head, "InitLinkList with array", print_general_node_info);
    CHECK_RET_OP(ret, "Init");

    Node *pPrev1 = head->next, *p1 = pPrev1->next;
    Node *pPrev2 = p1->next, *p2 = pPrev2->next;
    printf("pPrev1:%d p1:%d pPrev2:%d p2:%d\n", pPrev1->data, p1->data, pPrev2->data, p2->data);
    ret = SwapNode(pPrev1, p1, pPrev2, p2);
    CHECK_RET_OP(ret, "SwapNode");
    ret = Traverse(head, "SwapNode", print_general_node_info);
    CHECK_RET_OP(ret, "SwapNode");

    // 相邻, p1 在前
    pPrev1 = head->next;
    p1 = pPrev1->next;
    pPrev2 = p1;
    p2 = p1->next;
    printf("pPrev1:%d p1:%d pPrev2:%d p2:%d\n", pPrev1->data, p1->data, pPrev2->data, p2->data);
    ret = SwapNode(pPrev1, p1, pPrev2, p2);
    CHECK_RET_OP(ret, "SwapNode");
    ret = Traverse(head, "SwapNode", print_general_node_info);
    CHECK_RET_OP(ret, "SwapNode");

    // 相邻, p2 在前
    pPrev2 = head->next;
    p2 = pPrev2->next;
    pPrev1 = p2;
    p1 = pPrev1->next;
    printf("pPrev1:%d p1:%d pPrev2:%d p2:%d\n", pPrev1->data, p1->data, pPrev2->data, p2->data);
    ret = SwapNode(pPrev1, p1, pPrev2, p2);
    CHECK_RET_OP(ret, "SwapNode");
    ret = Traverse(head, "SwapNode", print_general_node_info);
    CHECK_RET_OP(ret, "SwapNode");
}

void LinkListTest6(void)
{
    printf("Linklist v4 test3\n");
    ElemType data, insertVal;
    Status ret;
    size_t listSize = 10;
    size_t index = 5;
    Node *head;
    ElemType arr[10] = {9999, 999, 99, 9, 8, 7, 6, 5, 4, 1};
    position_t pos;

    ret = InitLinkListWithArray(&head, arr, sizeof(arr)/sizeof(arr[0]));
    CHECK_RET_OP(ret, "Init with array");
    LinkListLength(head, &listSize);
    printf("List size:%d\n", listSize);
    ret = Traverse(head, "InitLinkList with array", print_general_node_info);
    CHECK_RET_OP(ret, "Init");

    // data = 4567;
    // ret = InsertAtTail(head, &data);
    // CHECK_RET_OP(ret, "insert:4567 at tail");
    // LinkListLength(head, &listSize);
    // printf("List size:%d\n", listSize);
    // ret = Traverse(head, "insert:4567 at tail", print_general_node_info);
    // CHECK_RET_OP(ret, "insert at tail");

    data = 0;
    ret = OrderInsert(&head, data, ReverseOrderCompare);
    CHECK_RET_OP(ret, "OrderInsert:0");
    LinkListLength(head, &listSize);
    printf("List size:%d\n", listSize);
    ret = Traverse(head, "OrderInsert:0", print_general_node_info);
    CHECK_RET_OP(ret, "OrderInsert:0");

    data = 258;
    ret = OrderInsert(&head, data, ReverseOrderCompare);
    CHECK_RET_OP(ret, "OrderInsert:258");
    LinkListLength(head, &listSize);
    printf("List size:%d\n", listSize);
    ret = Traverse(head, "OrderInsert:258", print_general_node_info);
    CHECK_RET_OP(ret, "OrderInsert:258");

    data = 99999;
    ret = OrderInsert(&head, data, ReverseOrderCompare);
    CHECK_RET_OP(ret, "OrderInsert:99999");
    LinkListLength(head, &listSize);
    printf("List size:%d\n", listSize);
    ret = Traverse(head, "OrderInsert:99999", print_general_node_info);
    CHECK_RET_OP(ret, "OrderInsert:99999");
}

void LinkListTest7(void)
{
    printf("Linklist v4 test\n");
    ElemType data, insertVal;
    Status ret;
    size_t listSize = 10;
    size_t index = 5;
    Node *head;
    ElemType arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1088};
    position_t pos;

    ret = InitLinkListWithArray(&head, arr, sizeof(arr)/sizeof(arr[0]));
    CHECK_RET_OP(ret, "Init with array");
    LinkListLength(head, &listSize);
    printf("List size:%d\n", listSize);
    ret = Traverse(head, "InitLinkList with array", print_general_node_info);
    CHECK_RET_OP(ret, "Init");

    data = 4567;
    ret = InsertAtTail(head, &data);
    CHECK_RET_OP(ret, "insert:4567 at tail");
    LinkListLength(head, &listSize);
    printf("List size:%d\n", listSize);
    ret = Traverse(head, "insert:4567 at tail", print_general_node_info);
    CHECK_RET_OP(ret, "insert at tail");

    // TODO:
    // sort linklist
    ret = BubbleSortLinkList(head, ReverseOrderCompare);
    CHECK_RET_OP(ret, "BubbleSortLinkList");
    LinkListLength(head, &listSize);
    printf("List size:%d\n", listSize);
    ret = Traverse(head, "BubbleSortLinkList", print_general_node_info);
    CHECK_RET_OP(ret, "BubbleSortLinkList");
}

void LinkListTest8(void)
{
    printf("Linklist test8\n");
    ElemType data, insertVal;
    Status ret;
    size_t listSize = 10;
    size_t index = 5;
    Node *head;
    ElemType arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1088};
    position_t pos;

    ret = InitLinkListWithArray(&head, arr, sizeof(arr)/sizeof(arr[0]));
    CHECK_RET_OP(ret, "Init with array");
    LinkListLength(head, &listSize);
    printf("List size:%d\n", listSize);
    ret = Traverse(head, "InitLinkList with array", print_general_node_info);
    CHECK_RET_OP(ret, "Init");
}

#endif


#endif
