/**
 * @file stack_v2.c
 * @author your name (you@domain.com)
 * @brief 链栈
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "stack_v2.h"
#include <stdlib.h>
#include <stdio.h>


// 栈的链式存储: 单向链表
// 不需要担心空间, 几乎是想存多少, 就存多少
// 只能从队尾插入, 队尾删除
// 包含头结点

/**
 * @brief initialize linklist stack
 *        (1) include a head node;
 *        (2) 栈顶指针, 栈底指针都只想头结点
 * 
 * @param s 
 * @return Status 
 */
Status InitStack_L(LinkListStack_t *s)
{
    if(!s){
        return ERROR;
    }

    StackNode_t *headNode = (StackNode_t*)malloc(sizeof(StackNode_t) * 1);
    s->base  = s->top = headNode;
    s->size = 0;
}

