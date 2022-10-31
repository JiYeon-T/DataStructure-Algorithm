/**
 * @file CircleLinkList.c
 * @author your name (you@domain.com)
 * @brief 首尾相连的链表, 循环终止条件变成了判断 temp->next!=head, 是否为头指针
 *        (1) 如果不适用头节点, 就需要使用 尾指针来保存 尾巴位置信息
 * @version 0.1
 * @date 2022-03-16
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "CircleLinkList.h"
#include <stdlib.h>
#include <time.h>
#include <limits.h>


/**
 * @brief 初始化循环链表(没有头节点)
 *        尾插法(如果没有头节点的链表就需要两个指针一个头指针, 一个尾指针，否则每次创建都要遍历)
 * @param head 头指针
 * @param size 链表大小
 */
LinkList_CL InitLinkListWithRandom_CL(size_t size)
{
    if(size <= 0){
        return ERROR;
    }
    int data = 0;
    LinkList_CL pHead = NULL, pTail = NULL;

    pHead = (LinkList_CL)malloc(sizeof(LinkList_CL) * 1);
    pHead->data = data++;
    pHead->next = pHead;
    pTail = pHead;
    srand(time(0));

    for(size_t ix = 0; ix < size-1; ++ix){
        //修改头指针的值 head
        LinkList_CL temp = (LinkList_CL)malloc(sizeof(Node_CL) * 1);
        temp->data = rand() % 100;
        temp->next = pHead;
        pTail->next = temp;
        pTail = temp;
    }

    return pHead;
}

Status InitLinkListWithArray_CL()
{

}

/**
 * @brief Traverse
 * @param[in] CL head pointer
 */
Status Traverse_CL(LinkList_CL CL)
{
    if(!CL){
        return ERROR;
    }
    LinkList curr = CL;

    while(curr->next != CL){ // 循环结束条件 temp->next 是否等于头指针
        printf("%d -> ", curr->data);
        curr = curr->next;
    }
    printf("%d\n", curr->data); // 打印最后一个节点的信息

    return OK;
}


/**
 * @brief 查找
 * @param[in] CL head pointer
 * @param[in] index start from 0
 * @param[out] *data
 */
Status GetElem_CL(LinkList_CL CL, size_t index, ElemType *data)
{
    if(!CL || index<0){
        return ERROR;
    }
    LinkList_CL curr = CL;
    size_t jx = 0;

    while(curr->next!=CL && jx<index){ // search node
        curr = curr->next;
        ++jx;
    }

    if(curr->next==CL || jx>index){ // index
        return ERROR;
    }
    *data = curr->data;

    return OK;
}


/**
 * @brief 删除节点
 *
 * @param[in] head
 * @param[in] nodeVal
 */
Status Delete_CL(LinkList_CL head, ElemType nodeVal)
{
    if(!head){
        return ERROR;
    }

    LinkList prev = NULL, cur = head;
    while(cur->next!=head && cur->data!=nodeVal){
        prev = cur;
        cur = cur->next;
    }

    if(cur->next == head){ // 要找的节点就是第一个节点的情况
        return ERROR;
    }

    prev->next = cur->next;
    free(cur);

    return OK;
}

/**
 * @brief 插入一个节点
 *
 * @param[in] head
 * @param[in] nodeVal 在 nodeVal 节点前插入 insertVal 节点
 * @param[in] insertVal
 */
Status Insert_CL(LinkList_CL head, ElemType nodeVal, ElemType insertVal)
{
    if(head == NULL){
        return OK;
    }

    LinkList_CL prev = NULL, curr = head;
    while(curr->next!=head && curr->data!=nodeVal){
        prev = curr;
        curr = curr->next;
    }

    if(curr->next == head){
        return ERROR;
    }

    LinkList_CL temp = (LinkList_CL)malloc(sizeof(Node_CL) * 1);
    temp->data = insertVal;
    temp->next = curr;
    prev->next = temp;

    return OK;
}

/**
 * @brief free heap memory
 *
 * @param head
 * @return Status
 */
Status Deinit_CL(LinkList_CL head)
{
    if(!head){
        return ERROR;
    }

    LinkList_CL curr = head;
    while(curr->next != head){  // 为什么有问题????????????????????????????
        LinkList temp = curr;
        curr = curr->next;
        free(temp);
    }

    // 处理最后一个节点
    free(curr);
    head = NULL;

    return OK;
}



