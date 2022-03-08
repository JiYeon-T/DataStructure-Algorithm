#include "ringbuffer.h"

/*
* @fun: ring buffer ��ʼ��
*/
void ring_buffer_init(ring_buffer_t *buffer)
{
    buffer->tail_index = 0;
    buffer->head_index = 0;

    return;
}

/*
* @fun: �ж� ring buffer �Ƿ���, ����Ƶ�����õĺ���, ������������
*/
uint8_t ring_buffer_is_full(ring_buffer_t *buffer)
{
    return ((buffer->head_index - buffer->tail_index) & RING_BUFFER_MASK) \
            == RING_BUFFER_MASK;
}

/*
* @fun:�ж�ringbuffer �Ƿ�Ϊ��
*/
uint8_t ring_buffer_is_empty(ring_buffer_t *buffer)
{
    return (buffer->head_index == buffer->tail_index);
}

/*
* @fun: ��ȡԪ�ظ���
*/
u8 ring_buffer_num_items(ring_buffer_t *buffer)
{
    return ((buffer->head_index - buffer->tail_index) & RING_BUFFER_MASK);
}

/*
* @fun: �洢:����ͷָ���ָ���λ��, head++
*       �������, βָ����ƶ�һ��λ��
*/
void ring_buffer_queue(ring_buffer_t *buffer, u8 data)
{
    //
    if(ring_buffer_is_full(buffer)){
        // overwrite the oldest data
        buffer->tail_index = ((buffer->tail_index + 1) & RING_BUFFER_MASK);
    }

    buffer->buffer[buffer->head_index] = data;
    buffer->head_index = ((buffer->head_index + 1) & RING_BUFFER_MASK);

    return;
}

/*
* @fun: �����洢����
*/
void ring_buffer_queue_arr(ring_buffer_t *buffer, const char *data, u8 len)
{
    for(u8 ix = 0; ix < len; ++ix){
        ring_buffer_queue(buffer, data[ix]);
    }
    return;
}

/*
* @fun:ȡ������
* @param[in]  buffer
* @param[out] data
*/
u8 ring_buffer_deque(ring_buffer_t *buffer, char *data)
{
    if(ring_buffer_is_empty(buffer)){
        return 0;
    }
    *data = buffer->buffer[buffer->tail_index];
    buffer->tail_index = ((buffer->tail_index + 1) & RING_BUFFER_MASK);
    return 1;
}

/*
* @fun: ��������Ԫ��
* @param[in]  buffer
* @param[out] data
* @param[in]  len
*/
u8 ring_buffer_dequeue_arr(ring_buffer_t *buffer, u8 *data, u8 len)
{
    if(ring_buffer_is_empty(buffer)){
        return 0;
    }
    char *data_ptr = data;
    u8 cnt = 0;
    while((cnt<len) && (ring_buffer_deque(buffer, data_ptr)))
    {
        ++cnt;
        ++data_ptr;
    }

    return cnt;
}

/*
* @fun:�鿴 ring_buffer �е�Ԫ��, ������ָ��ƫ��
* @param[in]  buffer
* @param[out] data
* @param[in]  index Ҫ�鿴��Ԫ�ص�ƫ����(�ڼ���Ԫ��)
*/
u8 ring_buffer_peek(ring_buffer_t *buffer, char *data, u8 index)
{
    if(index >= ring_buffer_num_items(buffer)){
        return 0;
    }

    u8 data_index = ((buffer->tail_index + index) & RING_BUFFER_MASK);
    *data = buffer->buffer[data_index];
    return 1;
}

/*
* @fun: ģ����Ժ���
*       �ںв���, �׺в���, ɳ����Զ���ʲô����
*/
void test()
{
    int i, cnt;
    char buf;
    char buf_arr[50];

    ring_buffer_t ring_buffer;
    ring_buffer_init(&ring_buffer);

    //����Ԫ��
    for(i = 0; i < 100; ++i){
        ring_buffer_queue(&ring_buffer, i);
    }

    //verify size
    assert(ring_buffer_num_items(&ring_buffer) == 100);

    printf("\n==============================\n");
    //deque all elements
    for(cnt = 0; ring_buffer_deque(&ring_buffer, &buf)>0; cnt++){
        assert(buf == cnt);
        printf("read:%d\n", buf);
    }
    printf("\n==============================\n");

    // enter queue
    ring_buffer_queue_arr(&ring_buffer, "hello, world", 13);
    assert(!ring_buffer_is_empty(&ring_buffer)); // assert

    printf("\n==============================\n");
    // deque
    while(ring_buffer_deque(&ring_buffer, &buf) > 0){
        printf("read:%d\n", buf);
    }

    printf("\n==============================\n");
    //����Ԫ��
    ring_buffer_queue_arr(&ring_buffer, "hello, world", 13);
    assert(!ring_buffer_is_empty(&ring_buffer)); // assert

    printf("\n==============================\n");
    //ȡ��Ԫ��
    cnt = ring_buffer_dequeue_arr(&ring_buffer, buf_arr, 13);
    printf("cnt = %d\n", cnt);
    assert(cnt == 13);
    buf_arr[13] = '\0';
    printf("data:%s\n", buf_arr);
}



















