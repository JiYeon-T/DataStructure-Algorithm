#include "LinkList_v3.h"
#include <limits.h>


#if defined(DataStructLinkListV3) && (DataStructLinkListV3 == 1)
/**
 * @brief 初始化一个链表, 要修改指针的值, 所以传递 Node** 类型
 *      没有头节点的链表, 空链表头指针为空即可
 *      非必要的一个接口
 * 
 * @param[in/out] L 没有头节点, 直接指向第一个节点的指针
 * Q:传参传 Node * 类型, 不使用 Node ** 类型可以吗?
 * A: 如果通过返回值设置头指针的话可以; 如果通过入参修改 头指针, 则不行;
 * @return
*/
Status InitLinkList(LinkList *L)
{
    //Node *p_first = *L;
    if (!L) {
        LOG_E("null ptr");
        return ERROR;
    }

    *L = NULL;

    return OK;
}

/**
 * @brief Destroy
 * 
 * @param[in/out] L 没有头节点, 直接指向第一个节点的指针
 * @return
*/
Status DestroyLinkList(LinkList *L)
{
    //Node *p_first = *L;
    if (!L) {
        LOG_E("null ptr");
        return ERROR;
    }

    Node *p_curr = *L;
    Node *temp = NULL;
    while (p_curr) {
        temp = p_curr;
        p_curr = p_curr->next;
        free(temp);
        LOG_D("free:%p", temp);
    }

    *L = NULL;

    return OK;
}

/**
 * @brief clear
 *        does not have head node, function equal to destroy
 * 
 * @param[in/out] L 没有头节点, 直接指向第一个节点的指针
 * @return
*/
Status ClearLinkList(LinkList *L)
{
    //Node *p_first = *L;
    return DestroyLinkList(L);
}

/**
 * @brief insert at tail
 * 
 * @param[in] p_first
 * @param[in] data
 * @return
*/
Status PutElem(Node **p_first, ElemType data)
{
    Node *p_prev, *p_curr, *p_insert;

    if (!p_first) {
        LOG_E("null ptr");
        return ERROR;
    }

    p_insert = (Node*)malloc(sizeof(Node) * 1);
    if (!p_insert)
        return ERROR;
    p_insert->data = data;
    p_insert->next = NULL;
    LOG_D("malloc:%p", p_insert);

    if (!(*p_first)) { // 空链表:要插入的节点是头节点
        // set head pointer
        *p_first = p_insert;
        return OK;
    }
    // else { // 非空链表:中间节点
    p_curr = *p_first;
    p_prev = NULL;

    while (p_curr) { // 寻找尾节点, 保存前一个节点
        p_prev = p_curr;
        p_curr = p_curr->next;
    }
    
    p_prev->next = p_insert;

    return OK;
}

/**
 * @brief List empty
 *        first node not null indicate it was not a empty list
 * 
 * @param[in/out] L 没有头节点, 直接指向第一个节点的指针
 * @return
*/
bool ListEmpty(const LinkList L)
{
    //Node *p_first = L;
    return !L ? true : false;
}


/**
 * @brief List length
 * 
 * @param[in/out] L 没有头节点, 直接指向第一个节点的指针
 * @return
*/
size_t ListLength(const LinkList L)
{
    if (!L) {
        LOG_E("empty");
        return 0;
    }

    Node *p_curr = L;
    size_t cnt = 0;

    while (p_curr) {
        ++cnt;
        p_curr = p_curr->next;
    }

    return cnt;
}

/**
 * @brief get linklist element
 *
 * @param[in]  L does not have head node
 * @param[in]  idx index start from 1
 * @param[out] e save value of index ix
 * @return
 */
Status GetElem(const LinkList L, int idx, ElemType *e)
{
    if (!L || !e) {
        LOG_E("null ptr");
        return ERROR;
    }

    Node *p_curr = L;
    int cur_idx = 1; //start from 1

    while (p_curr && cur_idx < idx) {
        ++cur_idx;
        p_curr = p_curr->next;
    }

    if (!p_curr || cur_idx > idx) {
        LOG_E("can't get this node idx:%d", idx);
        return ERROR;
    }

    *e = p_curr->data;

    return OK;
}

