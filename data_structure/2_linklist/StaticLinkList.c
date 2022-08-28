// ��0-1 �� �� 1-100 ȷʵ�Ǵ� 0-1 �Ƚ���
// �а����߰��ʮ

#if STATIC_LINK_LIST

#include "StaticLinkList.h"

// ����û��ָ�����������, ����ʹ�����ַ�ʽʵ�־�̬����
size_t headIndex = 0; // �Ѿ�ʹ�������ͷָ��(����), ͷָ�벻��������;headIndex=0 ��ʾ������, headIndex!=0��ʾ��Ԫ��
size_t available_space = MAXSIZE;

/**
 * @brief  ��̬�����ڴ�, ֻ����һ���ڵ�
 *
 * @param sl
 * @return int ���ط���Ľڵ���±�
 */
static int Malloc_SL(SLinkList sl)
{
    if(!sl[0].cur){ // û�пռ�
        return -1;
    }
    size_t temp = sl[0].cur;
    sl[0].cur = sl[temp].cur;
    return temp;
}

/**
 * @brief �ڴ����, ʵ���Ͼ��ǽ����õ��ڴ���뵽��������(ͷ�巨)
 *
 * @param sl
 * @param index ���±�Ϊindex �Ľڵ���յ���������
 */
static void Free_SL(SLinkList sl, int index)
{
    sl[index].cur = sl[0].cur;
    sl[0].cur = index;
    return;
}

/**
 * @brief static linklist intialization
 *        Ϊ�˷������, ��ʣ��ռ䱣�浽һ������������, ���������ͷָ�뱣���� SLinkList[0].cur ��
 *        ��ʼ������Ĭ��ֱ�Ӽ��뱸������
 *        ͷ�ڵ�� cur ָ���������һ��Ԫ��
 *        ���һ���ڵ�� cur Ϊ 0
 *        �м�ڵ�:cur = next_node.index;
 */
void InitSpace_SL(SLinkList sl) // component sl[MAXSIZE], ָ��
{
    for(int ix = 0; ix < MAXSIZE; ++ix){
        sl[ix].cur = ix + 1;
    }
    sl[MAXSIZE - 1].cur = 0;    //������������һ���ڵ�

    return;
}

/**
 * @brief Init LinkList, ʹ���������ʼ������
 *
 */
Status InitLinkList_SL(SLinkList sl, size_t size)
{
    component head; // ʵ���Ͼ����ָ�������
    if(size > MAXSIZE){
        printf("Not enough space\n");
        return ERROR;
    }

    head = sl[headIndex];
    srand(time(0));
    //��ʼ����������Ϊ��, ֱ�Ӵ�ͷ�ڵ㿪ʼ����
    for(size_t ix = 0; ix < size; ++ix){
        //printf("head.cur:%d\n", head.cur);
        sl[head.cur].data = rand() % 10;
        head = sl[head.cur];
    }
    sl[head.cur - 1].cur = 0; // װԪ�ص����һ��Ԫ�ص� cur
    sl[0].cur = head.cur - 1;   // ����������׽ڵ�

    headIndex = 1; // ����ͷָ��

    return OK;
}

/**
 * @brief ��������
 *        ��Ԫ�ص����� �� index=headIndex ��ʼ
 *        ��������� index = SLinkList[0].cur ��ʼ, ���һ��Ԫ�� SLinkList[lastElem].cur = 0
 *
 */
void Traverse_SL(SLinkList sl)
{
    if(headIndex == 0){
        printf("empty list\n");
        return;
    }
    component head = sl[headIndex]; // �ƶ���ָ��

    printf("Traverse:\n");
    while(head.cur != 0){ // ����һ��
        printf("%d -> ", head.data);
        head = sl[head.cur]; // pointer to next
    }
    printf("%d\n", head.data);

    return;
}

/**
 * @brief ���� �±�Ϊ index ��Ԫ�ص�ֵ
 *
 * @param[in]  sl
 * @param[in]  index �� 1 ��ʼ, ��һ��Ԫ�ؾ��� headIndex ��Ӧ�ڵ��ֵ
 * @param[out] elem �����ѯ����ֵ
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
 * @brief ɾ���� ix ���ڵ�
 *
 * @param[in]  sl
 * @param[in]  index
 * @param[out] elem ����ɾ����Ԫ�ص�ֵ
 * @retval OK/ERROR
 */
Status RemoveELem_SL(SLinkList sl, size_t index, component *elem)
{
    if(index>MAXSIZE || !sl){
        return ERROR;
    }
    size_t temp = 1;
    component head = sl[headIndex];
    component prev; //Ҫɾ���Ľڵ��ǰһ���ڵ�
    size_t prev_temp; //ǰһ���ڵ�� index

    while(temp<index && head.cur!=0){ //��������Ҫɾ���Ľڵ�
        prev = head;
        prev_temp = temp;
        head = sl[head.cur]; // ��һ���ڵ�
        ++temp;
    }

    if(temp>index || head.cur==0){
        return ERROR;
    }

    // ɾ���ڵ�
    sl[prev_temp].cur = head.cur; // ����ָ����һ���ڵ�
    sl[temp].data = 0;     //��������

    //��ɾ���Ľڵ�����ʹ��ͷ�巨 ���뵽��������ͷ��
    sl[temp].cur = sl[0].cur;   //sl[0].cur ��������ͷָ��
    sl[0].cur = temp;

    return OK;
}

/**
 * @brief ����: ��ͷ��㿪ʼ����, һֱ�����һ��Ԫ��, Ȼ��ʼ����
 *        ÿ����һ��Ԫ��, �������������һ��Ԫ��, ������Ҫ�� Malloc_SL() ֱ�Ӵӱ�����������, ˳����±�������
 *        Ҫ��Ȼ�൱��ͬʱ������������
 *
 * @param[in]  sl
 * @param[in]  index index �� 1 ��ʼ, �����һ���ڵ�ǰ������Ҫ���� previous node ����Ϣ, ����ں�������
 *             ����:
 *             ��������ֹ������Ϊ��
 * @param[out] elem Ҫ�����Ԫ��Ϊ component ����, ������ֵ����, �����Ǵ�������
 */
Status InsertElem_SL(SLinkList sl, size_t index, component elem)
{
    if(index > MAXSIZE){
        return ERROR;
    }
    size_t temp = 1, prev_index = 1;
    component head = sl[headIndex], prev;

    while(temp<index && head.cur!=0){ // ����������, ��������һ��Ԫ��ǰ����������⣬ �߽�����û��ȷ�����
        prev_index = temp;
        prev = head;
        ++temp;
        head = sl[head.cur];
    }

    if(temp>index || head.cur==0){
        return ERROR;
    }

    //insert
    size_t insert_pos = Malloc_SL(sl); //����һ���ڴ�
    sl[insert_pos] = elem; //��Ԫ�ظ�ֵ
    sl[insert_pos].cur = head.cur; // ��ȷ������
    sl[prev_index].cur = insert_pos; // ��ȷ��ǰ��

    return OK;
}

/********************************************* P33 ����1 *******************************************************/
/**
 * @brief test ����: (A-B)U(B-A),  A B ��Ϊ����
 *
 */
void difference(SLinkList space , int index)
{

}

//���Ժ���
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
