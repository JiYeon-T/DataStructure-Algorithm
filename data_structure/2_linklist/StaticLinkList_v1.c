#include "StaticLinkList_v1.h"

#if defined(STATIC_LINK_LIST_V1) && (STATIC_LINK_LIST_V1 == 1)

/**
 * @fun 备用链表非空, 
 *      space[0].cur 保存备用链表的头节点下标
 *      space[MAXSIZE-1].cur 保存数据链表的头节点下标
 * 
 * @ret返回备用链表头节点下标; 否则, 返回0;
*/
static int Malloc_SLL(StaticLinkList space)
{
    int idx = space[0].cur;

    if (space[0].cur) // 更新备用链表头节点
        space[0].cur = space[idx].cur;

    return idx;
}

/**
 * @fun: 将该节点下标添加到备用链表头部
*/
static void Free_SLL(StaticLinkList space, int idx)
{
    space[idx].cur = space[0].cur;
    space[0].cur = idx;
}

/**
 * @fun init list
 * @desc 1.arr[0] 作为备用链表起始节点(space[0].cur 保存备用链表的头节点下标);
 *       2.arr[MAXSIZE-1] 作为保存数据链表的起始节点, (space[MAXSIZE-1].cur 保存数据链表的头节点下标)
 *       保存数据的链表最后一个节点的 cur 为 0(尾节点的指针域为0,作为链表的结束标志)
 *       3. 因此, 静态链表的最大容量为:MAXSIZE-2;
 * 
 * @param[in] space
 * @ret
*/
Status ListInit(StaticLinkList space)
{
    // idx:0-998
    // cur 保存下一个节点的索引
    for (int ix = 0; ix < MAXSIZE - 1; ++ix) { // 备用链表初始化
        space[ix].cur = ix + 1;
    }

    // 数据链表初始化, 此时数据链表为空
    space[MAXSIZE - 1].cur = 0;

    return OK;
}

/**
 * @fun Put a item into list
*/
Status ListPutElem(StaticLinkList space, ElemType data)
{
    if (ListLength(space) >= MAXSIZE - 2) // except head and tail
        return ERROR;

    int prev_idx = MAXSIZE - 1, idx = space[MAXSIZE - 1].cur;
    int put_elem_idx = Malloc_SLL(space);

    while (idx != 0) {
        prev_idx = idx;
        idx = space[idx].cur;
    }

    space[put_elem_idx].data = data;
    space[put_elem_idx].cur = 0;
    space[prev_idx].cur = put_elem_idx;

    return OK;
}

/**
 * @fun: 在第 i 个节点前插入
 * @param[in] space
 * @param[in] i start from 0
 * @param[in] e
*/
Status ListInsert(StaticLinkList space, int i, ElemType e)
{
    if (i < 0 || ListLength(space) == 0 || i > (ListLength(space) - 1))
        return ERROR;
    int insert_idx, elemIdx = Malloc_SLL(space);
    int k = MAXSIZE - 1; // 链表起始位置

    if (elemIdx == 0)
        return ERROR;

    // 遍历寻找插入位置
    for (int jx = 0; jx < i; ++jx) { // 寻找第 i-1 个位置
        k = space[k].cur;
    }
    insert_idx = k;

    space[elemIdx].data = e;
    space[elemIdx].cur = space[insert_idx].cur;
    space[insert_idx].cur = elemIdx;

    return OK;
}

/**
 * @fun:从数据链表删除第 i 个节点
 * 
 * @param[in] space
 * @param[in] idx start from 0
 * @param[out] e
 * @ret
*/
Status ListDelete(StaticLinkList space, int idx, ElemType *e)
{
    if (idx < 0 || ListLength(space) == 0 ||idx >= ListLength(space))
        return ERROR;
    int k = MAXSIZE - 1; // previous node's index
    int delete_idx;

    for (int jx = 0; jx < idx; ++jx) // 寻找第 i-1 个位置
        k = space[k].cur;
    delete_idx = space[k].cur;

    space[k].cur = space[delete_idx].cur; // delete node
    *e = space[delete_idx].data; // memcpy(e, &space[delete_idx].data, sizeof(ElemType));
    Free_SLL(space, delete_idx);

    return OK;
}

