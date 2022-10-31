/**
 * @file StaticLinkList.c
 * @author your name (you@domain.com)
 * @brief 静态链表
 * @version 0.1
 * @date 2022-10-30
 *
 * @copyright Copyright (c) 2022
 *
 */
/***************************************************************************************************************/
// 1.从0-1 和 从 1-100 确实是从 0-1 比较难
// 2.行百里者半九十


#include "StaticLinkList.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <stdbool.h>


/** 对于没有指针的其它语言, 可以使用这种方式实现静态链表 */



/********************************************* 引入备用链表对空闲节点进行管理 *******************************************************/
typedef struct {
    // size_t maxSize;
    // size_t availableHeadIndex; // 已经使用链表的头指针(索引), 头指针不保存数据; headIndex=0 表示空链表, headIndex!=0表示有元素
    // size_t available_space;    // 剩余可用空间
    size_t dataLinkListIdx;       // 数据链表起始索引
    size_t freeLinkListIdx;       // 备用链表起始索引; 必须使用备用链表对所有空闲节点进行管理, 否则不好处理;
    bool initFlag;                // 是否初始化的标志, 是否包含头结点
} LinkListManager_SL;

static LinkListManager_SL _linkListManagerSL;


/**
 * @brief static linklist intialization
 *        数组元素初始化为全 0 这种方法不好搞
 *
 * @desc (1) 数组第 0 个节点为头结点;
 *       (2) 遍历结束条件: pNode.next == 0; // 下一个节点为头结点, 则链表尾部
 *       (3) 头结点的 next 记录第一个节点(firstNode) 的下标;
 *       (4) 最后一个节点(tailNode) 的 next 为 0;
 *       (5) 头结点的数据域不存放数据 = INT_MAX;
 *
 *        为了方便管理, 将剩余空间保存到一个备用链表中, 备用链表的头指针保存在 SLinkList[0].cur 中
 *        初始化链表（默认直接加入备用链表）
 *        头节点的 cur 指向备用链表第一个元素
 *        最后一个节点的 cur 为 0
 *        中间节点:cur = next_node.index;
 */
Status InitSpace_SL(LinkList_SL sL)
{
    // 数组元素初始化为全 0 这种方法不好搞
    // printf("address:%#p size:%ld\r\n", sL, sizeof(Node_SL) * MAXSIZE_SL);
    // memset((uint8_t*)sL, 0, sizeof(Node_SL) * MAXSIZE_SL);
    // sL[0].data = INT_MAX;
    // sL[0].next = 0;
    // for(int ix = 0; ix < MAXSIZE_SL; ++ix){
    //     printf("sL[%d] data:%d next:%d\r\n", ix, sL[ix].data, sL[ix].next);
    // }

    return OK;
}

/**
 * @brief 为了方便管理, 将剩余空间保存到一个备用链表中, 备用链表的头指针保存在 SLinkList[0].cur 中
 *        初始化的时候就让所有元素都排列成一个链表(就是对空闲元素通过链表进行管理, 初始化:元素链表为空; 空闲链表有 99 个元素(一个头结点不保存))
 *        0               1           2                   99
 *        (INT_MAX, 1) -> (xxx, 2) -> (yyy, 3) -> .... -> (nnn, 0)
 *        (1) 数据链表头结点 index = 0;
 *        (2) 备用链表头结点 index = 1;
 *        (3) 需要定义 malloc() 和 free() 从备用链表分配一个节点;
 *        (4) 实际上只有 MAXSIZE_SL - 2 个可用的节点;
 *
 * @param sl
 */
Status InitSpace_SL_v2(LinkList_SL sL) // component sl[MAXSIZE], 指针
{
    if(!sL){
        return ERROR;
    }
    // 数据链表初始化, index = 0
    _linkListManagerSL.dataLinkListIdx = 0;
    sL[_linkListManagerSL.dataLinkListIdx].next = 0; // empty link list

    // 备用链表初始化
    _linkListManagerSL.freeLinkListIdx = 1; // 备用链表头结点 index = 1;
    for(int ix = _linkListManagerSL.freeLinkListIdx; ix < MAXSIZE_SL; ++ix){ // 1 - 99
        sL[ix].next = ix + 1;
    }
    sL[MAXSIZE_SL - 1].next = 0;    // 最后一个节点指针域为 0

    _linkListManagerSL.initFlag = true;

    return OK;
}

/**
 * @brief deinit
 * 
 * @param sL 
 * @return Status 
 */
Status DeinitSpace_SL(LinkList_SL sL)
{
    if(!sL || !_linkListManagerSL.initFlag){
        return ERROR;
    }

    _linkListManagerSL.initFlag = false;

    return OK;
}

/**
 * @brief  动态分配内存, 只分配一个节点
 *
 * @param sl
 * @return int 返回分配的节点的下标 index
 */
