#ifndef __LOG_H__
#define __LOG_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LOG_TAG_D(tag, fmt, ...)  \
    printf("[%ld] [D] [%s] [%s:%d] "fmt"\r\n", time(NULL), tag, __func__, __LINE__, ##__VA_ARGS__)
#define LOG_TAG_I(tag, fmt, ...)  \
    printf("[%ld] [I] [%s] [%s:%d] "fmt"\r\n", time(NULL), tag, __func__, __LINE__, ##__VA_ARGS__)
#define LOG_TAG_W(tag, fmt, ...)  \
    printf("[%ld] [W] [%s] [%s:%d] "fmt"\r\n", time(NULL), tag, __func__, __LINE__, ##__VA_ARGS__)
#define LOG_TAG_E(tag, fmt, ...)  \
    printf("[%ld] [E] [%s] [%s:%d] "fmt"\r\n", time(NULL), tag, __func__, __LINE__, ##__VA_ARGS__)


#define LOG_D(fmt, ...) LOG_TAG_D("ds", fmt, ##__VA_ARGS__)
#define LOG_I(fmt, ...) LOG_TAG_I("ds", fmt, ##__VA_ARGS__)
#define LOG_W(fmt, ...) LOG_TAG_W("ds", fmt, ##__VA_ARGS__)
#define LOG_E(fmt, ...) LOG_TAG_E("ds", fmt, ##__VA_ARGS__)

#endif