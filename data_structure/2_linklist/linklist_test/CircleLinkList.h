#ifndef __CIRCLE_LINK_LIST_H__
#define __CIRCLE_LINK_LIST_H__

#include "LinkList.h"
typedef struct 
{
    ElemType data;
    struct Node_CL *next;
} Node_CL, *CLinkList;
//typedef struct Node* CLinkList;

void Init_CL(CLinkList head, size_t size);
void Test_CL();

#endif