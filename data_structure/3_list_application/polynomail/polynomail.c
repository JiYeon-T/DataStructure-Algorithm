
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

enum { // 作为两个值比较的结果返回
    INCREASE = 0, // 增序
    EQUAL,
    DECREASE // 降序
};

/**
 * @brief allocate memory for item_t * pointer
 * 
 * @param[out] p_elem item_t ** == ElemType* type
 * @param[in] p_item pointer to item value
 * @return
*/
Status MakeElemPolyItem(ElemType *p_elem, item_t *p_item)
{
    if (!p_elem || !p_item) {
        return false;
        LOG_E("null ptr");
    }
    
    item_t *p_temp = malloc(sizeof(item_t));
    if (!p_temp)
        return ERROR;

    memcpy(p_temp, p_item, sizeof(item_t));

    *p_elem = p_temp;
    LOG_D("alloc poly item elem:%p", *p_elem);

    return OK;
}

/**
 * @brief free memory allocated by ${MakeElemPolyItem}
 * 
 * @param[in] elem Elemtype type(item_t*)
*/
Status FreeElemPolyItem(ElemType elem)
{
    if (!elem)
        return ERROR;
    LOG_D("free poly item elem:%p", elem);
    free(elem);

    return OK;
}

/**
 * @brief allocate memory for node
 * 
 * @param[out] p struct Node **
 * @param[in] p_item
 * @return
*/
Status MakeNodePolyItem(struct Node **p, item_t *p_item)
{
    Status ret;
    ElemType elem;

    if (!p)
        return ERROR;

    ret = MakeElemPolyItem(&elem, p_item);
    CHECK_RET(ret);

    ret = MakeNode(p, elem);
    CHECK_RET(ret);

    return OK;
}

/**
 * @brief FreeNodeStr free memory allocated by ${MakeNodePolyItem}
 * 
 * @param[in] p
*/
void FreeNodePolyItem(struct Node *p)
{
    if (!p) {
        return;
    }

    if (p->data) {
        FreeElemPolyItem(p->data);
    }

    FreeNode(p);

    return;
}

/**
 * @brief 比较指数的大小
 *
 * @param a item_t *(ElemType)
 * @param b
 * @return int INCREASE:a>b; EQUAL:a==b; DECREASE:a<b; INVALID_VAL:ERROR
 */
static int CmpPolyItemExpn(item_t *a, item_t *b)
{
    if(!a || !b){
        printf("null ptr\r\n");
        return INVALID_VAL;
    }

    if (a->expn > b->expn){
        return DECREASE;
    } else if(a->expn == b->expn) {
        return EQUAL;
    } else{
        return INCREASE;
    }
}

/**
 * @fun 两个节点的系数数相加
 * 
 * @param[in] a
 * @paramp[in] b
*/
static int AddCoef(item_t *a, item_t *b)
{
    return (a->coef + b->coef);
}

/**
 * @fun 两个节点的指数相加
 * 
 * @param[in] a
 * @paramp[in] b
*/
static int AddExpn(item_t *a, item_t *b)
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
Status CreatPolyn(polynomial *p, item_t *pArr, int arrSize)
{
    if (!p || !pArr || arrSize <= 0)
        return ERROR;

    Status ret;
    item_t **itemPtrArr = malloc(sizeof(item_t*) * arrSize);
    if (!itemPtrArr)
        return ERROR;
    LOG_D("item_t* size:%d", sizeof(item_t*));

    // create item_t* pointer array:{p1, p2, p3...}
    // p1~pn pointer to a dynamic allocated memory
    for (int i = 0; i < arrSize; ++i) {
        itemPtrArr[i] = malloc(sizeof(item_t));
        if (!itemPtrArr[i]) {
            return ERROR;
        }
        LOG_D("alloc poly item elem:%p", itemPtrArr[i]);
        memcpy(itemPtrArr[i], &pArr[i], sizeof(item_t));
    }
    // ret = InitWithArray((LinkList*)p, (ElemType*)itemPtrArr, arrSize);
    ret = InitWithArray(p, itemPtrArr, arrSize);
    CHECK_RET(ret);

    free(itemPtrArr);

    return OK;
}

/**
 * @brief destory polynomial, deinit linklist(include head node)
 *
 * @param p
 * @return Status
 */
Status DestroyPolyn(polynomial *p)
{
    return DestroyList(p); //DestroyList((LinkList*)p);
}