/**
 * @brief Locate Elem
 * 
 * @param[in] L
 * @param[in] e
 * @param[in] compare compare function
 * @return success, return item index(start from 1), otherwise return 0(fail)
*/
size_t LocateElem(const LinkList L, ElemType e, bool (*compare)(ElemType, ElemType))
{
    if (!L || !compare) {
        LOG_E("null ptr");
        return ERROR;
    }

    Node *p_curr = L;
    size_t idx = 1; // start from 1

    while (p_curr) {
        if (compare(p_curr->data, e))
            break;
        ++idx;
        p_curr = p_curr->next;
    }

    if (!p_curr) {
        LOG_E("can't find this node data:%d", e);
        return 0;
    }

    return idx;
}

/**
 * @brief previous Element
 * Time Complexity:O(n)
 *
 * @param[in] L
 * @param[in] cur_e current element
 * @param[out] prev_e next element data part
 * @return success, return OK, otherwise return ERROR
*/
Status PriorElem(const LinkList L, ElemType cur_e, ElemType *prev_e)
{
    if (!L || !prev_e) {
        LOG_E("null ptr");
        return ERROR;
    }

    Node *p_curr = L, *p_prev = NULL;

    while (p_curr) {
        if (p_curr->data == cur_e)
            break;
        p_prev = p_curr;
        p_curr = p_curr->next;
    }

    if (!p_curr) {
        LOG_E("can't get this node val:%d", cur_e);
        return ERROR;
    }

    //prev == NULL, 第一个节点没有前驱节点
    if (!p_prev) {
        LOG_E("First node does not have previous node, node val:%d", cur_e);
        return ERROR;
    }

    *prev_e = p_prev->data;

    return OK;
}

/**
 * @brief next Element
 * Time Complexity:O(n)
 * 
 * @param[in] L
 * @param[in] cur_e current element
 * @param[out] next_e previous element data part
 * @return success, return OK, otherwise return ERROR
*/
Status NextElem(const LinkList L, ElemType cur_e, ElemType *next_e)
{
    if (!L || !next_e) {
        LOG_E("null ptr");
        return ERROR;
    }

    Node *temp = L;
    Node *next;

    while (temp) {
        if (temp->data == cur_e)
            break;
        temp = temp->next;
    }

    // can't find cur_e
    if (!temp) {
        LOG_E("can't get this node val:%d", cur_e);
        return ERROR;
    }

    //next == NULL, 最后一个节点没有后继节点
    next = temp->next;
    if (!next) {
        LOG_E("Last node does not have next node, node val:%d", cur_e);
        return ERROR;
    }

    *next_e = next->data;

    return OK;
}

/**
 * @brief insert
 * Time Complexity:O(n)
 * 没有头节点的链表, 就是插入/删除处理比较复杂
 * 
 * @param[in] L 
 * @param[in] idx insert a element before idxth element, start from 1, 1 <= idx <= (ListLength(L) + 1),
 * @param[in] e data
 * @return success, return OK, otherwise return ERROR
*/
Status ListInsert(LinkList *L, size_t idx, ElemType e)
{
    Node *p_curr = *L;
    Node *p_prev = NULL;
    Node *p_insert;
    size_t curr_idx = 1; // start from 1

    if (!L) {
        LOG_E("null ptr");
        return ERROR;
    }

    if (idx < 1 || idx > (ListLength(*L) + 1)) {
        LOG_E("invalid idx");
        return ERROR;
    }

    // empty list insert fist node
    if (!(*L) || idx == 1) { // if (!*L)
        p_insert = (Node*)malloc(sizeof(Node));
        p_insert->data = e;
        p_insert->next = p_curr; // empty list p_curr == NULL
        *L = p_insert;
        LOG_D("insert a first node:%p", p_insert);
        return OK;
    }

    p_insert = (Node*)malloc(sizeof(Node));
    if (!p_insert) {
        LOG_E("malloc failed");
        return ERROR;
    }

    while (p_curr) {
        if (curr_idx == idx)
            break;
        p_prev = p_curr;
        p_curr = p_curr->next;
    }

    // insert at tail
    if (idx == (ListLength(*L) + 1)) {
        p_insert->data = e;
        p_insert->next = NULL;
        p_prev->next = p_insert;
        LOG_D("insert at tail:%p", p_insert);
        return OK;
    }

    if (!p_curr || curr_idx > idx) {
        LOG_E("can't find a match node idx:%d", idx);
        return ERROR;
    }

    p_insert->data = e;
    p_insert->next = p_curr;
    p_prev->next = p_insert;
    LOG_D("insert a node:%p", p_insert);

    return OK;
}

