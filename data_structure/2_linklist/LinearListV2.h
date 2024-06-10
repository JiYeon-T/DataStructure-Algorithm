#ifndef __LINEARLISTV2_H__
#define __LINEARLISTV2_H__
#include <stdbool.h>

#include "util.h"
#include "build_config.h"

// 线性列表(顺序存储列表), 
// 与 LinearList_v1 相比,只不过使用动态分配内存(堆内存)

#if defined(DataStructLinearListV2) && (DataStructLinearListV2 == 1)

#define DEFAULT_LIST_SIZE       (20)
#define LIST_INCREMENT_SIZE     (20)
#define OVERFLOW                (-1)

// ���Ա���˳��洢��ʽ, ˳��洢�����Ա�(˳���)
// ʵ�ַ���:
// (1) ����(��ַ����);
// (2) ��̬�����ڴ�, malloc(), ��ַҲ��������0  ;

typedef int ElemType;


typedef struct{
    ElemType *elem;
    int curLength; // 当前  
    int listSize; // 总容量
} SqList;


Status InitList(SqList *L);
Status DestroyList(SqList *L);
Status ClearList(SqList *L);
bool ListEmpty(const SqList *L);
size_t ListLength(const SqList *L);
Status GetElem(const SqList *L, int i, ElemType *e);
Status SetElem(SqList *L, int i, ElemType e);
Status PutElem(SqList *L, ElemType e);
int LocateElem(const SqList *L, ElemType e, 
                bool (*comp_fun)(ElemType val1, ElemType val2));
Status PriorElem(const SqList *L, ElemType cur_e, ElemType *prev_e);
Status NextElem(const SqList *L, ElemType cur_e, ElemType *next_e);
Status ListInsert(SqList *L, int i, ElemType e);
Status ListDelete(SqList *L, int i, ElemType *e);
Status ListTraverse(SqList *L, void (*visit_fun)(ElemType e));

Status ListBubbleSort(SqList *L);
Status UnionList(SqList *La, SqList *Lb);
Status MergeList(const SqList *La, const SqList *Lb, SqList **Lc);

void LinearListV2Test(void);
void LinearListV2Test2(void);


#endif // LINEARLIST_H_INCLUDED


#endif