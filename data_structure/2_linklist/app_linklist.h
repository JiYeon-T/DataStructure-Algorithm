#ifndef __APP_LINKLIST_H__
#define __APP_LINKLIST_H__

#include <stdint.h>

typedef struct {
    float   coef; // 系数
    int     expn; // 指数
} ElemType_P;

//
typedef void (*pPrintInfo)(void *p);

#endif