/**
 * @file ringbuffer.c
 * @author your name (you@domain.com)
 * @brief ringbuffer �����ڴ��ڻ���, ����������ݵȵ�...
 * @version 0.1
 * @date 2022-03-26
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "ringbuffer.h"

#if defined(DATA_STRUCTURE_RINGBUFFER) && (DATA_STRUCTURE_RINGBUFFER == 1)


// definition
test_mode_t test_mode;

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
#if 0
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
#endif





#include <stdio.h>
#include <stdlib.h>
#include "ringbuffer.h"
#include <stddef.h>

void print(test_mode_t args)
{
    printf("%d\r\n", args);
    return;
}

void enum_type_test()
{
    print(TEST_MODE_DEFAULT);
    print(TEST_MODE_A);
    print(TEST_MODE_B);
    print(TEST_MODE_MAX);
}

// ������
typedef struct _type
{
  	uint8_t head;
  	union{
      	uint8_t data1;
      	uint16_t data2;
      	uint32_t data3;
  	}data;
} type_t;

#if 0
int main()
{
//////////    test();
//////////    for(test_mode_t ix = 0; ix < TEST_MODE_MAX; ++ix){
//////////        print(ix);
//////////    }

//    test_mode = TEST_MODE_B;
//    printf("%d\r\n", (int)test_mode);
//
//    int8_t a = (int8_t)-11;
//    printf("%X", a);


    type_t type;
    type.data.data2 = 1;

    printf("%d - %d - %p\n", type.data.data1, sizeof(type.data), &type.data.data1);
    printf("%d - %d - %p\n", type.data.data2, sizeof(type.data), &type.data.data2);
    printf("%d - %d - %p\n", type.data.data3, sizeof(type.data), &type.data.data3);

    return 0;
}
#endif

#endif // DATA_STRUCTURE_RINGBUFFER


