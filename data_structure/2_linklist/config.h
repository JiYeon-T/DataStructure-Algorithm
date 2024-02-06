#ifndef __CONFIG_H__
#define __CONFIG_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>

#include "build_config.h"
/****************************************************************************
 * COMMON MACRO
 ****************************************************************************/
#define OK                  0
#define ERROR               -1
#define TRUE                1
#define FALSE               0
#define INVALID_VAL         0xFFFFFFFF

#define CHECK_RET(ret)                  \
    do {                                \
        if (ret != OK) {                \
            printf("error:%d\n", ret);  \
            exit(-1);                   \
        }                               \
    }                                   \
    while (0)

#define CHECK_RET_OP(ret, op)               \
    if (ret != OK) {                        \
        printf("op:%s ret:%d\n", op, ret);  \
        exit(-1);                           \
    }

#define CHECK_NOT_NULL(ret)         \
    if (ret == NULL) {              \
        printf("null ptr\n");       \
        exit(-1);                   \
    }


// #define ASSERT(str)
typedef int Status;





#endif
