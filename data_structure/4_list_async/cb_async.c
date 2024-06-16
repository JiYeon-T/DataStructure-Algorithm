#include "cb_async.h"
#include "list.h"

#include <pthread.h>
//#include "uv.h"

/*
原理:
handler_list 链表, 链表的数据域部分保存指针;
通过 uv_async_t 将来自协议栈的所有事件 async 到 bt_loop 中执行:
cb_async.c
gap.c, hid.c, hfp.c, rfcomm.c, pan.c......
作用:没有线程同步问题;
应用场景:
1.需要配合 libuv 使用;
*/

struct async_event {
    int profile_id;
    uint8_t data[]; // 还不能用指针代替, 指针会占用空间, 但是这个柔性数组默认不占用空间;
};

//test
struct async_event2 {
    int profile_id;
    uint8_t *data;
};

// async_event 通过链表管理, 每个节点的数据域大小是一个指针,固定的, 但是指向的内容大小是动态的():
struct evt_node {
    struct list_node node;
    struct async_event *evt; //数据域大小是动态的
};

// event_handler 链表, 不同的 event 的处理也是通过链表管理
struct profile_handler {
    struct list_node node;
    int profile_id;
    async_handler handler; // pointer
};

//TODO:
static struct list_node async_evt_list = LIST_INITIAL_VALUE(async_evt_list);
// static pthread_mutext_t

void async_size_test(void)
{
    LOG_D("async_event size:%d", sizeof(struct async_event)); //4
    LOG_D("async_event2 size:%d", sizeof(struct async_event2)); //16
}