/**
 * @brief Get polynomial length
 *
 * @param p
 * @return int
 */
size_t PolynLength(const polynomial *p)
{
    return ListLength(p);
}

/**
 * @brief Traverse the linklist and print node information
 *
 * @param polyn polynomial type(Node *), linklist head pointer
 */
Status PrintPolyn(const polynomial *polyn, Status (*visit)(ElemType elem))
{
    if (!polyn || !visit)
        return ERROR;

    Status ret = ListTraverse(polyn, visit);
    CHECK_RET(ret);
}

/**
 * @brief p1 = p1 + p2, 结果保存到 p1, p2保留
 *        (1) 将原来的节点直接从链表上拿下来; 会修改原始值的方式;
 *        (2) 拷贝 -> 创建新节点 -> 插入;
 *        一元多项式的加法, 例如(按照指数由大到小排列):
 *        l1:a1x^100 + a2x^15 + a3x^2 + a4x^1 + a5
 *        l2:b1x^99 + b2x^10 + b3x^5 + b4x^1 + b5
 *        求 l1 = l1+l2?
 * 
 *        算法(与归并排序类似):
 *        1.  假设 q1, q2 分别指向 p1, p2(前提是有序链表)的某一个节点, 比较 p1, p2 的指数部分, 指数部分比较大小有三种情况
 *        (1) q1 < q2, 将 q1 插入到结果链表(引用);
 *        (2) q1 > q2, 将 q2 插入到结果链表(引用);
 *        (3) q1 == q2, 分以下两种情况
 *        a. 对于具有相同指数的项, 系数相加,和不为 0 则构成多项式中的一项; 和为 0, 则删除该项
 *        b. 对于没有相同系数的项, 则直接添加到结果链表中;
 *        key(1) 拷贝数据 -> 创建新节点 -> 插入结果链表(不直接从原链表上拿数据下来);
 *
 * @param p1 p1, p2 都是有序链表, 高次数写在前面(降序排列)TODO:如果是无序的链表, 要进行排序操作, type:Node**
 * @param p2
 * @return Status
 */
