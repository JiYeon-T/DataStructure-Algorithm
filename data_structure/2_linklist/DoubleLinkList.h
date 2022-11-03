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
#include "LinkList.h"

// 是否包含头指针的双向链表
#define WITHOUT_TAIL_POINTER   0


// v1:操作几乎和单向链表一致, 仅仅有小部分区别
typedef struct DoubleLinkList
{
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



#if WITHOUT_TAIL_POINTER
void DoubleListTest();
#else // #ifdef WITHOUT_TAIL_POINTER
void DoubleListTest_v2();
#endif // #ifdef HAVE_TAIL_POINTER

#endif
