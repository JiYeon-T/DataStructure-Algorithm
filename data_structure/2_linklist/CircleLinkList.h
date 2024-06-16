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

#include "util.h"
#include "build_config.h"

// 循环表(单向链表, 有头节点)
// 最后一个节点的指针域指向头节点
//逻辑简洁明了
// 判断标间变成了 p->next 是否等于 p_head


#if defined(DataStructCircleLinkList) && (DataStructCircleLinkList == 1)

typedef int ElemType;

typedef struct {
    ElemType data;
    struct Node_CL *next;
} Node_CL, *LinkList_CL;
//typedef struct Node* CLinkList;

Status InitCL(Node_CL **cl);
Status ClearCL(LinkList_CL cl);
Status DestroyCL(LinkList_CL *cl);
Status TraverseCL(const LinkList_CL cl, const char *p_info);
Status InitWithArrayCL(Node_CL **cl, ElemType *pArr, size_t len);
Status InsertHeadCL(LinkList_CL cl, ElemType elem);
Status InsertTailCL(LinkList_CL cl, ElemType elem);
Status RemoveByIdxCL(LinkList_CL cl, size_t idx, ElemType *elem);
Status ModifyByIdxCL(LinkList_CL cl, size_t idx, ElemType elem);
Status GetByIdxCL(const LinkList_CL cl, size_t idx, ElemType *elem);

// void Test_CL(void);
void TestCL(void);

#endif

#endif