/**
 * @brief delete
 * Time Complexity:O(n)
 * 
 * @param[in] L 
 * @param[in] idx delete a element  idxth element, start from 1, 1 <= idx <= (ListLength(L) + 1),
 * @param[out] e deleted node value
 * @return success, return OK, otherwise return ERROR
*/
Status ListDelete(LinkList *L, size_t idx, ElemType *e)
{
    if (!L || !*L) {
        LOG_E("null ptr");
        return ERROR;
    }

    if (idx < 1 || idx > ListLength(*L)) {
        LOG_E("invalid idx %d", idx);
        return ERROR;
    }

    Node *p_curr = *L;
    Node *p_prev = NULL;
    size_t cur_idx = 1; //start from 1

    // delete first node
    if (idx == 1) {
        *e = p_curr->data;
        *L = p_curr->next;
        free(p_curr);
        return OK;
    }

    while (p_curr) {
        if (cur_idx == idx)
            break;
        ++cur_idx;
        p_prev = p_curr;
        p_curr =p_curr->next;
    }

    if (!p_curr || cur_idx > idx) {
        LOG_E("can't find a match node, idx:%d", idx);
        return ERROR;
    }

    *e = p_curr->data;
    p_prev->next = p_curr->next;
    free(p_curr);
    LOG_D("free:%p", p_curr);

    return OK;
}

/**
 * @brief traverse linklist
 *
 * @param[in] head pointer to head node
 * @param[in] p_visit
 * @return Status
 */
Status ListTraverse(const LinkList L, void (*p_visit)(ElemType e))
{
    if (!L || !p_visit) {
        LOG_E("null ptr");
        return ERROR;
    }

    Node *p_curr = L;
    size_t idx = 1; // start from 1

    LOG_D("traverse:");

    while (p_curr) {
        printf("[%d]:", idx++);
        p_visit(p_curr->data);
        p_curr = p_curr->next;
    }
    printf("\n\n");

    return OK;
}

/**
 * @brief insert before position idx
 * 
 * @param[in] p_first head pointer
 * @param[in] idx start from 0
 * @param[in] data element data
 * @ret
*/
Status InsertElemBeforeIdx(Node **p_first, size_t idx, ElemType data)
{
    if (!(*p_first) && idx != 0) // 空链表还不插入第一个节点
        return ERROR;
    Node *p_insert, *p_curr, *p_prev;
    size_t jx = 0;

    p_insert = (Node*)malloc(sizeof(Node));
    if (!p_insert) {
        return ERROR;
    }
    p_insert->data = data;
    p_insert->next = NULL;
    if (!(*p_first)) { // 空链表:要插入的节点是头节点
        *p_first = p_insert;
        return OK;
    } else if (idx == 0) { // 非空链表:插入头节点
        p_insert->next = *p_first;
        *p_first = p_insert;
        return OK;
    }

    // else {} // 非空链表:中间节点
    p_curr = *p_first;
    p_prev = p_curr;
    while (p_curr && jx < idx) {
        p_prev = p_curr;
        p_curr = p_curr->next;
        ++jx;
    }

    if (!p_curr || jx > idx) {
        free(p_insert);
        return ERROR;
    }

    p_insert->next = p_curr;
    p_prev->next = p_insert;

    return OK;
}

/**
 * @fun insert before idx position
 * @param[in] p_first head pointer
 * @param[in] idx start from 0
 * @param[in] data element data
 * @ret
*/
Status DeleteElem(Node **p_first, size_t idx, ElemType *p_data)
{
    if (!p_first || !(*p_first) || idx < 0 || !p_data)
        return ERROR;

    Node *p_curr, *p_prev;
    size_t jx;

    p_curr = *p_first;
    if (idx == 0) { // delete first node
        *p_first = p_curr->next; // 更新头节点
        free(p_curr); // 删除节点
        return OK;
    }
    // else {} // 删除中间节点
    p_prev = p_curr;
    while (p_curr && jx < idx) {
        p_prev = p_curr;
        p_curr = p_curr->next;
        ++jx;
    }
    if (!p_curr || jx > idx) {
        return ERROR;
    }

    p_prev->next = p_curr->next;
    *p_data = p_curr->data;
    free(p_curr);

    return OK;
}

