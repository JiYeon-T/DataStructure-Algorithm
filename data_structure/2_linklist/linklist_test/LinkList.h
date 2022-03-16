#ifndef LINKLIST_H_INCLUDED
#define LINKLIST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int ElemType;
typedef int Status;
#define OK      1
#define ERROR   0
typedef unsigned int size_t;

//链表
typedef struct
{
    ElemType data;
    struct Node *next;
} Node, *LinkList;

//有/无头节点两种情况



#endif // LINKLIST_H_INCLUDED
