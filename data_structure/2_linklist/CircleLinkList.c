/**
 * @file CircleLinkList.c
 * @author your name (you@domain.com)
 * @brief 首尾相连的链表, 循环终止条件变成了判断 temp->next!=head, 是否为头指针
 *        (1) 如果不使用头节点, 就需要使用 尾指针来保存 尾巴位置信息
 * @version 0.1
 * @date 2022-03-16
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "CircleLinkList.h"
#include <stdlib.h>
#include <time.h>
#include <limits.h>


#if defined(CIRCLE_LINK_LIST) && (CIRCLE_LINK_LIST == 1)
/************************************************* 没有头结点 ***************************************************************/
/**
 * @brief 初始化循环链表(没有头节点)
 *        尾插法(如果没有头节点的链表就需要两个指针一个头指针, 一个尾指针，否则每次创建都要遍历)
 * @param head 头指针
 * @param size 链表大小
 */
LinkList_CL InitLinkListWithRandom_CL(size_t size)
{

}

/**
 * @fun Init circle list with array
 *      有头节点
 * 
 * @param[in] p_data
 * @param[in] len
 * @ret
*/
Status InitLinkListWithArray_CL(Node_CL **pList, ElemType *p_data, int len)
{

}

/**
 * @brief Traverse
 * @param[in] CL head pointer
 */
Status Traverse_CL(LinkList_CL CL)
{

}


/**
 * @brief 查找第 idx 个节点的元素
 * 
 * @param[in] CL head pointer
 * @param[in] index start from 0
 * @param[out] *data
 */
Status GetElem_CL(LinkList_CL CL, size_t idx, ElemType *pData)
{

}


/**
 * @brief 删除节点第一个元素值为 val 的节点
 *
 * @param[in] head Node_CL * type
 * @param[in] nodeVal
 */
Status Delete_CL(LinkList_CL head, ElemType val)
{

}

/**
 * @brief 插入一个节点
 *
 * @param[in] head
 * @param[in] nodeVal 在 nodeVal 节点前插入 insertVal 节点
 * @param[in] insertVal
 */
Status Insert_CL(LinkList_CL head, ElemType nodeVal, ElemType insertVal)
{

}

/**
 * @brief free heap memory
 *
 * @param head
 * @return Status
 */
Status Deinit_CL(LinkList_CL head)
{

}

void Test_CL()
{

}

/************************************************* 包含头结点 ***************************************************************/
/**
 * @brief initialize a circle linklist
 *        包含头结点的循环链表, 头结点不保存数据
 *        循环结束条件; 尾结点的 next 指针是否等于头指针(头结点的地址)
 *
 * @param cl
 * @return Status
 */
Status InitCircleLinkListV2(Node_CL **cl)
{
    if (!cl) {
        return ERROR;
    }

    // create head node
    Node_CL *pHead = (Node_CL*)malloc(sizeof(Node_CL) * 1);
    if(!pHead){
        printf("No enough memory\r\n");
        return ERROR;
    }
    pHead->data = INVALID_VAL; // 只有一个头节点
    pHead->next = pHead;
    *cl = pHead;

    return OK;
}

/**
 * @brief traverse
 *
 * @param cl head pointer, 头结点的地址
 * @return Status
 */
Status TraverseCLV2(LinkList_CL cl, const char *p_info)
{
    if (!cl) {
        return ERROR;
    }

    Node_CL *temp = cl->next;
    int jx = 0;

    printf("Traverse(%s):\r\n", p_info);
    while(temp != cl){
        printf("[%d]:%d -> ", jx, temp->data);
        temp = temp->next;
        ++jx;
    }
    printf("\r\n\r\n");

    return OK;
}

/**
 * @brief initialize circle linklist with array
 *
 * @param cl
 * @return Status
 */
