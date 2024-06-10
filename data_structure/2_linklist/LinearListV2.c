#include "LinearListV2.h"

#include <errno.h>

#if defined(DataStructLinearListV2) && (DataStructLinearListV2 == 1)

extern int errno;


/**
 * @brief: initialize list, allocate memory
 * 
 * @param: L
 */
Status InitList(SqList *L)
{
    if (!L) {
        fprintf(stderr, "null ptr\n");
        return ERROR;
    }
    /** 指针的值实际上保存的就是传入的变量的地址 **/
//    printf("address:%#p, pointer's address(local variable address):%#p\n", L, &L);
    L->elem = (ElemType*)malloc(sizeof(ElemType) * DEFAULT_LIST_SIZE);
//    (*L).elem = (ElemType*)malloc(sizeof(ElemType) * DEFAULT_LIST_SIZE);
   printf("malloc address:%#p\n", L->elem);
    if (!L->elem) {
        fprintf(stderr, "malloc failed:%d", errno);
        perror("malloc failed\n");
        return ERROR;
    }
    L->curLength = 0;
    L->listSize = DEFAULT_LIST_SIZE;

    return OK;
}

/**
 * @brief: destroy
 * : free memeory
 *
 * @param: L
*/
Status DestroyList(SqList *L)
{
    if (!L) {
        fprintf(stderr, "null ptr\n");
        return ERROR;
    }
    free(L->elem);
    L->elem = NULL;
    L->listSize = 0;
    L->curLength = 0;
    
    return OK;
}

/**
 * @brief: clear, does not free memory, only delte element
 * 
 * @param: L
 */
Status ClearList(SqList *L)
{
    if (!L) {
        fprintf(stderr, "null ptr\n");
        return ERROR;
    }
    memset((uint8_t*)L->elem, 0, (sizeof(ElemType) * L->listSize));
    L->listSize = 0;
    L->curLength = 0;
    return OK;
}

/**
* @brief: empty ?
 *
 * @param: L
 */
bool ListEmpty(const SqList *L)
{
    if (!L) {
        fprintf(stderr, "null ptr\n");
        return true;
    }

    return L->curLength ? false : true;
}

/**
 * @brief: empty ?
 *       get the element number
 * 
 * @param: L
 */
size_t ListLength(const SqList *L)
{
    if(!L){
        fprintf(stderr, "null ptr\n");
        return 0;
    }
    return L->curLength;
}

/**
 * @brief: get
 *  get the element number, 
 * 
 * @param[in] L
 * @param[in] idx idx from 0 to (N-1), N = ElemNum
 * @param[out] val
 * @ret
 */
Status GetElem(const SqList *L, int idx, ElemType *val)
{
    if (!L) {
        fprintf(stderr, "null ptr\n");
        return ERROR;
    }
    if(idx >= L->curLength){
        fprintf(stderr, "idx too large:%d %d", idx, L->curLength);
        return ERROR;
    }

    // L->elem[idx] 是 ElemType 类型, 相当于解引用
    // *val 也是解引用
    *val = L->elem[idx];

    return OK;
}

/**
 * @brief: set 
 * set the element number, 
 * 
 * @param[in] L
 * @param[in] idx idx from 0 to (N-1), N = ElemNum
 * @param[in] val
 */
Status SetElem(SqList *L, int idx, ElemType val)
{
    if(!L || idx >= L->listSize){
        fprintf(stderr, "null ptr:%s\n", __func__);
        return ERROR;
    }

    L->elem[idx] = val;
    ++L->curLength;
    return OK;
}


/**
 * @brief put elem at tail
 * 
 * @param[in] L
 * @param[in] e
 * @ret
 * 
*/
Status PutElem(SqList *L, ElemType e)
{
    if (!L)
        return ERROR;
    
    L->elem[L->curLength] = e;
    ++L->curLength;

    return OK;
}

/**
 * @brief:  能否定位到这个元素
 * 
 * @param[in] L
 * @param[in] e
 * @param[in] fun
 * @ret: index, 下标(0~N-1); UINT32_MAX not found
 */
