#include "LinkList.h"

#include <limits.h>

// 增 删 改 查
#define LINK_LIST     1
#if LINK_LIST

/**
 * @brief initialize a empty linklist, only a head node
 *
 * @param L struct Node **L
 * @return Status
 */
Status InitLinkList_L(LinkList *L)
{
    if(!L){
        return ERROR;
    }

    Node *pTemp = (Node*)malloc(sizeof(Node) * 1);
    if(!pTemp){
        return ERROR;
    }
    pTemp->data = INT_MAX;
    pTemp->next = NULL;

    *L = pTemp;

    return OK;
}


/**
* @fun: init linklist
* @param[in]  L pointer to head node
* @param[in]  size
*/
// Status Init_L(LinkList *L, unsigned int size)
LinkList InitHeadInsert_L(size_t size)
{
    // Node headNode;
    // headNode.next = NULL;
    LinkList pHead = NULL; // 没有头节点
    // pHead = &headNode;
    int data = 0;

    for(size_t ix = 0; ix < size; ++ix)
    {
        LinkList temp = (LinkList)malloc(sizeof(Node) * 1);
        if(!temp){
            // 分配失败,释放已经分配的内存, 防止内存泄漏
        }
        temp->data = data++;
        temp->next = pHead;
        pHead = temp;
    }

    return pHead;
}

