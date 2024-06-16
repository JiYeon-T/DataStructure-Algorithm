#ifndef __RING_BUFFER_H__
#define __RING_BUFFER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define RING_BUFFER_SIZE            4092

typedef struct
{
    char buffer[RING_BUFFER_SIZE];
    unsigned int size;
    unsigned int in;
    unsigned int out;
} RingBuffer_t;

unsigned int RingBufferPut(RingBuffer_t *ring_buff_p, void *buffer, uint32_t size);
unsigned int RingBufferGet(RingBuffer_t *ring_buffer_p, void *buffer, uint32_t size);
unsigned int RingBufferLen(const RingBuffer_t *ring_buffer_p);
void RingBufferClear(RingBuffer_t *ring_buffer_p);
void print_ring_buffer();

#endif // __RING_BUFFER_H__
