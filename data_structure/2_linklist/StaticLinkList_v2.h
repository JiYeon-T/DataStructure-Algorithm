#ifndef __STATIC_LINK_LIST_H__
#define __STATIC_LINK_LIST_H__

#include "config.h"

// 废弃

#if STATIC_LINK_LIST_V2
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "LinearList_v1.h"


#define MAXSIZE          100
typedef int ElemType;


typedef struct {
    ElemType data;      // 数据域
    size_t next;   // 指针域:通过数组下标(索引/cursor), 起到指针的作用, 指向链表下一个节点
} Node, LinkList[MAXSIZE]; // 结构体数组
// typedef component[MAXSIZE] SLinkList;
// SLinkList sl; // 相当于 component sl[10];





void test_SL();
void SL_test2();

#endif // STATIC_LINK_LIST
#endif
