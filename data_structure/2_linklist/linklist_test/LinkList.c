#include "LinkList.h"


// 增 删 改 查

//链表测试函数
void linklist_test()
{
//    Node node; //头节点, 数据域不保存数据, 可以选择保存链表长度之类的
//    LinkList head = &node; //pointer, size = 4; 指向 "头节点" 的指针
    Node head, node1, node2, node3; // struct Node, size = 8, printf("%d - %d", sizeof head, sizeof(node));
    ElemType data;

    //Init_L(head); //使用头节点的方式初始化链表
    head.next = &node1;
    node1.data = 1;
    node1.next = &node2;
    node2.data = 2;
    node2.next = &node3;
    node3.data = 3;
    node3.next = NULL;

    //traverse the linklist
    Traverse_L(&head);

    data = GetElem_L(&head, 0, &data);
    printf("linklist[%d] = %d\n", 0, data);

}


/**
* @fun: init liklist
* @param[in]  L pointer to head node
* @param[in]  size
*/
Status Init_L(LinkList L, unsigned int size)
{

}

/**
* @fun: traverse linklist
* @param[in]  head pointer to head node
*/
Status Traverse_L(LinkList head)
{
    if(head == NULL){
        return ERROR;
    }

    Node *p_temp = head->next;

    while(p_temp){
        printf("%d ->", p_temp->data);
        p_temp = p_temp->next;
    }
    printf("\n");

    return OK;
}


/**
* @fun: get linklist element
* @param[in]  L pointer to head node
* @param[in]  i index start from 0
* @param[out] e save value of index ix
*/
ElemType GetElem_L(LinkList L, int i, ElemType *e)
{
    Node *p_temp = L->next; //first node
    int j = 0;

    while(p_temp && j<i){
        p_temp = p_temp->next;
        ++j;
    }

    if( !p_temp || j>i ){
        return ERROR;
    }
    *e = p_temp->data;

    return OK;
}


