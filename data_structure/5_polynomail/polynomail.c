
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
    printf("%2.2f*x^%d + ", pNode->data.coef, pNode->data.expn);
}

/**
 * @brief polynomial ElemType 大小比较
 *        根据指数的大小返回不同的值
 *
 * @param a
 * @param b
 * @return int 1:a>b; 0:a==b; -1:a<b; -999:ERROR
 */
static int CmpExpn(term *a, term *b)
{
    if(!a || !b){
        printf("null ptr\r\n");
        return -999;
    }

    if(a->expn > b->expn){
        return 1;
    }
    else if(a->expn == b->expn){
        return 0;
    }
    else{
        return -1;
    }
}

/**
 * @fun 两个节点的系数数相加
 * 
 * @param[in] a
 * @paramp[in] b
*/
static int AddCoef(term *a, term *b)
{
    return (a->coef + b->coef);
}

/**
 * @fun 两个节点的指数相加
 * 
 * @param[in] a
 * @paramp[in] b
*/
static int AddExpn(term *a, term *b)
{
    return (a->expn + b->expn);
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
 * @brief p1 = p1 + p2, 结果保存到 p1, p2保留
 *        (1) 将原来的节点直接从链表上拿下来; 会修改原始值的方式;
 *        (2) 拷贝 -> 创建新节点 -> 插入;
 *        一元多项式的加法, 例如(按照指数由大到小排列):
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
 * @param p1 p1, p2 都是有序链表, TODO:如果是无序的链表, 要进行排序操作, type:Node**
 * @param p2
 * @return Status
 */
Status AddPolyV1(polynomial p1, polynomial p2)
{
    if (!p1 || !p2) {
        return ERROR;
    }
    Status ret;

    // if (!p1) {
    //     // TODO:
    //     // copy p2 to p1
    //     return OK;
    // }

    // if (!p2) {
    //     return OK;
    // }

    Node *q1 = p1->next, *q2 = p2->next;
    while (q1 && q2) { // 按照指数从大到小排序
        switch (CmpExpn(&q1->data, &q2->data)) { // 比较两个元素的指数部分
            Node *pDelete = NULL;
            case 1: { // q1 的指数部分比较大, q1 移动到下一位, q2 不移动
                q1 = q1->next;
                break;
            }
            case 0: { // 两个指数部分一样大, 系数相加
                float sum = q1->data.coef + q2->data.coef;
                if (sum != 0) { // 结果直接写入 q1 节点即可, 删除 q2
                    ElemType nodeNewVal = {
                        .coef = sum,
                        .expn = q1->data.expn
                    };
                    ret = SetCurrElem(p1, q1, nodeNewVal);
                    CHECK_RET(ret);
                    ret = DelFirst(p2, &pDelete);
                    CHECK_RET(ret);
                    ret = FreeNode(&pDelete);
                    CHECK_RET(ret);
                    q2 = p2->next;
                } else { // 系数部分和为 0, q1, q2 都删除
                    pDelete = q1;
                    q1 = q1->next;
                    ret = DeleteNode(p1, &pDelete);
                    CHECK_RET(ret);
                    ret = FreeNode(&pDelete);
                    CHECK_RET(ret);

                    ret = DelFirst(p2, &pDelete); // q2 肯定是 p2 的第一个节点
                    CHECK_RET(ret);
                    ret = FreeNode(&pDelete);
                    CHECK_RET(ret);
                    q2 = p2->next;
                }
                break;
            }
            case -1: { // q2 的指数部分比较大, q2 插入到 q1 前面
                ret = DelFirst(p2, &pDelete);
                CHECK_RET(ret);
                ret = InsertBefore(p1, q1, q2);
                CHECK_RET(ret);
                q2 = p2->next; // qb 指向下一个节点
                q1 = q1->next; // 避免出现重复出现 指数相同的项
                break;
            }
            default: {
                printf("error expression");
                return;
            }
        }
    }

    if (!ListEmpty(p2)) {
        Append(p1, q2);
    }

    // if (!ListEmpty(pa)) { // p1 = p1+p2, 不会出现这种情况
    // }

    return OK;
}

/**
 * @brief p1 = p1 + p2, 全部使用 LinkList 封装的接口：TODO
 *
 * @param p1
 * @param p2
 * @param p3
 * @return Status
 */
Status AddPolyV2(polynomial p1, polynomial p2)
{
    if(!p1 || !p2){
        return ERROR;
    }
    // TODO:
    return OK;
}

/**
 * @brief p1 = p1 - p2, 并销毁 p2
 *        法1:p3 = p1 + (-1)*p2
 *        法2:先比较指数, 指数不同, q1的系数部分取反加到q1
 *                      指数相同, q1+q2结果写到 q1;
 *
 * @param p1 
 * @param p2 
 * @return Status 
 */
Status SubtractPolyn(polynomial p1, polynomial p2)
{
    if (!p1 || !p2) {
        return ERROR;
    }
    Status ret;

    // if (!p1) {
    //     // TODO:
    //     // copy p2 to p1
    //     return OK;
    // }

    // if (!p2) {
    //     return OK;
    // }

}

/**
 * @fun 没有头节点, 仅仅将该节点插入到整个链表中合适的位置, 
 *      1. 链表中存在指数相同的节点, 合并该节点即可(指数相加), 释放内存
 *      2. 不存在指数相同的节点, 按照指数从大到小的顺序插入链表
 *
 * @param[in] p 有序链表, 链表按照指数从大到小排序
 * @param[in] pNode 仅仅是一个节点, 不是链表,没有头节点, 
 * @ret
*/
static Status PolynaddNode(polynomial p, Node *pNode)
{
    if (!p || !pNode)
        return ERROR;
    Status ret;
    Node *pPrev = p, *pCurr = p->next;

    while (pCurr) {
        switch (CmpExpn(&pCurr->data, &pNode->data)) { // 比较指数
            case 1: { // 当前节点指数大于待插入节点, 遍历下一个节点
                break;
            }
            case 0: { // 当前节点指数等于待插入节点, 系数相加后修改当前节点即可
                float sum = AddCoef(&pCurr->data, &pNode->data);
                ret = SetCurrElem(p, pCurr, sum);
                CHECK_RET(ret);
                ret = FreeNode(&pNode); // 释放内存
                CHECK_RET(ret);
                // break;
                return OK;
            }
            case -1: { // 当前节点指数小于待插入节点, 将待插入节点插入该节点前
                ret = InsertBefore(p, pCurr, pNode);
                CHECK_RET(ret);
                break;
            }
        }
        pPrev = pCurr;
        pCurr = pCurr->next;
    }

    if (!pCurr) { // 最后一个节点的指数都大于待插入节点, 插入尾部
        ret = InsertAtTail(p, &pNode->data);
        CHECK_RET(ret);
        ret = FreeNode(&pNode);
        CHECK_RET(ret);
    }

    return OK;
}

/**
 * @brief p3 = p1 * p2, p1,p2 保留
 * 
 * @param p1 
 * @param p2 
 * @param p3 
 * @return Status 
 */
Status MultiplyPolyn(polynomial p1, polynomial p2, polynomial p3)
{
    if (!p1 || !p2 || !p3)
        return ERROR;
    
    Node *q1 = p1->next, *q2 = p2->next;
    Status ret;

    while (q1) { // p2 链表的每一项都要和 p1 的每一项相乘
        while (q2 != NULL) {
            // 系数相乘, 指数相加
            float coefResult = q1->data.coef * q2->data.coef;
            int expnResult = q1->data.expn + q2->data.expn;
            Node *pNew = NULL;
            ElemType resultElem = {
                .coef = coefResult,
                .expn = expnResult
            };
            ret = MakeNode(&pNew, resultElem);
            CHECK_RET(ret);
            ret = PolynaddNode(p3, pNew); // 释放还是插入链表, 内存由该函数管理
            CHECK_RET(ret);
            // TODO:
            // FreeNode(&pNew);
        }
        q2 = p2->next; // 重置 q2, 重新开始遍历 p2 链表, 每一个都与 q1 相乘
        q1 = q1->next; // q1 指向下一个节点
    }

    return OK;
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
void PolynTest2(void)
{
    polynomial p1, p2, p3;
    // 有序链表
    // TODO: sortLinkList();
    ElemType arr1[] = {{21, 99}, {3, 55}, {1, 44}, {22, 2}, {-5, 1}, {5, 0}};
    ElemType arr2[] = {{15, 100}, {3, 55}, {-1, 44}, {9, 1}, {55, 0}};
    Status ret;

    printf("create p1:\r\n");
    ret = CreatPolyn(&p1, arr1, sizeof(arr1) / sizeof(arr1[0]));
    CHECK_RET_OP(ret, "create p1");
    ret = Traverse(p1, "create p1", print_poly_node_info);

    printf("create p2:\r\n");
    ret = CreatPolyn(&p2, arr2, sizeof(arr2) / sizeof(arr2[0]));
    CHECK_RET_OP(ret, "create p2");
    ret = Traverse(p2, "create p2", print_poly_node_info);

    // printf("polyn add:\r\n");
    // ret = AddPolyV1(p1, p2);
    // CHECK_RET_OP(ret, "p1=p1+p2");
    // ret = Traverse(p1, "p1=p1+p2", print_poly_node_info);
    // CHECK_RET_OP(ret, "p1=p1+p2");

    printf("polyn add:\r\n");
    ret = SubtractPolyn(p1, p2);
    CHECK_RET_OP(ret, "p1=p1+p2");
    ret = Traverse(p1, "p1=p1+p2", print_poly_node_info);
    CHECK_RET_OP(ret, "p1=p1+p2");

    printf("polyn multi:\r\n");
    ret = SubtractPolyn(p1, p2);
    CHECK_RET_OP(ret, "p1=p1+p2");
    ret = Traverse(p1, "p1=p1+p2", print_poly_node_info);
    CHECK_RET_OP(ret, "p1=p1+p2");

    return;
}

#endif