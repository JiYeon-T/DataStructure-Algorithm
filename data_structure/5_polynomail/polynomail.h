#ifndef POLYNOMAIL_H_INCLUDED
#define POLYNOMAIL_H_INCLUDED


// 带头节点的单向链表 - 一元多项式
// 使用链式存储结构,顺序存储结构对于指数差异较大时, 会有很多的 0 节点,浪费空间
// 编译该文件需要 DATA_STRUCTURE_POLYNOMAIL == 1 && DataStructLinkListV4 == 1

/* NOTE: 每个文件中都必须包含的部分 */
#include "util.h"
#include "build_config.h"

#if defined(DATA_STRUCTURE_POLYNOMAIL) && (DATA_STRUCTURE_POLYNOMAIL == 1)
#if defined(DataStructLinkListV4) && (DataStructLinkListV4 == 1)
#include "LinkList_v4.h"
#else
#error "polynomial test need use linklist"
#endif



// typedef struct {
//     float coef; // 系数
//     int expn; // 指数
// } term; // 两个类型名:term 用于 ADT; ElemType 用于 LinkList 数据类型
// #define ElemType term

// typedef struct _Node {
//     Node *next;
//     ElemType data;
// } Node, *LinkList; // 链表数据类型

typedef LinkList polynomial; // Node* type
// #define polynomial LinkList;

void PolynomailPrinfInfo(void *poly);
Status CreatPolyn(polynomial *p, ElemType *pArr, int arrSize);
Status DestroyPolyn(polynomial *p);
int PolynLength(polynomial p);
Status AddPolyV1(polynomial p1, polynomial p2);
Status AddPolyV2(polynomial p1, polynomial p2);
Status SubtractPolyn(polynomial p1, polynomial p2);

void PolynTest1(void);
void PolynTest2(void);

#endif // DATA_STRUCTURE_POLYNOMAIL

#endif // POLYNOMAIL_H_INCLUDED
