#include "service_bt_music.h"
#include "list.h"

#if defined(DATA_STRUCTURE_STREAM_CACHE) && (DATA_STRUCTURE_STREAM_CACHE == 1)

// cache queue node
typedef struct
{
        bt_node_t block_node;
        uint32_t data_len;
        uint8_t data_buff[900]; // pointer/array
} data_block_t;


bool service_bt_music_load_data();

#endif // DATA_STRUCTURE_STREAM_CACHE
