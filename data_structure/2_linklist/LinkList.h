#ifndef LINKLIST_H_INCLUDED
#define LINKLIST_H_INCLUDED

typedef int ElemType;
typedef int status;
#define OK      1
#define ERROR   0

//����
typedef struct
{
    ElemType data;
    struct Node *next;
} Node, *LinkList;

//��/��ͷ�ڵ��������



#endif // LINKLIST_H_INCLUDED
