#include "LinkListv4.h"


#if defined(DataStructLinkListV4) && (DataStructLinkListV4 == 1)
/*************************************************************************************
 * MACRO
 *************************************************************************************/
#define COPY_ELEM(dest_elem_addr, src_elem_addr, elem_size)   \
    memcpy(dest_elem_addr, src_elem_addr, elem_size)
/*************************************************************************************
 * PUBLIC FUNCTIONS
 *************************************************************************************/
/**
 * @brief allocatet a node space and init data 
 * 
 * @param[in/out] p Node **type
 * @param[in] e data
 * @return success return OK, otherwise return ERROR
*/
Status MakeNode(struct Node **p, ElemType elem)
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
    // COPY_ELEM(temp->data, elem, sizeof(ElemType));
    temp->data = elem;
    temp->next = NULL;
    LOG_D("malloc node ptr:%p", temp);

    *p = temp;

    return OK;
}

/**
 * @brief only free a node pointer(${next}) memory allocated by itself
 *        data field(${ElemType data}) managed by upper layer
 * 
 * @param[in/out] p
*/
void FreeNode(struct Node *p)
{
    if (!p) {
        LOG_E("null ptr");
        return;
    }

    // 如果这里不清空数据域, 由上层自己控制
    // if (p->data) {
    //     LOG_D("free node data:%p", p->data);
    //     free(p->data);
    // }

    free(p);
    LOG_D("free node ptr:%p", p);

    return;
}

/**
 * @brief 释放指针域分配的内存
 * 数据域部分分配的内存也被释放掉, 但是存在一个 bug, Elemtype 不支持嵌套指针, 否则还是会内存泄漏
 * 
*/
void ClearNode(struct Node *p)
{
    if (!p) {
        LOG_E("null ptr");
        return;
    }

    // also need free data part
    // 如果这里不清空数据域, FreeNode 就会导致内存泄漏了..
    if (p->data) {
        LOG_D("free node data:%p", p->data);
        free(p->data);
    }

    free(p);
    LOG_D("free node ptr:%p", p);

    return;
}

/**
 * @brief create a node allocated memory, 
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

    Status ret;
    // init a head node
    struct Node *p_head;
    ret = MakeNode(&p_head, NULL);
    p_head->next = NULL;

   // init struct LinkList
    L->head = p_head;
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
    struct Node *p_curr = L->head->next;

    while (p_curr != NULL) {
        struct Node *p_delete = p_curr;
        p_curr->next = p_delete->next; // 更新前一个节点的 next 指针

        p_curr = p_curr->next; // 迭代
        // LOG_D("delte[%d]:%p", idx++, temp);
        // FreeNode(p_delete); // 释放内存
        ClearNode(p_delete); // 释放内存
        --L->len; // 链表长度 -1
    }

    L->head->next = NULL;

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
    ClearNode(L->head);
    L->head = NULL;
    // L->len = 0;

    return OK;
}

/**
 * @brief Insert before first node, aftet head node,
 * 
 * @param[in] h pointer to head node
 * @param[in] s insert before first node, s become the fist node,
*/
Status InsFirst(LinkList *L, struct Node *s)
{
    if (!L || !s) {
        LOG_E("null ptr");
        return ERROR;
    }

    struct Node *p_first = L->head->next;

    if (!p_first) { // empty list
        s->next = NULL;
        L->head->next = s;
    } else {
        s->next = p_first;
        L->head->next = s;
    }
    ++L->len;

    return OK;
}

