/**
 * @file Triplet.c
 * @author your name (you@domain.com)
 * @brief 通过抽象数据类型三元组学习数据抽象
 * @version 0.1
 * @date 2021-12-09
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "Triplet.h"
#include <stdlib.h>
#include <stdio.h>

/** 算法:有穷性, 确定性, 可行性, 输入, 输出 **/

// member functions
Triplet* InitTriplet(ElemType a, ElemType b, ElemType c)
{
    Triplet *T = (Triplet*)malloc(sizeof(Triplet) * 1);
    if(!T){
        perror("malloc failed\n");
        return NULL;
    }
    T->data[0] = a;
    T->data[1] = b;
    T->data[2] = c;
    return T;
}

Status DestroyTriplet(Triplet *T)
{
    free(T);
    T = NULL;
    return OK;
}

// 下标从 0 开始
ElemType Get(Triplet *T, int i)
{
    if(i<0 || i>3){
        return ERROR;
    }
    return T->data[i];

}

Status Put(Triplet *T, int i, ElemType elem)
{
    if(i < 0 || i > 3){
        return ERROR;
    }
    T->data[i] = elem;
}

Status IsAscending(Triplet *T)
{
    return (T->data[0] <= T->data[1]) && \
            (T->data[1] <= T->data[2]);
}

Status IsDescending(Triplet *T)
{
    return (T->data[0] >= T->data[1]) && \
            (T->data[1] >= T->data[2]);
}

ElemType Max(Triplet *T)
{
    return (T->data[0] >= T->data[1]) ? \
           (T->data[0] >= T->data[2] ? T->data[0] : T->data[2]) : \
           (T->data[1] >= T->data[2] ? T->data[1] : T->data[2]);
}

ElemType Min(Triplet *T)
{
    return (T->data[0] <= T->data[1]) ? \
           (T->data[0] <= T->data[2] ? T->data[0] : T->data[2]) : \
           (T->data[1] <= T->data[2] ? T->data[1] : T->data[2]);
}

void TripletTest()
{
    Triplet *T; // 指针的值保存的是数据区的一个地址;
    int index = 2;

    T = InitTriplet(1, 2, 3);
    printf("data[%d]:%d\n", index, Get(T, index));
    Put(T, index, 100);
    printf("data[%d]:%d\n", index, Get(T, index));
    printf("isAsending:%d, isDesending:%d\n", IsAscending(T), IsDescending(T));
    printf("max:%d\t min:%d\n", Max(T), Min(T));
    DestroyTriplet(T);

    printf("HELLO,WORLD.");
}