void Test_CL()
{
    LinkList_CL head; // 指针没有成员变量的说法, 它本身就是一块内存的首地址而已
    size_t listSize = 10;
    ElemType data;
    // Node_CL node;
    // node.data = 111;
    // node.next = NULL;
    // head = &node; // head 指向 node
    // printf("%d - %d\n", sizeof(head), sizeof(Node_CL));
    // printf("head:%#p - &node:%#p, &head:%#p", head, &node, &head); // head的值就是 node 的首地址
    head = InitLinkListWithRandom_CL(listSize);
    Traverse_CL(head);

    Insert_CL(head, 4, 1000);
    Traverse_CL(head);

    Delete_CL(head, 8);
    Traverse_CL(head);

    GetElem_CL(head, 2, &data);
    printf("data = %d\n", data);

    Deinit_CL(head);
    // head = NULL;
    // printf("head val:%#X %#p",head, &head);
    Traverse_CL(head);
}

/************************************************* 包含头结点 ***************************************************************/
/**
 * @brief initialize a circle linklist
 *        包含头结点的循环链表, 头结点不包含数据
 *        循环结束条件; 尾结点的 next 指针是否等于头指针(头结点的地址)
 *
 * @param cl
 * @return Status
 */
Status InitLinkList_CL_v2(LinkList_CL *cl)
{
    if(!cl){
        return ERROR;
    }

    // create head node
    Node_CL *temp = (Node_CL*)malloc(sizeof(Node_CL) * 1);
    if(!temp){
        printf("No enough memory\r\n");
        return ERROR;
    }
    temp->data = INT_MAX;
    temp->next = temp;
    *cl = temp;

    return OK;
}

/**
 * @brief traverse
 *
 * @param cl head pointer, 头结点的地址
 * @return Status
 */
Status Traverse_CL_v2(LinkList_CL cl)
{
    if(!cl){
        return ERROR;
    }

    Node_CL *temp = cl->next;

    printf("Traverse:\r\n");
    while(temp != cl){
        printf("%d ->", temp->data);
        temp = temp->next;
    }
    printf("\r\n\r\n");

    return OK;
}

/**
 * @brief initialize circle linklist with array
 *
 * @param cl
 * @return Status
 */
Status InitWithArray_CL_v2(LinkList_CL cl, ElemType *arr, size_t len)
{
    if(!cl || !arr || len <= 0){
        return ERROR;
    }
    Node_CL *temp = cl->next;

    for(int ix = 0; ix < len; ++ix){
        // head/tail insert
    }

    return OK;
}

/**
 * @brief head insert
 *
 * @param cl
 * @param elem
 * @return Status
 */
Status InsertHead_CL_v2(LinkList_CL cl, ElemType elem)
{
    if(!cl){
        return ERROR;
    }

    Node_CL *temp = (Node_CL*)malloc(sizeof(Node_CL) * 1);
    temp->data = elem;
    temp->next = cl->next; // next node
    cl->next = temp; // update first node

    return OK;
}

/**
 * @brief tail insert
 *
 * @param cl
 * @param elem
 * @return Status
 */
Status InsertTail_CL_v2(LinkList_CL cl, ElemType elem)
{
    if(!cl){
        return ERROR;
    }

    Node *temp = cl->next, *prev = temp;

    while (temp != cl) // 结束条件 next != 头指针
    {
        prev = temp;
        temp = temp->next;
    }

    // allocate memory
    temp = (Node_CL*)malloc(sizeof(Node_CL) * 1);
    temp->data = elem;
    temp->next = cl; // head pointer
    prev->next = temp; // previous node's next poniter

    return OK;
}

/**
 * @brief remove the indexTh node 
 * 
 * @param cl 
 * @param index index from 0
 * @param elem 
 * @return Status 
 */
Status RemoveElem_CL_v2(LinkList_CL cl, size_t index, ElemType *elem)
{
    if(!cl || !elem || index < 0){
        return ERROR;
    }

    Node_CL *temp = cl->next, *prev = temp;
    size_t jx = 0;

    while(temp != cl && jx < index){
        prev = temp;
        ++jx;
        temp = temp->next;
    }

    if(temp == cl || jx > index){
        return ERROR;
    }

    *elem = temp->data;
    prev->next = temp->next; // update next pointer
    free(temp);

    return OK;
}

