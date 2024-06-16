#ifndef __CIRCLE_LINKLIST_V2_H__
#define __CIRCLE_LINKLIST_V2_H__

#include "util.h"
#include "build_config.h"

// 循环链表
// 链表结构中增加尾指针(指向最后一个节点, 便于 merge 操作)以及链表长度
// 使用更加实用的一套 api 接口

#if defined(DataStructCircleLinkListv2) && (DataStructCircleLinkListv2 == 1)

typedef int ElemType;


typedef struct Node {
    ElemType data;
    struct Node *next;
} *Link, *Position;

typedef struct {
    struct Node *head, *tail; // 保存头指针呢以及尾指针, struct Node *类型
    // Link head, tail;
    int len; // 链表中元素个数
} LinkList;



Status MakeNode(struct Node **p, ElemType e);
void FreeNode(struct Node *p);

Status InitList(LinkList *L);
Status ClearList(LinkList *L);
Status DestroyList(LinkList *L);
// Status InsFirst(struct Node *h, struct Node *s);
// Status DelFirst(struct Node *h, struct Node **p_first);
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

Status MergeListV1(const LinkList *La, const LinkList *Lb, LinkList *Lc, bool (*compare)(ElemType, ElemType));
Status MergeListV2(const LinkList *La, const LinkList *Lb, LinkList *Lc);

void CircleListTest1(void);
void CircleListTest2(void);
void CircleListTest3(void);

#endif /* DataStructCircleLinkListv2 */
#endif