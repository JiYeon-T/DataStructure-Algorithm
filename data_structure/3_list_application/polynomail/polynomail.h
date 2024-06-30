#ifndef POLYNOMAIL_H_INCLUDED
#define POLYNOMAIL_H_INCLUDED


//TODO:
// 链表应用1:
// 一元多项式的加法 /乘法 C(x) = A(x) * B(x)

// 带头节点的单向链表 - 一元多项式
// 使用链式存储结构,顺序存储结构对于指数差异较大时, 会有很多的 0 节点,浪费空间
// 编译该文件需要 DATA_STRUCTURE_POLYNOMAIL == 1 && DataStructLinkListV4 == 1


/* NOTE: 每个文件中都必须包含的部分 */
#include "util.h"
#include "build_config.h"

#if defined(DATA_STRUCTURE_POLYNOMAIL) && (DATA_STRUCTURE_POLYNOMAIL == 1)
#if defined(DataStructLinkListV4) && (DataStructLinkListV4 == 1)
#include "LinkListv4.h"
#else
#error "polynomial test need use linklist"
#endif


// ElemType 用于 LinkList 数据类型
// term 用于 ADT; 
typedef struct {
    float coef; // 系数
    int expn; // 指数
} item_t; // 多项式的一项, 节点数据域部分 item_t*类型 (Elemtype 类型(void*))

typedef LinkList polynomial; // Node* type

Status MakeElemPolyItem(ElemType *p_elem, item_t *p_item);
Status FreeElemPolyItem(ElemType elem);
Status MakeNodePolyItem(struct Node **p, item_t *p_item);
void FreeNodePolyItem(struct Node *p);


void PolynomailPrinfInfo(void *poly);
Status CreatPolyn(polynomial *p, item_t *pArr, int arrSize);
Status DestroyPolyn(polynomial *p);
size_t PolynLength(const polynomial *p);
Status PrintPolyn(const polynomial *polyn, Status (*visit)(ElemType elem));
Status AddPolyV1(polynomial *p1, polynomial *p2);
Status AddPolyV2(polynomial *p1, polynomial *p2);
Status SubtractPolyn(polynomial *p1, polynomial *p2);
Status MultiplyPolyn(polynomial *p1, polynomial *p2);



void PolynTest1(void);
void PolynTest2(void);

#endif // DATA_STRUCTURE_POLYNOMAIL

#endif // POLYNOMAIL_H_INCLUDED
