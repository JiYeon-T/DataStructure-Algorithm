#ifndef LINKLIST_V4_H_INCLUDED
#define LINKLIST_V4_H_INCLUDED


#include "util.h"
#include "build_config.h"

// 有头节点的单向链表
// 定义通用的 ElemType 类型, 以及 ElemType 的遍历方法, 用于 ElemType 是结构体之类的其他链表使用
// TODO:

#if defined(DataStructLinkListV4) && (DataStructLinkListV4 == 1)
#include <time.h>

// 多项式的计算
#if defined(DATA_STRUCTURE_POLYNOMAIL) && (DATA_STRUCTURE_POLYNOMAIL == 1)
typedef struct {
    float coef; // 系数
    int expn; // 指数
} term; // 两个类型名:term 用于 ADT; ElemType 用于 LinkList 数据类型
#define ElemType    term
#endif

// 有头节点
// 带有头节点的链表的插入/删除第一个节点的操作与操作与对其他节点的插入删除操作一致，不需要特殊处理


// typedef int ElemType;
// typedef unsigned int size_t;
// #define ElemType    int

#ifndef ElemType
#error "ElemType not defined"
#define ElemType                int
// #define INVALID_VAL
// #define INITIALIZE_ELEM(elem)   memset()
#endif



//链表
typedef struct {
    ElemType data;      // 数据域
    struct Node *next;  // 指针域
} Node, *LinkList;
// typedef Node* LinkList;

typedef void (*print_node_info_fun)(Node *pNode); // print node information
typedef int (*compare_t)(ElemType a, ElemType b); // 满足交换要求返回 true, 不满足返回 false;比较两个元素的值，例如: 从小到大排序:a <= b,返回 0; a>b 返回 1, 需要交换

typedef enum {
    FROM_SMALL_TO_BIG,
    FROM_BIG_TO_SMALL
} SORT_TYPE_E;

typedef int position_t; // 节点位置


void struct_member_size_test(void);
Status InitLinkList(LinkList *ll);
Status InitLinkListWithArray(LinkList *L, ElemType *pArr, size_t len);
Status Traverse(const LinkList L, char *p_op_info, print_node_info_fun p_print_node_fun);
Status GetElem(const LinkList L, int i, ElemType *e);
Status LocateElem(const LinkList L, ElemType nodeVal, position_t *pos, compare_t pCompareFun);
Status OrderInsert(LinkList *L, ElemType nodeVal, compare_t pCompareFun);
Status LinkListLength(const LinkList ll, size_t *pLen);
Status InsertBeforePosIdx(LinkList *L, size_t idx, ElemType *pElem);
Status InsertBeforeElem(LinkList L, ElemType *pElem, ElemType *pInsertElem);
Status InsertAtFirst(LinkList L, ElemType *pVal);
Status InsertAtTail(LinkList L, ElemType *pVal);
Status DeleteElem(LinkList L, ElemType *pDeleteVal);
Status DeleteByIdx(LinkList *L, size_t idx, ElemType *e);
Status MakeNode(Node **pNode, ElemType nodeVal);
Status FreeNode(Node **pNode);
Status DelFirst(LinkList L, Node **pDelNode);
Status Append(LinkList L, Node *pNew);
Status RemoveTail(LinkList L, Node **pDelNode);
Status InsertBefore(LinkList L, Node *p, Node *s);
Status InsertAfter(LinkList L, Node *p, Node *s);
Status SetCurrElem(LinkList L, Node *p, ElemType nodeNewVal);
Status GetCurrElem(LinkList L, Node *p, ElemType *pNode);
Status DeleteNode(LinkList L, Node **pDelete);
bool ListEmpty(LinkList L);

Status BubbleSortLinkList(LinkList L, compare_t pCompareFun);
Status ClearLinkList(LinkList L);
Status DeinitLinkList(LinkList *L);


void LinkListTest3(void);
void linklist_api_test4(void);
void LinkListTest5(void);
void LinkListTest6(void);
void LinkListTest7(void);
void LinkListTest8(void);

#endif // DataStructLinkListV4

#endif // LINKLIST_V4_H_INCLUDED
