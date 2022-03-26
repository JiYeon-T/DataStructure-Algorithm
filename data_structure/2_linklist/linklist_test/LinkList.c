#include "LinkList.h"


// 增 删 改 查

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

/**
* @fun: init liklist
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
* @fun: traverse linklist
* @param[in]  head pointer to head node
*/
Status Traverse_L(LinkList head)
{
    if(head == NULL){
        return ERROR;
    }

    Node *p_temp = head->next; // include a head node

    while(p_temp){
        printf("%d ->", p_temp->data);
        p_temp = p_temp->next;
    }
    printf("\n");

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
    LinkList p_temp = L->next; //first node
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
 * @brief LinkList insert
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
    LinkList prev = L, cur = L->next;
    LinkList pInsertNode = NULL;

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
    LinkList prev = L, cur = L->next;

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
* @fun: free heap memory , had head node
* @param[in]  L pointer to head node
* @retval Status
*/
Status Deinit_L(LinkList L)
{
    LinkList pTemp = L->next;
    LinkList pFree = NULL;

    while(pTemp != NULL){
        pFree = pTemp;
        pTemp = pTemp->next;
        free(pFree);
    }

    return OK;
}


