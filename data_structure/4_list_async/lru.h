#ifndef LRU_H_INCLUDED
#define LRU_H_INCLUDED
#include "list.h"
#include "util.h"

//Least Recently Used


#define LRU_VALUE_TYPE      bonded_dev_t
#define LRU_CAPACITY        3
#define LRU_SAVE_FILE_PATH  "lru_save.bin"


typedef uint8_t bt_address[6];

typedef struct {
    bt_address btaddr;
    bt_address bleaddr;
} bonded_dev_t;

typedef struct {
    char key[16];
    LRU_VALUE_TYPE value;
} data_t;

typedef struct {
    struct list_node list; // linklist's head node
    int capacity; // linklist's maximum size, if add new when linklist is full, remove the old one
} lru_t;

typedef void (*item_removed_callback_t)(LRU_VALUE_TYPE *value);

void lru_add(lru_t *lru, const char *key, const LRU_VALUE_TYPE *value,
                bool force_update, item_removed_callback_t removed_cb);
LRU_VALUE_TYPE *lru_peek_latest(lru_t *lru);
void lru_dump(lru_t *lru, data_t **arr, int *arr_size);
lru_t *lru_restore(void);


void lru_test(void);


#endif // LRU_H_INCLUDED
