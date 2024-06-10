#ifndef LINKLIST_V2_H_INCLUDED
#define LINKLIST_V2_H_INCLUDED


#include "util.h"
#include "build_config.h"

// 有头节点的单向链表
// :增 删 改 查

#if defined(DataStructLinkListV2) && (DataStructLinkListV2 == 1)


// 有头节点
// 带有头节点的链表的插入/删除第一个节点的操作与操作与对其他节点的插入删除操作一致，不需要特殊处理
typedef int ElemType;
// typedef unsigned int size_t;

//链表
typedef struct {
    ElemType data;      // 数据域
    struct Node *next;  // 指针域
} Node, *LinkList;
// typedef Node* LinkList;

Status InitLinkList(LinkList *L);
// LinkList InitHeadInsert(size_t size);
// LinkList InitTailInsert(size_t size);
// Status InitLinkListWithArray(LinkList *L, ElemType *pArr, size_t len);
Status DestroyLinkList(LinkList *L);
Status ClearLinkList(LinkList L);
bool ListEmpty(const LinkList L);
size_t ListLength(const LinkList L);
Status GetElem(const LinkList L, int i, ElemType *e);
size_t LocateElem(const LinkList L, ElemType e, bool (*compare)(ElemType, ElemType));
Status PriorElem(const LinkList L, ElemType cur_e, ElemType *prev_e);
Status NextElem(const LinkList L, ElemType cur_e, ElemType *next_e);
Status ListInsert(LinkList L, size_t idx, ElemType e);
Status ListDelete(LinkList L, size_t idx, ElemType *e);
Status ListTraverse(const LinkList L, void (*p_visit)(ElemType e));
// Status Traverse(const LinkList L, char *info);
// Status InsertBeforePosIdx(LinkList *L, size_t idx, ElemType elem);
// Status InsertBeforeElem(LinkList L, ElemType elem, ElemType insertElem);
// Status InsertAtFirst(LinkList L, ElemType data);
// Status InsertAtTail(LinkList L, ElemType data);
// Status DeleteElem(LinkList L, ElemType deleteElem);
// Status DeleteByIdx(LinkList *L, size_t idx, ElemType *e);

LinkList MergeSortedLinkListV1(LinkList L1, LinkList L2);
LinkList MergeSortedLinkListV2(LinkList L1, LinkList L2);


void linklist_api_test(void);
void linklist_api_test2(void);
void LinkListTest2(void);
void LinkListTest3(void);

#endif // LINK_LIST_V2

#endif // LINKLIST_H_INCLUDED
