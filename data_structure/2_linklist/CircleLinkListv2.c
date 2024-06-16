#include "CircleLinkListv2.h"


#if defined(DataStructCircleLinkListv2) && (DataStructCircleLinkListv2 == 1)

/**
 * @brief allocatet a node space and init data 
 * 
 * @param[in/outt] p Node **type
 * @param[in] e data
 * @return success return OK, otherwise return ERROR
*/
Status MakeNode(struct Node **p, ElemType e)
{
    if (!p) {
        LOG_E("null ptr");
        return ERROR;
    }

    struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
    if (!temp) {
        LOG_E("allocate failed");
        return ERROR;
    }
    temp->data = e;
    temp->next = NULL;
    // LOG_D("malloc:%p", temp);

    *p = temp;

    return OK;
}

/**
 * @brief free a node allocated memory
 * 
 * @param[in/out] p
*/
void FreeNode(struct Node *p)
{
    if (!p) {
        LOG_E("null ptr");
        return;
    }
    free(p);
    // LOG_D("free:%p", p);

    return;
}

/**
 * @brief free a node allocated memory, 
 * a empty linklist, only have a head node
 * 
 * @param[in] p
*/
Status InitList(LinkList *L)
{
    if (!L) {
        LOG_E("null ptr");
        return ERROR;
    }

    // init a head node
    struct Node *p_head = (struct Node*)malloc(sizeof(struct Node));
    if (!p_head) {
        LOG_E("allocate failed");
        return ERROR;
    }
    LOG_D("head node:%p", p_head);
    p_head->next = p_head;
    p_head->data = INVALID_VAL;

    // init struct LinkList
    L->head = p_head;
    L->tail = p_head;
    L->len = 0;

    return OK;
}

/**
 * @brief delete all node, does not include head
 * 
 * @param[in] p
*/
Status ClearList(LinkList *L)
{
    if (!L) {
        LOG_E("null ptr");
        return ERROR;
    }

    size_t idx = 0;
    struct Node *p_prev = L->head;
    struct Node *p_curr = L->head->next;

    while (p_curr != L->head) {
        struct Node *temp = p_curr;
        p_prev->next = p_curr->next; // 更新前一个节点的 next 指针

        p_curr = p_curr->next; // 迭代
        // LOG_D("delte[%d]:%p", idx++, temp);
        FreeNode(temp); // 释放内存
        --L->len; // 链表长度 -1
    }

    L->tail = L->head;

    return OK;
}

/**
 * @brief delete all node, include head
 * 
 * @param[in] p
*/
Status DestroyList(LinkList *L)
{
    if (!L) {
        LOG_E("null ptr");
        return ERROR;
    }

    if (ClearList(L) != OK) // L->len = 0;
        return ERROR;
    
    // free head node
    LOG_D("free head node:%p", L->head);
    FreeNode(L->head);
    L->head = NULL;
    L->tail = NULL;

    return OK;
}

/**
 * @brief Insert before first node, aftet head node, 如果没有第一个节点(空链表只有头节点, 返回错误)
 * 尽量废弃, 无法更新 LinkList 结构体
 * 
 * circle list structure:
 * head -> fist -> second -> head
 * 
 * @param[in] h pointer to head node
 * @param[in] s insert before first node, s become the fist node,
*/
Status InsFirst(struct Node *h, struct Node *s)
{
    if (!h || !s) {
        LOG_E("null ptr");
        return ERROR;
    }

    if (h->next == h) {
        LOG_E("empty list, does not have fist node");
        return ERROR;
    }

    s->next = h->next;
    h->next = s;

    // 更新链表, head, tail, len
    // 这里没有办法更新, 拿不到 LinkList *L, 更新不了 L->tail, L-> len
    // if (s->next == h) { // 之前是个空链表, 插入节点为第一个节点, 需要更新尾指针和链表长度
    // }

    return OK;
}

