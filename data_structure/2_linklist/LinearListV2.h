#ifndef __LINEARLISTV2_H__
#define __LINEARLISTV2_H__
#include <stdbool.h>

#include "util.h"
#include "build_config.h"

// 线性列表(顺序存储列表), 
// 与 LinearList_v1 相比,只不过使用堆内存

#if defined(DataStructLinearListV2) && (DataStructLinearListV2 == 1)


// ���Ա���˳��洢��ʽ, ˳��洢�����Ա�(˳���)
// ʵ�ַ���:
// (1) ����(��ַ����);
// (2) ��̬�����ڴ�, malloc(), ��ַҲ��������0  ;

typedef int ElemType;


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

void LinearListTest_L();


#endif // LINEARLIST_H_INCLUDED


#endif