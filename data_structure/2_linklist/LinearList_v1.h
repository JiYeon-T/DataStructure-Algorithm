#ifndef __LINEAR_LIST_V1_H__
#define __LINEAR_LIST_V1_H__
#include "config.h"

// 顺序存储列表
// 存储时间复杂度低
// 插入和删除效率低, 适用于经常查询而很少插入/删除的场景

#if defined(DataStructLinearListV1) && (DataStructLinearListV1 == 1)


#define MAXSZIE     20  // 列表中元素的最大个数

typedef int ElemType;


typedef struct {
    ElemType data[MAXSZIE];
    int length; // 表中存储的元素个数,初始值为 0
} SqList; // Sequence list

Status GetElem(const SqList *L, int i, ElemType *e);
Status SetElem(SqList *L, int i, ElemType e);
Status PutElem(SqList *L, ElemType e);
Status ListInsert(SqList *L, int i, ElemType e);
Status ListDelte(SqList *L, int i, ElemType *e);
void LinearListV1Test(void);

#endif // DataStructLinkListV1

#endif
