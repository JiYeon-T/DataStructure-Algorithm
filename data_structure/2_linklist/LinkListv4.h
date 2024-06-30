#ifndef __LINKLISTV4_H__
#define __LINKLISTV4_H__

#include "util.h"
#include "build_config.h"



// basic linklist ElemType use void *
// node memory allocate, free,compare all implement by upper layer who use these api
// NOTE:
// 该实现中 ElemType 指针指向一次性分配的内存, 不可以使用嵌套的指针
// 否则在 ClearList()/DestroyList() 时会内存泄漏

#if defined(DataStructLinkListV4) && (DataStructLinkListV4 == 1)


typedef void * ElemType;

typedef struct Node {
    struct Node *next;
    ElemType data; // data field:pointer type
} *Link, *Position;

typedef struct {
    struct Node *head;
    int len;
} LinkList;


Status MakeNode(struct Node **p, ElemType p_elem);
void FreeNode(struct Node *p);
void ClearNode(struct Node *p);


Status InitList(LinkList *L);
Status ClearList(LinkList *L);
Status DestroyList(LinkList *L);
Status InsFirst(LinkList *L, struct Node *s);
Status DelFirst(LinkList *L, struct Node **p_first);
Status Append(LinkList *L, struct Node *s);
Status RemoveTail(LinkList *L, struct Node **q);
Status InsBefore(LinkList *L, struct Node *p, struct Node *s);
Status InsAfter(LinkList *L, struct Node *p, struct Node *s);
Status SetCurrElem(struct Node *p, ElemType e);
ElemType GetCurrElem(const struct Node *p);
bool ListEmpty(const LinkList *L);
size_t ListLength(const LinkList *L);
Position GetHead(const LinkList *L);
Position GetLast(const LinkList *L);
Position PriorPos(const LinkList *L, const struct Node *p);
Position NextPos(const LinkList *L, const struct Node *p);
Status LocatePos(const LinkList *L, size_t i, const struct Node **p);
Position LocateElem(const LinkList *L, ElemType e, bool (*compare)(ElemType, ElemType));
Status ListTraverse(const LinkList *L, Status(*visit)(ElemType e));

/**
 * externsion api
*/
Status InitWithArray(LinkList *L, ElemType *elemArr, size_t arrSize);
Status InsertBefore(LinkList *L, struct Node *p, struct Node *s);
Status DeleteNode(LinkList *L, struct Node *p);
struct Node * NexPos(LinkList *L, struct Node *p);

void linklist_api_test_integer(void);
void linklist_api_integer_test2(void);
void linklist_api_test_string(void);


#endif //DataStructApplicationLinkList


#endif