/**
 * @fun set
 * 
 * @param[in] p_first head pointer
 * @param[in] idx start from 0
 * @param[in] data element data
 * @ret
 **/
Status SetElem(Node *p_first, size_t idx, ElemType data)
{
    if (!p_first || idx < 0)
        return ERROR;
    Node *p_curr = p_first;
    size_t jx;

    while (p_curr && jx < idx) {
        p_curr = p_curr->next;
        ++jx;
    }
    if (!p_curr || jx > idx)
        return ERROR;
    
    p_curr->data = data;

    return OK;
}

/**
 * @fun get
 *
 * @param[in] p_first head pointer
 * @param[in] idx start from 0
 * @param[in] data element data
 * @ret
 **/
Status GetElem2(const Node *p_first, size_t idx, ElemType *p_data)
{
    if (!p_first || idx < 0 || !p_data)
        return ERROR;
    Node *p_curr = p_first;
    size_t jx;

    while (p_curr && jx < idx) {
        p_curr = p_curr->next;
        ++jx;
    }
    if (!p_curr || jx > idx)
        return ERROR;
    
    *p_data = p_curr->data;

    return OK;
}

// 没有头节点
Status Traverse(const Node *p_first, const char *p_op_info)
{
    if (!p_first)
        return ERROR;
    size_t idx = 0;

    printf("traverse(%s):\n", p_op_info);
    Node *pTemp = p_first; // first node
    while (pTemp) {
        printf("[%d]:%d ->", idx++, pTemp->data);
        pTemp = pTemp->next;
    }
    printf("\n\n");

    return OK;
}

void linklist_api_test(void)
{
    Node *p_head = NULL;
    Status ret;
    ElemType data;

    ret = InitLinkList(&p_head);
    CHECK_RET_OP(ret, "Init");

    ret = PutElem(&p_head, 0);
    CHECK_RET_OP(ret, "put");
    ret = Traverse(p_head, "put:0");
    CHECK_RET_OP(ret, "put:0");

    ret = PutElem(&p_head, 1);
    CHECK_RET_OP(ret, "put");
    ret = Traverse(p_head, "put：1");
    CHECK_RET_OP(ret, "put");

    ret = InsertElemBeforeIdx(&p_head, 0, 123);
    CHECK_RET_OP(ret, "insert:123 at head");
    ret = Traverse(p_head, "insert at head");
    CHECK_RET_OP(ret, "insert at head");

    ret = DeleteElem(&p_head, 0, &data);
    CHECK_RET_OP(ret, "delete");
    printf("delte idx:%d elem:%d\n", 0, data);
    ret = Traverse(p_head, "delete head node");
    CHECK_RET_OP(ret, "delete");

    ret = SetElem(p_head, 1, 111);
    CHECK_RET_OP(ret, "set");
    ret = Traverse(p_head, "set idx:1 val:111");
    CHECK_RET_OP(ret, "set");

    ret = GetElem2(p_head, 1, &data);
    CHECK_RET_OP(ret, "get");
    printf("get idx:%d val:%d\n", 1, data);
    ret = Traverse(p_head, "get");
    CHECK_RET_OP(ret, "get");
}

static bool compare_elem(ElemType e1, ElemType e2)
{
    return (e1 == e2);
}

static void visit_elem(ElemType e)
{
    printf("%d  ", e);
}

