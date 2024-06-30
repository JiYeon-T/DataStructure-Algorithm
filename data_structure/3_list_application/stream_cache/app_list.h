#ifndef APP_LIST_H_INCLUDED
#define APP_LIST_H_INCLUDED

#include "list.h"


// 链表的使用:

#if defined(DATA_STRUCTURE_STREAM_CACHE) && (DATA_STRUCTURE_STREAM_CACHE == 1)

// 在音频数据，mic 数据，铃声数据缓冲等场景作为缓冲队列使用

typedef enum
{
    BT_MUSIC_STATE_STOP,    // play stop
    BT_MUSIC_STATE_START,   // 播放启动中, 没有收i都熬数据请求
    BT_MUSIC_STATE_RUN,     // 正在播放
} BT_MUSIC_STATE_E;

void music_init();

void list_test();
#endif //DATA_STRUCTURE_STREAM_CACHE

#endif // APP_LIST_H_INCLUDED
