#ifndef __STATIC_LINK_LIST_H__
#define __STATIC_LINK_LIST_H__

#if STATIC_LINK_LIST

#include "LinkList.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXSIZE     100

typedef struct
{
    ElemType data;      // 数据域
    unsigned int cur;   // 起到指针的作用, 指向链表下一个节点的索引(数组下标)
} component, SLinkList[MAXSIZE]; // 结构体数组

//typedef component[MAXSIZE] SLinkList;
//SLinkList sl; // 相当于 component sl[10];

void InitSpace_SL();
Status InitLinkList_SL(SLinkList sl, size_t size);
void Traverse_SL(SLinkList sl);
Status LocateElem_SL(SLinkList sl, size_t index, component *elem);
Status RemoveELem_SL(SLinkList sl, size_t index, component *elem);
Status InsertElem_SL(SLinkList sl, size_t index, component elem);

void test_SL();

#endif // STATIC_LINK_LIST
#endif
