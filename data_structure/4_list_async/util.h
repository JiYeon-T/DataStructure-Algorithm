#ifndef __UTIL_H__
#define __UTIL_H__

#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>


#define DEBUG 1

#ifdef DEBUG
#define LOG_D(fmt, ...) printf("[D][%s:%d] "fmt"\n", __func__, __LINE__, ##__VA_ARGS__)
#define LOG_I(fmt, ...) printf("[I][%s:%d] "fmt"\n", __func__, __LINE__, ##__VA_ARGS__)
#define LOG_W(fmt, ...) printf("[W][%s:%d] "fmt"\n", __func__, __LINE__, ##__VA_ARGS__)
#define LOG_E(fmt, ...) printf("[E][%s:%d] "fmt"\n", __func__, __LINE__, ##__VA_ARGS__)
#else
#define LOG_D(fmt, ...)
#endif


#define CASE_RETURN_STR(val) \
    case val:                \
        return #val;


#endif