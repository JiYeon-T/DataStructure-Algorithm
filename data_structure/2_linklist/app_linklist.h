#ifndef __APP_LINKLIST_H__
#define __APP_LINKLIST_H__


#include "util.h"
#include "build_config.h"

// 链表的应用:
// 一元多项式的操作;

#if defined(APP_LINKLIST) && (APP_LINKLIST == 1)


#include <stdint.h>

typedef struct {
    float   coef; // 系数
    int     expn; // 指数
} ElemType_P;

//
typedef void (*pPrintInfo)(void *p);

#endif

#endif