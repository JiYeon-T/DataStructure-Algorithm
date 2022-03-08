#include "ringbuffer.h"

/*
* @fun: ring buffer 初始化
*/
void ring_buffer_init(ring_buffer_t *buffer)
{
    buffer->tail_index = 0;
    buffer->head_index = 0;

    return;
}

/*
* @fun: 判断 ring buffer 是否满, 三个频繁调用的函数, 做成内联函数
*/
uint8_t ring_buffer_is_full(ring_buffer_t *buffer)
{
    return ((buffer->head_index - buffer->tail_index) & RING_BUFFER_MASK) \
            == RING_BUFFER_MASK;
}

/*
* @fun:判断ringbuffer 是否为空
*/
uint8_t ring_buffer_is_empty(ring_buffer_t *buffer)
{
    return (buffer->head_index == buffer->tail_index);
}

/*
* @fun: 获取元素个数
*/
u8 ring_buffer_num_items(ring_buffer_t *buffer)
{
    return ((buffer->head_index - buffer->tail_index) & RING_BUFFER_MASK);
}

/*
* @fun: 存储:保存头指针的指向的位置, head++
*       如果满了, 尾指针后移动一个位置
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
* @fun: 批量存储数据
*/
void ring_buffer_queue_arr(ring_buffer_t *buffer, const char *data, u8 len)
{
    for(u8 ix = 0; ix < len; ++ix){
        ring_buffer_queue(buffer, data[ix]);
    }
    return;
}

/*
* @fun:取出数据
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
* @fun: 批量读出元素
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
* @fun:查看 ring_buffer 中的元素, 不进行指针偏移
* @param[in]  buffer
* @param[out] data
* @param[in]  index 要查看的元素的偏移量(第几个元素)
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
* @fun: 模块测试函数
*       黑盒测试, 白盒测试, 沙箱测试都是什么东西
*/
void test()
{
    int i, cnt;
    char buf;
    char buf_arr[50];

    ring_buffer_t ring_buffer;
    ring_buffer_init(&ring_buffer);

    //插入元素
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
    //插入元素
    ring_buffer_queue_arr(&ring_buffer, "hello, world", 13);
    assert(!ring_buffer_is_empty(&ring_buffer)); // assert

    printf("\n==============================\n");
    //取出元素
    cnt = ring_buffer_dequeue_arr(&ring_buffer, buf_arr, 13);
    printf("cnt = %d\n", cnt);
    assert(cnt == 13);
    buf_arr[13] = '\0';
    printf("data:%s\n", buf_arr);
}



















