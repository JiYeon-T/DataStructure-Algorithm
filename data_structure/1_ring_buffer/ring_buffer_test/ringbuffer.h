#ifndef __RING_BUFFER_H__
#define __RING_BUFFER_H__
#include <stdint.h>
#include <assert.h>
#include <stdio.h>

/*
* @fun: 嵌入式开发中经常使用, 串口中断接收数据进行缓存, 方式处理过程中的数据覆盖
*       造成数据丢失
*       初始状态 head = rear = 0
*       插入数据 head++
*       取走数据 rear++
*/
#define RING_BUFFER_SIZE        128
typedef unsigned char u8;
#define RING_BUFFER_MASK        (RING_BUFFER_SIZE - 1)

//ring buffer 数据结构
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
#endif // __RING_BUFFER_H__
