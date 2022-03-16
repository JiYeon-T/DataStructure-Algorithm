#include "LinkList.h"


// �� ɾ �� ��

//������Ժ���
void linklist_test()
{
//    Node node; //ͷ�ڵ�, �����򲻱�������, ����ѡ�񱣴�������֮���
//    LinkList head = &node; //pointer, size = 4; ָ�� "ͷ�ڵ�" ��ָ��
    Node head, node1, node2, node3; // struct Node, size = 8, printf("%d - %d", sizeof head, sizeof(node));
    ElemType data;

    //Init_L(head); //ʹ��ͷ�ڵ�ķ�ʽ��ʼ������
    head.next = &node1;
    node1.data = 1;
    node1.next = &node2;
    node2.data = 2;
    node2.next = &node3;
    node3.data = 3;
    node3.next = NULL;

    //traverse the linklist
    Traverse_L(&head);

    data = GetElem_L(&head, 0, &data);
    printf("linklist[%d] = %d\n", 0, data);

}


/**
* @fun: init liklist
* @param[in]  L pointer to head node
* @param[in]  size
*/
Status Init_L(LinkList L, unsigned int size)
{

}

/**
* @fun: traverse linklist
* @param[in]  head pointer to head node
*/
Status Traverse_L(LinkList head)
{
    if(head == NULL){
        return ERROR;
    }

    Node *p_temp = head->next;

    while(p_temp){
        printf("%d ->", p_temp->data);
        p_temp = p_temp->next;
    }
    printf("\n");

    return OK;
}


/**
* @fun: get linklist element
* @param[in]  L pointer to head node
* @param[in]  i index start from 0
* @param[out] e save value of index ix
*/
ElemType GetElem_L(LinkList L, int i, ElemType *e)
{
    Node *p_temp = L->next; //first node
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


