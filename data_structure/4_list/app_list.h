#ifndef APP_LIST_H_INCLUDED
#define APP_LIST_H_INCLUDED

#include "service_bt_list.h"

typedef enum
{
    BT_MUSIC_STATE_STOP,    // play stop
    BT_MUSIC_STATE_START,   // 播放启动中, 没有收i都熬数据请求
    BT_MUSIC_STATE_RUN,     // 正在播放
} BT_MUSIC_STATE_E;

void music_init();

#endif // APP_LIST_H_INCLUDED
