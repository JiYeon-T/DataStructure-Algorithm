/**
 * @file DoubleCircleLinkList.h
 * @author your name (you@domain.com)
 * @brief 双向循环链表
 * @version 0.1
 * @date 2022-11-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __DOUBLE_CIRCLE_LINKLIST_H__
#define __DOUBLE_CIRCLE_LINKLIST_H__

#include "util.h"
#include "build_config.h"

// 双向循环链表
// 除了保存头指针外, 还保存了尾指针,

// TODO: 
// (2) 保存尾指针的双向循环链表 & p37 定义的方法都还没有实现;
// #define HAVE_TAIL_POINTER 1


#if defined(DOUBLE_CIRCLE_LINKLIST) && (DOUBLE_CIRCLE_LINKLIST == 1)

#define HAVE_TAIL_POINTER       0

typedef int ElemType;

typedef struct {
    ElemType data;
    struct Node_DCL *prev;
    struct Node_DCL *next;
} Node_DCL, *LinkList_DCL;

#if HAVE_TAIL_POINTER
// 保存头, 尾指针链表
typedef struct  {
    // LinkList_DCL pHead, pTail;
    Node_DCL *pHead, *pTail;
    size_t len;
} LinkList_DCL_v2;

Status InitLinkList_DCL(LinkList_DCL_v2 *dcl);
Status TraverseNext_DCL(const LinkList_DCL_v2 *dcl);
Status TraversePrev_DCL(const LinkList_DCL_v2 *dcl);

#else
Status InitLinkList_DCL(Node_DCL **dcl);
Status TraverseNext_DCL(const Node_DCL *dcl, const char *pInfo);
Status TraversePrev_DCL(const Node_DCL *dcl, const char *pInfo);
Status InsertHead_DCL(Node_DCL *dcl, ElemType data);
Status InsertTail_DCL(Node_DCL *dcl, ElemType data);
Status GetElem_DCL(Node_DCL *dcl, size_t idx, ElemType *pData);
Status SetElem_DCL(Node_DCL *dcl, size_t idx, ElemType *pData);
Status InsertBefore_DCL(Node_DCL *dcl, size_t idx, ElemType *pData);
Status RemoveElem_DCL(Node_DCL *dcl, size_t idx, ElemType *pData);
Status GetHead_DCL(Node_DCL *dcl, Node_DCL **pHead);
Status GetTail_DCL(Node_DCL *dcl, Node_DCL **pTail);
Status GetNode_DCL(Node_DCL *dcl, size_t idx, Node_DCL **pNode);
Status ClearLinkList_DCL(Node_DCL *dcl);
Status DeinitLinkList_DCL(Node_DCL *dcl);

void LinkListTest_DCL2(void);
#endif



#endif
#endif