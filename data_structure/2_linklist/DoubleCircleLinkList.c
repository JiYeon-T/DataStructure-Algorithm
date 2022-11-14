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
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>


/**
 * @brief 包含头结点
 *        空链表, 仅有头结点
 *
 * @param dcl
 * @return Status
 */
Status InitLinkList_DCL(LinkList_DCL_v2 *dcl)
{
    if(!dcl){
        return ERROR;
    }
    // head node
    Node_DCL *pHead = (Node_DCL*)malloc(sizeof(Node_DCL) * 1);
    if(!pHead){
        return ERROR;
    }
    pHead->data = INT_MAX;
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
Status TraverseNext_DCL(const LinkList_DCL_v2 *dcl)
{
    if(!dcl){
        return ERROR;
    }

    Node_DCL *temp = dcl->pHead->next;

    printf("next traverse:\r\n");
    while(temp != dcl->pHead){
        printf("%d <=> ", temp->data);
        temp = temp->next;
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
Status TraversePrev_DCL(const LinkList_DCL_v2 *dcl)
{
    if(!dcl){
        return ERROR;
    }

    // 尾部没有多余的结点
    Node_DCL *temp = dcl->pTail;

    printf("prev traverse:\r\n");
    while(temp->prev != dcl->pTail){
        printf("%d <=> ", temp->data);
        temp = temp->prev;
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
    if(!pNode){
        return ERROR;
    }
    Node_DCL *temp = (Node_DCL*)malloc(sizeof(Node_DCL) * 1);
    if(!temp){
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
    if(!pNode){
        return ERROR;
    }

    free(pNode);

    return OK;
}

/**
 * @brief get node
 *
 * @param dcl
 * @param idx
 * @param[out] pNode
 * @return Status
 */
Status GetNode_DCL(const LinkList_DCL_v2 *dcl, size_t idx, Node_DCL **pNode)
{
    // 短路法则
    if(!dcl || !pNode || idx >= dcl->len){
        return ERROR;
    }

    Node_DCL * temp = dcl->pHead->next;
    size_t jx = 0;

    while (jx < idx && temp != NULL)
    {
        temp = temp->next;
        ++jx;
    }

    if(jx > idx || !temp){
        return ERROR;
    }

    *pNode = temp;

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
    if(!dcl || !pNode || !pInsert){
        return ERROR;
    }

    // empty linklist(only have a head node):pNode = dcl->pHead;
    // 传入的为头指针
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

    Node_DCL *prev = pNode->prev;

    pInsert->next = pNode;
    pInsert->prev = pNode->prev;
    // 为什么双重解引用会报错: dereferencing pointer to incomplete type 'struct Node_DCL'
    // pNode->prev->next = pInsert;
    prev->next = pInsert;
    pNode->prev = pInsert;

    // 只要在头指针前插入, 就要更新尾指针(因为是循环链表)
    if(pNode == dcl->pHead){
        // update tail ndoe
        dcl->pTail = pInsert;
    }
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

void test_DCL()
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