static int Malloc_SL(LinkList_SL sL)
{
    if(!sL || !_linkListManagerSL.initFlag){
        return -1;
    }
    if(sL[_linkListManagerSL.freeLinkListIdx].next == 0){ // 没有空间
        printf("No enough space\r\n");
        return -1;
    }

    size_t temp = sL[_linkListManagerSL.freeLinkListIdx].next;
    sL[_linkListManagerSL.freeLinkListIdx].next = sL[temp].next;
    return temp;
}

/**
 * @brief 内存回收, 实际上就是将不用的内存插入到备用链表(头插法)
 *        将下标加入到备用链表头部
 *
 * @param sl
 * @param index 将下表为index 的节点回收到备用链表
 */
static Status Free_SL(LinkList_SL sL, int index)
{
    if(!sL || index >= MAXSIZE_SL || !_linkListManagerSL.initFlag){
        return ERROR;
    }
    sL[index].next = sL[_linkListManagerSL.freeLinkListIdx].next;
    sL[_linkListManagerSL.freeLinkListIdx].next = index;
    return OK;
}

/**
 * @brief Init LinkList, 使用随机数初始化链表
 *        仅仅适用于包含头结点的链表的初始化, 要判断初始化标志位
 *
 */
Status InitLinkListWithRandom_SL(LinkList_SL sL, size_t size)
{
    if(!sL || !_linkListManagerSL.initFlag){
        return ERROR;
    }

    if(size > MAXSIZE_SL -1){
        printf("No enough space\n");
        return ERROR;
    }

    srand(time(0));
    for(size_t ix = 0; ix < size; ++ix){
        // 头插法/尾插法
        // InsertTail_SL(sL, rand() % 100);
        InsertHead_SL(sL, rand() % 100);
    }

    return OK;
}

/**
 * @brief Initialize static linklist with array
 *        仅仅适用于空链表的初始化
 *
 * @param sl
 * @param arr
 * @param len
 * @return Status
 */
Status InitLinkListWithArray_SL(LinkList_SL sL, ElemType *arr, size_t len)
{
    if(!sL || !arr || len <= 0 || !_linkListManagerSL.initFlag){
        return ERROR;
    }

    for(int ix = 0; ix < len; ++ix){
        InsertTail_SL(sL, arr[ix]);
    }

    return OK;
}

/**
 * @brief 遍历链表(包含头结点)
 *        有元素的链表 从 index=headIndex 开始
 *        备用链表从 index = SLinkList[0].cur 开始, 最后一个元素 SLinkList[lastElem].cur = 0
 *
 * @param sL linklist
 */
Status Traverse_SL(const LinkList_SL sL)
{
    if(!sL || !_linkListManagerSL.initFlag){
        return ERROR;
    }

    if(sL[_linkListManagerSL.dataLinkListIdx].next == 0){
        printf("empty list\n");
        return ERROR;
    }

    size_t tempIdx = sL[_linkListManagerSL.dataLinkListIdx].next; // 第 1 个节点(不包含头结点)

    printf("Traverse:\n");
    while(tempIdx != 0){
        printf("%d -> ", sL[tempIdx].data);
        tempIdx = sL[tempIdx].next; // pointer to next
    }
    printf("\r\n\r\n");

    return OK;
}

/**
 * @brief 回 下标为 index 的元素的值
 * 
 * @param sL 
 * @param index 从 0 开始, 返回链表中的第 idx 个元素(不包括头结点)
 * @param[out] result 
 * @return Status ERROR/OK
 */
Status GetElem_SL(LinkList_SL sL, size_t index, ElemType *result)
{
    if(!sL || index >= MAXSIZE_SL || !_linkListManagerSL.initFlag){
        return ERROR;
    }

    size_t tempLinkListIdx = sL[_linkListManagerSL.dataLinkListIdx].next;
    size_t findIdx = 0;

    while(findIdx < index && tempLinkListIdx != 0){
        ++findIdx;
        tempLinkListIdx = sL[tempLinkListIdx].next;
    }

    if(findIdx > index || tempLinkListIdx == 0){
        return ERROR;
    }

    *result = sL[tempLinkListIdx].data;

    return OK;
}

/**
 * @brief 删除第 ix 个节点
 *        删除节点 -> 将 index 添加到备用链表
 *
 * @param[in]  sl
 * @param[in]  index 从 0 开始
 * @param[out] elem 保存删除的元素的值
 * @retval OK/ERROR
 */
