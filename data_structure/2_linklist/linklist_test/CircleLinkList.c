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

/**
 * @brief 初始化循环链表(没有头节点)
 *        尾插法(如果没有头节点的链表就需要两个指针一个头指针, 一个尾指针，否则每次创建都要遍历)
 * @param head 头指针
 * @param size 链表大小
 */
LinkList_CL Init_CL(size_t size)
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

    for(size_t ix = 0; ix < size-1; ++ix){
        //修改头指针的值 head
        LinkList_CL temp = (LinkList_CL)malloc(sizeof(Node_CL) * 1);
        temp->data = data++;
        temp->next = pHead;
        pTail->next = temp;
        pTail = temp;
    }

    return pHead;
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
    head = Init_CL(listSize);
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