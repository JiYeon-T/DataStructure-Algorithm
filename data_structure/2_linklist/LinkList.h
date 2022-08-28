#ifndef LINKLIST_H_INCLUDED
#define LINKLIST_H_INCLUDED


#include "head.h"
#define LINK_LIST     1
#if LINK_LIST

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/** �� ���� **/
// Ŀǰ�� type �����������һ������, ���ʵ�ֱ���������������?
/** Ӧ�ó��� **/
// (1)app app queue �����ʵ�ֵ�?
// (2) ͨ���ṹ��Ԫ�ػ�ȡ�ṹ������Ԫ�ص�ַ, service_bt_list.c
typedef int ElemType;
typedef int Status;
#define OK      1
#define ERROR   0
typedef unsigned int size_t;

//����
typedef struct
{
    ElemType data;      // ������
    struct Node *next;  // ָ����
} Node, *LinkList;

//��/��ͷ�ڵ��������

/* ��ͷ�ڵ� */
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
