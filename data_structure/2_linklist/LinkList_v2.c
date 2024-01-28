#include "LinkList_v2.h"
#include <limits.h>



#if defined(DataStructLinkListV2) && (DataStructLinkListV2 == 1)

/**
 * @brief initialize a empty linklist, only a head node
 *
 * @param L struct Node **L, 头指针, 初始化一个头指针指向头节点(头节点不保存数据)
 *          传入一个指向头节点的指针, 初始化后, 将该指针改为指向头节点(值为头节点的地址)
 * @return Status
 */
Status InitLinkList(LinkList *L)
{
    if (!L) {
        return ERROR;
    }

    Node *pTemp = (Node*)malloc(sizeof(Node) * 1);
    if (!pTemp) {
        return ERROR;
    }
    pTemp->data = INVALID_VAL;
    pTemp->next = NULL;

    *L = pTemp;

    return OK;
}

/**
 * @fun: init linklist with index, 头插法初始化链表
 *
 * @param[in]  L pointer to head node
 * @param[in]  size
 **/
// Status Init_L(LinkList *L, unsigned int size)
LinkList InitHeadInsert(size_t size)
{
    Node *pHead;
    int data = 0;

    pHead = (Node*)malloc(sizeof(Node) * 1); // 头节点
    pHead->data = INVALID_VAL;
    pHead->next = NULL;

    for (size_t ix = 0; ix < size; ++ix) {
        Node *temp = (Node*)malloc(sizeof(Node) * 1);
        if(!temp){
            // 分配失败,删除已经创建的所有节点,释放已经分配的内存, 防止内存泄漏
            // ListDestroy(pHead); // 头节点也一起释放
            return NULL;
        }
        temp->data = data++;
        temp->next = pHead;
        pHead = temp;
    }

    return pHead;
}

