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

#define HAVE_TAIL_POINTER 1 /* 链表数据结构中保存头尾指针 */
#if HAVE_TAIL_POINTER

typedef int ElemType;

typedef struct Node {
    ElemType data; // 数据域
    struct Node *prev; // 指向前驱节点
    struct Node *next; // 指向后继节点
} *Link, *Position;

typedef struct  {
    struct Node *head;  // Link pHead, pTail;
    struct Node *tail;
    size_t len;
} LinkList;


Status MakeNode(struct Node **p, ElemType e);
void FreeNode(struct Node *p);

Status InitList(LinkList *L);
Status ClearList(LinkList *L);
Status DestroyList(LinkList *L);
// Status InsFirst(struct Node *h, struct Node *s);
// Status DelFirst(struct Node *h, struct Node **p_first);
Status Append(LinkList *L, struct Node *s);
Status RemoveTail(LinkList *L, struct Node **q);
Status InsBefore(LinkList *L, struct Node *p, struct Node *s);
Status InsAfter(LinkList *L, struct Node *p, struct Node *s);
Status SetCurrElem(struct Node *p, ElemType e);
ElemType GetCurrElem(const struct Node *p);
bool ListEmpty(const LinkList *L);
size_t ListLength(const LinkList *L);
Position GetHead(const LinkList *L);
Position GetLast(const LinkList *L);
Position PriorPos(const LinkList *L, const struct Node *p);
Position NextPos(const LinkList *L, const struct Node *p);
Status LocatePos(const LinkList *L, size_t i, const struct Node **p);
Position LocateElem(const LinkList *L, ElemType e, bool (*compare)(ElemType, ElemType));
Status ListTraverse(const LinkList *L, Status(*visit)(ElemType e));
Status ListReverseTraverse(const LinkList *L, Status(*visit)(ElemType e));

void DoubleCircleListTest1(void);

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