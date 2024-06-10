#ifndef __UTIL_H__
#define __UTIL_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "log.h"
/****************************************************************************
 * COMMON MACRO
 ****************************************************************************/
#define OK                  (0)
#define ERROR               (-1)
#define TRUE                (1)
#define FALSE               (0)
#define INVALID_VAL         (INT_MAX)

#define CHECK_RET(ret)                  \
    do {                                \
        if (ret != OK) {                \
            printf("error:%d\n", ret);  \
            exit(-1);                   \
        }                               \
    }                                   \
    while (0)

//TODO:
//使用可变参数的宏
#define CHECK_RET_OP(ret, hint)             \
    if (ret != OK) {                        \
        printf("op:%s ret:%d\n", hint, ret);\
        exit(-1);                           \
    }

#define CHECK_NOT_NULL(ret)         \
    if (ret == NULL) {              \
        printf("null ptr\n");       \
        exit(-1);                   \
    }


#define ASSERT(val)                 \
    do {                            \
        if (!(val)) {               \
            printf("assert, %s:%d", __FILE__, __LINE__); \
            exit(-1);               \
        }                           \
    } while (0)

typedef int Status;

#define SWAP(a, b)  { ElemType temp = (a); (a) = (b); (b) = temp; }


#endif