/**
 * @brief Insert before fist node
 * 尽量废弃, 无法更新 LinkList 结构体
 * 
 * @param[in] h pointer to head node
 * @param[in/out] q delete first node , return return with this pointer
*/
Status DelFirst(struct Node *h, struct Node **p_first)
{
    if (!h || !p_first) {
        LOG_E("null ptr");
        return ERROR;
    }

    struct Node *f = h->next;
    if (f == h) { // h->next == h;
        LOG_E("empty list, does not have fist node");
        return ERROR;
    }

    h->next = f->next;
    *p_first = f;

    // 更新链表, head, tail, len -> 不更新

    return OK;
}

/**
 * @brief append a node at tail
 * 
 * @param[in] L
 * @param[in] s
*/
Status Append(LinkList *L, struct Node *s)
{
    if (!L || !s) {
        LOG_E("null ptr");
        return ERROR;
    }

    s->next = L->head; // 直接通过尾指针更新
    L->tail->next = s;

    L->tail = s; // 更新 LinkList 尾指针以及长度
    ++L->len;

    return OK;
}

/**
 * @brief remove tail node
 * 
 * @param[in] L LinkList L
 * @param[in] q removed Node
 * @return 
*/
Status RemoveTail(LinkList *L, struct Node **q)
{
    if (!L || !q) {
        LOG_E("null ptr");
        return ERROR;
    }

    struct Node *prev = L->head;
    struct Node *curr = L->head->next;

    if (curr == L->head) {
        LOG_E("empty list, does not have fist node");
        return ERROR;
    }

    while (curr->next != L->head) {
        prev = curr;
        curr = curr->next;
    }

    prev->next = curr->next;

    L->tail = prev; // 更新尾节点
    --L->len;

    *q = curr;

    return OK;
}

/**
 * @brief insert s before p
 * 并修改 p 指向新插入的指针???
 *
 * @param[in] L LinkList L
 * @param[in] p 不可以是头指针, 只能从数据节点中进行选择
 * @param[in] s
 * @return 
*/
Status InsBefore(LinkList *L, struct Node *p, struct Node *s)
{
    if (!L || !p || !s) {
        LOG_E("null ptr");
        return ERROR;
    }

    struct Node *prev = L->head;
    struct Node *curr = L->head->next;

    while (curr != p && curr != L->head) {
        prev = curr;
        curr = curr->next;
    }

    if (curr != p || curr == L->head) {
        LOG_E("can't find node:%p data:%d", p, p->data);
        return ERROR;
    }

    s->next = curr;
    prev->next = s;

    // 插入的节点不可能是尾节点, 所以不用更新尾指针
    ++L->len;

    return OK;
}


/**
 * @brief insert s after p
 * 并修改 p 指向新插入的指针???
 *
 * @param[in] L LinkList L
 * @param[in] p 不可以是头指针, 只能从数据节点中进行选择
 * @param[in] s
 * @return 
*/
Status InsAfter(LinkList *L, struct Node *p, struct Node *s)
{
    if (!L || !p || !s) {
        LOG_E("null ptr");
        return ERROR;
    }

    // Q:判断 p 是否在链表中? 这个操作是否需要?
    // A:已知 p 指向链表中的一个节点
    struct Node *curr = L->head->next;
    while (curr != p && curr != L->head) {
        curr = curr->next;
    }
    if (curr != p || curr == L->head) {
        LOG_E("can't find node:%p data:%d", p, p->data);
        return ERROR;
    }

    s->next = p->next;
    p->next = s;

    ++L->len;
    // 更新尾指针
    if (s->next == L->head) {
        L->tail = s;
    }

    return OK;
}


/**
 * @brief set current element
 *
 * @param[in] p
 * @param[in] e
 * @return 
*/
Status SetCurrElem(struct Node *p, ElemType e)
{
    if (!p) {
        LOG_E("null ptr");
        return ERROR;
    }

    p->data = e;

    return OK;
}

