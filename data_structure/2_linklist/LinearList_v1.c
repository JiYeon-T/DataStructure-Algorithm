#include "LinearList_v1.h"


#if defined(DataStructLinearListV1) && (DataStructLinearListV1 == 1)

/**
 * @brief: Init
*/
Status InitList(SqList *L)
{
    memset(L, 0, sizeof(SqList));
    return OK;
}

/**
 * @brief deint
 * 
*/
Status DestroyList(SqList *L)
{
    memset(L, 0, sizeof(SqList));
    return OK;
}

/**
 * @brief  clear
 * 
*/
Status ClearList(SqList *L)
{
    memset(L, 0, sizeof(SqList));
    // L->length = 0;
    return OK;
}

/**
 * @brief  Whether empty or not
 * 
*/
bool ListEmpty(const SqList *L)
{
    return (L->length ? true : false);
}

/**
 * @brief get element number in the list
 * 
*/
size_t ListLength(const SqList *L)
{
    return L->length;
}

/**
 * @brief  Get
 *
 * @param[in]  L
 * @param[in]  i start from 1
 * @param[out]  e
 * @ret
*/
Status GetElem(const SqList *L, int i, ElemType *e)
{
    if (L->length == 0 || i < 1 || i > L->length)
        return ERROR;
    
    *e = L->data[i - 1];

    return OK;
}

/**
 * @brief: Set
 *
 * @param[in] L
 * @param[in] i start from 1
 * @param[out] e
 * @ret
*/
Status SetElem(SqList *L, int i, ElemType e)
{
    if (L->length == MAXSIZE || i > MAXSIZE)
        return ERROR;
    
    L->data[i-1] = e;

    return OK;
}

/**
 * @brief  Put, insert at list tail
 *
 * @param[in] L
 * @param[in] e
 * @ret
*/
Status PutElem(SqList *L, ElemType e)
{
    if (L->length == MAXSIZE)
        return ERROR;

    L->data[L->length] = e;
    L->length++;

    return OK;
}

static bool equal(ElemType val1, ElemType val2)
{
    return (val1 == val2);
}

/**
 * @brief return the first element that match the compare function(@param[comp])
 *
 * @param[in] L
 * @param[in] e
 * @param[in] comp
 * @ret return element index, start from 1; fail return 0
*/
int LocateElem(const SqList *L, ElemType e, comp_fun comp)
{
    if (!L)
        return 0;
    int ret = 0;

    for (int i = 0; i < L->length; ++i) {
        if (comp(L->data[i], e)){
            ret = i + 1; //start from 1
            break;
        }
    }

    return ret;
}

/**
 * @brief get previous element
 *
 * @param[in]  L
 * @param[in]  cur_e
 * @param[out] prev_e
 * @ret
*/
Status PriorElem(const SqList *L, ElemType cur_e, ElemType *prev_e)
{
    if (!L || !prev_e)
        return ERROR;

    int i = LocateElem(L, cur_e, equal);
    if (i == 0 || i == 1) // first element does not have previous node
        return ERROR;
        
    *prev_e = L->data[i-2];

    return OK;
}

/**
 * @brief get next element
 *
 * @param[in]  L
 * @param[in]  cur_e
 * @param[out] next_e
 * @ret
*/
Status NextElem(const SqList *L, ElemType cur_e, ElemType *next_e)
{
    if (!L || !next_e)
        return ERROR;

    int i = LocateElem(L, cur_e, equal);
    if (i == 0 || i == MAXSIZE) // last element does not have next node
        return ERROR;
        
    *next_e = L->data[i];

    return OK;
}

/**
 * @brief: 在第 i 个位置前插入
 * 时间复杂度:O(n)
 *
 * @param[in] L
 * @param[in] i start from 1(第 i 个元素)
 * @param[in] e elem
 * @ret
*/
Status ListInsert(SqList *L, int i, ElemType e)
{
    if (L->length == MAXSIZE) // full sequence list
        return ERROR;
    
    // 插入位置不可以超出已有数据范围, 否则可能会不连续
    // if (i < 1 || i > L->length)
    //     return ERROR;
    if (i < 1)
        return ERROR;
    
    
    // if (i <= L->length) { // 插入数据不在表尾, 需要移动元素
        // k: 要移动的元素的下标, 移动方法:data[k+1] = data[k]
        // i-1:最后一个要移动的元素的下标: i-1
        for (int k = L->length - 1; k >= i - 1; --k) {
            // printf("k:%d\n", k);
            L->data[k+1] = L->data[k];
        }
    // }

    L->data[i-1] = e; // 插入新元素
    L->length++;

    return OK;
}

/**
 * @brief: 删除第 i 个元素
 * 时间复杂度:O(n)
 *
 * @param[in] L
 * @param[in] i start from 1
 * @param[out] e element data
 * @ret
*/
Status ListDelete(SqList *L, int i, ElemType *e)
{
    int k;

    if (L->length == 0)
        return ERROR;
    
    if (i < 1 || i > L->length)
        return ERROR;
    
    *e = L->data[i-1];

    // if (i < L->length)
    for (k = i; k < L->length; k++)
        L->data[k-1] = L->data[k];

    L->length--;

    return OK;
}

/**
 * @brief: Traverse
*/
Status ListTraverse(SqList *L, visit_fun visit)
{
    if (!L)
        return ERROR;
    printf("Traverse:\n");
    for (int i = 0; i < L->length; ++i) {
        printf("[%d]:", i);
        visit(L->data[i]);
        printf("\n");
    }
    printf("\n");

    return OK;
}

static void visit(ElemType e)
{
    printf("%d", e);
}