Status InitWithArrayCLV2(Node_CL **cl, ElemType *pArr, size_t len)
{
    if(!cl || !pArr || len <= 0){
        return ERROR;
    }
    Node_CL *pTail;
    Node_CL *pHead = (Node_CL*)malloc(sizeof(Node_CL));
    if (!pHead)
        return ERROR;
    pHead->data = INVALID_VAL;
    pHead->next = pHead;

    *cl = pHead; // update head node

    pTail = pHead;
    for(int ix = 0; ix < len; ++ix){
        // tail insert
        Node_CL *pInsert = (Node_CL*)malloc(sizeof(Node_CL));
        if (!pInsert)
            // goto ERROR;
            return ERROR;
        pInsert->data = pArr[ix];
        pInsert->next = *cl; // 循环链表
        pTail->next = pInsert;
        pTail = pInsert;
    
        // head insert
    }

    return OK;
}

/**
 * @brief head insert, 插入第一个节点
 *
 * @param cl
 * @param elem
 * @return Status
 */
Status InsertHeadCLV2(LinkList_CL cl, ElemType elem)
{
    if (!cl) {
        return ERROR;
    }

    Node_CL *pInsert = (Node_CL*)malloc(sizeof(Node_CL) * 1);
    if (!pInsert)
        return ERROR;
    pInsert->data = elem;
    pInsert->next = cl->next;
    cl->next = pInsert; // update first node

    return OK;
}

/**
 * @brief tail insert
 *
 * @param cl
 * @param elem
 * @return Status
 */
Status InsertTailCLV2(LinkList_CL cl, ElemType elem)
{
    if (!cl) {
        return ERROR;
    }

    Node_CL *pCurr = cl->next, *pPrev = pCurr;
    Node_CL *pTemp;

    while (pCurr != cl) {// 结束条件 next != 头指针
        pPrev = pCurr;
        pCurr = pCurr->next;
    }

    // allocate memory
    pTemp = (Node_CL*)malloc(sizeof(Node_CL) * 1);
    pTemp->data = elem;
    pTemp->next = cl; // 尾节点的 next 指针指向头节点
    pPrev->next = pTemp; // previous node's next poniter

    return OK;
}

/**
 * @brief remove the indexTh node 
 * 
 * @param cl 
 * @param idx index from 0
 * @param elem 
 * @return Status 
 */
Status RemoveElemByIdxCLV2(LinkList_CL cl, size_t idx, ElemType *elem)
{
    if(!cl || !elem || idx < 0){
        return ERROR;
    }

    Node_CL *pCurr = cl->next, *pPrev = cl;
    size_t jx = 0;

    while(pCurr != cl && jx < idx){
        pPrev = pCurr;
        ++jx;
        pCurr = pCurr->next;
    }

    if(pCurr == cl || jx > idx){
        return ERROR;
    }

    *elem = pCurr->data;
    pPrev->next = pCurr->next; // update next pointer
    free(pCurr);

    return OK;
}

/**
 * @brief modify element data
 * 
 * @param cl 
 * @param idx index from 0
 * @param elem 
 * @return Status 
 */
Status ModifyElemCLV2(LinkList_CL cl, size_t idx, ElemType elem)
{
    if(!cl || idx < 0){
        return ERROR;
    }

    Node_CL *pCurr = cl->next;
    size_t jx = 0;
    while(pCurr != cl && jx < idx){
        ++jx;
        pCurr = pCurr->next;
    }

    if(pCurr == cl || jx > idx){
        return ERROR;
    }

    pCurr->data = elem;

    return OK;
}

/**
 * @brief get elem
 * 
 * @param cl 
 * @param idx index start from 0
 * @param elem 
 * @return Status 
 */
Status GetElemCLV2(LinkList_CL cl, size_t idx, ElemType *elem)
{
    if(!cl || idx < 0 || !elem){
        return ERROR;
    }

    Node_CL *pCurr = cl->next;
    size_t jx = 0;
    while(pCurr != cl && jx < idx){
        ++jx;
        pCurr = pCurr->next;
    }

    if(pCurr == cl || jx > idx){
        return ERROR;
    }

    *elem = pCurr->data;

    return OK;
}

/**
 * @brief only clear data node
 *        does not free head node
 * 
 * @param cl 
 * @return Status 
 */
Status ClearCLV2(LinkList_CL cl)
{
    if(!cl){
        return ERROR;
    }

    Node_CL *pCurr = cl->next;

    while (pCurr != cl){
        Node_CL *temp = pCurr;
        cl->next = pCurr->next; // 更新头节点的下一个节点
        pCurr = pCurr->next;
        free(temp); // free memory
    }
    
    return OK;
}