/**
 * @brief get current element
 *
 * @param[in] p
 * @return 
*/
ElemType GetCurrElem(const struct Node *p)
{
    if (!p) {
        LOG_E("null ptr");
        return ERROR;
    }

    return p->data;
}

/**
 * @brief list is empty
 *
 * @param[in] L
 * @return 
*/
bool ListEmpty(const LinkList *L)
{
    if (!L) {
        LOG_E("null ptr");
        return ERROR;
    }

    return L->len == 0;
}

size_t ListLength(const LinkList *L)
{
    if (!L) {
        LOG_E("null ptr");
        return ERROR;
    }

    return L->len;
}

/**
 * @brief get list head pointer, not the first node
 *
 * @param[in] L
 * @return struct Node * type, otherwise return NULL
*/
Position GetHead(const LinkList *L)
{
    if (!L ) {
        LOG_E("null ptr");
        return NULL;
    }

    if (ListEmpty(L)) {
        return NULL;
    }

    return L->head;
}

/**
 * @brief get list last node's pointer, tail pointer
 *
 * @param[in] L
 * @return struct Node * type
*/
Position GetLast(const LinkList *L)
{
    if (!L) {
        LOG_E("null ptr");
        return NULL;
    }

    if (ListEmpty(L)) {
        return NULL;
    }

    return L->tail;
}

/**
 * @brief get previous node
 * 已知 p 是链表中的一个节点
 *
 * @param[in] L
 * @param[in/out] p
 * @return struct Node * type
*/
Position PriorPos(const LinkList *L, const struct Node *p)
{
    if (!L || !p) {
        LOG_E("null ptr");
        return NULL;
    }

    struct Node * prev = L->head;
    struct Node *curr = L->head->next;

    // 判断 p 是否在链表中
    while (curr != p && curr != L->head) {
        prev = curr;
        curr = curr->next;
    }

    if (curr != p && curr == L->head) {
        LOG_E("can't find node:%p", p);
        return NULL;
    }

    return prev;
}

/**
 * @brief get next node
 * 已知 p 是链表中的一个节点
 *
 * @param[in] L
 * @param[in/out] p
 * @return struct Node * type
*/
Position NextPos(const LinkList *L, const struct Node *p)
{
    if (!L || !p) {
        LOG_E("null ptr");
        return NULL;
    }

    struct Node *curr = L->head->next;

    // 判断 p 是否在链表中
    while (curr != p && curr != L->head) {
        curr = curr->next;
    }

    if (curr != p && curr == L->head) {
        LOG_E("can't find node:%p", p);
        return NULL;
    }

    return curr->next;
}

/**
 * @brief get idxth node in the list
 *
 * @param[in] L
 * @param[in/out] idx start from 0
 * @return 
*/
Status LocatePos(const LinkList *L, size_t i, const struct Node **p)
{
    if (!L || !p) {
        LOG_E("null ptr");
        return ERROR;
    }

    if (i >= L->len) { // 判断过 i 的合法性
        LOG_D("invalid idx:%ld", i);
        return ERROR;
    }

    size_t j = 0;
    struct Node *curr = L->head->next;

    while (j < i) {
        curr = curr->next;
        ++j;
    }

    // 已经判断过 i 的合法性
    *p = curr;

    return OK;
}

/**
 * @brief get element matched node
 *
 * @param[in] L
 * @param[in/out] e element
 * @param[in] compare
 * @return struct Node * type
*/
Position LocateElem(const LinkList *L, ElemType e, bool (*compare)(ElemType, ElemType))
{
    if (!L || !compare) {
        LOG_E("null ptr");
        return NULL;
    }

    struct Node *curr = L->head->next;

    while (curr != L->head) {
        if (compare(curr->data, e))
            break;
        curr = curr->next;
    }

    if (compare(curr->data, e) == false) { // 没有遍历到
        LOG_E("can't find node elem:%d", e);
        return NULL;
    }

    return curr;
}

