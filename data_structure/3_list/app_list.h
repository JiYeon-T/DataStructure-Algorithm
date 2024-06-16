#ifndef APP_LIST_H_INCLUDED
#define APP_LIST_H_INCLUDED

#include "list.h"


// 链表的使用:
// 法1. 将成员放到 ElemType 中;
// 法2. 链表的 node 作为结构体成员, #include <nuttx/list.h>

// 在音频数据，mic 数据，铃声数据缓冲等场景作为缓冲队列使用

typedef enum
{
    BT_MUSIC_STATE_STOP,    // play stop
    BT_MUSIC_STATE_START,   // 播放启动中, 没有收i都熬数据请求
    BT_MUSIC_STATE_RUN,     // 正在播放
} BT_MUSIC_STATE_E;

void music_init();

void list_test();

#endif // APP_LIST_H_INCLUDED
