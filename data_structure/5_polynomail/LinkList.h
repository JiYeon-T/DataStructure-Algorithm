#ifndef LINKLIST_H_INCLUDED
#define LINKLIST_H_INCLUDED

// 用于控制打印格式
typedef void (*pPrintInfo)(void *p);

typedef struct
{
    float   coef; // 系数
    int     expn; // 指数
} ElemType;

typedef int Status;
#define OK      1
#define ERROR   0
typedef unsigned int size_t;


typedef struct 
{
    ElemType data;
    struct Node *next;
} Node, *LinkList;

Status InitLinkList(LinkList *l);
Status InitLinkListWithArray(LinkList *l, ElemType *arr, size_t len);
Status ClearLinkList(LinkList l);
Status DestroyLinkList(LinkList *l);
Status MakeNode(Node **pNode, ElemType data);
Status FreeNode(Node **pNode);
Status Traverse(const LinkList l, pPrintInfo printFun);
Status GetNode(const LinkList l, size_t idx, Node **pNode);
Status GetTailNode(const LinkList l, Node **pNode);
Status InsertBefore(LinkList l, size_t idx, ElemType data);
Status InsertAfter(LinkList l, size_t idx, ElemType data);
Status InsertTail(LinkList l, ElemType data);
Status InsertTailWithNode(LinkList l, Node *node);
Status ModifyNode(LinkList l, size_t idx, ElemType data);
Status DeleteNode(LinkList l, size_t idx);
Status LinkListLength(LinkList l, size_t *len);
Status LinkListAppend(LinkList l, LinkList listToAppend);

void LinkListTest();
void LinkListTest2();


#endif // LINKLIST_H_INCLUDED