/**
 * @brief get idxth node in the list
 *
 * @param[in] L
 * @param[in/out] e element
 * @param[in] compare
 * @return struct Node * type
*/
Status ListTraverse(const LinkList *L, Status(*visit)(ElemType e))
{
    if (!L || !visit) {
        LOG_E("null ptr");
        return ERROR;
    }

    if (!L->head || !L->tail) {
        LOG_E("null head ptr");
        return ERROR;
    }

    size_t i = 0;
    struct Node *prev = L->head;
    struct Node *curr = L->head->next;

    LOG_D("traverse:");
    while (curr != L->head) {
        printf("[%d]:", i++);
        visit(curr->data);
        curr = curr->next;
    }
    printf("\r\n\r\n");

    return OK;
}

/**
 * @brief 合并两个链表, 归并排序
 * 
 * @param[in] La La & Lb是有序链表
 * @param[in] Lb
 * @param[out] Lc 只需要传入一个 LinkList 地址, 该函数会进行初始化
 * @return Status
*/
Status MergeListV1(const LinkList *La, const LinkList *Lb, LinkList *Lc, bool (*compare)(ElemType, ElemType))
{
    if (!La || !Lb || !Lc) {
        LOG_E("null ptr");
        return ERROR;
    }

    if (InitList(Lc) != OK) {
        LOG_E("init failed");
        return ERROR;
    }

    struct Node *ha = GetHead(La);
    struct Node *hb = GetHead(Lb);
    struct Node *pa = NextPos(La, ha);
    struct Node *pb = NextPos(Lb, hb);
    ElemType a;
    ElemType b;
    struct Node *temp;

    while (pa != ha && pb != hb) { // 循环链表
        a = GetCurrElem(pa);
        b = GetCurrElem(pb);
        if (compare(a, b)) {
            MakeNode(&temp, a);
            Append(Lc, temp);
            pa = NextPos(La, pa);
        } else {
            MakeNode(&temp, b);
            Append(Lc, temp);
            pb = NextPos(Lb, pb);
        }
    }

    while (pa != ha) {
        a = GetCurrElem(pa);
        MakeNode(&temp, a);
        Append(Lc, temp);
        pa = NextPos(La, pa);
    }

    while (pb != hb) {
        b = GetCurrElem(pb);
        MakeNode(&temp, b);
        Append(Lc, temp);
        pb = NextPos(Lb, pb);
    }

    return OK;
}

/**
 * @brief 含有尾节点的好处 -> 便与合并两个链表
 * 
 * @param[in] La La & Lb是有序链表
 * @param[in] Lb
 * @param[out] Lc 只需要传入一个 LinkList 地址, 该函数会进行初始化
 * @return Status
*/
Status MergeListV2(const LinkList *La, const LinkList *Lb, LinkList *Lc)
{
    //TODO:
}
/*************************************************************************************
 * Test
 *************************************************************************************/
static bool compare(ElemType a, ElemType b)
{
    return a == b;
}

static visit(ElemType e)
{
    printf("%d  ", e);
}