int LocateElem(const SqList *L, ElemType e, 
                bool (*comp_fun)(ElemType val1, ElemType val2))
{
    if (!L) {
        fprintf(stderr, "null ptr:%s\n", __func__);
        return ERROR;
    }

    ElemType *p = L->elem; // 指针起点
    int i = 0;
    while (i < L->curLength && !(*comp_fun)(*p, e)) {
        ++i;
        ++p;
    }

    if (i == L->curLength)
        return INT_MAX;
    else
        return i;
}

/**
 * @brief:  prior element
 *
 * @param: L
 * @ret:
 */
Status PriorElem(const SqList *L, ElemType elem, ElemType *prev_e)
{
    if (!L) {
        fprintf(stderr, "null ptr\n");
        return ERROR;
    }

    // 顺序表, 所以不需要记录当前位置, 只需要返回 elem[idx-1] 的元素即可
    for (int ix = 0; ix < L->curLength; ++ix) {
        if(L->elem[ix] == elem){
            if(ix == 0){
                return ERROR;
            }
            *prev_e = L->elem[ix - 1];
            return OK;
        }
    }

    return ERROR;
}

/**
 * @brief:  next element
 *
 * @param: L
 * @ret:
 */
Status NextElem(const SqList *L, ElemType elem, ElemType *next_e)
{
    if (!L) {
        fprintf(stderr, "null ptr\n");
        return ERROR;
    }

    for (int ix = 0; ix < L->curLength; ++ix) {
        if (L->elem[ix] == elem) {
            if (ix == (L->curLength - 1)) {
                return ERROR;
            }
            *next_e = L->elem[ix+1];
            return OK;
        }
    }

    return ERROR;
}

/**
 * @brief: 插入, 在 elem[idx] 之前插入
 *         类似于 C++ vector 的扩容算法, 达到大小时, 内存就增大一倍
 *
 * @param: L
 * @param: idx start from 0
 * @ret: Status
 */
Status ListInsert(SqList *L, int idx, ElemType e)
{
    if (!L || idx>=L->curLength) {
        fprintf(stderr, "null ptr\n");
        return ERROR;
    }

    if (L->curLength >= L->listSize) { // 扩容
        ElemType *new_base = (ElemType*)realloc(L->elem, 
            (L->listSize + LIST_INCREMENT_SIZE) * sizeof(ElemType));
        if (!new_base)
            return ERROR;
        L->elem = new_base;
        L->listSize += LIST_INCREMENT_SIZE;
    }

    ElemType *q = &(L->elem[idx]); // 最后一个要向后移动的元素
    for (ElemType *p = &(L->elem[L->curLength - 1]); p >= q; --p) {
        *(p + 1) = *p;
    }

    *q = e;
    ++L->curLength;

    return OK;
}

/**
 * @brief:  delete a element
 *
 * @param[in] L
 * @param[in] idx index start from 0
 * @param[out] e
 * @ret:
 */
Status ListDelete(SqList *L, int idx, ElemType *e)
{
    if(!L || idx >= L->curLength){
        fprintf(stderr, "null ptr\n");
        return ERROR;
    }

    *e = L->elem[idx];

    // 直接前移, 覆盖
    ElemType *q = &(L->elem[L->curLength - 1]);
    for (ElemType *p = &(L->elem[idx]); p < q; ++p) {
        *p = *(p + 1);
    }
    --L->curLength;

    return OK;
}

/**
 * @brief:  traverse
 *
 * @param[in] L
 * @param[in] visit
 * @ret:
 */
Status ListTraverse(SqList *L, void (*visit_fun)(ElemType e))
{
    if (!L) {
        fprintf(stderr, "null ptr\n");
        return ERROR;
    }

    printf("traverse:\n");
    for(int ix = 0; ix < L->curLength; ++ix){
        printf("[%d]:", ix);
        (*visit_fun)(L->elem[ix]);
        printf("\n");
    }
    puts(""); // \n

    return OK;
}


/**
 * @brief:  bubble sort, from small to big
 *          O(n^2)
 * 
 * @param: L
 * @param: idx index
 * @ret:
 */
Status ListBubbleSort(SqList *L)
{
    if (!L) {
        fprintf(stderr, "null ptr\n");
        return ERROR;
    }

    for(int ix = 0; ix < L->curLength; ++ix){
        for(int jx = ix + 1; jx < L->curLength; ++jx){
            if(L->elem[ix] > L->elem[jx]){
                SWAP(L->elem[ix], L->elem[jx]);
            }
        }
    }

    return OK;
}

