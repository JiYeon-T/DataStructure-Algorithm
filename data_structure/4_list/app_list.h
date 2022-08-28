#ifndef APP_LIST_H_INCLUDED
#define APP_LIST_H_INCLUDED

#include "service_bt_list.h"

typedef enum
{
    BT_MUSIC_STATE_STOP,    // play stop
    BT_MUSIC_STATE_START,   // ����������, û����i������������
    BT_MUSIC_STATE_RUN,     // ���ڲ���
} BT_MUSIC_STATE_E;

void music_init();

#endif // APP_LIST_H_INCLUDED