void CircleListTest1(void)
{
    LinkList l;
    Status ret;
    struct Node *p_node, *p_node2;
    ElemType e;

    ret = InitList(&l);
    CHECK_RET(ret);
    ret = ListTraverse(&l, visit);
    CHECK_RET(ret);

    e = 100;
    ret = MakeNode(&p_node, e);
    CHECK_RET(ret);
    ret = Append(&l, p_node);
    CHECK_RET(ret);
    ret = ListTraverse(&l, visit);
    CHECK_RET(ret);


    MakeNode(&p_node, 200);
    Append(&l, p_node);
    MakeNode(&p_node, 300);
    Append(&l, p_node);
    MakeNode(&p_node, 400);
    Append(&l, p_node);
    MakeNode(&p_node, 500);
    Append(&l, p_node);
    MakeNode(&p_node, 600);
    Append(&l, p_node);
    
    LOG_D("len:%d", ListLength(&l));
    ret = ListTraverse(&l, visit);
    CHECK_RET(ret);

    ret = RemoveTail(&l, &p_node);
    CHECK_RET(ret);
    LOG_D("removed node:%p data:%d", p_node, p_node->data);
    FreeNode(p_node);
    LOG_D("len:%d", ListLength(&l));
    ret = ListTraverse(&l, visit);
    CHECK_RET(ret);

    p_node = GetHead(&l);
    CHECK_NOT_NULL(p_node);
    LOG_D("head:%p", p_node);
    p_node = NextPos(&l, p_node); // first node
    LOG_D("first node:%p data:%d", p_node, p_node->data);
    MakeNode(&p_node2, 1000);
    ret = InsBefore(&l, p_node, p_node2);
    CHECK_RET(ret);
    MakeNode(&p_node2, 1001);
    ret = InsAfter(&l, p_node, p_node2);
    CHECK_RET(ret);
    LOG_D("len:%d", ListLength(&l));
    ret = ListTraverse(&l, visit);
    CHECK_RET(ret);


    p_node = GetLast(&l);
    CHECK_NOT_NULL(p_node);
    LOG_D("tail:%p data:%d", p_node, p_node->data);
    MakeNode(&p_node2, 2000);
    ret = InsBefore(&l, p_node, p_node2);
    CHECK_RET(ret);
    MakeNode(&p_node2, 2001);
    ret = InsAfter(&l, p_node, p_node2);
    CHECK_RET(ret);
    LOG_D("len:%d", ListLength(&l));
    ret = ListTraverse(&l, visit);
    CHECK_RET(ret);

    LOG_D("node:%p data:%d", p_node, GetCurrElem(p_node));
    p_node = NextPos(&l, p_node);
    LOG_D("next node:%p data:%d", p_node, GetCurrElem(p_node));

    p_node = LocateElem(&l, 400, compare);
    CHECK_NOT_NULL(p_node);
    LOG_D("node:%p data:%d", p_node, GetCurrElem(p_node));

    ret = LocatePos(&l, 2, &p_node);
    CHECK_RET(ret);
    LOG_D("5th node:%p data:%d", p_node, GetCurrElem(p_node));

    ret = ClearList(&l);
    CHECK_RET(ret);
    ret = ListTraverse(&l, visit);
    CHECK_RET(ret);

    ret= DestroyList(&l);
    CHECK_RET(ret);
    ret = ListTraverse(&l, visit);
    CHECK_RET(ret);
}

static bool from_small2big(ElemType a, ElemType b)
{
    return a <= b;
}

void CircleListTest2(void)
{
    Status ret;
    LinkList L1;
    LinkList L2;
    LinkList L3;
    struct Node *node;

    ret = InitList(&L1);
    CHECK_RET(ret);
    MakeNode(&node, 100);
    Append(&L1, node);
    MakeNode(&node, 200);
    Append(&L1, node);
    MakeNode(&node, 300);
    Append(&L1, node);
    MakeNode(&node, 400);
    Append(&L1, node);
    MakeNode(&node, 500);
    Append(&L1, node);
    MakeNode(&node, 600);
    Append(&L1, node);
    ret = ListTraverse(&L1, visit);
    CHECK_RET(ret);

    ret = InitList(&L2);
    CHECK_RET(ret);
    MakeNode(&node, 101);
    Append(&L2, node);
    MakeNode(&node, 250);
    Append(&L2, node);
    MakeNode(&node, 3000);
    Append(&L2, node);
    MakeNode(&node, 4000);
    Append(&L2, node);
    MakeNode(&node, 5000);
    Append(&L2, node);
    MakeNode(&node, 6000);
    Append(&L2, node);
    MakeNode(&node, 7000);
    Append(&L2, node);
    ret = ListTraverse(&L2, visit);
    CHECK_RET(ret);

    ret = MergeListV1(&L1, &L2, &L3, from_small2big);
    CHECK_RET(ret);
    ret = ListTraverse(&L3, visit);
    CHECK_RET(ret);
}

void CircleListTest3(void)
{

}
#endif /* DataStructCircleLinkListv2 */