/**
 * @brief modify data
 * 
 * @param cl 
 * @param index index from 0
 * @param elem 
 * @return Status 
 */
Status ModifyElem_CL_v2(LinkList_CL cl, size_t index, ElemType elem)
{
    if(!cl || index < 0){
        return ERROR;
    }

    Node_CL *temp = cl->next;
    size_t jx = 0;
    while(temp != cl && jx < index){
        ++jx;
        temp = temp->next;
    }

    if(temp == cl || jx > index){
        return ERROR;
    }

    temp->data = elem;

    return OK;
}

/**
 * @brief get elem
 * 
 * @param cl 
 * @param index 
 * @param elem 
 * @return Status 
 */
Status GetElem_CL_v2(LinkList_CL cl, size_t index, ElemType *elem)
{
    if(!cl || index < 0 || !elem){
        return ERROR;
    }

    Node_CL *temp = cl->next;
    size_t jx = 0;
    while(temp != cl && jx < index){
        ++jx;
        temp = temp->next;
    }

    if(temp == cl || jx > index){
        return ERROR;
    }

    *elem = temp->data;

    return OK;
}

/**
 * @brief only clear data node
 *        does not free head node
 * 
 * @param cl 
 * @return Status 
 */
Status Clear_CL_v2(LinkList_CL cl)
{
    if(!cl){
        return ERROR;
    }

    Node_CL *curr = cl->next;

    while (curr != cl){
        Node_CL *temp = curr;
        cl->next = curr->next;
        curr = curr->next;
        free(temp); // free memory
    }
    
    return OK;
}

/**
 * @brief clear data node and head node
 * 
 * @param cl 
 * @return Status 
 */
Status Deinit_CL_v2(LinkList_CL *cl)
{
    if(!cl){
        return ERROR;
    }

    Node_CL *curr = (*cl)->next;

    // clear data list
    while (curr != (*cl)){
        Node_CL *temp = curr;
        (*cl)->next = curr->next;
        curr = curr->next;
        free(temp); // free memory
    }

    // clear head node
    free((*cl));
    *cl = NULL;

    return OK;
}



void Test2_CL()
{
    LinkList_CL cl; // 头指针
    ElemType data;
    size_t idx;

    InitLinkList_CL_v2(&cl);
    Traverse_CL_v2(cl);

    data = 111;
    printf("insert:%d\r\n", data);
    InsertHead_CL_v2(cl, data);
    Traverse_CL_v2(cl);

    data = 25;
    printf("insert:%d\r\n", data);
    InsertTail_CL_v2(cl, data);
    Traverse_CL_v2(cl);

    data = 100;
    printf("insert:%d\r\n", data);
    InsertHead_CL_v2(cl, data);
    Traverse_CL_v2(cl);
    
    idx = 1;
    RemoveElem_CL_v2(cl, idx, &data);
    printf("remove index:%d\r\n", idx);
    Traverse_CL_v2(cl);
    printf("removed data:%d\r\n\r\n", data);

    idx = 0;
    data = -100;
    printf("modify idx:%d val:%d\r\n", idx, data);
    ModifyElem_CL_v2(cl, idx, data);
    Traverse_CL_v2(cl);

    idx = 1;
    data = -200;
    printf("modify idx:%d val:%d\r\n", idx, data);
    ModifyElem_CL_v2(cl, idx, data);
    Traverse_CL_v2(cl);

    idx = 1;
    printf("get index:%d\r\n", idx);
    if(GetElem_CL_v2(cl, idx, &data) == OK){
        printf("data:%d\r\n", data);
    }
    Traverse_CL_v2(cl);

    idx = 2;
    printf("get index:%d\r\n", idx);
    if(GetElem_CL_v2(cl, idx, &data) == OK){
        printf("data:%d\r\n", data);
    }
    else{
        printf("get failed\r\n");
    }
    Traverse_CL_v2(cl);

    Clear_CL_v2(cl);
    printf("clear:\r\n");
    Traverse_CL_v2(cl);

    Deinit_CL_v2(&cl);
    printf("Deinit:\r\n");
    Traverse_CL_v2(cl);
}

// #endif
