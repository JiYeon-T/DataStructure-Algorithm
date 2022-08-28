#include "LinkList.h"



// �� ɾ �� ��
#define LINK_LIST     1
#if LINK_LIST

/**
* @fun: init linklist
* @param[in]  L pointer to head node
* @param[in]  size
*/
// Status Init_L(LinkList *L, unsigned int size)
LinkList InitHeadInsert_L(size_t size)
{
    // Node headNode;
    // headNode.next = NULL;
    LinkList pHead = NULL; // û��ͷ�ڵ�
    // pHead = &headNode;
    int data = 0;

    for(size_t ix = 0; ix < size; ++ix)
    {
        LinkList temp = (LinkList)malloc(sizeof(Node) * 1);
        temp->data = data++;
        temp->next = pHead;
        pHead = temp;
    }

    return pHead;
}

/**
* @fun: init liklist
* @param[in]  L pointer to head node
* @param[in]  size
*/
// Status Init_L(LinkList *L, unsigned int size)
LinkList InitTailInsert_L(size_t size)
{
    // ��ͷ���
    Node headNode; // head node, don't save data
    LinkList pHead = NULL, pTail = NULL; // include a head node

    pHead = &headNode;
    pTail = &headNode;
    int data = 0;

    for(size_t ix = 0; ix < size; ++ix)
    {
        LinkList temp = (LinkList)malloc(sizeof(Node) * 1);
        temp->data = data++;
        temp->next = NULL;
        // tail insert
        pTail->next= temp;
        pTail = temp;
    }

    return pHead;
}


/**
* @fun: init liklist with array
* @param[in] pHead head pointer, ͷָ��ָ��ͷ���, ͷ��㲻��������
* @param[in] pArr
* @param[in] len
*/
Status InitLinkListWithArray_L(LinkList *pHead, ElemType *pArr, size_t len)
{
    if(!pHead || !pArr || !len){
        fprintf(stderr, "null ptr\n");
        return ERROR;
    }

    // head node
    Node *head = (Node*)malloc(sizeof(Node) * 1);
    printf("malloc address:%#p\n", head);
    if(!head){
        perror("malloc failed\n");
        return ERROR;
    }
    head->data = 0;
    head->next = NULL;
    *pHead = head;  // ͷָ��ָ��ͷ���, �����ַ; LinkList = struct Node *

    // other node, tail insert
    Node *pTail = head; // βָ��
    for(int ix = 0; ix < len; ++ix){
        Node *pNew = (Node*)malloc(sizeof(Node) * 1);
        if(!pNew){
            perror("malloc failed\n");
            goto EXIT;
        }
        pNew->data = pArr[ix];
        pNew->next = NULL;
        pTail->next = pNew;
        pTail = pNew;
    }

    return OK;
EXIT:
    // �ͷ��Ѿ������ڴ�
    // deinit ������߱����Ѿ���ʼ���Ĳ���
    // ���� ERROR
    return ERROR;
}

/**
* @fun: traverse linklist
* @param[in]  head pointer to head node
*/
Status Traverse_L(LinkList head)
{
    printf("traverse:\n");
    if(head == NULL){
        fprintf(stderr, "null ptr\n");
        return ERROR;
    }

    Node *p_temp = head->next; // include a head node

    while(p_temp){
        printf("%d ->", p_temp->data);
        p_temp = p_temp->next;
    }
    printf("\n\n");

    return OK;
}


/**
* @fun: get linklist element
* @param[in]  L pointer to head node
* @param[in]  i index start from 0
* @param[out] e save value of index ix
*/
Status GetElem_L(LinkList L, int i, ElemType *e)
{
    if(!L){
        return ERROR;
    }
    LinkList p_temp = L->next; // head node
    int j = 0;

    while(p_temp && j<i){
        p_temp = p_temp->next;
        ++j;
    }

    if( !p_temp || j>i ){
        return ERROR;
    }
    *e = p_temp->data;

    return OK;
}

/**
 * @brief Insert a node before node "elem"
 * @param[in] L LinkList
 * @param[in] elem
 * @param[in] insertElem
 * @retval
 */
Status Insert_L(LinkList L, ElemType elem, ElemType insertElem)
{
    if(!L){
        return ERROR;
    }
    // insert insertElem before elem
    LinkList prev = L, cur = L->next;
    LinkList pInsertNode = NULL;

    while(cur && cur->data!=elem){
        prev = cur;
        cur = cur->next;
    }

    // can't find node elem
    if(!cur){
        return ERROR;
    }

    // inser node
    pInsertNode = (LinkList)malloc(sizeof(Node) * 1);
    pInsertNode->data = insertElem;
    pInsertNode->next = cur;
    prev->next = pInsertNode;

    return OK;
}

/**
 * @brief Insert a node before first node
 * @param[in] L head pointer
 * @param[in] elem
 * @retval
 */
Status InserHead_L(LinkList L, ElemType data)
{
    Node *pInsert = (Node*)malloc(sizeof(Node) * 1);
    if(!pInsert){
        perror("malloc failed\n");
        return ERROR;
    }

    pInsert->data = data;
    pInsert->next = L->next; // head node
    L->next = pInsert;

    return OK;
}


