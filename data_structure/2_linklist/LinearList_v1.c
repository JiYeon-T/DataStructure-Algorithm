#include "LinearList_v1.h"


#if defined(DataStructLinearListV1) && (DataStructLinearListV1 == 1)

/**
 * @fun: Init
*/
Status ListInit(SqList *L)
{
    memset(L, 0, sizeof(SqList));
    return OK;
}

/**
 * @fun: Get
 * @param[in] L
 * @param[in] i start from 1
 * @param[out] e
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
 * @fun: Set
 * @param[in] L
 * @param[in] i start from 1
 * @param[out] e
 * @ret
*/
Status SetElem(SqList *L, int i, ElemType e)
{
    if (L->length == MAXSZIE || i > MAXSZIE)
        return ERROR;
    
    L->data[i-1] = e;

    return OK;
}

/**
 * @fun: Put, insert at list tail
 * @param[in] L
 * @param[in] e
 * @ret
*/
Status PutElem(SqList *L, ElemType e)
{
    if (L->length == MAXSZIE)
        return ERROR;

    L->data[L->length] = e;
    L->length++;

    return OK;
}

/**
 * @fun: 在第 i 个位置前插入
 * @param[in] L
 * @param[in] i start from 1
 * @param[in] e elem
 * @ret
*/
Status ListInsert(SqList *L, int i, ElemType e)
{
    int k;

    if (L->length == MAXSZIE) // full sequence list
        return ERROR;
    
    if (i < 1 || i > L->length + 1)
        return ERROR;
    
    // if (i <= L->length) { // 插入数据不在表尾, 需要移动元素
        for (k = L->length - 1; k >= i - 1; --k) {
            L->data[k+1] = L->data[k];
        }
    // }

    L->data[i-1] = e; // 插入新元素
    L->length++;

    return OK;
}

/**
 * @fun: 删除第 i 个元素
 * @param[in] L
 * @param[in] i start from 1
 * @param[out] e element data
 * @ret
*/
Status ListDelte(SqList *L, int i, ElemType *e)
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
 * @fun: 遍历
*/
Status Traverse(const SqList *L)
{
    // if (L->length == 0)
    //     return ERROR;

    printf("Traverse:\n");
    for (int ix = 0; ix < L->length; ++ix)
        printf("%d\t", L->data[ix]);
    printf("\n");

    return OK;
}

void LinearListV1Test(void)
{
    SqList L;
    Status ret;
    ElemType e;
    printf("Linear List Test:\n\n");
    ret = ListInit(&L);
    CHECK_RET(ret);

    ret = Traverse(&L);
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
    ret = Traverse(&L);
    CHECK_RET(ret);

    ret = GetElem(&L, 2, &e);
    CHECK_RET(ret);
    printf("arr 2d val:%d\n", e);

    ret = GetElem(&L, 6, &e);
    CHECK_RET(ret);
    printf("arr 6d val:%d\n", e);

    ret = SetElem(&L, 3, 5);
    CHECK_RET(ret);
    ret = Traverse(&L);
    CHECK_RET(ret);

    ret = ListInsert(&L, 3, 0);
    CHECK_RET(ret);
    ret = Traverse(&L);
    CHECK_RET(ret);

    ret = ListDelte(&L, 1, &e);
    CHECK_RET(ret);
    printf("delte 1 val:%d\n", e);
    ret = Traverse(&L);
    CHECK_RET(ret);

}
#endif