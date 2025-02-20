#ifndef __STACK_V2_H__
#define __STACK_V2_H__

#include "stack_v1.h"
#include <stdbool.h>


// 栈的链式存储: 单向链表


typedef struct {
    struct StackNode_t *next;
    ElemType data;
} StackNode_t;


typedef struct{
    StackNode_t *top;
    StackNode_t *base;
    size_t size; // 保存栈中保存的元素个数
} LinkListStack_t; // 链栈


Status InitStack_L(LinkListStack_t *s);
Status Traverse_L(LinkListStack_t *s);
bool StackEmpty_L(const LinkListStack_t *s);
Status Push_L(LinkListStack_t *s, ElemType *data);
Status Pop_L(LinkListStack_t *s, ElemType *data);


void LinkListStackTest2();

#endif