/**
 * @brief Insert a node after last node
 * @param[in] L LinkList
 * @param[in] elem
 * @retval
 */
Status InsertTail_L(LinkList L, ElemType data)
{
    Node *pTail = L->next;
    Node *pTemp = L->next;

    Node *pInsert = (Node*)malloc(sizeof(Node) * 1);
    if(!pInsert){
        perror("malloc failed\n");
        return ERROR;
    }
    pInsert->data = data;
    pInsert->next = NULL;

    while(!pTemp){
        pTail = pTemp;
        pTemp = pTemp->next;
    }

    pTail->next = pInsert;

    return OK;
}

/**
 * @brief delete a node
 * @param[in] L LinkList
 * @param[in] deleteElem
 * @retval
 */
Status Delete_L(LinkList L, ElemType deleteElem)
{
    if(!L){
        return ERROR;
    }
    LinkList prev = L, cur = L->next;

    while(cur && cur->data!=deleteElem){
        prev = cur;
        cur = cur->next;
    }

    if(!cur){ // can't find deleteElem
        return ERROR;
    }
    // delete ndoe
    prev->next = cur->next;
    free(cur);

    return OK;
}


/**
* @fun: free heap memory(include head node)
* @param[in]  L pointer to head node
* @retval Status
*/
Status Deinit_L(LinkList *L)
{
    Node *pTemp = (Node*)(*L);
    Node *pFree = NULL;

    while(pTemp != NULL){
        pFree = pTemp;
        pTemp = pTemp->next;
        free(pFree);
    }

    *L = NULL;

    return OK;
}

/**
* @fun: clear linklist, not delte head node, becomde a empty linklist
* @param[in]  L pointer to head node
* @retval Status
*/
Status Clear_L(LinkList L)
{
    printf("param:%#p\n", L);
    Node *pTemp = L->next; // not include head node
    Node *pFree = NULL;

    while(pTemp != NULL){
        pFree = pTemp;
        pTemp = pTemp->next;
        free(pFree);
        pFree = NULL; // �ͷ��ڴ沢���޸�Ϊ NULL, Ҫ��Ȼ�´α����������
    }

    L->next = NULL;

    return OK;
}

/**
* @fun: merge 2 linklist
* @param[in]  L1 pointer to head node*
* @param[in]  L2 pointer to head node
* @retval Status
*/
Status MergeLinkList_L(LinkList L1, LinkList L2)
{

}

/**
* @fun: sort linklist
* @param[in]  L pointer to head node*
* @retval Status
*/
Status SortLinkList_L(LinkList L1)
{

}



//������Ժ���
void linklist_test()
{
//    Node node; //ͷ�ڵ�, �����򲻱�������, ����ѡ�񱣴�������֮���
//    LinkList head = &node; //pointer, size = 4; ָ�� "ͷ�ڵ�" ��ָ��
    // Node head, node1, node2, node3; // struct Node, size = 8, printf("%d - %d", sizeof head, sizeof(node));
    ElemType data;

    // head.next = &node1;
    // node1.data = 1;
    // node1.next = &node2;
    // node2.data = 2;
    // node2.next = &node3;
    // node3.data = 3;
    // node3.next = NULL;

    size_t listSize = 10;
    size_t index = 5;
    LinkList head;
    // head = InitHeadInsert_L(listSize); //ʹ��ͷ�ڵ�ķ�ʽ��ʼ������
    head = InitTailInsert_L(listSize);

    Traverse_L(head);

    GetElem_L(head, 5, &data);
    // printf("linklist[%d] = %d\n", index, data); // Ϊʲô����һ��ӡ�ͳ����⣬����˼����������������������������������
    // printf("abc\n");
    // for(int ix = 0; ix < 4; ++ix){
    //     printf("data = %d\n", data);
    // }

    Insert_L(head, index, 1000);
    Traverse_L(head);
    // printf("data = %d\r\n", data); // Ϊʲô�м䲻���Դ�ӡ����????????????????????????????????????

    Delete_L(head, 6);
    Traverse_L(head);

    Deinit_L(head);
    printf("deinit linklist\n");

    Traverse_L(head);

}

void LinkListTest2()
{
    LinkList pList; // Node * pList;
    ElemType arr[5] = {5, 7, 22, 111, 3};

    InitLinkListWithArray_L(&pList, arr, sizeof(arr)/sizeof(arr[0]));
    printf("get address:%#p\n", pList);
    Traverse_L(pList);
    Insert_L(pList, 22, 99);
    Traverse_L(pList);
    Delete_L(pList, 111);
    Traverse_L(pList);
    printf("arg:%#p\n", pList);
    Clear_L(pList);
    Traverse_L(pList);
    InserHead_L(pList, 1234);
    Traverse_L(pList);
    InsertTail_L(pList, 4568);
    Traverse_L(pList);

    Deinit_L(&pList);
    Traverse_L(pList);

}

#endif
