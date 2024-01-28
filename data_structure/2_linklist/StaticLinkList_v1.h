#ifndef __STATIC_LINK_LIST_H__
#define __STATIC_LINK_LIST_H__
#include "config.h"


// 静态链表(对于不支持指针的语言,可以使用静态链表)
// 缺点: 长度难以控制
#if defined(STATIC_LINK_LIST_V1) && (STATIC_LINK_LIST_V1 == 1)

#define MAXSIZE 10
typedef int ElemType;

typedef struct {
    ElemType data;
    size_t cur; // 游标, 为 0 时无指向
} Node, StaticLinkList[MAXSIZE];


static int Malloc_SLL(StaticLinkList space);
static void Free_SLL(StaticLinkList space, int idx);
Status ListInit(StaticLinkList space);
Status ListInsert(StaticLinkList space, int i, ElemType e);
Status ListDelete(StaticLinkList space, int idx, ElemType *e);
int ListLength(StaticLinkList space);
Status Traverse(StaticLinkList space, const char *p_op_info);
Status LocateElem_SL(StaticLinkList, ElemType e, int *idx);
void static_link_list_test(void);


#endif // end STATIC_LINK_LIST_V1
#endif