static bool equal(ElemType a, ElemType b)
{
    return (a == b);
}

/**
 * @brief:  A = A U B
 * 遍历 B 中的每一个元素, 判断是否在 A 中, 如果在, 则跳过; 不在, 插入 A 的末尾
 *
 * @param: L
 * @param: idx index
 * @ret:
 */
Status UnionList(SqList *L1, SqList *L2)
{
    if (!L1 || !L2) {
        fprintf(stderr, "null ptr\n");
        return ERROR;
    }

    for (int ix = 0; ix <L2->curLength; ++ix) {
        // 不在 L1 中
        if(LocateElem(L1, L2->elem[ix], equal) == INT_MAX){
            PutElem(L1, L2->elem[ix]);
        }
    }

    return OK;
}


/**
 * @brief:  归并排序里的最后一步, 
 *          La and Lb are sequenced list, from small to big
 *          Lc = La + Lb
 *
 * @param[in]  La
 * @param[in]  Lb
 * @param[in]  Lc a poninter, from small to big
 * @ret:
 */
Status MergeList(const SqList *La, const SqList *Lb, SqList **Lc)
{
    if (!La || !Lb || !Lc)
        return ERROR;
    
    // allocate memory for Lc
    SqList *pMergedList;
    pMergedList = (SqList*)malloc(sizeof(SqList));
    if (!pMergedList)
        return ERROR;
    InitList(pMergedList);

    ElemType *pa = La->elem, *pb = Lb->elem;
    ElemType *pa_last = &La->elem[La->curLength - 1], *pb_last = &Lb->elem[Lb->curLength - 1];

    while ((pa <= pa_last) && (pb <= pb_last)) {
        // printf("1pa:%d pb:%d\n", *pa, *pb);
        if (*pa <= *pb) {
            PutElem(pMergedList, *pa);
            ++pa;
        } else {
            PutElem(pMergedList, *pb);
            ++pb;
        }
    }

    // if (pb > pb_last) {
        while (pa <= pa_last) {
            // printf("2pa:%d pb:%d\n", *pa, *pb);
            PutElem(pMergedList, *pa);
            ++pa;
        }
    // }

    // if (pa > pa_last) {
        while (pb <= pb_last) {
            // printf("3pa:%d pb:%d\n", *pa, *pb);  
            PutElem(pMergedList, *pb);
            ++pb;
        }
    // }
    *Lc = pMergedList;

    return OK;
}

static void visit(ElemType e)
{
    printf("%d", e);
}


void LinearListV2Test(void)
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
    printf("arr[2] val:%d list len:%d\n", e, ListLength(&L));

    ret = GetElem(&L, 5, &e);
    CHECK_RET(ret);
    printf("arr[5] val:%d\n\n", e);

    ret = SetElem(&L, 3, 500);
    CHECK_RET(ret);
    printf("sel elem[3] val:5");
    ret = ListTraverse(&L, visit);
    CHECK_RET(ret);

    ret = LocateElem(&L, 5, equal);
    printf("Locate val:5 idx:%d\n\n", ret);

    ret = ListInsert(&L, 3, 999999);
    CHECK_RET(ret);
    printf("insert before elem[3] len:%d\n", ListLength(&L));
    ret = ListTraverse(&L, visit);
    CHECK_RET(ret);

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

void LinearListV2Test2(void)
{
    SqList L1, L2;
    SqList *L3;

    InitList(&L1);
    PutElem(&L1, 1);
    PutElem(&L1, 1);
    PutElem(&L1, 3);
    PutElem(&L1, 5);
    PutElem(&L1, 7);
    PutElem(&L1, 9);
    PutElem(&L1, 100);
    PutElem(&L1, 200);
    PutElem(&L1, 300);
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
    ListTraverse(L3, visit);

    UnionList(&L1, &L2);
    printf("L1:");
    ListTraverse(&L1, visit);

    ListBubbleSort(&L1);
    printf("Sort L1:");
    ListTraverse(&L1, visit);
    
    free(L3);
}

#endif