/**
* @fun: init liklist
* @param[in]  L pointer to head node
* @param[in]  size
*/
// Status Init_L(LinkList *L, unsigned int size)
LinkList InitTailInsert_L(size_t size)
{
    // 有头结点
    Node headNode; // head node, don't save data
    LinkList pHead = NULL, pTail = NULL; // include a head node

    pHead = &headNode;
    pTail = &headNode;
    int data = 0;

    for(size_t ix = 0; ix < size; ++ix)
    {
        LinkList temp = (LinkList)malloc(sizeof(Node) * 1);
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
* @param[in] pHead head pointer, 头指针指向头结点, 头结点不保存数据
* @param[in] pArr
* @param[in] len
*/
Status InitLinkListWithArray_L(LinkList *L, ElemType *pArr, size_t len)
{
    if(!L || !pArr || !len){
        fprintf(stderr, "null ptr\n");
        return ERROR;
    }

    // initialize head node
    Node *pHead = (Node*)malloc(sizeof(Node) * 1);
    printf("malloc address:%#p\n", pHead);
    if(!pHead){
        perror("malloc failed\n");
        return ERROR;
    }
    pHead->data = INT_MAX;
    pHead->next = NULL;
    *L = pHead;  // 头指针指向头结点, 保存地址; LinkList = struct Node *
    // LinkList *L;  // struct Node **L; // 解引用一层变成 Node * 类型

    // other node, tail insert
    Node *pTail = pHead; // 尾指针
    for(int ix = 0; ix < len; ++ix){
        Node *pNew = (Node*)malloc(sizeof(Node) * 1);
        if(!pNew){
            perror("malloc failed\n");
            goto EXIT;
        }
        pNew->data = pArr[ix];
        pNew->next = NULL;
        // pTail->next = pNew;
        // pTail = pNew;
        // InsertHead_L2(*L, pNew); // head insert
        InsertTail_L2(*L, pNew); // tail insert
    }

    return OK;
EXIT:
    // 释放已经分配内存
    // deinit 链表或者保留已经初始化的部分
    // 返回 ERROR
    return ERROR;
}

/**
* @fun: traverse linklist
* @param[in]  head pointer to head node
*/
Status Traverse_L(LinkList L)
{
    printf("traverse:\n");
    if(L == NULL){
        fprintf(stderr, "null ptr\n");
        return ERROR;
    }

    Node *pTemp = L->next; // include a head node

    while(pTemp){
        printf("%d ->", pTemp->data);
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
Status GetElem_L(LinkList L, int i, ElemType *e)
{
    if(!L){
        return ERROR;
    }
    LinkList p_temp = L->next; // head node
    int j = 0;

    while(p_temp && j<i){
        p_temp = p_temp->next;
        ++j;
    }

    if( !p_temp || j>i ){
        return ERROR;
    }
    *e = p_temp->data;

    return OK;
}

/**
 * @brief Insert a node before node "elem"
 * @param[in] L LinkList
 * @param[in] elem
 * @param[in] insertElem
 * @retval
 */
Status Insert_L(LinkList L, ElemType elem, ElemType insertElem)
{
    if(!L){
        return ERROR;
    }
    // insert insertElem before elem
    Node *prev = L, *cur = L->next;
    Node *pInsertNode = NULL;

    while(cur && cur->data!=elem){
        prev = cur;
        cur = cur->next;
    }

    // can't find node elem
    if(!cur){
        return ERROR;
    }

    // inser node
    pInsertNode = (LinkList)malloc(sizeof(Node) * 1);
    pInsertNode->data = insertElem;
    pInsertNode->next = cur;
    prev->next = pInsertNode;

    return OK;
}

/**
 * @brief Insert a node before first node
 * @param[in] L head pointer
 * @param[in] elem
 * @retval
 */
Status InserHead_L(LinkList L, ElemType data)
{
    if(!L){
        return ERROR;
    }
    Node *pInsert = (Node*)malloc(sizeof(Node) * 1);
    if(!pInsert){
        perror("malloc failed\n");
        return ERROR;
    }

    Node *pFirstNode = L->next; // get first node
    pInsert->data = data;
    pInsert->next = pFirstNode;
    L->next = pInsert; // update first node

    return OK;
}


/**
 * @brief Insert a node after last node
 * @param[in] L LinkList
 * @param[in] elem
 * @retval
 */
Status InsertTail_L(LinkList L, ElemType data)
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

// insert a node at head
Status InsertHead_L2(LinkList L, Node *pNode)
{
    if(!L || !pNode){
        return ERROR;
    }

    Node *pFirstNode = L->next;
    pNode->next = pFirstNode;
    // pFirstNode = pNode; // 对局部变量 pFirstNode 赋值
    L->next = pNode; // (*L).next = pNode;

    return OK;
}

// insert a node at tail
Status InsertTail_L2(LinkList L, Node *pNode)
{
    if(!L || !pNode){
        return ERROR;
    }

    Node *pTemp = L->next; // first node
    Node *pPrev = pTemp;

    // empty linklist, only have a head node
    if(!pTemp){
        // pTemp = pNode; // 仅仅是修改局部变量
        L->next = pNode;
        return OK;
    }

    while(pTemp){
        pPrev = pTemp;
        pTemp = pTemp->next;
    }

    pPrev->next = pNode; // 这种赋值却不一样, 等价于:(*pPrev).next = pNode;
    // (*pPrev).next = pNode;

    return OK;
}

/**
 * @brief delete a node
 * @param[in] L LinkList
 * @param[in] deleteElem
 * @retval
 */
Status Delete_L(LinkList L, ElemType deleteElem)
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

// /**
//  * @brief delete a node
//  * @param[in] L LinkList
//  * @param[in] deleteElem
//  * @retval
//  */
// Status Delete_L2(LinkList L, Node* node)
// {

// }

/**
* @fun: free heap memory(include head node)
* @param[in]  L pointer to head node
* @retval Status
*/
Status Deinit_L(LinkList *L)
{
    Node *pTemp = (Node*)(*L);
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
* @desc: does not delte head node, becomde a empty linklist
* @param[in]  L pointer to head node
* @retval Status
*/
Status Clear_L(LinkList L)
{
    printf("param:%#p\n", L);
    printf("head node, pinter:%#p data area:%ld\r\n", (*L).next, (*L).data);
    printf("INT_MAX:%ld\r\n", INT_MAX);

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
* @fun: merge 2 sorted linklist
* @desc: 归并排序 从小到大
* @param[in]  L1 pointer to head node*
* @param[in]  L2 pointer to head node
* @retval LinkList struct Node *
*/
LinkList MergeLinkList_L(LinkList L1, LinkList L2)
{
    if(!L1 || !L2){
        return ERROR;
    }
    LinkList mergedList;
    Node *pL1Temp = L1->next, *pL2Temp = L2->next; // fisrt ndoe

    InitLinkList_L(&mergedList); // 初始化保存链表
    // printf("mergedList:\r\n");
    // Traverse_L(mergedList);
    // InserHead_L(mergedList, 111);
    // Traverse_L(mergedList);

    // 归并排序
    while(pL1Temp && pL2Temp){ // L1, L2 都不为空
        if(pL1Temp->data <= pL2Temp->data){ // 如果是 C++ 这里就要重载 <= 运算符了
            InsertTail_L(mergedList, pL1Temp->data);
            pL1Temp = pL1Temp->next;
        }
        else{
            InsertTail_L(mergedList, pL2Temp->data);
            pL2Temp = pL2Temp->next;
        }
        // Traverse_L(mergedList);
    }

    // if(pL1Temp) // L1 不为空退出循环
    { 
        while(pL1Temp){
            InsertTail_L(mergedList, pL1Temp->data);
            pL1Temp = pL1Temp->next;
            // Traverse_L(mergedList);
        }
    }

    // if(pL2Temp) // L2 不为空退出循环
    { 
        while(pL2Temp){
            InsertTail_L(mergedList, pL2Temp->data);
            pL2Temp = pL2Temp->next;
            // Traverse_L(mergedList);
        }
    }

    return mergedList;
}


/**
* @fun: merge 2 sorted linklist, 直接合并链表, 不创建新的链表, 减小算法的空间复杂度
* @desc: 直接将原链表上的节点转移到新链表;只使用两条链表, 不引入第三条链表
* @param[in]  L1 pointer to head node*, 从小到大
* @param[in]  L2 pointer to head node
* @retval Status
*/
LinkList MergeLinkList_L_v2(LinkList L1, LinkList L2)
{
    if(!L1 || !L2){
        return ERROR;
    }
    LinkList mergedList;
    InitLinkList_L(&mergedList);

    Node *pL1Temp = L1->next, *pL2Temp = L2->next;
    // 原来链表的内存不释放, 也不进行重新创建, 直接将节点移过来
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

    if(pL1Temp){ // L1 不为空退出循环
        temp->next = pL1Temp; 
    }

    if(pL2Temp){ // L2 不为空退出循环
        temp->next = pL2Temp; // 链表剩余部分全拿过来
    }

    // temp->next = pL1Temp ? pL1Temp : pL2Temp; // 使用条件表达式

    // Deinit_L(&LL1); // 释放头结点内存
    // Deinit_L(&L2);
    return mergedList;
}



//链表测试函数
void linklist_test()
{
//    Node node; //头节点, 数据域不保存数据, 可以选择保存链表长度之类的
//    LinkList head = &node; //pointer, size = 4; 指向 "头节点" 的指针
    // Node head, node1, node2, node3; // struct Node, size = 8, printf("%d - %d", sizeof head, sizeof(node));
    ElemType data;

    // head.next = &node1;
    // node1.data = 1;
    // node1.next = &node2;
    // node2.data = 2;
    // node2.next = &node3;
    // node3.data = 3;
    // node3.next = NULL;

    size_t listSize = 10;
    size_t index = 5;
    LinkList head;
    // head = InitHeadInsert_L(listSize); //使用头节点的方式初始化链表
    head = InitTailInsert_L(listSize);

    Traverse_L(head);

    GetElem_L(head, 5, &data);
    // printf("linklist[%d] = %d\n", index, data); // 为什么这里一打印就出问题，有意思？？？？？？？？？？？？？？？？？
    // printf("abc\n");
    // for(int ix = 0; ix < 4; ++ix){
    //     printf("data = %d\n", data);
    // }

    Insert_L(head, index, 1000);
    Traverse_L(head);
    // printf("data = %d\r\n", data); // 为什么中间不可以打印东西????????????????????????????????????

    Delete_L(head, 6);
    Traverse_L(head);

    Deinit_L(head);
    printf("deinit linklist\n");

    Traverse_L(head);

}

void LinkListTest2()
{
    LinkList pList; // Node * pList;
    ElemType arr[5] = {5, 7, 22, 111, 3};

    InitLinkListWithArray_L(&pList, arr, sizeof(arr)/sizeof(arr[0]));
    printf("get address:%#p\n", pList);
    printf("init:\r\n");
    Traverse_L(pList);

    Insert_L(pList, 22, 99);
    printf("insert:99\r\n");
    Traverse_L(pList);

    Delete_L(pList, 111);
    printf("delete:111\r\n");
    Traverse_L(pList);

//    printf("arg:%#p\n", pList);
    Clear_L(pList);
    printf("clear\r\n");
    Traverse_L(pList);

    InserHead_L(pList, 1234);
    printf("insert head node:1234\r\n");
    Traverse_L(pList);

    InsertTail_L(pList, 4568);
    printf("insert tail node:4568\r\n");
    Traverse_L(pList);

    Deinit_L(&pList);
    printf("deinit\r\n");
    Traverse_L(pList);
}

void LinkListTest3()
{
    LinkList L1, L2, L3;
    ElemType arr1[] = {5, 7, 22, 111};
    ElemType arr2[] = {3, 4, 57, 487};
    InitLinkListWithArray_L(&L1, arr1, 4);
    InitLinkListWithArray_L(&L2, arr2, 4);
    Traverse_L(L1);
    Traverse_L(L2);

    printf("merge:\r\n");
    // L3 = MergeLinkList_L(L1, L2);
    L3 = MergeLinkList_L_v2(L1, L2);
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
    Traverse_L(L3);
}
#endif
