#ifndef __LINEAR_LIST_V1_H__
#define __LINEAR_LIST_V1_H__


#include "util.h"
#include "build_config.h"

// 顺序存储列表结构(使用数组实现)
// 存储时间复杂度低
// 优点:
// 查找效率高, 适用于经常查询而很少插入/删除的场景
// 缺点:
// 不灵活
// 插入和删除效率低, 

#if defined(DataStructLinearListV1) && (DataStructLinearListV1 == 1)


#define MAXSIZE     100  // 列表中元素的最大个数

typedef int ElemType;
typedef bool (*comp_fun)(ElemType val1, ElemType val2);
typedef void (*visit_fun)(ElemType e);

typedef struct {
    ElemType data[MAXSIZE];
    int length; // 表中存储的元素个数,初始值为 0
} SqList; // Sequence list

Status InitList(SqList *L);
Status DestroyList(SqList *L);
Status ClearList(SqList *L);
bool ListEmpty(const SqList *L);
size_t ListLength(const SqList *L);
Status GetElem(const SqList *L, int i, ElemType *e);
Status SetElem(SqList *L, int i, ElemType e);
Status PutElem(SqList *L, ElemType e);
int LocateElem(const SqList *L, ElemType e, comp_fun comp);
Status PriorElem(const SqList *L, ElemType cur_e, ElemType *prev_e);
Status NextElem(const SqList *L, ElemType cur_e, ElemType *next_e);
Status ListInsert(SqList *L, int i, ElemType e);
Status ListDelete(SqList *L, int i, ElemType *e);
Status ListTraverse(SqList *L, visit_fun visit);

void UnionList(SqList *La, SqList *Lb);
void MergeList(const SqList *La, const SqList *Lb, SqList *Lc);


void LinearListV1Test(void);
void LinearListV1Test2(void);

#endif // DataStructLinkListV1

#endif