/**
 * @fun 获取保存链表实际长度,当前保存元素个数
*/
int ListLength(StaticLinkList space)
{
    int idx = space[MAXSIZE-1].cur;
    int size = 0;

    while (idx != 0) {
        idx = space[idx].cur;
        ++size;
    }

    return size;
}

Status Traverse(StaticLinkList space, const char *p_op_info)
{
    int cur = space[MAXSIZE - 1].cur;
    int idx = 0;

    printf("traverse(%s):\n", p_op_info);
    while (cur != 0) {
        printf("[%d]:%d ->", idx++, space[cur].data);
        cur = space[cur].cur;
    }
    printf("\n\n");

    return OK;
}

/**
 * @fun 查找链表中第一个为 e 的元素
 * @param[in] list
 * @param[in] e
 * @param[out] 查找到的 idx
 * @ret
 **/
Status LocateElem_SL(StaticLinkList space, ElemType e, int *idx)
{
    int curr = space[MAXSIZE - 1].cur;
    int prev =curr;

    while (curr != 0) {
        if (space[curr].data == e) {
            *idx = curr;
            break;
        }
        curr = space[curr].cur;
    }

    if (curr == 0)
        return ERROR;

    return OK;
}


/********************************************* P33 例题1 *******************************************************/
/**
 * @brief test 计算: (A-B)U(B-A),  A B 都为链表
 *
 */
void difference(StaticLinkList space , int index)
{

}


void static_link_list_test(void)
{
    StaticLinkList sl;
    Status ret;
    ElemType data;
    int idx;

    ret = ListInit(sl);
    CHECK_RET_OP(ret, "init");
    ret = Traverse(sl, "init static linklist");
    CHECK_RET_OP(ret, "init");

    ret = ListPutElem(sl, 0);
    CHECK_RET_OP(ret, "put");
    ret = Traverse(sl, "put:0");
    CHECK_RET_OP(ret, "put");


    ret = ListPutElem(sl, 1);
    CHECK_RET_OP(ret, "put");
    ret = Traverse(sl, "put:1");
    CHECK_RET_OP(ret, "put");


    ret = ListPutElem(sl, 2);
    CHECK_RET_OP(ret, "put");
    ret = Traverse(sl, "put:2");
    CHECK_RET_OP(ret, "put");

    ret = ListInsert(sl, 0, 111);
    CHECK_RET_OP(ret, "insert");
    ret = Traverse(sl, "insert:111 at idx：0");
    CHECK_RET_OP(ret, "insert");

    ret = ListInsert(sl, 1, 222);
    CHECK_RET_OP(ret, "insert");
    ret = Traverse(sl, "insert：222 at idx:1");
    CHECK_RET_OP(ret, "insert");

    ret = ListDelete(sl, 1, &data);
    CHECK_RET_OP(ret, "delete");
    printf("delete idx:%d val:%d\n",1, data);
    ret = Traverse(sl, "delete idx:1");
    CHECK_RET_OP(ret, "delete");


    ret = ListDelete(sl, 0, &data);
    CHECK_RET_OP(ret, "delete");
    printf("delete idx:%d val:%d\n", 0, data);
    ret = Traverse(sl, "delete idx:0");
    CHECK_RET_OP(ret, "delete");

    printf("List length:%d\n", ListLength(sl));

    ret = LocateElem_SL(sl, 2, &idx);
    CHECK_RET_OP(ret, "LocateElem");
    printf("val:%d at idx:%d\n", 2, idx);
    ret = Traverse(sl, "LocateElem");
    CHECK_RET_OP(ret, "LocateElem");
}

#endif // end STATIC_LINK_LIST_V1