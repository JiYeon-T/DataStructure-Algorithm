#include "app_list.h"
//#inlcude <stdint.h>
//#include <stdbool.h>

#if 0
// define
#define MUSIC_DATA_BLOCK_LEN        900
#define MUSIC_DATA_BLOCK_NUM        40

typedef struct
{
    bt_node_t block_node;
    uin32_t data_len;
    uint8_t data_buf[MUSIC_DATA_BLOCK_LEN];
} data_block_t; // 数据块

typedef struct
{
    bt_list_t data_list;
    bt_list_t free_list;
    int curr_fp;
    char file_name[50];
    data_block_t *curr_block;   // 动态分配内存
    uint32_t send_len;
    BT_MUSIC_STATE_E state;
} music_dev_t; // music device

// static variables
static music_dev_t _g_music_dev;
static bool _g_loop_mode = false;

// init
bool music_init()
{
    data_block_t *block = NULL;
    bt_node_t *node = NULL;

    bt_list_init(&music_dev.data_list);
    bt_list_init(&music_dev.free_list);

    // 申请音频缓冲区 free_list
    for(int ix = 0; ix < MUSIC_DATA_BLOCK_NUM; ++ix){
        block = (data_block_t*)malloc(sizeof(data_block_t));
        if(!block){ // 申请内存失败
            printf("malloc failed.\r\n");
            // 释放已经申请的内存
            node = bt_list_remove_first(&_g_music_dev.free_list);
            while(node != NULL){
                block = bt_list_container_of(node, data_block_t, block_node);
                // 解决宏问题的最好版办法就是把他们都写出来，拆开
                //#define bt_list_container_of(node, type, member) (type*)((uint32_t)node - (uint32_t)&((type*)0)->member)
                // (type*)((uint32_t)node - (uint32_t)&((type*)0)->member)
                // (data_block_t*)((uint32_t)(node) - (uint32_t)&((data_block_t*)0)->block_node)
                if(block != NULL){
                    free(block);
                }
                node = bt_list_remove_first(&_g_music_dev.free_list);
            }
            return false;
        }
        // 内存分配成功
        memset(block, 0, sizeof(block)); // sizeof(data_block_t) 可能不等于 sizeof(block)
        bt_list_add_last(&_g_music_dev.free_list, &block->block_node);
    }

}

#endif
