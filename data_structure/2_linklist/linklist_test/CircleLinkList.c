/**
 * @file CircleLinkList.c
 * @author your name (you@domain.com)
 * @brief ��β����������, ѭ����ֹ����������ж� temp->next!=head, �Ƿ�Ϊͷָ��
 *        (1) ���������ͷ�ڵ�, ����Ҫʹ�� βָ�������� β��λ����Ϣ
 * @version 0.1
 * @date 2022-03-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "CircleLinkList.h"

/**
 * @brief ��ʼ��ѭ������(û��ͷ�ڵ�)
 *        β�巨(���û��ͷ�ڵ���������Ҫ����ָ��һ��ͷָ��, һ��βָ�룬����ÿ�δ�����Ҫ����)
 * @param head ͷָ��
 * @param size �����С
 */
LinkList_CL Init_CL(size_t size)
{
    if(size <= 0){
        return ERROR;
    }
    int data = 0;
    LinkList_CL pHead = NULL, pTail = NULL;
    
    pHead = (LinkList_CL)malloc(sizeof(LinkList_CL) * 1);
    pHead->data = data++;
    pHead->next = pHead;
    pTail = pHead;

    for(size_t ix = 0; ix < size-1; ++ix){
        //�޸�ͷָ���ֵ head
        LinkList_CL temp = (LinkList_CL)malloc(sizeof(Node_CL) * 1);
        temp->data = data++;
        temp->next = pHead;
        pTail->next = temp;
        pTail = temp;
    }

    return pHead;
}

/**
 * @brief Traverse
 * @param[in] CL head pointer
 */
Status Traverse_CL(LinkList_CL CL)
{
    if(!CL){
        return ERROR;
    }
    LinkList curr = CL;

    while(curr->next != CL){ // ѭ���������� temp->next �Ƿ����ͷָ��
        printf("%d -> ", curr->data);
        curr = curr->next;
    }
    printf("%d\n", curr->data); // ��ӡ���һ���ڵ����Ϣ

    return OK;
}

/**
 * @brief ����
 * @param[in] CL head pointer
 * @param[in] index start from 0
 * @param[out] *data 
 */
Status GetElem_CL(LinkList_CL CL, size_t index, ElemType *data)
{
    if(!CL || index<0){
        return ERROR;
    }
    LinkList_CL curr = CL;
    size_t jx = 0;

    while(curr->next!=CL && jx<index){ // search node
        curr = curr->next;
        ++jx;
    }

    if(curr->next==CL || jx>index){ // index
        return ERROR;
    }
    *data = curr->data;

    return OK;
}


/**
 * @brief ɾ���ڵ�
 * 
 * @param[in] head
 * @param[in] nodeVal 
 */
Status Delete_CL(LinkList_CL head, ElemType nodeVal)
{
    if(!head){
        return ERROR;
    }

    LinkList prev = NULL, cur = head;
    while(cur->next!=head && cur->data!=nodeVal){
        prev = cur;
        cur = cur->next;
    }

    if(cur->next == head){ // Ҫ�ҵĽڵ���ǵ�һ���ڵ�����
        return ERROR;
    }

    prev->next = cur->next;
    free(cur);

    return OK;
}

/**
 * @brief ����һ���ڵ�
 * 
 * @param[in] head
 * @param[in] nodeVal �� nodeVal �ڵ�ǰ���� insertVal �ڵ�
 * @param[in] insertVal
 */
Status Insert_CL(LinkList_CL head, ElemType nodeVal, ElemType insertVal)
{
    if(head == NULL){
        return OK;
    }

    LinkList_CL prev = NULL, curr = head;
    while(curr->next!=head && curr->data!=nodeVal){
        prev = curr;
        curr = curr->next;
    }

    if(curr->next == head){
        return ERROR;
    }

    LinkList_CL temp = (LinkList_CL)malloc(sizeof(Node_CL) * 1);
    temp->data = insertVal;
    temp->next = curr;
    prev->next = temp;

    return OK;
}

/**
 * @brief free heap memory
 * 
 * @param head 
 * @return Status 
 */
Status Deinit_CL(LinkList_CL head)
{
    if(!head){
        return ERROR;
    }

    LinkList_CL curr = head;
    while(curr->next != head){  // Ϊʲô������????????????????????????????
        LinkList temp = curr;
        curr = curr->next;
        free(temp);   
    }

    // �������һ���ڵ�
    free(curr);
    head = NULL;

    return OK;
}



void Test_CL()
{
    LinkList_CL head; // ָ��û�г�Ա������˵��, ���������һ���ڴ���׵�ַ����
    size_t listSize = 10;
    ElemType data;
    // Node_CL node;
    // node.data = 111;
    // node.next = NULL;
    // head = &node; // head ָ�� node
    // printf("%d - %d\n", sizeof(head), sizeof(Node_CL));
    // printf("head:%#p - &node:%#p, &head:%#p", head, &node, &head); // head��ֵ���� node ���׵�ַ
    head = Init_CL(listSize);
    Traverse_CL(head);

    Insert_CL(head, 4, 1000);
    Traverse_CL(head);

    Delete_CL(head, 8);
    Traverse_CL(head);

    GetElem_CL(head, 2, &data);
    printf("data = %d\n", data);

    Deinit_CL(head);
    // head = NULL;
    // printf("head val:%#X %#p",head, &head);
    Traverse_CL(head);
}