#ifndef LINKLIST_V3_H_INCLUDED
#define LINKLIST_V_H_INCLUDED

#include "util.h"
#include "build_config.h"

// 没有头节点的单向链表

#if defined(DataStructLinkListV3) && (DataStructLinkListV3 == 1)
typedef int ElemType;

typedef struct {
    ElemType data;
    struct Node *next;
} Node;

typedef Node* LinkList;


Status InitLinkList(Node **p_first);
Status PutElem(Node **p_first, ElemType data);
Status InsertElemBeforeIdx(Node **p_first, size_t idx, ElemType data);
Status DeleteElem(Node **p_first, size_t idx, ElemType *p_data);
Status SetElem(Node *p_first, size_t idx, ElemType data);
Status GetElem(const Node *p_first, size_t idx, ElemType *p_data);
Status Traverse(const Node *p_first, const char *p_op_info);
void linklist_api_test_v3(void);

#endif // end LINK_LIST_V3

#endif