/**
 * @file DoubleLinkList.h
 * @author your name (you@domain.com)
 * @brief 双向链表
 * @version 0.1
 * @date 2022-11-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __DOUBLE_LINK_LIST_H__
#define __DOUBLE_LINK_LIST_H__

#include "config.h"

// 双向链表

#if defined(DataStructDoubleLinkListV1) && (DataStructDoubleLinkListV1 == 1)

#define HAVE_TAIL_POINTER   0


typedef int ElemType;
// v1:操作几乎和单向链表一致, 仅仅有小部分区别
typedef struct DoubleLinkList {
    ElemType data;
    struct Node_DL *prev;
    struct Node_DL *next;
} Node_DL, *LinkList_DL; // double linklist



/*********************************** 2.包含尾指针 ********************************************/
// v2:另一种写法:将头结点和尾节点都保存下来, 翻遍前向遍历以及后向遍历
typedef struct {
    LinkList_DL pHead, pTail; // pointer type:Node* pHead, Node *pTail;
    size_t len;
} LinkList_DL_v2;





#if HAVE_TAIL_POINTER
void DoubleListTest_v2();
#else

Status InitLinkList_DL(LinkList_DL *dl);
Status InitLinkListWithArray_DL(LinkList_DL *dl, ElemType *pArr, size_t len);
Status InsertHead_DL(LinkList_DL dl, ElemType data);
Status InsertTail_DL(LinkList_DL dl, ElemType data);
Status RemoveElem_DL(LinkList_DL dl, size_t idx, ElemType *data);
Status ModifyElem_DL(LinkList_DL dl, size_t idx, ElemType *data);
Status GetElem_DL(LinkList_DL dl, size_t idx, ElemType *pData);
Status GetNode_DL(LinkList_DL dl, size_t idx, Node_DL **pNode);
Status TraverseNext_DL(LinkList_DL dl, const char *pInfo);
Status Clear_DL(LinkList_DL dl);
Status Deinit_DL(LinkList_DL *dl);
void DoubleListTest(void);

#endif // #ifdef HAVE_TAIL_POINTER

#endif

#endif