/**
 * @brief A = A U B, 并集
 * 将 B 中的元素在 A 中进行遍历, 不存在插入 A 末尾即可
 * 时间复杂度:O(m*n)
 * 
 * @param[in] La
 * @param[in] Lb
 * @ret
*/
void UnionList(SqList *La, SqList *Lb)
{
    int La_len = ListLength(La), Lb_len = ListLength(Lb);
    ElemType elem_b;
    Status ret;

    for (int i = 1; i <= Lb_len; ++i) {
        ret = GetElem(Lb, i, &elem_b); // GetElem i start from 1
        if (ret != OK) {
            break;
        }
        // ListInsert(La,)
        PutElem(La, elem_b);
    }

    return OK;
}

/**
 * @brief La 和 Lb 都是有序链表, Lc = La + Lb 且, Lc 也是有序排列
 *        归并排序的后合并部分
 *        e.g. 两个人有两手有序的牌, 进行合并, A 的每一张牌与 b 的每一张牌比较
 *        时间复杂度:O(m + n)
 * @param[in]  La 从小到大排序
 * @param[in]  Lb
 * @param[out] Lc
 * @ret
*/
void MergeList(const SqList *La, const SqList *Lb, SqList *Lc)
{
    if (!La || !Lb || !Lc)
        return;

    InitList(Lc);
    int La_len = ListLength(La), Lb_len = ListLength(Lb), Lc_len = 0;
    ElemType elem_a, elem_b;
    int i = 1, j = 1;

    while ((i <= La_len) && (j <= Lb_len)) { // La, Lb 均有牌
        GetElem(La, i, &elem_a);
        GetElem(Lb, j, &elem_b);
        if (elem_a <= elem_b) { // ai 小, 将 ai 插入 Lc, a 拿下一张牌
            PutElem(Lc, elem_a);
            ++i;
        } else { // bi 小, 将 bi 插入 Lc, b 拿下一张牌
            PutElem(Lc, elem_b);
            ++j;
        }
        ++Lc_len;
    }

    // 外面的 if 可以注释掉
    // if (i > La_len) { // a 没有手牌了, 将 b 剩余的牌全部插到 Lc 末尾
        while (j <= Lb_len) {
            GetElem(Lb, j, &elem_b);
            PutElem(Lc, elem_b);
            ++Lc_len;
            ++j;
        }
    // }

    // if (j > Lb_len) { // b 没有手牌了, 将 a 剩余的牌全部插到 Lc 末尾
        while (i <= La_len) {
            GetElem(La, i, &elem_a);
            PutElem(Lc, elem_a);
            ++Lc_len;
            ++i;
        }
    // }

    return;
}

void LinearListV1Test(void)
{
    SqList L;
    Status ret;
    ElemType e;
    printf("Linear List Test: size:%d\n\n", sizeof(L));
    ret = InitList(&L);
    CHECK_RET(ret);

    ret = ListTraverse(&L, visit);
    CHECK_RET(ret);
    ret = PutElem(&L, 1);
    CHECK_RET(ret);
    ret = PutElem(&L, 2);
    CHECK_RET(ret);
    ret = PutElem(&L, 3);
    CHECK_RET(ret);
    ret = PutElem(&L, 4);
    CHECK_RET(ret);
    ret = PutElem(&L, 5);
    CHECK_RET(ret);
    ret = PutElem(&L, 6);
    CHECK_RET(ret);
    ret = ListTraverse(&L, visit);
    CHECK_RET(ret);

    ret = GetElem(&L, 2, &e);
    CHECK_RET(ret);
    printf("arr 2d val:%d list len:%d\n", e, ListLength(&L));

    ret = GetElem(&L, 6, &e);
    CHECK_RET(ret);
    printf("arr 6d val:%d\n", e);

    ret = SetElem(&L, 3, 5);
    CHECK_RET(ret);
    ret = ListTraverse(&L, visit);
    CHECK_RET(ret);

    ret = ListInsert(&L, 3, 0);
    CHECK_RET(ret);
    ret = ListTraverse(&L, visit);
    CHECK_RET(ret);
    printf("insert at 3 len:%d\n", ListLength(&L));

    ret = ListDelete(&L, 1, &e);
    CHECK_RET(ret);
    printf("delte 1 val:%d list len:%d\n", e, ListLength(&L));
    ret = ListTraverse(&L, visit);
    CHECK_RET(ret);

    ret = ClearList(&L);
    CHECK_RET(ret);
    printf("clear, len:%d\n", ListLength(&L));
    ret = ListTraverse(&L, visit);
    CHECK_RET(ret);

    ret = DestroyList(&L);
    CHECK_RET(ret);
    printf("destroy:\n");
    ret = ListTraverse(&L, visit);
    CHECK_RET(ret);
}

void LinearListV1Test2(void)
{
    SqList L1, L2, L3;

    InitList(&L1);
    PutElem(&L1, 1);
    PutElem(&L1, 1);
    PutElem(&L1, 3);
    PutElem(&L1, 5);
    PutElem(&L1, 7);
    PutElem(&L1, 9);
    printf("L1:");
    ListTraverse(&L1, visit);

    InitList(&L2);
    PutElem(&L2, 2);
    PutElem(&L2, 2);
    PutElem(&L2, 4);
    PutElem(&L2, 6);
    PutElem(&L2, 8);
    PutElem(&L2, 10);
    PutElem(&L2, 12);
    PutElem(&L2, 14);
    PutElem(&L2, 16);
    printf("L2:");
    ListTraverse(&L2, visit);

    MergeList(&L1, &L2, &L3);
    printf("L3:");
    ListTraverse(&L3, visit);

    UnionList(&L1, &L2);
    printf("L1:");
    ListTraverse(&L1, visit);

}

#endif