/**
 * @brief clear data node and head node
 * 
 * @param cl 
 * @return Status 
 */
Status DeinitCLV2(LinkList_CL *cl)
{
    if (!cl) {
        return ERROR;
    }

    Node_CL *pCurr = (*cl)->next;

    // clear data list
    while (pCurr != (*cl)){
        Node_CL *temp = pCurr;
        (*cl)->next = pCurr->next;
        pCurr = pCurr->next;
        free(temp); // free memory
    }

    // clear head node
    free((*cl));
    *cl = NULL;

    return OK;
}



void CircleLinkListTestV2()
{
    LinkList_CL cl; // 头指针
    ElemType data;
    size_t idx;
    Status ret;

    ret = InitCircleLinkListV2(&cl);
    CHECK_RET_OP(ret, "init");
    ret = TraverseCLV2(cl, "init circle linklist");
    CHECK_RET_OP(ret, "init");

    data = 111;
    printf("insert:%d\r\n", data);
    ret = InsertHeadCLV2(cl, data);
    CHECK_RET_OP(ret, "insert head");
    ret = TraverseCLV2(cl, "insert head node:111");
    CHECK_RET_OP(ret, "insert");

    data = 25;
    printf("insert:%d\r\n", data);
    ret = InsertTailCLV2(cl, data);
    CHECK_RET_OP(ret, "insert tail");
    ret = TraverseCLV2(cl, "insert tail node:25");
    CHECK_RET_OP(ret, "insert");

    data = 100;
    printf("insert:%d\r\n", data);
    ret = InsertHeadCLV2(cl, data);
    CHECK_RET_OP(ret, "insert head");
    ret = TraverseCLV2(cl, "insert head node:100");
    CHECK_RET_OP(ret, "insert");
    
    data = 200;
    printf("insert:%d\r\n", data);
    ret = InsertTailCLV2(cl, data);
    CHECK_RET_OP(ret, "insert tail");
    ret = TraverseCLV2(cl, "insert tail node:200");
    CHECK_RET_OP(ret, "insert");

    idx = 1;
    ret = RemoveElemByIdxCLV2(cl, idx, &data);
    CHECK_RET_OP(ret, "remove idx:1");
    printf("remove index:%d val:%d\r\n", idx, data);
    ret = TraverseCLV2(cl, "remove idx:1");
    CHECK_RET_OP(ret, "remove");

    idx = 0;
    data = -100;
    printf("modify idx:%d val:%d\r\n", idx, data);
    ret = ModifyElemCLV2(cl, idx, data);
    CHECK_RET_OP(ret, "modify");
    ret = TraverseCLV2(cl, "modify idx:0 val:-100");
    CHECK_RET_OP(ret, "modify");

    idx = 1;
    data = -200;
    printf("modify idx:%d val:%d\r\n", idx, data);
    ret = ModifyElemCLV2(cl, idx, data);
    CHECK_RET_OP(ret, "modify");
    ret = TraverseCLV2(cl, "modify idx:1 val:-200");
    CHECK_RET_OP(ret, "modify");

    idx = 1;
    ret = GetElemCLV2(cl, idx, &data);
    CHECK_RET_OP(ret, "get");
    printf("get elem index:%d val:%d\r\n", idx, data);
    ret = TraverseCLV2(cl, "get idx:1");
    CHECK_RET_OP(ret, "get");

    idx = 2;
    ret = GetElemCLV2(cl, idx, &data);
    CHECK_RET_OP(ret, "get");
    printf("get elem index:%d val:%d\r\n", idx, data);
    ret = TraverseCLV2(cl, "get idx:2");
    CHECK_RET_OP(ret, "get");

    ret = ClearCLV2(cl);
    CHECK_RET_OP(ret, "clear");
    ret = TraverseCLV2(cl, "clear");
    CHECK_RET_OP(ret, "clear");

    ret = DeinitCLV2(&cl);
    CHECK_RET_OP(ret, "deinit");
    ret = TraverseCLV2(cl, "deinit");
    CHECK_RET_OP(ret, "deinit");

}

#endif
