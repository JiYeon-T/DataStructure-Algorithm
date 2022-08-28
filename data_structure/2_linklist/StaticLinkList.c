// 从0-1 和 从 1-100 确实是从 0-1 比较难
// 行百里者半九十

#if STATIC_LINK_LIST

#include "StaticLinkList.h"

// 对于没有指针的其它语言, 可以使用这种方式实现静态链表
size_t headIndex = 0; // 已经使用链表的头指针(索引), 头指针不保存数据;headIndex=0 表示空链表, headIndex!=0表示有元素
size_t available_space = MAXSIZE;

/**
 * @brief  动态分配内存, 只分配一个节点
 *
 * @param sl
 * @return int 返回分配的节点的下标
 */
static int Malloc_SL(SLinkList sl)
{
    if(!sl[0].cur){ // 没有空间
        return -1;
    }
    size_t temp = sl[0].cur;
    sl[0].cur = sl[temp].cur;
    return temp;
}

/**
 * @brief 内存回收, 实际上就是将不用的内存插入到备用链表(头插法)
 *
 * @param sl
 * @param index 将下表为index 的节点回收到备用链表
 */
static void Free_SL(SLinkList sl, int index)
{
    sl[index].cur = sl[0].cur;
    sl[0].cur = index;
    return;
}

/**
 * @brief static linklist intialization
 *        为了方便管理, 将剩余空间保存到一个备用链表中, 备用链表的头指针保存在 SLinkList[0].cur 中
 *        初始化链表（默认直接加入备用链表）
 *        头节点的 cur 指向备用链表第一个元素
 *        最后一个节点的 cur 为 0
 *        中间节点:cur = next_node.index;
 */
void InitSpace_SL(SLinkList sl) // component sl[MAXSIZE], 指针
{
    for(int ix = 0; ix < MAXSIZE; ++ix){
        sl[ix].cur = ix + 1;
    }
    sl[MAXSIZE - 1].cur = 0;    //别用链表的最后一个节点

    return;
}

/**
 * @brief Init LinkList, 使用随机数初始化链表
 *
 */
Status InitLinkList_SL(SLinkList sl, size_t size)
{
    component head; // 实际上就起个指针的作用
    if(size > MAXSIZE){
        printf("Not enough space\n");
        return ERROR;
    }

    head = sl[headIndex];
    srand(time(0));
    //初始化假设链表为空, 直接从头节点开始插入
    for(size_t ix = 0; ix < size; ++ix){
        //printf("head.cur:%d\n", head.cur);
        sl[head.cur].data = rand() % 10;
        head = sl[head.cur];
    }
    sl[head.cur - 1].cur = 0; // 装元素的最后一个元素的 cur
    sl[0].cur = head.cur - 1;   // 备用链表的首节点

    headIndex = 1; // 更新头指针

    return OK;
}

/**
 * @brief 遍历链表
 *        有元素的链表 从 index=headIndex 开始
 *        备用链表从 index = SLinkList[0].cur 开始, 最后一个元素 SLinkList[lastElem].cur = 0
 *
 */
void Traverse_SL(SLinkList sl)
{
    if(headIndex == 0){
        printf("empty list\n");
        return;
    }
    component head = sl[headIndex]; // 移动的指针

    printf("Traverse:\n");
    while(head.cur != 0){ // 少了一次
        printf("%d -> ", head.data);
        head = sl[head.cur]; // pointer to next
    }
    printf("%d\n", head.data);

    return;
}

/**
 * @brief 返回 下标为 index 的元素的值
 *
 * @param[in]  sl
 * @param[in]  index 从 1 开始, 第一个元素就是 headIndex 对应节点的值
 * @param[out] elem 储存查询到的值
 * @retval OK/ERROR
 */
Status LocateElem_SL(SLinkList sl, size_t index, component *elem)
{
    size_t temp = 1;
    component head = sl[headIndex];

    while(temp<index && head.cur!=0){
        ++temp;
        head = sl[head.cur];
    }
    *elem = head;

    if(temp>index || head.cur==0){
        return ERROR;
    }

    return OK;
}

/**
 * @brief 删除第 ix 个节点
 *
 * @param[in]  sl
 * @param[in]  index
 * @param[out] elem 保存删除的元素的值
 * @retval OK/ERROR
 */
Status RemoveELem_SL(SLinkList sl, size_t index, component *elem)
{
    if(index>MAXSIZE || !sl){
        return ERROR;
    }
    size_t temp = 1;
    component head = sl[headIndex];
    component prev; //要删除的节点的前一个节点
    size_t prev_temp; //前一个节点的 index

    while(temp<index && head.cur!=0){ //遍历查找要删除的节点
        prev = head;
        prev_temp = temp;
        head = sl[head.cur]; // 下一个节点
        ++temp;
    }

    if(temp>index || head.cur==0){
        return ERROR;
    }

    // 删除节点
    sl[prev_temp].cur = head.cur; // 索引指向下一个节点
    sl[temp].data = 0;     //数据清零

    //将删除的节点索引使用头插法 插入到备用链表头部
    sl[temp].cur = sl[0].cur;   //sl[0].cur 备用链表头指针
    sl[0].cur = temp;

    return OK;
}

/**
 * @brief 插入: 从头结点开始遍历, 一直到最后一个元素, 然后开始插入
 *        每插入一个元素, 备用链表里就少一个元素, 所以需要用 Malloc_SL() 直接从备用链表里拿, 顺便更新备用链表
 *        要不然相当于同时操作两条链表
 *
 * @param[in]  sl
 * @param[in]  index index 从 1 开始, 如果在一个节点前插入需要保存 previous node 的信息, 如果在后面则不用
 *             或者:
 *             遍历的终止条件改为从
 * @param[out] elem 要插入的元素为 component 类型, 这里是值传递, 而不是传递引用
 */
Status InsertElem_SL(SLinkList sl, size_t index, component elem)
{
    if(index > MAXSIZE){
        return ERROR;
    }
    size_t temp = 1, prev_index = 1;
    component head = sl[headIndex], prev;

    while(temp<index && head.cur!=0){ // 这里有问题, 如果在最后一个元素前面插入有问题， 边界条件没有确定清除
        prev_index = temp;
        prev = head;
        ++temp;
        head = sl[head.cur];
    }

    if(temp>index || head.cur==0){
        return ERROR;
    }

    //insert
    size_t insert_pos = Malloc_SL(sl); //分配一个内存
    sl[insert_pos] = elem; //对元素赋值
    sl[insert_pos].cur = head.cur; // 先确定后面
    sl[prev_index].cur = insert_pos; // 再确定前面

    return OK;
}

/********************************************* P33 例题1 *******************************************************/
/**
 * @brief test 计算: (A-B)U(B-A),  A B 都为链表
 *
 */
void difference(SLinkList space , int index)
{

}

//测试函数
void test_SL()
{
    SLinkList sl;
    component temp;

    InitSpace_SL(sl);
    InitLinkList_SL(sl, 5);
    Traverse_SL(sl);

    printf("\n");
    LocateElem_SL(sl, 2, &temp);
    Traverse_SL(sl);
    printf("locate data:%d, cursor:%d\n", temp.data, temp.cur);
    printf("\n");

    RemoveELem_SL(sl, 3, &temp);
    Traverse_SL(sl);
    printf("removed data:%d, cursor:%d\n", temp.data, temp.cur);
    printf("\n");

    temp.data = 100;
    InsertElem_SL(sl, 3, temp);
    Traverse_SL(sl);
    printf("insert data:%d\n", temp.data);
    printf("\n");

    return;
}

#endif // STATIC_LINK_LIST
