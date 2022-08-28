#ifndef __DOUBLE_LINK_LIST_H__
#define __DOUBLE_LINK_LIST_H__

#if DOUBLE_LINK_LIST

#include "LinkList.h"

typedef struct DoubleLinkList
{
    ElemType data;
    struct Node_D *next;
    struct Node_D *prior;
} Node_D, *LinkList_D; // double linklist

// functons
void Init_D(LinkList_D *DL, size_t size);
Status Traverse_D(LinkList_D *DL);
Status GetElem_D(LinkList_D *DL, size_t index);


void DoubleListTest();
#endif //DOUBLE_LINK_LIST

#endif