Status AddPolyV1(polynomial *p1, polynomial *p2)
{
    if (!p1) {
        return ERROR;
    }

    if (!p2 || !p2->head || ListEmpty(p2)) // p2 is empty, p1 + p2 = p1
        return OK;

    Status ret;

    struct Node *q1 = p1->head->next;
    struct Node *q2 = p2->head->next; // 分别指向第一个节点
    item_t *poly_item1, *poly_item2;
    struct Node *p_delete = NULL;

    while (q1 && q2) { // 按照指数从大到小排序
        // // 比较两个元素的指数部分
        poly_item1 = (item_t*)q1->data;
        poly_item2 = (item_t*)q2->data;
        switch (CmpPolyItemExpn(poly_item1, poly_item2)) {
            case DECREASE: { // q1 的指数部分比较大, q1 移动到下一位, q2 不移动
                q1 = NextPos(p1, q1);
                break;
            }
            case EQUAL: { // 两个指数部分一样大, 系数相加
                float coef_sum = poly_item1->coef + poly_item2->coef;
                if (coef_sum != 0) { // 结果直接写入 q1 节点即可, 删除 q2
                    item_t new_poly_item = {
                        .coef = coef_sum,
                        .expn = poly_item1->expn
                    };
                    // Free allocated data space
                    item_t *p_data = (item_t*)GetCurrElem(q1);
                    CHECK_NOT_NULL(p_data);
                    ret= FreeElemPolyItem((ElemType)p_data);
                    CHECK_RET(ret);
                    // create new data space
                    ret = MakeElemPolyItem(&p_data, &new_poly_item);
                    CHECK_RET(ret);

                    ret = SetCurrElem(q1, p_data); // 直接在 p1 中修改指针域
                    CHECK_RET(ret);

                    p_delete = q2;
                    q2 = NexPos(p2, q2);
                    ret = DeleteNode(p2, p_delete);
                    CHECK_RET(ret);
                } else { // 系数部分和为 0, q1, q2 都删除
                    p_delete = q1;
                    q1 = NextPos(p1, q1);
                    ret = DeleteNode(p1, p_delete);
                    CHECK_RET(ret);

                    p_delete = q2;
                    q2 = NexPos(p2, q2);
                    ret = DeleteNode(p2, p_delete); // q2 肯定是 p2 的第一个节点
                    CHECK_RET(ret);
                }
                break;
            }
            case INCREASE: { // q2 的指数部分比较大, q2 插入到 q1 前面(链表 p1 中)
                q2 = NextPos(p2, q2); // qb 指向下一个节点
                ret = DelFirst(p2, &p_delete);
                CHECK_RET(ret);
                ret = InsertBefore(p1, q1, p_delete);
                CHECK_RET(ret);
                // q1 = q1->next; // 避免出现重复出现 指数相同的项
                break;
            }
            default: {
                LOG_E("error expression");
                return;
            }
        }
    }

    if (!ListEmpty(p2)) {
        Append(p1, q2);
    }

    // if (!ListEmpty(pa)) { // p1 = p1+p2, 不需要进行额外操作
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
Status AddPolyV2(polynomial *p1, polynomial *p2)
{
//     if(!p1 || !p2){
//         return ERROR;
//     }
//     // TODO:
//     return OK;
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
Status SubtractPolyn(polynomial *p1, polynomial *p2)
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
static Status PolynaddNode(polynomial p, struct Node *pNode)
{
    // if (!p || !pNode)
    //     return ERROR;
    // Status ret;
    // Node *pPrev = p, *pCurr = p->next;

    // while (pCurr) {
    //     switch (CmpExpn(&pCurr->data, &pNode->data)) { // 比较指数
    //         case 1: { // 当前节点指数大于待插入节点, 遍历下一个节点
    //             break;
    //         }
    //         case 0: { // 当前节点指数等于待插入节点, 系数相加后修改当前节点即可
    //             float sum = AddCoef(&pCurr->data, &pNode->data);
    //             ret = SetCurrElem(p, pCurr, sum);
    //             CHECK_RET(ret);
    //             ret = FreeNode(&pNode); // 释放内存
    //             CHECK_RET(ret);
    //             // break;
    //             return OK;
    //         }
    //         case -1: { // 当前节点指数小于待插入节点, 将待插入节点插入该节点前
    //             ret = InsertBefore(p, pCurr, pNode);
    //             CHECK_RET(ret);
    //             break;
    //         }
    //     }
    //     pPrev = pCurr;
    //     pCurr = pCurr->next;
    // }

    // if (!pCurr) { // 最后一个节点的指数都大于待插入节点, 插入尾部
    //     ret = InsertAtTail(p, &pNode->data);
    //     CHECK_RET(ret);
    //     ret = FreeNode(&pNode);
    //     CHECK_RET(ret);
    // }

    // return OK;
}

/**
 * @brief p3 = p1 * p2, p1,p2 保留
 *        TODO:
 * 
 * @param p1 
 * @param p2 
 * @param p3 
 * @return Status 
 */
Status MultiplyPolyn(polynomial *p1, polynomial *p2)
{
    // if (!p1 || !p2 || !p3)
    //     return ERROR;
    
    // Node *q1 = p1->next, *q2 = p2->next;
    // Status ret;

    // while (q1) { // p2 链表的每一项都要和 p1 的每一项相乘
    //     while (q2 != NULL) {
    //         // 系数相乘, 指数相加
    //         float coefResult = q1->data.coef * q2->data.coef;
    //         int expnResult = q1->data.expn + q2->data.expn;
    //         Node *pNew = NULL;
    //         ElemType resultElem = {
    //             .coef = coefResult,
    //             .expn = expnResult
    //         };
    //         ret = MakeNode(&pNew, resultElem);
    //         CHECK_RET(ret);
    //         ret = PolynaddNode(p3, pNew); // 释放还是插入链表, 内存由该函数管理
    //         CHECK_RET(ret);
    //         // TODO:
    //         // FreeNode(&pNew);
    //     }
    //     q2 = p2->next; // 重置 q2, 重新开始遍历 p2 链表, 每一个都与 q1 相乘
    //     q1 = q1->next; // q1 指向下一个节点
    // }

    // return OK;
}
/*************************************************************************************
 * Elemtype - PolyItem_t
 *************************************************************************************/
/**
 * @brief linklist node print function
 *      only print current node information
 * @param[in] elem pointer type
*/
static void VisitPolyItem(ElemType elem)
{
    if (!elem)
        return;
    item_t *item = (item_t*)elem;
    printf("%2.2f*x^%d", item->coef, item->expn);
}

/**
 * @brief 系数增序
*/
static bool ComparePolyItemCoefInorder(ElemType e1, ElemType e2)
{
    if (!e1 || !e2) {
        return false;
        LOG_E("null ptr");
    }
    return ((item_t*)e1)->coef <= ((item_t*)e2)->coef;
}

/**
 * @brief 指数增序
*/
static bool ComparePolyItemExpenInorder(ElemType e1, ElemType e2)
{
    if (!e1 || !e2) {
        return false;
        LOG_E("null ptr");
    }
    return ((item_t*)e1)->expn <= ((item_t*)e2)->expn;
}

// linklist basic operation
void PolynTest1(void)
{
    printf("polynomial test1\n");
    polynomial polyn = {.head = NULL, .len = 0};
    Status ret;
    item_t polyn_item_array[] = {{1.5, 1}, {2.5, 2}, {3.5, 3}};
    item_t *p_temp, *p_insert;

    ret = CreatPolyn(&polyn, polyn_item_array, ARRAY_SIZE(polyn_item_array));
    CHECK_RET(ret);
    LOG_D("poly item number:%d", PolynLength(&polyn));
    ret = PrintPolyn(&polyn, VisitPolyItem);
    CHECK_RET(ret);

    // insert at tail again
    ret = MakeNodePolyItem(&p_insert, &polyn_item_array[0]);
    CHECK_RET(ret);
    ret = Append(&polyn, p_insert);
    CHECK_RET(ret);
    ret = MakeNodePolyItem(&p_insert, &polyn_item_array[1]);
    CHECK_RET(ret);
    ret = Append(&polyn, p_insert);
    CHECK_RET(ret);
    ret = MakeNodePolyItem(&p_insert, &polyn_item_array[2]);
    CHECK_RET(ret);
    ret = Append(&polyn, p_insert);
    CHECK_RET(ret);
    LOG_D("poly item number:%d", PolynLength(&polyn));
    ret = PrintPolyn(&polyn, VisitPolyItem);
    CHECK_RET(ret);

    ret = DestroyPolyn(&polyn);
    CHECK_RET(ret);

    LOG_D("poly item number:%d", PolynLength(&polyn));
    ret = PrintPolyn(&polyn, VisitPolyItem);
    CHECK_RET(ret);
}

// polynomial math operation
void PolynTest2(void)
{
    polynomial p1, p2, p3;
    // 有序链表
    // TODO: sortLinkList();
    Status ret;
    item_t polynArr1[] = {{21, 99}, {3, 55}, {1, 44}, {22, 2}, {-5, 1}, {5, 0}};
    item_t polynArr2[] = {{15, 100}, {3, 55}, {-1, 44}, {9, 1}, {55, 0}};

    LOG_D("create p1:\r\n");
    ret = CreatPolyn(&p1, polynArr1, ARRAY_SIZE(polynArr1));
    CHECK_RET(ret);
    ret = PrintPolyn(&p1, VisitPolyItem);
    CHECK_RET(ret);

    LOG_D("create p2:\r\n");
    ret = CreatPolyn(&p2, polynArr2, ARRAY_SIZE(polynArr2));
    CHECK_RET(ret);
    ret = PrintPolyn(&p2, VisitPolyItem);
    CHECK_RET(ret);

    LOG_D("polyn add:\r\n");
    ret = AddPolyV1(&p1, &p2);
    CHECK_RET(ret);
    ret = PrintPolyn(&p1, VisitPolyItem);
    CHECK_RET(ret);

    // printf("polyn subtract:\r\n");
    // ret = SubtractPolyn(p1, p2);
    // CHECK_RET_OP(ret, "p1=p1+p2");
    // ret = Traverse(p1, "p1=p1+p2", print_poly_node_info);
    // CHECK_RET_OP(ret, "p1=p1+p2");

    // printf("polyn multi:\r\n");
    // //TODO:
    // // ret = MultiplyPolyn(p1, p2);
    // CHECK_RET_OP(ret, "p1=p1+p2");
    // ret = Traverse(p1, "p1=p1+p2", print_poly_node_info);
    // CHECK_RET_OP(ret, "p1=p1+p2");


    ret = DestroyPolyn(&p1);
    CHECK_RET(ret);
    ret = DestroyPolyn(&p2);
    CHECK_RET(ret);
}

#endif // DATA_STRUCTURE_POLYNOMAIL
