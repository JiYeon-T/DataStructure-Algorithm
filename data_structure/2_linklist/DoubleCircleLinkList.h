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

#include "config.h"
#include "LinkList.h"

// 节点
typedef struct 
{
    ElemType data;
    struct Node_DCL *prev;
    struct Node_DCL *next;
} Node_DCL, *LinkList_DCL;

// 保存头, 尾指针链表
typedef struct 
{
    LinkList_DCL pHead, pTail;
    size_t len;
} LinkList_DCL_v2;


Status InitLinkList_DCL(LinkList_DCL_v2 *dcl);
Status TraverseNext_DCL(const LinkList_DCL_v2 *dcl);
Status TraversePrev_DCL(const LinkList_DCL_v2 *dcl);


void test_DCL();

#endif