Status RemoveELem_SL(LinkList_SL sL, size_t index, Node_SL *elem)
{
    if(index > MAXSIZE_SL || !sL || !_linkListManagerSL.initFlag){
        return ERROR;
    }
   
    size_t tempIdx = 0;
    size_t tempNodeIdx = sL[_linkListManagerSL.dataLinkListIdx].next; // 遍历节点
    size_t prevNodeIdx = tempNodeIdx; //要删除的节点的前一个节点

    while(tempIdx < index && tempNodeIdx != 0){ //遍历查找要删除的节点
        prevNodeIdx = tempNodeIdx;
        tempNodeIdx = sL[tempNodeIdx].next; // 下一个节点
        ++tempIdx;
    }

    if(tempIdx > index || tempNodeIdx == 0){ // 没有搜索到
        return ERROR;
    }

    // 删除节点
    sL[prevNodeIdx].next = sL[tempNodeIdx].next; // 索引指向下一个节点

    // 数据清零
    elem->data = sL[tempNodeIdx].data;
    sL[tempNodeIdx].data = 0;     

    //将删除的节点索引使用头插法 插入到备用链表头部
    Free_SL(sL, tempNodeIdx);

    return OK;
}

/**
 * @brief 在头部插入节点
 *        从备用链表分配节点 -> 插入数据链表
 * 
 * @param sL 
 * @param insertValue 
 * @return Status 
 */
Status InsertHead_SL(LinkList_SL sL, ElemType insertValue)
{
    if(!sL || !_linkListManagerSL.initFlag){
        return ERROR;
    }

    // 分配节点
    size_t insertIdx = Malloc_SL(sL);
    if(insertIdx <= 0){
        return ERROR;
    }
    sL[insertIdx].data = insertValue;
    sL[insertIdx].next = sL[_linkListManagerSL.dataLinkListIdx].next;
    sL[_linkListManagerSL.dataLinkListIdx].next = insertIdx;

    return OK;

}


/**
 * @brief 尾部插入
 *        备用链表分配节点 -> 插入数据链表尾部
 * 
 * @param sl 
 * @param elem 要插入的值
 * @return Status 
 */
Status InsertTail_SL(LinkList_SL sL, ElemType elem)
{
    if(!sL || !_linkListManagerSL.initFlag){
        return ERROR;
    }

    size_t insertIdx = Malloc_SL(sL);
    if(insertIdx <= 0){
        return ERROR;
    }
    sL[insertIdx].data = elem;
    sL[insertIdx].next = 0; // tail ndoe

    size_t tempIdx = sL[_linkListManagerSL.dataLinkListIdx].next, prevIdx = tempIdx;

    while(tempIdx != 0){
        prevIdx = tempIdx;
        tempIdx = sL[tempIdx].next;
    }

    sL[prevIdx].next = insertIdx;

    return OK;
}

/**
 * @brief merge two sorted LinkList
 * 
 * @param[in]  sL1 
 * @param[in]  sL2 
 * @param[out] sL3 result
 * @return Status 
 */
Status MergetLinkList_SL(LinkList_SL sL1, LinkList_SL sL2, LinkList_SL sL3)
{

}

/********************************************* P33 例题1 *******************************************************/
/**
 * @brief test 计算: (A-B)U(B-A),  A B 都为链表
 *
 */
void difference(LinkList_SL space , int index)
{

}

//测试函数
void test_SL()
{
    LinkList_SL sL; // array
    Node_SL temp;
    ElemType data;
    size_t idx = 1;

    printf("array address:%#p\r\n", &sL);
    InitSpace_SL_v2(sL);
    Traverse_SL(sL);

    data = 100;
    InsertHead_SL(sL, data);
    printf("head insert:%d\r\n", data);
    Traverse_SL(sL);

    data = 123;
    InsertTail_SL(sL, data);
    printf("tail insert:%d\r\n", data);
    Traverse_SL(sL);

    data = 45;
    InsertHead_SL(sL, data);
    printf("head insert:%d\r\n", data);
    Traverse_SL(sL);

    RemoveELem_SL(sL, idx, &temp);
    printf("remove index:%d, value:%d\r\n", idx, temp.data);
    Traverse_SL(sL);

    GetElem_SL(sL, idx, &temp);
    printf("get elem index:%d, value:%d\r\n", idx, temp.data);
    Traverse_SL(sL);

    return;
}

void SL_test2()
{
    LinkList_SL sL; // array
    LinkList_SL sL2;
    ElemType arr[] = {1, 22, 444, 55555};

    InitSpace_SL_v2(sL); // &sL;
    Traverse_SL(sL);

    InitLinkListWithRandom_SL(sL, 10);
    printf("init with random:\r\n");
    Traverse_SL(sL);

    printf("=================\r\n");
    InitSpace_SL_v2(sL2); // &sL;
    Traverse_SL(sL2);

    printf("init with array:\r\n");
    InitLinkListWithArray_SL(sL2, arr, sizeof(arr)/sizeof(ElemType));
    Traverse_SL(sL2);
}


