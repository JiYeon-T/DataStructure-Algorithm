#include "app_list.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "list.h"



// define
#define MUSIC_DATA_BLOCK_LEN        900
#define MUSIC_DATA_BLOCK_NUM        40

typedef struct
{
    node_t block_node;
    uint32_t data_len;
    uint8_t data_buf[MUSIC_DATA_BLOCK_LEN];
} data_block_t; // 数据块

typedef struct
{
    list_t data_list;
    list_t free_list;
    int curr_fp;
    char file_name[50];
    data_block_t *curr_block;   // 动态分配内存
    uint32_t send_len;
    BT_MUSIC_STATE_E state;
} music_dev_t; // music device

// static variables
static music_dev_t _g_music_dev;
static bool _g_loop_mode = false;

/**
 *@fun:
 *@desc:
 */
bool music_cache_init()
{
    data_block_t *block = NULL;
    node_t *node = NULL;

    list_init(&_g_music_dev.data_list);
    list_init(&_g_music_dev.free_list);

    // 申请音频缓冲区 free_list
    for(int ix = 0; ix < MUSIC_DATA_BLOCK_NUM; ++ix){
        block = (data_block_t*)malloc(sizeof(data_block_t));
        if(!block){ // 申请内存失败
            printf("malloc failed.\r\n");
            // 释放已经申请的内存
            node = list_remove_first(&_g_music_dev.free_list);
            while(node != NULL){
                block = bt_list_container_of(node, data_block_t, block_node);
                // 解决宏问题的最好版办法就是把他们都写出来，拆开
                //#define bt_list_container_of(node, type, member) (type*)((uint32_t)node - (uint32_t)&((type*)0)->member)
                // (type*)((uint32_t)node - (uint32_t)&((type*)0)->member)
                // (data_block_t*)((uint32_t)(node) - (uint32_t)&((data_block_t*)0)->block_node)
                if(block != NULL){
                    free(block);
                }
                node = list_remove_first(&_g_music_dev.free_list);
            }
            return false;
        }
        // 内存分配成功
        memset(block, 0, sizeof(block)); // sizeof(data_block_t) 可能不等于 sizeof(block)
        list_add_last(&_g_music_dev.free_list, &block->block_node);
    }

}

/**
 * @fun:
 * @desc:
*/
bool music_cache_deinit()
{

}

/**
 * @fun:
 * @desc:
*/
bool music_play()
{

}

bool music_stop()
{


}


void list_test()
{
    printf("%s\r\n", __func__);
    list_test_raw();
}
