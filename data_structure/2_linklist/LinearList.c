#include "LinearList.h"

//#define LINEAR_LIST 1
#if LINEAR_LIST

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>


extern int errno;


#define DEFAULT_LIST_SIZE       20

/**
* @fun: initialize list
* @desc: allocate memory
* @param: L
*/
Status InitList_L(LList *L)
{
    if(!L){
        fprintf(stderr, "null ptr\n");
        return ERROR;
    }
    /** 指针的值实际上保存的就是传入的变量的地址 **/
//    printf("address:%#p, pointer's address(local variable address):%#p\n", L, &L);
    L->elem = (ElemType*)malloc(sizeof(ElemType) * DEFAULT_LIST_SIZE);
//    (*L).elem = (ElemType*)malloc(sizeof(ElemType) * DEFAULT_LIST_SIZE);
//    printf("malloc address:%#p\n", L->elem);
    if(!L->elem){
        fprintf(stderr, "malloc failed:%d", errno);
        perror("malloc failed\n");
        return ERROR;
    }
    L->curLength = 0;
    L->listSize = DEFAULT_LIST_SIZE;
    return OK;
}

/**
* @fun: destroy
* @desc: free memeory
* @param: L
*/
Status DestroyList_L(LList *L)
{
    if(!L){
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
* @fun: clear
* @desc: does not free memory, only delte element
* @param: L
*/
Status CLearList_L(LList *L)
{
    if(!L){
        fprintf(stderr, "null ptr\n");
        return ERROR;
    }
    memset((uint8_t*)L->elem, 0, (sizeof(ElemType) * L->listSize));
    L->listSize = 0;
    L->curLength = 0;
    return OK;
}

/**
* @fun: empty ?
* @desc:
* @param: L
*/
bool ListIsEmpty_L(const LList *L)
{
    if(!L){
        fprintf(stderr, "null ptr\n");
        return true;
    }

    return L->curLength ? false : true;
}

/**
* @fun: empty ?
* @desc: get the element number
* @param: L
*/
size_t ListLength_L(const LList *L)
{
    if(!L){
        fprintf(stderr, "null ptr\n");
        return 0;
    }
    return L->curLength;
}

/**
* @fun: get
* @desc: get the element number, idx from 0 to (N-1), N = ElemNum
* @param: L
*/
Status GetElem_L(const LList *L, size_t idx, ElemType *val)
{
    if(!L){
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
* @fun: set
* @desc: get the element number, idx from 0 to (N-1), N = ElemNum
* @param: L
*/
Status SetElem_L(LList *L, size_t idx, ElemType val)
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
* @fun:  能否定位到这个元素
* @desc: get the element number, idx from 0 to (N-1), N = ElemNum
* @param: L
* @ret: index, 下标; UINT32_MAX - not found
*/
static bool equal(ElemType a, ElemType b)
{
    // 这里的 ElemType 是 int 类型, 所以可以直接用 == 运算符
    // 如果是一个结构体(或者类)则还需要重载 ==
    return a == b;
}
size_t LocateElem_L(const LList *L, ElemType e, pCompare fun)
{
    if(!L){
        fprintf(stderr, "null ptr:%s\n", __func__);
        return ERROR;
    }
    size_t pos = UINT32_MAX;

    for(int ix = 0; ix < L->curLength; ++ix){
        if(fun(e, L->elem[ix])){
            pos = ix;
            break;
        }
    }

    return pos != UINT32_MAX ? pos : UINT32_MAX;
}

/**
* @fun:  prior element
* @desc:
* @param: L
* @ret:
*/
Status PriorElem_L(const LList *L, ElemType elem, ElemType *prior)
{
    if(!L){
        fprintf(stderr, "null ptr\n");
        return ERROR;
    }
    // 顺序表, 所以不需要记录当前位置, 只需要返回 elem[idx-1] 的元素即可
    for(int ix = 0; ix < L->curLength; ++ix){
        if(L->elem[ix] == elem){
            if(ix == 0){
                return ERROR;
            }
            *prior = L->elem[ix - 1];
            return OK;
        }
    }

    return ERROR;

}

/**
* @fun:  next element
* @desc:
* @param: L
* @ret:
*/
Status NextElem_L(const LList *L, ElemType elem, ElemType *next)
{
    if(!L){
        fprintf(stderr, "null ptr\n");
        return ERROR;
    }

    for(int ix = 0; ix < L->curLength; ++ix){
        if(L->elem[ix] == elem){
            if(ix == (L->curLength - 1)){
                return ERROR;
            }
            *next = L->elem[ix+1];
            return OK;
        }
    }

    return ERROR;
}

/**
* @fun:  插入
* @desc: 是否需要做类似于 C++ 里面的扩容操作?
*         暂时先不扩容, 如果大于总大小, 就 ERROR
*         如果要扩容的话, 也不可以无限扩容
* @param: L
* @param: idx 要插入的下标
* @ret: Status
*/
Status ListInsert_L(LList *L, size_t idx, ElemType val)
{
    if(!L || idx>=L->curLength || L->curLength>=L->listSize){
        fprintf(stderr, "null ptr\n");
        return ERROR;
    }

    //
    for(int ix = L->curLength - 1; ix >= idx; --ix){
        L->elem[ix+1] = L->elem[ix];
    }
    L->elem[idx] = val;
    ++(L->curLength);
    return OK;
}

/**
* @fun:  delete a element
* @desc:
* @param: L
* @param: idx index
* @ret:
*/
Status ListDelete_L(LList *L, size_t idx, ElemType *val)
{
    if(!L || idx>=L->curLength){
        fprintf(stderr, "null ptr\n");
        return ERROR;
    }

    // 直接前移, 覆盖
    *val = L->elem[idx];
    for(int ix = idx; ix < L->curLength - 1; ++ix){
        L->elem[ix] = L->elem[ix + 1];
    }
    --(L->curLength);

    return OK;
}

/**
* @fun:  delete a element
* @desc:
* @param: L
* @param: idx index
* @ret:
*/
Status ListTraverse_L(const LList *L)
{
    if(!L){
        fprintf(stderr, "null ptr\n");
        return ERROR;
    }

    printf("traverse:\n");
    for(int ix = 0; ix < L->curLength; ++ix){
        printf("%d ", L->elem[ix]);
    }
    puts(""); // \n

    return OK;
}


/**
* @fun:  bubble sort
* @desc: O(n^2), 从小到大
* @param: L
* @param: idx index
* @ret:
*/
#define SWAP(a, b)  { ElemType temp = (a); (a) = (b); (b) = temp; }
Status ListSort_L(LList *L)
{
    if(!L){
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

/**
* @fun:  A = A U B
* @desc: 遍历 B 中的每一个元素, 判断是否在 A 中, 如果在, 则跳过; 不在, 插入 A 的末尾
* @param: L
* @param: idx index
* @ret:
*/
Status UnionList_L(const LList *L1, const LList *L2)
{
    if(!L1 || !L2){
        fprintf(stderr, "null ptr\n");
        return ERROR;
    }

    size_t len2 = L2->curLength;

    for(int ix = 0; ix <len2; ++ix){
        // 不在 L1 中
        if(LocateElem_L(L1, L2->elem[ix], equal) == UINT32_MAX){
            SetElem_L(L1, L1->curLength, L2->elem[ix]);
        }
    }
    return OK;
}


/**
* @fun:  归并排序里的最后一步
* @desc:
* @param: L
* @param: idx index
* @ret:
*/
void MergeList_L(const LList *L1, const LList *L2)
{

}


void ListTest_L()
{
    LList list, list2;
    Status ret;
    ElemType temp = 123;
    ElemType tempRes;
    size_t idx = 5;

    ret = InitList_L(&list);
//    printf("original address:%#p\n", &list);
//    printf("accept address:%#p\n", list.elem);

    if(ret != OK){
        fprintf(stderr, "error:%d", ret);
        return;
    }
    printf("length:%d\n", ListLength_L(&list));
    ListTraverse_L(&list);
    SetElem_L(&list, 0, 10660);
    SetElem_L(&list, 1, 140);
    SetElem_L(&list, 2, 130);
    SetElem_L(&list, 3, 120);
    SetElem_L(&list, 4, 150);
    SetElem_L(&list, 5, 190);
    SetElem_L(&list, 6, 1098);
    printf("length:%d\n", ListLength_L(&list));
    ListTraverse_L(&list);
    GetElem_L(&list, idx, &temp);
    printf("index:%d, data:%d\n", idx, temp);
    PriorElem_L(&list, temp, &tempRes);
    printf("cur:%d, prior:%d\n", temp, tempRes);
    NextElem_L(&list, temp, &tempRes);
    printf("cur:%d, next:%d\n", temp, tempRes);
    temp = 15999;
    ListInsert_L(&list, idx, temp);
    printf("length:%d\n", ListLength_L(&list));
    ListTraverse_L(&list);
    idx = 3;
    ListDelete_L(&list, idx, &temp);
    printf("delete idx:%d, data:%d\n", idx, temp);
    printf("length:%d\n", ListLength_L(&list));
    ListTraverse_L(&list);
    ListSort_L(&list);
    printf("length:%d\n", ListLength_L(&list));
    ListTraverse_L(&list);
    printf("locate elem:%d %d %d\n", LocateElem_L(&list, 130, equal), \
            LocateElem_L(&list, 1098, equal),\
            LocateElem_L(&list, 11, equal));


    printf("\n\nlist2:\n");
    InitList_L(&list2);
    SetElem_L(&list2, 0, 130);
    SetElem_L(&list2, 1, 96);
    SetElem_L(&list2, 2, 458);
    SetElem_L(&list2, 3, 1);
    SetElem_L(&list2, 4, 5);
    SetElem_L(&list2, 5, 22559);
    SetElem_L(&list2, 6, 448);
    printf("length:%d\n", ListLength_L(&list2));
    ListTraverse_L(&list2);
    ListSort_L(&list2);
    printf("length:%d\n", ListLength_L(&list2));
    ListTraverse_L(&list2);

//    printf("\n\nunion:\n");
//    UnionList_L(&list, &list2);
//    printf("length:%d\n", ListLength_L(&list));
//    ListTraverse_L(&list);
//    printf("length:%d\n", ListLength_L(&list2));
//    ListTraverse_L(&list2);


    print("merge:\n");
    MergeList_L(&list, &list2);

}

#endif // LINEAR_LIST


