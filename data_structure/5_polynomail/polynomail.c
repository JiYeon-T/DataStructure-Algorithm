
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


#if defined(DATA_STRUCTURE_POLYNOMAIL) && (DATA_STRUCTURE_POLYNOMAIL == 1)

/**
 * @fun linklist node print function
 *      only print current node information
 * @param[in] pNode node pointer
*/
static void print_poly_node_info(Node *pNode)
{
    printf("%2.2f X^%d + ", pNode->data.coef, pNode->data.expn);
}


/**
 * @brief 创建由 arrSize 个(系数,指数)对 组成的 "有序链表"
 *
 * @param p
 * @param pArr array consist of (coef, expn) pair
 * @param arrSize
 * @return Status
 */
Status CreatPolyn(polynomial *p, ElemType *pArr, int arrSize)
{
    if (!p || !pArr || arrSize <= 0)
        return ERROR;

    return InitLinkListWithArray(p, pArr, arrSize);
}

/**
 * @brief destory polynomial, deinit linklist(include head node)
 *
 * @param p
 * @return Status
 */
Status DestroyPolyn(polynomial *p)
{
    return DeinitLinkList(p);
}


/**
 * @brief Traverse the linklist and print node information
 *
 * @param poly polynomial type(Node *), linklist head pointer
 */
void PrintPoly(const polynomial poly, const char *pInfo)
{
    Status ret = Traverse(poly, pInfo, print_poly_node_info);
    CHECK_RET_OP(ret, pInfo);
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

    if (LinkListLength(p, &len) != OK) {
        return -1;
    }

    return len;
}

/**
 * @brief p1 = p1 + p2, 结果保存到 p1, 销毁 p2
 *        (1) 将原来的节点直接从链表上拿下来; 会修改原始值的方式;
 *        (2) 拷贝 -> 创建新节点 -> 插入;
 *        一元多项式的加法, 例如:
 *        l1:a1x^100 + a2x^15 + a3x^2 + a4x^1 + a5
 *        l2:b1x^99 + b2x^10 + b3x^5 + b4x^1 + b5
 *        求 l1+l2?
 * 
 *        算法(与归并排序类似):
 *        1.  假设 q1, q2 分别指向 p1, p2(前提是有序链表)的某一个节点, 比较 p1, p2 的指数部分, 系数部分比较大小有三种情况
 *        (1) q1 < q2, 将 q1 插入到结果链表(引用);
 *        (2) q1 > q2, 将 q2 插入到将诶过链表(引用);
 *        (3) q1 == q2, 分以下两种情况
 *        a. 对于具有相同指数的项, 系数相加,和不为 0 则构成多项式中的一项; 和为 0, 则删除该项
 *        b. 对于没有相同系数的项, 则直接添加到结果链表中;
 *        key(1) 拷贝数据 -> 创建新节点 -> 插入结果链表(不直接从原链表上拿数据下来);
 *
 * @param p1 p1, p2 都是有序链表, 如果是无序的链表, 要进行排序操作
 * @param p2
 * @return Status
 */
Status AddPolyV1(polynomial *p1, polynomial *p2)
{
    if (!p1 && !p2) {
        return ERROR;
    }

    if (!p1) {
        // TODO:
        // copy p2 to p1
        return OK;
    }

    if (!p2) {
        return OK;
    }

    Node *temp1 = p1->next, *temp2 = p2->next;
    f(!temp1 && !temp2){
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
 *        key(2) 将原来的节点直接从链表上拿下来; 会修改原始链表的方式;
 *
 * @param p1
 * @param p2
 * @param p3
 * @return Status
 */
Status AddPolyV2(polynomial p1, polynomial p2, polynomial *p3)
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
 * @brief p1 = p1 - p2, 并销毁 p2
 *        p3 = p1 + (-1)*p2
 * 
 * @param p1 
 * @param p2 
 * @return Status 
 */
Status SubtractPolyn(polynomial *p1, polynomial *p2)
{

}

/**
 * @brief p1 = p1 * p2, 并销毁 p2
 * 
 * @param p1 
 * @param p2 
 * @param p3 
 * @return Status 
 */
Status MultiplyPolyn(polynomial *p1, polynomial *p2)
{

}

/**
 * @brief 根据指数的大小返回不同的值
 *
 * @param a
 * @param b
 * @return int 1:a>b; 0:a==b; -1:a<b; -999:ERROR
 */
int CmpExpn(term *a, term *b)
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

// linklist basic operation
void PolynTest1(void)
{
    printf("polynomial test1\n");
    polynomial poly;
    Status ret;
    ElemType val = {1.5, 2};

    ret = InitLinkList(&poly);
    CHECK_RET_OP(ret, "Init");
    ret = Traverse(poly, "Init poly", print_poly_node_info);
    CHECK_RET_OP(ret, "Init");

    ret = InsertAtFirst(poly, &val);
    CHECK_RET_OP(ret, "Insert Head");
    ret = Traverse(poly, "Insert Head:(1.5x^2)", print_poly_node_info);
    CHECK_RET_OP(ret, "Insert Head");
}

// polynomial math operation
#if 0
void PolynTest2(void)
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
#endif

#endif