/**
* @fun: init liklist, initialize with index
*       尾插法, 有头结点的链表
*
* @param[in]  L pointer to head node
* @param[in]  size
*/
// Status Init_L(LinkList *L, unsigned int size)
LinkList InitTailInsert(size_t size)
{
    Node *pHead, *pTail;
    int data = 0;

    pHead = (Node*)malloc(sizeof(Node) * 1);
    if (!pHead)
        return NULL;
    pHead->data = INVALID_VAL;
    pHead->next = NULL;
    pTail = pHead;

    for (size_t ix = 0; ix < size; ++ix) {
        Node *temp = (Node*)malloc(sizeof(Node) * 1);
        temp->data = data++;
        temp->next = NULL;
        // tail insert
        pTail->next= temp;
        pTail = temp;
    }

    return pHead;
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
    pHead->data = INVALID_VAL;
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
* @ret Status
*/
Status Traverse(const LinkList L, char *p_op_info)
{
    if (L == NULL) {
        fprintf(stderr, "null ptr\n");
        return ERROR;
    }
    size_t idx = 0;

    printf("traverse(%s):\n", p_op_info != NULL ? p_op_info : "unamed op");
    Node *pTemp = L->next; // first node
    while (pTemp) {
        printf("[%d]:%d -> ", idx++, pTemp->data);
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
    Node *p_temp = L->next; // head node
    int j = 0;

    while (p_temp && j < i) {
        p_temp = p_temp->next;
        ++j;
    }

    if (!p_temp || j > i) {
        return ERROR;
    }
    *e = p_temp->data;
    // copy_data_fidld(e, p_temp->data);

    return OK;
}

/**
* @fun: Insert a number
* @desc: 有头节点的链表对于第一个节点的插入和删除操作和中间节点的操作一致, 
*       不需要区分是否在第一个节点前插入/删除, 如果要插入的为第 0 个元素, 就需要修改头指针, 所以传入 Node** 类型
*
* @param[in]  L pointer to head node
* @param[in]  i index start from 0
* @param[out] e save value of index ix
*/
Status InsertBeforePosIdx(LinkList *L, size_t idx, ElemType elem)
{
    if (!L || idx < 0)
        return ERROR;
    
    Node *p_curr = *L; // LinkList * == struct Node **
    Node *p_insert;
    size_t jx = 0;

    while (p_curr != NULL && jx < idx) { // 寻找第 i-1 个节点
        p_curr = p_curr->next;
        jx++;
    }

    if (!p_curr || jx > idx)
        return ERROR;

    p_insert = (struct Node *)malloc(sizeof(Node) * 1);
    p_insert->data = elem;
    p_insert->next =p_curr->next;
    p_curr->next = p_insert;

    return OK;   
}

/**
 * @brief Insert a node before node "elem"
 * @param[in] L LinkList
 * @param[in] elem
 * @param[in] insertElem
 * @retval
 */
Status InsertBeforeElem(LinkList L, ElemType elem, ElemType insertElem)
{
    if(!L){
        return ERROR;
    }
    // insert insertElem before elem
    Node *prev = L, *cur = L->next;
    Node *pInsert = NULL;

    while(cur && cur->data != elem){
        prev = cur;
        cur = cur->next;
    }

    // can't find node elem
    if(!cur){
        return ERROR;
    }

    // inser node
    pInsert = (LinkList)malloc(sizeof(Node) * 1);
    pInsert->data = insertElem;
    pInsert->next = cur;
    prev->next = pInsert;

    return OK;
}

/**
 * @brief Insert a node before first node
 * @param[in] L head pointer
 * @param[in] elem
 * @retval
 */
Status InsertAtFirst(LinkList L, ElemType data)
{
    if (!L) {
        return ERROR;
    }
    Node *pInsert = (Node*)malloc(sizeof(Node) * 1);
    if (!pInsert) {
        perror("malloc failed\n");
        return ERROR;
    }

    pInsert->data = data;
    pInsert->next = L->next; // first node
    L->next = pInsert; // update first node

    return OK;
}

// insert a node at head
// Status InsertHead_L2(LinkList L, Node *pNode)
// {
//     if(!L || !pNode){
//         return ERROR;
//     }

//     Node *pFirstNode = L->next;
//     pNode->next = pFirstNode;
//     // pFirstNode = pNode; // 对局部变量 pFirstNode 赋值
//     L->next = pNode; // (*L).next = pNode;

//     return OK;
// }

/**
 * @brief Insert a node after last node
 * @param[in] L LinkList
 * @param[in] elem
 * @retval
 */
Status InsertAtTail(LinkList L, ElemType data)
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
    pInsert->data = data;
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

// insert a node at tail
// Status InsertTail_L2(LinkList L, Node *pNode)
// {
//     if(!L || !pNode){
//         return ERROR;
//     }

//     Node *pTemp = L->next; // first node
//     Node *pPrev = pTemp;

//     // empty linklist, only have a head node
//     if(!pTemp){
//         // pTemp = pNode; // 仅仅是修改局部变量
//         L->next = pNode;
//         return OK;
//     }

//     while(pTemp){
//         pPrev = pTemp;
//         pTemp = pTemp->next;
//     }

//     pPrev->next = pNode; // 这种赋值却不一样, 等价于:(*pPrev).next = pNode;
//     // (*pPrev).next = pNode;

//     return OK;
// }

/**
 * @brief delete a node
 * @param[in] L LinkList
 * @param[in] deleteElem
 * @retval
 */
Status DeleteElem(LinkList L, ElemType deleteElem)
{
    if(!L){
        return ERROR;
    }
    Node *prev = L, *cur = L->next;

    while(cur && cur->data!=deleteElem){
        prev = cur;
        cur = cur->next;
    }

    if(!cur){ // can't find deleteElem
        return ERROR;
    }
    // delete ndoe
    prev->next = cur->next;
    free(cur);

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
    *e = pDelete->data;
    free(pDelete);

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
 * @fun: merge 2 sorted linklist, L1, L2 是两个有序链表
 *       归并排序 从小到大
 *       创建新节点然后插入
 *
 * @param[in]  L1 pointer to head node*
 * @param[in]  L2 pointer to head node
 * @retval LinkList struct Node *
 **/
LinkList MergeSortedLinkListV1(LinkList L1, LinkList L2)
{
    if(!L1 || !L2){
        return ERROR;
    }
    LinkList mergedList;
    Node *pL1Temp = L1->next, *pL2Temp = L2->next; // fisrt ndoe

    InitLinkList(&mergedList); // 初始化保存链表
    // printf("mergedList:\r\n");
    // Traverse_L(mergedList);
    // InserHead_L(mergedList, 111);
    // Traverse_L(mergedList);

    // 归并排序
    while(pL1Temp && pL2Temp){ // L1, L2 都不为空
        if(pL1Temp->data <= pL2Temp->data){ // 如果是 C++ 这里就要重载 <= 运算符了
            InsertAtTail(mergedList, pL1Temp->data);
            pL1Temp = pL1Temp->next;
        }
        else{
            InsertAtTail(mergedList, pL2Temp->data);
            pL2Temp = pL2Temp->next;
        }
        // Traverse_L(mergedList);
    }

    // if(pL1Temp) // L1 不为空
    { 
        while(pL1Temp){
            InsertAtTail(mergedList, pL1Temp->data);
            pL1Temp = pL1Temp->next;
            // Traverse_L(mergedList);
        }
    }

    // if(pL2Temp) // L2 不为空
    { 
        while(pL2Temp){
            InsertAtTail(mergedList, pL2Temp->data);
            pL2Temp = pL2Temp->next;
            // Traverse_L(mergedList);
        }
    }

    return mergedList;
}


/**
* @fun: merge 2 sorted linklist, 直接合并链表, 不创建新的链表, 减小算法的空间复杂度
*       直接将原链表上的节点转移到新链表, 不创建新的节点;
*       只使用两条链表, 不引入第三条链表
*
* @param[in]  L1 pointer to head node*, 从小到大
* @param[in]  L2 pointer to head node
* @retval Status
*/
LinkList MergeSortedLinkListV2(LinkList L1, LinkList L2)
{
    if(!L1 || !L2){
        return ERROR;
    }
    LinkList mergedList;
    InitLinkList(&mergedList);

    // 原来链表的内存不释放, 也不进行重新创建, 直接将节点移过来
    Node *pL1Temp = L1->next, *pL2Temp = L2->next;
    Node *temp = mergedList; // merged linklist's first node
    while(pL1Temp && pL2Temp){ // L1, L2 都不为空
        // Node *temp;
        if(pL1Temp->data <= pL2Temp->data){
            temp->next = pL1Temp;
            temp = pL1Temp;
            pL1Temp = pL1Temp->next;
        }
        else{
            temp->next = pL2Temp;
            temp = pL2Temp;
            pL2Temp = pL2Temp->next;
        }
    }

    if (pL1Temp) { // L1 不为空退出循环
        temp->next = pL1Temp; 
    }

    if (pL2Temp) { // L2 不为空退出循环
        temp->next = pL2Temp; // 链表剩余部分全拿过来
    }

    // temp->next = pL1Temp ? pL1Temp : pL2Temp; // 使用条件表达式

    // Deinit_L(&LL1); // 释放头结点内存
    // Deinit_L(&L2);
    return mergedList;
}

//链表测试函数
void linklist_api_test(void)
{
//    Node node; //头节点, 数据域不保存数据, 可以选择保存链表长度之类的
//    LinkList head = &node; //pointer, size = 4; 指向 "头节点" 的指针
    // Node head, node1, node2, node3; // struct Node, size = 8, printf("%d - %d", sizeof head, sizeof(node));
    printf("Linklist v2 test\n");
    ElemType data;
    Status ret;
    size_t listSize = 10;
    size_t index = 5;
    Node *head;

    // head = InitHeadInsert_L(listSize);
    head = InitTailInsert(listSize);
    CHECK_NOT_NULL(head);
    ret = Traverse(head, "InitLinkList");
    CHECK_RET_OP(ret, "Init");

    ret = GetElem(head, 5, &data);
    CHECK_RET_OP(ret, "Get");
    printf("idx:%d val:%d\n", 5, data);

    ret = GetElem(head, 4, &data);
    CHECK_RET_OP(ret, "Get");
    printf("idx:%d val:%d\n", 4, data);

    ret = InsertBeforePosIdx(&head, 1, 1000);
    CHECK_RET_OP(ret, "insert:1000 before idx[1]");
    ret = Traverse(head, "insert:1000 before idx[1]");
    CHECK_RET_OP(ret, "insert before idx");

    ret = InsertBeforeElem(head, 1000, 2000);
    CHECK_RET_OP(ret, "insert:2000 before elem 1000");
    ret = Traverse(head, "insert:2000 before elem 1000");
    CHECK_RET_OP(ret, "insert before elem");

    ret = InsertAtFirst(head, 1234);
    CHECK_RET_OP(ret, "insert:1234 at first");
    ret = Traverse(head, "insert:1234 at first");
    CHECK_RET_OP(ret, "insert at first");

    ret = InsertAtTail(head, 4567);
    CHECK_RET_OP(ret, "insert:4567 at tail");
    ret = Traverse(head, "insert:4567 at tail");
    CHECK_RET_OP(ret, "insert at tail");

    ret = DeleteElem(head, 4567);
    CHECK_RET_OP(ret, "delete elem:4567");
    ret = Traverse(head, "delete elem:4567");
    CHECK_RET_OP(ret, "delete elem");

    ret = DeleteByIdx(&head, 5, &data);
    CHECK_RET_OP(ret, "delete elem idx:[5]");
    printf("delte idx:%d val:%d\n", 5, data);
    ret = Traverse(head, "delete elem idx:[5]");
    CHECK_RET_OP(ret, "delete elem");

    ret = ClearLinkList(head);
    CHECK_RET_OP(ret, "clear linklist");
    ret = Traverse(head, "clear");
    CHECK_RET_OP(ret, "clear");
}

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

void LinkListTest3()
{
    LinkList L1, L2, L3;
    ElemType arr1[] = {5, 7, 22, 111, 333, 444, 7777};
    ElemType arr2[] = {3, 4, 57, 222, 666, 999, 1024};
    InitLinkListWithArray(&L1, arr1, 7);
    InitLinkListWithArray(&L2, arr2, 7);
    Traverse(L1, "L1:");
    Traverse(L2, "L2");

    // L3 = MergeSortedLinkListV1(L1, L2);
    L3 = MergeSortedLinkListV2(L1, L2);
    // Traverse(L1, "L1:");
    // Traverse(L2, "L2");
    Traverse(L3, "Mergedv2");
 
//     InitLinkList_L(&L3);
//     Traverse_L(L3);
//     Node a, b, c;
//     a.data = 1;
//     a.next =NULL;
//     InsertTail_L2(L3, &a);
//     Traverse_L(L3);
//     b.data = 2;
//     b.next = NULL;
//     InsertTail_L2(L3, &b);
}
#endif
