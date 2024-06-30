#ifndef __RING_BUFFER_H__
#define __RING_BUFFER_H__
#include <stdint.h>
#include <assert.h>
#include <stdio.h>

#if defined(DATA_STRUCTURE_RINGBUFFER) && (DATA_STRUCTURE_RINGBUFFER == 1)

/*
* @fun ö�����͵�ʹ��
*/
typedef enum{
    TEST_MODE_DEFAULT   = 0,
    TEST_MODE_A         = 0,
    TEST_MODE_B         = 1,
    TEST_MODE_MAX
} test_mode_t;


// declaration
test_mode_t test_mode;

/*
* @fun: Ƕ��ʽ�����о���ʹ��, �����жϽ������ݽ��л���, ��ʽ���������е����ݸ���
*       ������ݶ�ʧ
*       ��ʼ״̬ head = rear = 0
*       �������� head++
*       ȡ������ rear++
*/
#define RING_BUFFER_SIZE        128
typedef unsigned char u8;
#define RING_BUFFER_MASK        (RING_BUFFER_SIZE - 1)

//ring buffer ���ݽṹ
typedef struct{
    uint8_t buffer[RING_BUFFER_SIZE];
    uint8_t tail_index;
    uint8_t head_index;
}ring_buffer_t;

void ring_buffer_init(ring_buffer_t *buffer);
uint8_t ring_buffer_is_full(ring_buffer_t *buffer);
uint8_t ring_buffer_is_empty(ring_buffer_t *buffer);
u8 ring_buffer_num_items(ring_buffer_t *buffer);
void ring_buffer_queue(ring_buffer_t *buffer, u8 data);
void ring_buffer_queue_arr(ring_buffer_t *buffer, const char *data, u8 len);
u8 ring_buffer_deque(ring_buffer_t *buffer, char *data);
u8 ring_buffer_dequeue_arr(ring_buffer_t *buffer, u8 *data, u8 len);
u8 ring_buffer_peek(ring_buffer_t *buffer, char *data, u8 index);
void test();

#endif // DATA_STRUCTURE_RINGBUFFER

#endif // __RING_BUFFER_H__