/**
 * @brief delete fist node, only remove from linklist, does not free memory
 * 
 * @param[in] h pointer to head node
 * @param[in/out] q delete first node , return with this pointer
*/
Status DelFirst(LinkList *L, struct Node **p_first)
{
    if (!L || !p_first) {
        LOG_E("null ptr");
        return ERROR;
    }

    struct Node *p_first_node = L->head->next; // first node

    if (!p_first_node) {
        *p_first = NULL;
        return ERROR;
    }

    L->head->next = p_first_node->next;
    --L->len;

    *p_first = p_first_node;

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

    struct Node *p_prev = L->head;
    struct Node *p_curr = L->head->next;

    while (p_curr) {
        p_prev = p_curr;
        p_curr = p_curr->next;
    }

    s->next = NULL;
    p_prev->next = s;
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

    if (!curr) {
        LOG_E("empty list, does not have tail node");
        return ERROR;
    }

    while (curr->next) {
        prev = curr;
        curr = curr->next;
    }

    prev->next = curr->next; // NULL

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
 * @param[in] s node pointer to insert
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

    while (curr != NULL && curr != p) {
        prev = curr;
        curr = curr->next;
    }

    if (curr != p || curr == NULL) {
        LOG_E("can't find node:%p", p);
        return ERROR;
    }

    s->next = curr;
    prev->next = s;

    ++L->len;

    return OK;
}


