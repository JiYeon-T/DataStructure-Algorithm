#ifndef __APP_LINKLIST_H__
#define __APP_LINKLIST_H__


#include "util.h"
#include "build_config.h"

#include <time.h>


// 链表(使用单向链表举例)的使用方法:
// 有头节点的单向链表
// 定义通用的 ElemType 类型, 以及 ElemType 的遍历方法, 用于 ElemType 是结构体之类的其他链表使用
// 带有头节点的链表的插入/删除第一个节点的操作与操作与对其他节点的插入删除操作一致，不需要特殊处理
// 代码逻辑相对简洁, 一般使用有头节点的方式


// 定义通用 ElemType 的两种方式:
// 法1. 定义指针包含到 struct Node 数据结构中(linklist node include element)
// 数据域使用 void * 类型的指针, 而不是下面的这种方式
#if defined(V1)
typedef struct {
    Node *next; //指针域
    void *p_data; // 数据域部分, 数据域可以使用不同的数据类型
    int len;
    /* other member */
} Node, *LinkList;

// 另一种写法
// typedef struct {
//     Node *next;
//     int data[]; // 不占用实际内存, 使用的时候为该地址分配多少内存, 就是多少
// } Node; // 结构体的 size = 指针的 size, 8
#endif

// 法2:
// 链表节点不包含数据域(element include linklist node)
// 更通用的方法, 直接将链表节点包含到数据结构中, 通过 container_of() 获取结构体
#if defined(V2)
struct {
    Node *prev;
    Node *next;
} Node, *LinkList;

typedef struct {
    // 将链表节点嵌套到要使用的数据结构中, 也可不是第一个元素, 通过 offsetof(), container_of 获取结构体地址
    struct Node node;
    char a;
    int b;
    float c;
    char *p;
} elem_t;
#endif


#if defined(DataStructApplicationLinkList) && (DataStructApplicationLinkList == 1)
// 比较数据内容是否相同, 而不是比较节点指针(deep copy but only copy data)
// ElemType *, ElemType*
// Allocate memory for ${elem_dest} if it does not have
#define COPY_ELEM_DATA(elem_dest, elem_src)                 \
    if (!elem_dest->p_data) {                               \
        elem_dest->data = malloc(elem_src->len);            \
        if (!elem_dest->data) {                             \
            exit(-1);                                       \
        }                                                   \
    }                                                       \
    memcpy(elem_dest->data, elem_src->data, elem_src->len)

// 比较数据内容:相同返回 true, 不同返回 false
// ElemType *, ElemType*
// return:integer
#define COMPARE_ELEM_DATA(elem1, elem2)                     \
    strcmp((const char *)elem1->p_data, (const char *)elem2->p_data)

// Only copy pointer and len(shallow copy does not copy data)
// ElemType *, ElemType*
#define COPY_ELEM_PTR(elem_dest, elem_src)               \
    (memcpy(elem_dest, elem_src, sizeof(*elem_src)))

// only compare pointer and len
// ElemType *, ElemType*
// return:integer
#define COMPARE_ELEM_PTR(elem_dest, elem_src)            \
    (memcmp(elem_dest, elem_src, sizeof(*elem_src)))


typedef struct {
    void *p_data; // save string type data, must end with '\0' for traverse
    int len; // length include '\0'
} ElemType;

typedef struct {
    struct Node *next; //指针域
    ElemType data; // 数据域部分, 数据域可以使用不同的数据类型
    //TODO:
    // 数据域部分, 后续可以使用 void *
    // void *data;
} Node, *LinkList;

typedef int position_t; // 节点位置
typedef  int (*compare_t)(ElemType *a, ElemType *b);
typedef void (*visit_t)(ElemType *elem);


Status MakeStringElem(ElemType *p_elem, const char *str);
Status FreeStringElem(ElemType *p_elem);
Status MakeNode(Node **p, ElemType *e);
void FreeNode(Node *p);


Status InitLinkList(LinkList *ll);
Status ClearLinkList(LinkList L);
Status DestroyLinkList(LinkList *L);
Status InitLinkListWithArray(LinkList *L, ElemType **pElemArr, size_t len);
Status Traverse(const LinkList L, void (*visit)(ElemType *data));
Status GetElem(const LinkList L, int i, ElemType *e);
Status LocateElem(const LinkList L, ElemType *pNodeVal, position_t *pos);
Status OrderInsert(LinkList *L, ElemType nodeVal, compare_t p_compare);
Status LinkListLength(const LinkList ll, size_t *pLen);
Status InsertBeforePosIdx(LinkList *L, size_t idx, ElemType *pElem);
Status InsertBeforeElem(LinkList L, ElemType *pElem, ElemType *pInsertElem);
Status InsertAtFirst(LinkList L, ElemType *pVal);
Status InsertAtTail(LinkList L, ElemType *pVal);
Status DeleteElem(LinkList L, ElemType *pDeleteVal);
Status DeleteByIdx(LinkList *L, size_t idx, ElemType *e);
Status DelFirst(LinkList L, Node **pDelNode);
Status Append(LinkList L, Node *pNew);
Status RemoveTail(LinkList L, Node **pDelNode);
Status InsertBefore(LinkList L, Node *p, Node *s);
Status InsertAfter(LinkList L, Node *p, Node *s);
Status SetCurrElem(LinkList L, Node *p, ElemType nodeNewVal);
Status GetCurrElem(LinkList L, Node *p, ElemType *pNode);
Status DeleteNode(LinkList L, Node **pDelete);
bool ListEmpty(const LinkList L);

Status BubbleSortLinkList(LinkList L, bool (*compare)(ElemType *a, ElemType *b));


void struct_member_size_test(void);
void app_linklist_api_test1(void);
void LinkListTest2(void);
void LinkListTest3(void);
void linklist_api_test4(void);
void LinkListTest5(void);
void LinkListTest6(void);
void LinkListTest7(void);
void LinkListTest8(void);

#endif // DataStructApplicationLinkList

#endif // __APP_LINKLIST_H__
