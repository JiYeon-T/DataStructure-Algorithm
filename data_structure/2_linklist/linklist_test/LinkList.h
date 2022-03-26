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

//����
typedef struct
{
    ElemType data;
    struct Node *next;
} Node, *LinkList;

//��/��ͷ�ڵ��������

/* ��ͷ�ڵ� */
//
LinkList InitHeadInsert_L(size_t size);
LinkList InitTailInsert_L(size_t size);
Status GetElem_L(LinkList L, int i, ElemType *e);
Status Insert_L(LinkList L, ElemType elem, ElemType insertElem);
Status Delete_L(LinkList L, ElemType deleteElem);
Status Deinit_L(LinkList L);
#endif // LINKLIST_H_INCLUDED
