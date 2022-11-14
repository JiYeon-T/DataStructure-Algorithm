/**
 * @file stack_v1.c
 * @author your name (you@domain.com)
 * @brief 栈
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "stack_v1.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/**
 * @brief 相当于只能从顶部插入元素、顶部弹出元素的顺序表
 *      (1)顺序存储;
 *      (2)链式存储;
 */

// static variables
static void print_int_elem(void *param);

// 元素
pPrintFun _print_fun = print_int_elem;

/**
 * @brief 打印函数
 * 
 * @param param 
 */
static void print_int_elem(void *param)
{
    printf("    %d\r\n", *(ElemType*)(param));
}

/**
 * @brief Init a empty stack
 *        栈底、栈顶指针都指向同一个位置
 * 
 * @param s 
 * @return Status 
 */
Status InitStack(Stack *s)
{
    if(!s){
        return ERROR;
    }

    s->top = s->base = (ElemType*)malloc(sizeof(ElemType) * STACK_MAX_SIZE);
    if(!s->top){
        return ERROR;
    }
    s->size = STACK_MAX_SIZE;

    return OK;
}

/**
 * @brief clear a stack
 * 
 * @param s 
 * @return Statuc 
 */
Status ClearStack(Stack *s)
{
    if(!s){
        return ERROR;
    }

    s->top = s->base;
    s->size = 0;

    return OK;
}

/**
 * @brief stack is empty?
 * 
 * @param s 
 * @return true/false
 */
bool EmptyStack(const Stack *s)
{
    if(!s || !s->base || !s->top){
        return false;
    }

    return s->top == s->base;
}

/**
 * @brief 返回栈中元素的个数
 * 
 * @param s 
 * @return int 
 */
int StackSize(const Stack *s)
{
    if(!s || !s->base || !s->top){
        return -1;
    }

    // 遍历
    ElemType *temp = s->base;
    size_t size = 0;

    while(temp != s->top){
        ++size;
        ++temp;
    }

    return size;
}

/**
 * @brief Get the Top object, 返回栈顶元素, 不弹出
 *        Peek(Stack);
 * 
 * @param s 
 * @param[out] e Elem
 * @return Status 
 */
Status GetTop(const Stack *s, ElemType *e)
{
    if(!s || !s->base || !s->top){
        return ERROR;
    }

    if(EmptyStack(s)){
        return ERROR;
    }

    ElemType *temp = s->top;
    *e = *(--temp);

    return OK;
}

/**
 * @brief top 指向顶部元素的下一个位置
 *        base 始终指向底部元素
 * 
 * @param s 
 * @param e 
 * @return Status 
 */
Status Push(Stack *s, ElemType *e)
{
    if(!s || !s->base || !s->top || !e){
        return ERROR;
    }

    // 如果空间不够, 则需要进行扩容
    if((s->top - s->base) >= s->size){
        s->base = (ElemType*)realloc(s->base, (s->size + STACK_INCREMENT_SIZE) * sizeof(ElemType));
        if(!s->base){
            printf("malloc error\r\n");
            return false;
        }
    }

    *(s->top) = *e;
    ++s->top; 

    return OK;
}

/**
 * @brief pop a element
 *        (1) 如果
 * 
 * @param s 
 * @param e 
 * @return Status 
 */
Status Pop(Stack *s, ElemType *e)
{
    if(!s || !s->base || !s->base){
        return ERROR;
    }

    if(EmptyStack(s)){
        return ERROR;
    }

    *e = *--s->top;

    return OK;
}

/**
 * @brief traver a stack
 *        from stack top to base
 * 
 * @param s 
 */
static void StackTraverse(const Stack *s)
{
    if(!s || !s->base || !s->base){
        return ERROR;
    }

    printf("Traverse:\r\n");
    if(EmptyStack(s)){
        printf("\r\n");
        return ERROR;
    }
    ElemType *temp = s->top;
    --temp; // 从栈顶第一个元素开始
    while(temp >= s->base){
        _print_fun(temp);
        --temp;
    }
    printf("\r\n");

    return;
}

/**
 * @brief Deinit a stack
 * 
 * @param s 
 * @return Status 
 */
Status DeinitStack(Stack *s)
{
    if(!s || !s->base){
        return ERROR;
    }

    free(s->base);
    s->base = s->top = NULL;
    s->size = 0;

    return OK;
}



void StackTest1()
{
    Stack s;
    ElemType data;

    printf("init stack\r\n");
    InitStack(&s);
    StackTraverse(&s);

    data = 5;
    printf("push data:%d\r\n", data);
    if(Push(&s, &data) != OK){
        printf("ERROR\r\n");
    }
    StackTraverse(&s);

    data = 999;
    printf("push data:%d\r\n", data);
    if(Push(&s, &data) != OK){
        printf("ERROR\r\n");
    }
    StackTraverse(&s);

    data = 89;
    printf("push data:%d\r\n", data);
    if(Push(&s, &data) != OK){
        printf("ERROR\r\n");
    }
    StackTraverse(&s);

    data = 52;
    printf("push data:%d\r\n", data);
    if(Push(&s, &data) != OK){
        printf("ERROR\r\n");
    }
    StackTraverse(&s);

    if(GetTop(&s, &data) != OK){
        printf("ERROR\r\n");
    }
    printf("Get top data:%d\r\n", data);
    StackTraverse(&s);

    Pop(&s, &data);
    printf("Pop data:%d\r\n", data);
    StackTraverse(&s);

    Pop(&s, &data);
    printf("Pop data:%d\r\n", data);
    StackTraverse(&s);


}


