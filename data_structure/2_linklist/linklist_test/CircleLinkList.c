/**
 * @file CircleLinkList.c
 * @author your name (you@domain.com)
 * @brief ��β����������, ѭ����ֹ����������ж� temp->next!=head, �Ƿ�Ϊͷָ��
 * @version 0.1
 * @date 2022-03-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "CircleLinkList.h"

/**
 * @brief ��ʼ��ѭ������(û��ͷ�ڵ�)
 *        ͷ�巨��������
 * @param head ͷָ��
 * @param size �����С
 */
void Init_CL(Node_CL *head, size_t size)
{
    Node_CL *temp;
    srand(time(0));
    for(size_t ix = 0; ix < size; ++ix){
        //�޸�ͷָ���ֵ head
        temp = (Node_CL*)malloc(sizeof(Node_CL) * 1);
        temp->data = rand() % 10;
        temp->next = head;
    }
}

/**
 * @brief Traverse
 * 
 */


/**
 * @brief ��ɾ�Ĳ�
 * 
 */


/**
 * @brief �ͷ�������ڴ�
 * 
 * @param head 
 */
void Delete_CL(CLinkList head)
{

}


void Test_CL()
{
    CLinkList head; // ָ��û�г�Ա������˵��, ���������һ���ڴ���׵�ַ����
    Node_CL node;
    node.data = 111;
    node.next = NULL;
    head = &node; // head ָ�� node
    printf("%d - %d\n", sizeof(head), sizeof(Node_CL));
    printf("head:%#p - &node:%#p, &head:%#p", head, &node, &head); // head��ֵ���� node ���׵�ַ
    
}