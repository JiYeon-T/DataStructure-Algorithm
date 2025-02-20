#ifndef __STACK_V1_H__
#define __STACK_V1_H__

<<<<<<< Updated upstream:data_structure/6_stack_queue/stack_v1.h
#include <stddef.h>

// 顺序存储的栈
=======
#include <stdbool.h>

>>>>>>> Stashed changes:data_structure/5_stack_queue/stack_v1.h

typedef int Status;
#define OK      1
#define ERROR   0
// typedef unsigned int size_t;
typedef int ElemType;



// 预先分配的栈最大空间, 如果超出还需要进行动态扩容
#define STACK_MAX_SIZE          50
#define STACK_INCREMENT_SIZE    50 // 每次扩容的大小


// 打印的函数指针, 打印使用
typedef void (*pPrintFun)(void *param);

// 使用堆内存, 动态分配内存, 分配的空间地址也是连续的
typedef struct{
    ElemType *base; // 栈底
    ElemType *top; // 栈顶
    int  size; // stack size, 栈的总大小
} Stack;

// 使用栈内存, 使用数组
typedef struct{
    size_t base;  // 保存数组下标
    size_t top;
    int size;
} Stack_v2;

// 外部函数使用特殊的元素类型, 需要修改这个变量


void SetPrintFormat(pPrintFun fun);
Status InitStack(Stack *s);
Status ClearStack(Stack *s);
bool EmptyStack(const Stack *s);
int StackSize(const Stack *s);
Status GetTop(const Stack *s, ElemType *e);
Status Push(Stack *s, ElemType *e);
Status Pop(Stack *s, ElemType *e);
Status StackTraverse(const Stack *s);
Status InverseTraverseStack(const Stack *s);
Status DeinitStack(Stack *s);


void StackTest1();


#endif

