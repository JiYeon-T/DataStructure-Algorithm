#include "ring_buffer2.h"


#if defined(DATA_STRUCTURE_RINGBUFFER) && (DATA_STRUCTURE_RINGBUFFER == 1)

unsigned int RingBufferPut(RingBuffer_t *ring_buff_p, void *buffer, uint32_t size)
{
    unsigned int len = 0;
    if(ring_buff_p == NULL || buffer == NULL){
        return -1;
    }

    //get actual write size
    size = MIN(size, ring_buff_p->size - (ring_buff_p->in - ring_buff_p->out) );

    //min, free space
    //first put the data starting from fifo->in to buffer end
    len = MIN(size, ring_buff_p->in & (ring_buff_p->size - 1));
    memcpy(ring_buff_p->buffer + (ring_buff_p->in & (ring_buff_p->size - 1)), buffer, size);

    if(size > len){
        memcpy(ring_buff_p->buffer, (char*)buffer + len, size - len);
    }

    return size;
}

unsigned int RingBufferGet(RingBuffer_t *ring_buffer_p, void *buffer, uint32_t size)
{
    unsigned int len = 0;
    if(ring_buffer_p == NULL || buffer == NULL){
        return -1;
    }

    size = MIN(size, (ring_buffer_p->in - ring_buffer_p->out));

    len = MIN(size, ring_buffer_p->size - (ring_buffer_p->out & (ring_buffer_p->size - 1)));
    memcpy(buffer, ring_buffer_p->buffer + (ring_buffer_p->out & (ring_buffer_p->size - 1)), len);

    if(size > len){
        memcpy((char*)buffer + len, ring_buffer_p->buffer, size - len);
    }

    return size;
}

unsigned int RingBufferLen(const RingBuffer_t *ring_buffer_p)
{
    return (ring_buffer_p->in - ring_buffer_p->out);
}

void RingBufferClear(RingBuffer_t *ring_buffer_p)
{
    ring_buffer_p->in = 0;
    ring_buffer_p->out = 0;
}

void print_ring_buffer()
{
    printf("This is a ring buffer;\n");
}

#endif // DATA_STRUCTURE_RINGBUFFER
