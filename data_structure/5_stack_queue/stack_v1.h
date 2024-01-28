#ifndef __STACK_V1_H__
#define __STACK_V1_H__

// 顺序存储的栈

typedef int Status;
#define OK      1
#define ERROR   0
typedef unsigned int size_t;
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


void StackTest1();


#endif

