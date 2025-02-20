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
#include <limits.h>



// 栈的链式存储: 单向链表
// 不需要担心空间, 几乎是想存多少, 就存多少
// 只能从队尾插入, 队尾删除
// 包含头结点

/**
 * @brief initialize linklist stack
 *        (1) include a head node;
 *        (2) 空栈:栈顶指针, 栈底指针都只想头结点;
 *        (3) 含有元素时:栈顶指头头结点; 栈底指向最后一个节点; 
 *        (4) 入栈出栈都从头结点处;
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
    if(!headNode){
        return ERROR;
    }
    headNode->data = INT_MAX;
    headNode->next = NULL;
    s->base  = s->top = headNode;
    s->size = 0;

    return OK;
}

/**
 * @brief 遍历
 *        栈顶指向头结点; 栈底指向最后一个节点
 * 
 * @param s 
 * @return Status 
 */
Status Traverse_L(LinkListStack_t *s)
{
    if(!s){
        return ERROR;
    }
    printf("Traverse:\r\n");
    StackNode_t *temp = s->top->next;
    while(temp){
        printf("  %d\r\n", temp->data);
        temp = temp->next;
    }
    printf("\r\n");
}

/**
 * @brief 是否为空栈
 * 
 * @param s 
 * @return true 
 * @return false 
 */
bool StackEmpty_L(const LinkListStack_t *s)
{
    if(!s || !s->base || !s->top){
        return ERROR;
    }
    return s->base == s->top;
}

/**
 * @brief 等效于插入第一个结点
 *        每次都在头结点后插入节点
 * 
 * @param s 
 * @param data 
 * @return Status 
 */
Status Push_L(LinkListStack_t *s, ElemType *data)
{
    if(!s || !data){
        return ERROR;
    }

    StackNode_t *temp = (StackNode_t*)malloc(sizeof(StackNode_t) * 1);
    if(!temp){
        return ERROR;
    }

    // 空栈 - 更新尾节点
    if(StackEmpty_L(s)){
        s->base = temp;
    }
    temp->data = *data;
    temp->next = s->top->next;
    s->top->next = temp;
    ++s->size;
    return OK;
}

/**
 * @brief pop a data
 *        删除第一个节点
 *        (1) 删除的节点是最后一个节点, 则要更新栈底
 * 
 * @param s 
 * @param data 
 * @return Status 
 */
Status Pop_L(LinkListStack_t *s, ElemType *data)
{
    if(!s || !data || StackEmpty_L(s)){
        return ERROR;
    }

    StackNode_t *temp = s->top->next;

    // 要出栈的元素为最后一个节点, 更新栈底
    if(temp == s->base){
        s->base = s->top;
    }
    *data = temp->data;
    s->top->next = temp->next;
    free(temp); // free memory

    return OK;
}



void LinkListStackTest2()
{
    LinkListStack_t s;
    ElemType data;

    printf("Init:\r\n");
    InitStack_L(&s);
    Traverse_L(&s);

    data = 154;
    printf("push data:%d\r\n", data);
    Push_L(&s, &data);
    Traverse_L(&s);

    data = 222;
    printf("push data:%d\r\n", data);
    Push_L(&s, &data);
    Traverse_L(&s);

    data = 333;
    printf("push data:%d\r\n", data);
    Push_L(&s, &data);
    Traverse_L(&s);

    if(Pop_L(&s, &data) != OK){
        printf("Pop error\r\n");
        return;
    }
    printf("pop data:%d\r\n", data);
    Traverse_L(&s);

    if(Pop_L(&s, &data) != OK){
        printf("Pop error\r\n");
        return;
    }
    printf("pop data:%d\r\n", data);
    Traverse_L(&s);

    if(Pop_L(&s, &data) != OK){
        printf("Pop error\r\n");
        return;
    }
    printf("pop data:%d\r\n", data);
    Traverse_L(&s);

    if(Pop_L(&s, &data) != OK){
        printf("Pop error\r\n");
        return;
    }
    printf("pop data:%d\r\n", data);
    Traverse_L(&s);
}
