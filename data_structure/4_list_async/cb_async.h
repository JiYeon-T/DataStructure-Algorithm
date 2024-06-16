#ifndef __CB_ASYNC_H__
#define __CB_ASYNC_H__

#include "util.h"

enum {
    PROFILE_GAP,
    PROFILE_GATT,
    PROFILE_RFCOMM,
    PROFILE_HFP,
    PROFILE_HID,
    PROFILE_A2DP,
    PROFILE_PAN,
    PROFILE_HFP_AG,
};


typedef void (*async_handler)(void *data);

void *async_init(int profile_id, int data_size);
void async_size_test(void);

// void *

#endif

