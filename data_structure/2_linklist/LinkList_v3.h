#ifndef LINKLIST_V3_H_INCLUDED
#define LINKLIST_V_H_INCLUDED

#include "util.h"
#include "build_config.h"

// 没有头节点的单向链表
// 插入/删除第一个节点/最后一个节点的情况稍微复杂一点点, 需要特殊处理
// TODO:
// 翻转链表

#if defined(DataStructLinkListV3) && (DataStructLinkListV3 == 1)
typedef int ElemType;

typedef struct {
    ElemType data;
    struct Node *next;
} Node, *LinkList;
// typedef Node* LinkList;


Status InitLinkList(LinkList *L);
Status DestroyLinkList(LinkList *L);
Status ClearLinkList(LinkList *L);
bool ListEmpty(const LinkList L);
size_t ListLength(const LinkList L);
Status GetElem(const LinkList L, int i, ElemType *e);
size_t LocateElem(const LinkList L, ElemType e, bool (*compare)(ElemType, ElemType));
Status PriorElem(const LinkList L, ElemType cur_e, ElemType *prev_e);
Status NextElem(const LinkList L, ElemType cur_e, ElemType *next_e);
Status ListInsert(LinkList *L, size_t idx, ElemType e);
Status ListDelete(LinkList *L, size_t idx, ElemType *e);
Status ListTraverse(const LinkList L, void (*p_visit)(ElemType e));

// Status PutElem(Node **p_first, ElemType data);
// Status InsertElemBeforeIdx(Node **p_first, size_t idx, ElemType data);
// Status DeleteElem(Node **p_first, size_t idx, ElemType *p_data);
// Status SetElem(Node *p_first, size_t idx, ElemType data);
// Status GetElem(const Node *p_first, size_t idx, ElemType *p_data);
// Status Traverse(const Node *p_first, const char *p_op_info);
void linklist_api_test(void);
void linklist_api_test2(void);

#endif // end LINK_LIST_V3

#endif