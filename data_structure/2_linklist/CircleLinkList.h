/**
 * @file CircleLinkList.h
 * @author your name (you@domain.com)
 * @brief 循环链表
 * @version 0.1
 * @date 2022-10-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __CIRCLE_LINK_LIST_H__
#define __CIRCLE_LINK_LIST_H__

#include "config.h"

// 循环表(单向链表, 包含头节点)
// 最后一个节点的指针域指向头节点

#if defined(CIRCLE_LINK_LIST) && (CIRCLE_LINK_LIST == 1)

typedef int ElemType;

typedef struct
{
    ElemType data;
    struct Node_CL *next;
} Node_CL, *LinkList_CL;
//typedef struct Node* CLinkList;

Status InitCircleLinkListV2(Node_CL **cl);
Status TraverseCLV2(LinkList_CL cl, const char *p_info);
Status InitWithArrayCLV2(Node_CL **cl, ElemType *pArr, size_t len);
Status InsertHeadCLV2(LinkList_CL cl, ElemType elem);
Status InsertTailCLV2(LinkList_CL cl, ElemType elem);
Status RemoveElemByIdxCLV2(LinkList_CL cl, size_t idx, ElemType *elem);
Status ModifyElemCLV2(LinkList_CL cl, size_t idx, ElemType elem);
Status GetElemCLV2(LinkList_CL cl, size_t idx, ElemType *elem);
Status ClearCLV2(LinkList_CL cl);
Status DeinitCLV2(LinkList_CL *cl);

void Test_CL(void);
void CircleLinkListTestV2(void);

#endif

#endif
