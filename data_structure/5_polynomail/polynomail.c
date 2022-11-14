
/**
 * @file polynomail.c
 * @author your name (you@domain.com)
 * @brief 链式存储的多项式的运算, 存储方式 -> 数据域:(系数, 指数)
 * @version 0.1
 * @date 2022-11-08
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "polynomail.h"

/**
 * @brief
 *
 * @param poly
 */
void PolynomailPrinfInfo(void *poly)
{
    ElemType *temp = (ElemType*)poly;
    printf("%2.1fx^%d -> ", temp->coef, temp->expn);

    return;
}

/**
 * @brief 创建由 m 个元素组成的 "有序链表"
 *
 * @param p
 * @param arr
 * @param m
 * @return Status
 */
Status CreatPolyn(polynomial *p, ElemType *arr, int m)
{
    if(InitLinkList(p) != OK){
        return ERROR;
    }
    return InitLinkListWithArray(p, arr, m);
}

/**
 * @brief destory polynomial
 *
 * @param p
 * @return Status
 */
Status DestroyPolyn(polynomial *p)
{
    return DestroyLinkList(p);
}

/**
 * @brief Get polynomial length
 *
 * @param p
 * @return int
 */
int PolynLength(polynomial p)
{
    int len;
    if(LinkListLength(p, &len) != OK){
        len = -1;
    }

    return len;
}

/**
 * @brief p3 = p1 + p2
 *        (1) 将原来的节点直接从链表上拿下来; 会修改原始值的方式;
 *        (2) 拷贝 -> 创建新节点 -> 插入;
 *
 * @param p1
 * @param p2
 * @param p3
 * @return Status
 */
Status PolynAdd_v1(polynomial p1, polynomial p2, polynomial *p3)
{
    if(!p3){
        return ERROR;
    }

    Node *temp1 = p1->next, *temp2 = p2->next;
    if(!temp1 && !temp2){
        return OK;
    }
    else if(!temp1){

    }
    else if(!temp2){

    }
    else{
        ;
    }

    while(temp1 && temp2){

        switch(CmpExpn(temp1, temp2)){
            case 1:

            break;
            case 0:
            break;
            case -1:
            break;

        }
    }
    temp1 = temp1->next;
    temp2 = temp2->next;
}

/**
 * @brief p3 = p1 + p2
 *        (1) 将原来的节点直接从链表上拿下来; 会修改原始值的方式;
 *        (2) 拷贝 -> 创建新节点 -> 插入;
 *
 * @param p1
 * @param p2
 * @param p3
 * @return Status
 */
Status PolynAdd_v2(polynomial p1, polynomial p2, polynomial *p3)
{
    if(!p3){
        return ERROR;
    }

    Node *temp1 = p1->next, *temp2 = p2->next;

    while(temp1 && temp2){
        switch(CmpExpn(temp1, temp2)){
            case 1:
            {
                // InsertTailWithNode(*p3, temp2);
                InsertTail(*p3, temp2->data); // create a new node
                temp2 = temp2->next;
            }
            break;
            case 0:
            {
                // 相等情况下使用 temp1
                // temp1->data.coef += temp2->data.coef;
                // InsertTailWithNode(*p3, temp1);
                ElemType data;
                data.coef = temp1->data.coef + temp2->data.coef;
                data.expn = temp1->data.expn;
                InsertTail(*p3, data);
                temp1 = temp1->next;
                temp2 = temp2->next;
            }
            break;
            case -1:
            {
                // InsertTailWithNode(*p3, temp1);
                InsertTail(*p3, temp1->data);
                temp1 = temp1->next;
            }
            break;
            case -999:
                printf("ERROR\r\n");
                return ERROR;
        }
    }

    if(!temp1){
        LinkListAppend(*p3, temp2);
        // *p3 = temp2; // 仍然使用 p1, p2 申请的内存
        return OK;
    }
    else if(!temp2){
        LinkListAppend(*p3, temp1);
        return OK;
    }
    else{
        return OK;
    }
}

/**
 * @brief p1 = p1 + p2
 *
 * @param p1
 * @param p2
 * @return Status
 */
Status PolynAdd_v2(polynomial p1, polynomial p2)
{

}


/**
 * @brief p3 = p1 - p2 -> p3 = p1 + (-1)*p2
 * 
 * @param p1 
 * @param p2 
 * @param p3 
 * @return Status 
 */
Status PolynSubtract(polynomial p1, polynomial p2, polynomial *p3)
{

}

/**
 * @brief multiply p3 = p1 * p2
 * 
 * @param p1 
 * @param p2 
 * @param p3 
 * @return Status 
 */
Status PolynMultiply(polynomial p1, polynomial p2, polynomial *p3)
{

}

/**
 * @brief 根据指数的大小返回不同的值
 *
 * @param a
 * @param b
 * @return int 1:a>b; 0:a==b; -1:a<b; -999:ERROR
 */
int CmpExpn(Node * a, Node *b)
{
    if(!a || !b){
        printf("null ptr\r\n");
        return -999;
    }

    if(a->data.expn > b->data.expn){
        return 1;
    }
    else if(a->data.expn == b->data.expn){
        return 0;
    }
    else{
        return -1;
    }
}



void PolynTest()
{
    polynomial p1, p2, p3;
    // 有序链表
    ElemType arr1[] = {{21, 0}, {3, 3}, {1, 5}, {22, 9}};
    ElemType arr2[] = {{15, 0}, {3, 2}, {5, 5}, {9, 100}};

    printf("create p1:\r\n");
    CreatPolyn(&p1, arr1, sizeof(arr1) / sizeof(arr1[0]));
    Traverse(p1, PolynomailPrinfInfo);

    printf("create p2:\r\n");
    CreatPolyn(&p2, arr2, sizeof(arr2) / sizeof(arr2[0]));
    Traverse(p2, PolynomailPrinfInfo);

    printf("create p3:\r\n");
    InitLinkList(&p3);
    Traverse(p3, PolynomailPrinfInfo);

    // printf("delete p1:\r\n");
    // DestroyPolyn(&p1);
    // Traverse(p1, PolynomailPrinfInfo);

    // printf("p1 len:%d\r\n", PolynLength(p1));

    // printf("cmp result:%d\r\n", CmpExpn(p1->next, p2->next));

    printf("polyn add:\r\n");
    PolynAdd_v2(p1, p2, &p3);
    Traverse(p3, PolynomailPrinfInfo);

    return;
}
