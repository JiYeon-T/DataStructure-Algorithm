#ifndef __CIRCLE_LINK_LIST_H__
#define __CIRCLE_LINK_LIST_H__

#if CIRCLE_LINK_LIST

#include "LinkList.h"
typedef struct
{
    ElemType data;
    struct Node_CL *next;
} Node_CL, *LinkList_CL;
//typedef struct Node* CLinkList;

LinkList_CL Init_CL(size_t size);
Status Traverse_CL(LinkList_CL CL);
Status GetElem_CL(LinkList_CL CL, size_t index, ElemType *data);
Status Delete_CL(LinkList_CL head, ElemType nodeVal);
Status Insert_CL(LinkList_CL head, ElemType nodeVal, ElemType insertVal);
Status Deinit_CL(LinkList_CL head);

void Test_CL();

#endif // CIRCLE_LINK_LIST

#endif
