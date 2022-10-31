#ifndef LINEARLIST_H_INCLUDED
#define LINEARLIST_H_INCLUDED

#include "config.h"
//#define LINEAR_LIST     1
// #if LINEAR_LIST

#include <stdio.h>
#include <stdbool.h>

// ���Ա���˳��洢��ʽ, ˳��洢�����Ա�(˳���)
// ʵ�ַ���:
// (1) ����(��ַ����);
// (2) ��̬�����ڴ�, malloc(), ��ַҲ��������0  ;


typedef int Status;
typedef int ElemType;
#define OK              1
#define ERROR           0


typedef struct{
//    ElemType elem[ElemSize];
    ElemType *elem;
    // Ҳ����ʹ�ö��ڴ�, Ҳ��������: ElemType *elem;
    int curLength; // ��ǰʹ�ó���
    int listSize; // ��ǰ������ܴ�С, ��λ:sizeof(ElemType)
} LList;

// ����һ������ָ��, ������λԪ��
// ĳ����Ԫ��, ����ĳһ�ֹ�ϵ��λ��
typedef bool (*pCompare)(ElemType a, ElemType b);

Status InitList_L(LList *L);
Status DestroyList_L(LList *L);
Status CLearList_L(LList *L);
bool ListIsEmpty_L(const LList *L);
size_t ListLength_L(const LList *L);
Status GetElem_LL(const LList *L, size_t idx, ElemType *val);
Status SetElem_L(LList *L, size_t idx, ElemType val);
size_t LocateElem_L(const LList *L, ElemType e, pCompare fun);
Status PriorElem_L(const LList *L, ElemType cur, ElemType *prior);
Status NextElem_L(const LList *L, ElemType cur, ElemType *next);
Status ListInsert_L(LList *L, size_t idx, ElemType val);
Status ListDelete_L(LList *L, size_t idx, ElemType *val);
Status ListTraverse_L(const LList *L);

Status ListSort_L(LList *L);
Status UnionList_L(const LList *L1, const LList *L2);
void MergeList_L(const LList *L1, const LList *L2);

void ListTest_L();

// #endif //LINEAR_LIST

#endif // LINEARLIST_H_INCLUDED
