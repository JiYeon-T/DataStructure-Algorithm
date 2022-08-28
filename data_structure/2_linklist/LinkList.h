#ifndef LINKLIST_H_INCLUDED
#define LINKLIST_H_INCLUDED


#include "head.h"
#define LINK_LIST     1
#if LINK_LIST

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/** 二 链表 **/
// 目前的 type 仅仅保存的是一个整型, 如何实现保存其他数据类型?
/** 应用场景 **/
// (1)app app queue 是如何实现的?
// (2) 通过结构体元素获取结构体其他元素地址, service_bt_list.c
typedef int ElemType;
typedef int Status;
#define OK      1
#define ERROR   0
typedef unsigned int size_t;

//链表
typedef struct
{
    ElemType data;      // 数据域
    struct Node *next;  // 指针域
} Node, *LinkList;

//有/无头节点两种情况

/* 有头节点 */
LinkList InitHeadInsert_L(size_t size);
LinkList InitTailInsert_L(size_t size);
Status InitLinkListWithArray_L(LinkList *pHead, ElemType *pArr, size_t len);
Status GetElem_L(LinkList L, int i, ElemType *e);
Status Insert_L(LinkList L, ElemType elem, ElemType insertElem);
Status InserHead_L(LinkList L, ElemType data);
Status InsertTail_L(LinkList L, ElemType data);
Status Delete_L(LinkList L, ElemType deleteElem);
Status Clear_L(LinkList L);
Status Deinit_L(LinkList *L);
Status SortLinkList_L(LinkList L1);
Status MergeLinkList_L(LinkList L1, LinkList L2);

void linklist_test();
void LinkListTest2();

#endif // LINKLIST

#endif // LINKLIST_H_INCLUDED