/**
 * @brief insert s after p
 * p -> s -> p->next
 * 
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
    while (curr != p && curr != NULL) {
        curr = curr->next;
    }
    if (curr != p || curr == NULL) {
        LOG_E("can't find node:%p data:", p);
        return ERROR;
    }

    s->next = p->next;
    p->next = s;

    ++L->len;

    return OK;
}


/**
 * @brief set current element
 *
 * @param[in] p linklist node
 * @param[in] e must be a pointer which point to the new data field
 * @return 
*/
Status SetCurrElem(struct Node *p, ElemType e)
{
    if (!p) {
        LOG_E("null ptr");
        return ERROR;
    }

    // Free Previous?

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
        return NULL;
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
        return false;
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
 * @return struct Node * type, return NULL when list is empty
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

    struct Node *p_curr = L->head->next;

    if (!p_curr) { // empty list
        return NULL;
    }

    while (p_curr->next) {
        p_curr = p_curr->next;
    }

    return p_curr;
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
    while (curr != p && curr != NULL) {
        prev = curr;
        curr = curr->next;
    }

    if (curr != p && curr == NULL) {
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

    if (p == L->head) { // p is head node
        return L->head->next;
    }

    struct Node *curr = L->head->next;

    // 判断 p 是否在链表中
    while (curr != p && curr != NULL) {
        curr = curr->next;
    }

    if (curr != p && curr == NULL) {
        LOG_E("can't find node:%p data:", p);
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
    struct Node *p_curr = L->head->next;

    while (p_curr && j < i) {
        p_curr = p_curr->next;
        ++j;
    }

    if (!p_curr) {
        LOG_E("can't find node idx:%d", i);
        return ERROR;
    }

    // 已经判断过 i 的合法性
    *p = p_curr;

    return OK;
}

/**
 * @brief get element matched node, compare node content part
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

    while (curr != NULL) {
        if (compare(curr->data, e))
            break;
        curr = curr->next;
    }

    if (compare(curr->data, e) == false) { // 没有遍历到
        LOG_E("can't find node elem data:%p", e);
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
    if (!L || !visit || !L->head) {
        LOG_E("null ptr");
        return ERROR;
    }

    size_t i = 0;
    struct Node *prev = L->head;
    struct Node *curr = L->head->next;

    LOG_D("traverse:");
    while (curr != NULL) {
        // printf("{[%d]:", i++);
        printf("{");
        visit(curr->data);
        printf("}  ->  ");
        curr = curr->next;
    }
    printf("\r\n\r\n");

    return OK;
}

/**
 * @brief 尾插法
 * 
 * @param[in] L
 * @param[in] elemArr void ** type, pointer
 * @param[in] arrSize
 * @return
*/
Status InitWithArray(LinkList *L, ElemType *elemArr, size_t arrSize)
{
    Status ret;
    struct Node *p_temp, *p_insert;

    if (!L || !elemArr || arrSize <= 0) {
        LOG_E("null ptr");
        return ERROR;
    }

    // 判断是否有头节点,没有的话初始化一个头节点
    if (!L->head) {
        LOG_I("does not have head node, create");
        ret = MakeNode(&p_temp, NULL);
        CHECK_RET(ret);
        p_temp->next = NULL;
        L->head = p_temp;
        L->len = 0;
    }

    for (int i = 0; i < arrSize; ++i) {
        ret = MakeNode(&p_insert, elemArr[i]);
        CHECK_RET(ret);
        p_insert->next = NULL;

        p_temp = GetLast(L);
        if (!p_temp) { // empty list
            ret = InsFirst(L, p_insert);
            CHECK_RET(ret);
        } else { // 尾插法
            ret = InsAfter(L, p_temp, p_insert);
            CHECK_RET(ret);
        }
    }

    return OK;
}

/**
 * @brief insert s before p
 *        prev -> s -> p
 * 
 * @param[in] p
 * @param[in] s
 * @return
*/
Status InsertBefore(LinkList *L, struct Node *p, struct Node *s)
{
    if (!L || !p || !s) {
        LOG_E("null ptr");
        return ERROR;
    }

    struct Node *p_prev = L->head;
    struct Node *p_curr = L->head->next;

    if (!p_curr) {
        LOG_E("empty list");
        return ERROR;
    }

    while (p_curr && p_curr != p) {
        p_prev = p_curr;
        p_curr = p_curr->next;
    }

    if (p_curr != p) {
        LOG_E("can't find node:%p", p);
        return ERROR;
    }

    s->next = p;
    p_prev->next = s;

    ++L->len;

    return OK;
}

/**
 * @brief delete a node, it will clear node memory
 * 
 * @param[in] L
 * @param[in] p_node
*/
Status DeleteNode(LinkList *L, struct Node *p)
{
    if (!L || !p) {
        LOG_E("null ptr");
        return ERROR;
    }

    struct Node *p_prev = L->head;
    struct Node *p_curr = L->head->next;

    if (!p_curr) {
        LOG_E("empty list");
        return ERROR;
    }

    while (p_curr && p_curr != p) {
        p_prev = p_curr;
        p_curr = p_curr->next;
    }

    if (p_curr != p) {
        LOG_E("can't find node:%p", p);
        return ERROR;
    }

    p_prev->next = p->next;

    // Free Memory
    ClearNode(p);

    --L->len;

    return OK;
}

/**
 * @brief Get Next Node
*/
struct Node * NexPos(LinkList *L, struct Node *p)
{
    if (!L || !p) {
        LOG_E("null ptr");
        return ERROR;
    }

    return p->next;
}
/*************************************************************************************
 * Elemtype - int *
 *************************************************************************************/
static bool CompareInt(ElemType a, ElemType b)
{
    return *(int*)a == *(int*)b;
}

static void VisitInt(ElemType e)
{
    printf("%d", *(int*)e);
}

static bool Small2bigInt(ElemType a, ElemType b)
{
    return *(int*)a <= *(int*)b;
}

/**
 * @brief allocate memory for elem
 * 
 * @param[out] p_elem int ** type
*/
static Status MakeElemInt(ElemType *p_elem, int val)
{
    if (!p_elem)
        return ERROR;

    int *p_val = malloc(sizeof(int));
    if (!p_val)
        return ERROR;
    *p_val = val;

    *p_elem = p_val;
    LOG_D("alloc int elem:%p", *p_elem);

    return OK;
}

static Status FreeElemInt(ElemType elem)
{
    if (!elem)
        return ERROR;

    LOG_D("free int elem:%p", elem);
    free(elem);

    return OK;
}

static Status MakeNodeInt(struct Node **p, int val)
{
    Status ret;
    ElemType elem;

    if (!p)
        return ERROR;

    ret = MakeElemInt(&elem, val);
    CHECK_RET(ret);

    ret = MakeNode(p, elem);
    CHECK_RET(ret);

    return OK;
}

static void FreeNodeInt(struct Node *p)
{
    if (!p) {
        return;
    }

    if (p->data) {
        FreeElemInt(p->data);
    }

    FreeNode(p);

    return;
}


/**
 * @brief p_data pointer to a interger variable
*/
void linklist_api_test_integer(void)
{
    LinkList l;
    Status ret;
    struct Node *p_node, *p_node2;
    ElemType elem; // pointer
    struct Node *p_insert;

    LOG_D("v4");

    ret = InitList(&l);
    CHECK_RET(ret);
    ret = ListTraverse(&l, VisitInt);
    CHECK_RET(ret);

    ret = MakeNodeInt(&p_node, 100);
    CHECK_RET(ret);
    ret = Append(&l, p_node);
    CHECK_RET(ret);
    ret = ListTraverse(&l, VisitInt);
    CHECK_RET(ret);


    MakeNodeInt(&p_node, 200);
    Append(&l, p_node);
    MakeNodeInt(&p_node, 300);
    Append(&l, p_node);
    MakeNodeInt(&p_node, 400);
    Append(&l, p_node);
    MakeNodeInt(&p_node, 500);
    Append(&l, p_node);
    MakeNodeInt(&p_node, 600);
    Append(&l, p_node);
    
    LOG_D("len:%d", ListLength(&l));
    ret = ListTraverse(&l, VisitInt);
    CHECK_RET(ret);

    ret = RemoveTail(&l, &p_node);
    CHECK_RET(ret);
    LOG_D("removed node:%p data:", p_node);
    VisitInt(p_node->data);
    printf("\n");
    FreeElemInt(p_node->data);
    FreeNode(p_node);
    LOG_D("len:%d", ListLength(&l));
    ret = ListTraverse(&l, VisitInt);
    CHECK_RET(ret);

    p_node = GetHead(&l);
    CHECK_NOT_NULL(p_node);
    LOG_D("head:%p", p_node);
    p_node = NextPos(&l, p_node); // first node
    LOG_D("first node:%p data:", p_node);
    VisitInt(p_node->data);
    printf("\n");
    MakeNodeInt(&p_node2, 1000);
    ret = InsBefore(&l, p_node, p_node2);
    CHECK_RET(ret);
    MakeNodeInt(&p_node2, 1001);
    ret = InsAfter(&l, p_node, p_node2);
    CHECK_RET(ret);
    LOG_D("len:%d", ListLength(&l));
    ret = ListTraverse(&l, VisitInt);
    CHECK_RET(ret);


    p_node = GetLast(&l);
    CHECK_NOT_NULL(p_node);
    LOG_D("tail:%p data:", p_node);
    VisitInt(p_node->data);
    printf("\n");
    MakeNodeInt(&p_node2, 2000);
    ret = InsBefore(&l, p_node, p_node2);
    CHECK_RET(ret);
    MakeNodeInt(&p_node2, 2001);
    ret = InsAfter(&l, p_node, p_node2);
    CHECK_RET(ret);
    LOG_D("len:%d", ListLength(&l));
    ret = ListTraverse(&l, VisitInt);
    CHECK_RET(ret);

    LOG_D("node:%p data:", p_node);
    VisitInt(GetCurrElem(p_node));
    printf("\n");
    p_node = NextPos(&l, p_node);
    LOG_D("next node:%p data:", p_node);
    VisitInt(GetCurrElem(p_node));
    printf("\n");

    ret = MakeElemInt(&elem, 400);
    CHECK_RET(ret);
    p_node = LocateElem(&l, elem, CompareInt);
    CHECK_NOT_NULL(p_node);
    LOG_D("node:%p data:", p_node);
    VisitInt(GetCurrElem(p_node));
    printf("\n");
    FreeElemInt(elem);


    ret = LocatePos(&l, 2, &p_node);
    CHECK_RET(ret);
    LOG_D("2th node:%p data:", p_node);
    VisitInt(GetCurrElem(p_node));
    printf("\n");

    LOG_D("insert before node2");
    ret = MakeNodeInt(&p_insert, 5000);
    CHECK_RET(ret);
    ret =InsertBefore(&l, p_node, p_insert);
    CHECK_RET(ret);
    LOG_D("len:%d", ListLength(&l));
    ret = ListTraverse(&l, VisitInt);
    CHECK_RET(ret);

    LOG_D("delete ndoe2");
    ret = DeleteNode(&l, p_node);
    CHECK_RET(ret);
    ret = ListTraverse(&l, VisitInt);
    CHECK_RET(ret);

    LOG_D("head's next data:");
    p_node = GetHead(&l);
    p_node = NextPos(&l, p_node);
    VisitInt(p_node->data);
    printf("\n");

    ret = ClearList(&l);
    CHECK_RET(ret);
    ret = ListTraverse(&l, VisitInt);
    CHECK_RET(ret);

    ret= DestroyList(&l);
    CHECK_RET(ret);
    ret = ListTraverse(&l, VisitInt);
    CHECK_RET(ret);
}

void linklist_api_integer_test2(void)
{
    Status ret;
    int a = 1, b = 2, c = 3, d = 4;
    int *intArr[] = {&a, &b, &c, &d};
    LinkList list = {NULL, 0};

    ret = InitWithArray(&list, intArr, ARRAY_SIZE(intArr));
    CHECK_RET(ret);
    ret = ListTraverse(&list, VisitInt);
    CHECK_RET(ret);
}
/*************************************************************************************
 * Elemtype - StrElem_t*(string type)
 *************************************************************************************/
typedef struct {
    int len; // include '\0'
    char data[]; // 这里不占用内存
} StrElem_t;

static void struct_size_test(void)
{
    LOG_D("struct size:%d", sizeof(StrElem_t));
    LOG_D("offset:%d %d", offsetof(StrElem_t, len), offsetof(StrElem_t, data));
    StrElem_t *p1 = malloc(20);
    LOG_D("strcut object size:%d", sizeof(*p1));
    free(p1);
}

static bool CompareStr(ElemType a, ElemType b)
{
    return strcmp(((StrElem_t*)a)->data, ((StrElem_t*)b)->data) == 0;
}

static void VisitStr(ElemType elem)
{
    StrElem_t *p_elem = elem;
    printf("%s(len:%d)", p_elem->data, p_elem->len);
}

static bool Small2bigStr(ElemType a, ElemType b)
{
    return strcmp(((StrElem_t*)a)->data, ((StrElem_t*)b)->data) < 0;
}

/**
 * @brief allocate memory for elem
 * 
 * @param[out] p_elem int ** type
*/
static Status MakeElemStr(ElemType *p_elem, const char *str)
{
    if (!p_elem)
        return ERROR;

    StrElem_t *p_val = malloc(strlen(str) + 1 + 4);
    if (!p_val)
        return ERROR;
    p_val->len = strlen(str) + 1;
    strcpy(p_val->data, str);

    *p_elem = p_val;
    LOG_D("alloc string elem:%p", *p_elem);

    return OK;
}

static Status FreeElemStr(ElemType elem)
{
    if (!elem)
        return ERROR;

    LOG_D("free string elem:%p", elem);
    free(elem);

    return OK;
}

static Status MakeNodeStr(struct Node **p, const char *str)
{
    Status ret;
    ElemType elem;

    if (!p)
        return ERROR;

    ret = MakeElemStr(&elem, str);
    CHECK_RET(ret);

    ret = MakeNode(p, elem);
    CHECK_RET(ret);

    return OK;
}

static void FreeNodeStr(struct Node *p)
{
    if (!p) {
        return;
    }

    if (p->data) {
        FreeElemInt(p->data);
    }

    FreeNode(p);

    return;
}

void linklist_api_test_string(void)
{
    LinkList l;
    Status ret;
    struct Node *p_node, *p_node2;
    ElemType elem; // StrElem_t*

    ret = InitList(&l);
    CHECK_RET(ret);
    ret = ListTraverse(&l, VisitStr);
    CHECK_RET(ret);

    ret = MakeNodeStr(&p_node, "first node");
    CHECK_RET(ret);
    ret = Append(&l, p_node);
    CHECK_RET(ret);
    ret = ListTraverse(&l, VisitStr);
    CHECK_RET(ret);

    MakeNodeStr(&p_node, "Second Node");
    Append(&l, p_node);
    MakeNodeStr(&p_node, "Third Node");
    Append(&l, p_node);
    MakeNodeStr(&p_node, "Fourth Node");
    Append(&l, p_node);
    MakeNodeStr(&p_node, "Fifth Node");
    Append(&l, p_node);
    MakeNodeStr(&p_node, "Sixth Node");
    Append(&l, p_node);
    
    LOG_D("len:%d", ListLength(&l));
    ret = ListTraverse(&l, VisitStr);
    CHECK_RET(ret);

    ret = RemoveTail(&l, &p_node);
    CHECK_RET(ret);
    LOG_D("removed node:%p data:", p_node);
    VisitStr(p_node->data);
    printf("\n");
    FreeElemInt(p_node->data);
    FreeNode(p_node);
    LOG_D("len:%d", ListLength(&l));
    ret = ListTraverse(&l, VisitStr);
    CHECK_RET(ret);

    p_node = GetHead(&l);
    CHECK_NOT_NULL(p_node);
    LOG_D("head:%p", p_node);
    p_node = NextPos(&l, p_node); // first node
    LOG_D("first node:%p data:", p_node);
    VisitStr(p_node->data);
    printf("\n");
    MakeNodeStr(&p_node2, "Node 1001");
    ret = InsBefore(&l, p_node, p_node2);
    CHECK_RET(ret);
    MakeNodeStr(&p_node2, "Node 1002");
    ret = InsAfter(&l, p_node, p_node2);
    CHECK_RET(ret);
    LOG_D("len:%d", ListLength(&l));
    ret = ListTraverse(&l, VisitStr);
    CHECK_RET(ret);


    p_node = GetLast(&l);
    CHECK_NOT_NULL(p_node);
    LOG_D("tail:%p data:", p_node);
    VisitStr(p_node->data);
    printf("\n");
    MakeNodeStr(&p_node2, "Node 2001");
    ret = InsBefore(&l, p_node, p_node2);
    CHECK_RET(ret);
    MakeNodeStr(&p_node2, "Node 2002");
    ret = InsAfter(&l, p_node, p_node2);
    CHECK_RET(ret);
    LOG_D("len:%d", ListLength(&l));
    ret = ListTraverse(&l, VisitStr);
    CHECK_RET(ret);

    LOG_D("node:%p data:", p_node);
    VisitStr(GetCurrElem(p_node));
    printf("\n");
    p_node = NextPos(&l, p_node);
    LOG_D("next node:%p data:", p_node);
    VisitStr(GetCurrElem(p_node));
    printf("\n");

    ret = MakeElemStr(&elem, "Node 2001");
    CHECK_RET(ret);
    p_node = LocateElem(&l, elem, CompareStr);
    CHECK_NOT_NULL(p_node);
    LOG_D("node:%p data:", p_node);
    VisitStr(GetCurrElem(p_node));
    printf("\n");
    FreeElemInt(elem);


    ret = LocatePos(&l, 2, &p_node);
    CHECK_RET(ret);
    LOG_D("2th node:%p data:", p_node);
    VisitStr(GetCurrElem(p_node));
    printf("\n");

    ret = ClearList(&l);
    CHECK_RET(ret);
    ret = ListTraverse(&l, VisitStr);
    CHECK_RET(ret);

    ret= DestroyList(&l);
    CHECK_RET(ret);
    ret = ListTraverse(&l, VisitStr);
    CHECK_RET(ret);
}


#endif //DataStructureLinkListv4