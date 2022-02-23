#ifndef LINKLIST_H_INCLUDED
#define LINKLIST_H_INCLUDED

typedef int ElemType;
typedef int status;
#define OK      1
#define ERROR   0

//链表
typedef struct
{
    ElemType data;
    struct Node *next;
} Node, *LinkList;

//有/无头节点两种情况



#endif // LINKLIST_H_INCLUDED
