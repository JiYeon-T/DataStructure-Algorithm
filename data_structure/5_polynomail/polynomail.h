#ifndef POLYNOMAIL_H_INCLUDED
#define POLYNOMAIL_H_INCLUDED

#include "LinkList.h"

typedef LinkList polynomial;


void PolynomailPrinfInfo(void *poly);
Status CreatPolyn(polynomial *p, ElemType *arr, int m);
Status DestroyPolyn(polynomial *p);
int PolynLength(polynomial p);


void PolynTest();

#endif // POLYNOMAIL_H_INCLUDED