void linklist_api_test2(void)
{
    LinkList p_head; // first node pointer
    Status ret;
    ElemType elem_data;
    size_t idx;

    ret = InitLinkList(&p_head);
    CHECK_RET(ret);
    // fail case
    // ret = ListTraverse(p_head, visit_elem);
    // CHECK_RET(ret);

    LOG_D("empty:%d  length:%d", ListEmpty(p_head), ListLength(p_head));
    
    //fail case
    // ret = GetElem(p_head, 1, &elem_data);
    // CHECK_RET(ret);
    // ret = PriorElem(p_head, 1, &elem_data);
    // CHECK_RET(ret);
    // ret = NextElem(p_head, 1, &elem_data);
    // CHECK_RET(ret);
    // ret = ListInsert(&p_head, 2, 100);
    // CHECK_RET(ret);
    // ret = ListDelete(&p_head, 1, &elem_data);
    // CHECK_RET(ret);

    ret = ListInsert(&p_head, 1, 100);
    CHECK_RET(ret);
    ret = ListInsert(&p_head, 1, 200);
    CHECK_RET(ret);
    ret = ListInsert(&p_head, 1, 300);
    CHECK_RET(ret);
    ret = ListInsert(&p_head, 1, 400);
    CHECK_RET(ret);
    ret = ListInsert(&p_head, 1, 500);
    CHECK_RET(ret);
    ret = ListInsert(&p_head, 1, 600);
    CHECK_RET(ret);
    LOG_D("empty:%d  length:%d", ListEmpty(p_head), ListLength(p_head));
    ret = ListTraverse(p_head, visit_elem);
    CHECK_RET(ret);

    idx = 1;
    ret = GetElem(p_head, idx, &elem_data);
    CHECK_RET(ret);
    LOG_D("[%d] = %d", idx, elem_data);
    idx = 6;
    ret = GetElem(p_head, idx, &elem_data);
    CHECK_RET(ret);
    LOG_D("[%d] = %d", idx, elem_data);

    // fail case
    // idx = 7;
    // ret = GetElem(p_head, 7, &elem_data);
    // CHECK_RET(ret);
    // LOG_D("[%d] = %d", idx, elem_data);

    elem_data = 500;
    idx = LocateElem(p_head, elem_data, compare_elem);
    LOG_D("data:%d result:%d %s", elem_data, idx, idx == 0 ? "fail" : "success");
    elem_data = 1000;
    idx = LocateElem(p_head, elem_data, compare_elem);
    LOG_D("data:%d result:%d %s", elem_data, idx, idx == 0 ? "fail" : "success");

    ret = PriorElem(p_head, 100, &elem_data);
    CHECK_RET(ret);
    LOG_D("data before 100:%d", elem_data);

    //fail case
    // ret = PriorElem(p_head, 1000, &elem_data);
    // CHECK_RET(ret);
    // LOG_D("data before 1000:%d", elem_data);
    // ret = PriorElem(p_head, 600, &elem_data);
    // CHECK_RET(ret);
    // LOG_D("data before 600:%d", elem_data);

    // //fail case
    // ret = NextElem(p_head, 100, &elem_data);
    // CHECK_RET(ret);
    // LOG_D("data next 100:%d", elem_data);
    // ret = NextElem(p_head, 1000, &elem_data);
    // CHECK_RET(ret);
    // LOG_D("data next 1000:%d", elem_data);
    ret = NextElem(p_head, 600, &elem_data);
    CHECK_RET(ret);
    LOG_D("data next 600:%d", elem_data);

    idx = 1;
    ret = ListDelete(&p_head, idx, &elem_data);    
    CHECK_RET(ret);
    LOG_D("delete idx:%d data:%d", idx, elem_data);
    LOG_D("empty:%d  length:%d", ListEmpty(p_head), ListLength(p_head));
    ret = ListTraverse(p_head, visit_elem);
    CHECK_RET(ret);

    // fail case
    // idx = 100;
    // ret = ListDelete(&p_head, idx, &elem_data);    
    // CHECK_RET(ret);
    // LOG_D("delete idx:%d data:%d", idx, elem_data);
    // LOG_D("empty:%d  length:%d", ListEmpty(p_head), ListLength(p_head));
    // ret = ListTraverse(p_head, visit_elem);
    // CHECK_RET(ret);

    idx = 5;
    ret = ListDelete(&p_head, idx, &elem_data);    
    CHECK_RET(ret);
    LOG_D("delete idx:%d data:%d", idx, elem_data);
    LOG_D("empty:%d  length:%d", ListEmpty(p_head), ListLength(p_head));
    ret = ListTraverse(p_head, visit_elem);
    CHECK_RET(ret);

    ret = ClearLinkList(&p_head);
    CHECK_RET(ret);
    ret = ListTraverse(p_head, visit_elem);
    CHECK_RET(ret);

    ret = DestroyLinkList(&p_head);
    CHECK_RET(ret);
    ret = ListTraverse(p_head, visit_elem);
    CHECK_RET(ret);
}

#endif