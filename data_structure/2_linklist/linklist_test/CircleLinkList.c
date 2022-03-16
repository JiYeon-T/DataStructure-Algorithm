/**
 * @file CircleLinkList.c
 * @author your name (you@domain.com)
 * @brief 首尾相连的链表, 循环终止条件变成了判断 temp->next!=head, 是否为头指针
 * @version 0.1
 * @date 2022-03-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "CircleLinkList.h"

/**
 * @brief 初始化循环链表(没有头节点)
 *        头插法创建链表
 * @param head 头指针
 * @param size 链表大小
 */
void Init_CL(Node_CL *head, size_t size)
{
    Node_CL *temp;
    srand(time(0));
    for(size_t ix = 0; ix < size; ++ix){
        //修改头指针的值 head
        temp = (Node_CL*)malloc(sizeof(Node_CL) * 1);
        temp->data = rand() % 10;
        temp->next = head;
    }
}

/**
 * @brief Traverse
 * 
 */


/**
 * @brief 增删改查
 * 
 */


/**
 * @brief 释放链表的内存
 * 
 * @param head 
 */
void Delete_CL(CLinkList head)
{

}


void Test_CL()
{
    CLinkList head; // 指针没有成员变量的说法, 它本身就是一块内存的首地址而已
    Node_CL node;
    node.data = 111;
    node.next = NULL;
    head = &node; // head 指向 node
    printf("%d - %d\n", sizeof(head), sizeof(Node_CL));
    printf("head:%#p - &node:%#p, &head:%#p", head, &node, &head); // head的值就是 node 的首地址
    
}