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
#include "LinkList.h"


typedef struct
{
    ElemType data;
    struct Node_CL *next;
} Node_CL, *LinkList_CL;
//typedef struct Node* CLinkList;


void Test_CL(void);
void Test2_CL(void);

#endif
