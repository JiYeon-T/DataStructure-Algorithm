#ifndef LINEARLIST_H_INCLUDED
#define LINEARLIST_H_INCLUDED

#include "head.h"

//#define LINEAR_LIST     1
#if LINEAR_LIST

#include <stdio.h>
#include <stdbool.h>

// 线性表的顺序存储方式, 顺序存储的线性表(顺序表)
// 实现方法:
// (1) 数组(地址连续);
// (2) 动态分配内存, malloc(), 地址也是连续的0  ;


typedef int Status;
typedef int ElemType;
#define OK              1
#define ERROR           0


typedef struct{
//    ElemType elem[ElemSize];
    ElemType *elem;
    // 也可以使用堆内存, 也是连续的: ElemType *elem;
    int curLength; // 当前使用长度
    int listSize; // 当前分配的总大小, 单位:sizeof(ElemType)
} LList;

// 定义一个函数指针, 用来定位元素
// 某两个元素, 满足某一种关系的位置
typedef bool (*pCompare)(ElemType a, ElemType b);

Status InitList_L(LList *L);
Status DestroyList_L(LList *L);
Status CLearList_L(LList *L);
bool ListIsEmpty_L(const LList *L);
size_t ListLength_L(const LList *L);
Status GetElem_L(const LList *L, size_t idx, ElemType *val);
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

#endif //LINEAR_LIST

#endif // LINEARLIST_H_INCLUDED
