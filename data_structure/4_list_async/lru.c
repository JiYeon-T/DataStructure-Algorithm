#include "lru.h"#ifndef LRU_VALUE_TYPE#define LRU_VALUE_TYPE int#endif // LRU_VALUE_TYPE#ifndef LRU_CAPACITY#define LRU_CAPACIRY    3#endif // LRU_CAPACITY#ifndef LRU_SAVE_FILE_PATH#define LRU_SAVE_FILE_PATH "lru/lru_save.bin"#endif // LRU_SAVE_FILE_PATHtypedef struct {    struct list_node node;    data_t data;} item_t;/** * @fun create lru * * @param[in] capacity lru's maximum size * @ret */static lru_t* lru_create(int capacity){    lru_t *lru = malloc(sizeof(lru_t));    if (!lru)        return NULL;    list_initialize(&lru->list);    lru->capacity = capacity;    return lru;}static void lru_save(lru_t *lru){    FILE *fd = fopen(LRU_SAVE_FILE_PATH, "wb");    if (!fd)        return;    item_t *entry;    list_for_every_entry(&lru->list, entry, item_t, node) {        fwrite(&entry->data, sizeof(data_t), 1, fd);    }    fclose(fd);}/** * @fun find a lru item by key */static struct list_node *lru_find(lru_t *lru, const char *key){    if (!lru || !key)        return;    item_t *entry;    list_for_every_entry(&lru->list, entry, item_t, node) {        if (strcmp(entry->data.key, key) == 0) {            return &entry->node;        }    }    return NULL;}/** * @fun add lru item to the list tail(newest item) * * @param[in] lru * @param[in] key * @param[in] value * @param[in] force_update * @param[in] removed_cb * @ret */void lru_add(lru_t *lru, const char *key, const LRU_VALUE_TYPE *value,                bool force_update, item_removed_callback_t removed_cb){    if (!lru || !key || !value)        return;    item_t *item_node;    struct list_node *node;    if ((node = lru_find(lru, key))) {        // force update node's value        if (force_update) {            item_node = list_entry(node, item_t, node);            memcpy(&item_node->data.value, value, sizeof(LRU_VALUE_TYPE));        }        // update to latest(set node as list tail)        if (node != list_peek_tail(&lru->list)) {            list_delete(node);            list_add_tail(&lru->list, node);            lru_save(lru);        }        // else {} // node is tail node, only update item's value        return;    }    item_node = calloc(1, sizeof(item_t)); // allocate memory    if (!item_node)        return;    strncpy(item_node->data.key, key, sizeof(item_node->data.key) - 1);    memcpy(&item_node->data.value, value, sizeof(LRU_VALUE_TYPE));    list_add_tail(&lru->list, &item_node->node);    // remove oldest node(list head) when list is full    if (list_length(&lru->list) > lru->capacity) {        node = list_remove_head(&lru->list);        item_node = list_entry(node, item_t, node);        if (removed_cb) {            removed_cb(&item_node->data.value);        }        free(item_node); // free node memory    }    lru_save(lru);}/** * @fun peek latest item(list tail) */LRU_VALUE_TYPE *lru_peek_latest(lru_t *lru){    if (!lru || list_length(&lru->list) == 0)        return NULL;    struct list_node *node;    item_t *item;    node = list_peek_tail(&lru->list);    item = list_entry(node, item_t, node);    return &item->data.value;}/** * @fun dump lru list data * * @param[in] lru * @param[out] arr output array * @param[out] arr_size output array size * @ret */void lru_dump(lru_t *lru, data_t **arr, int *arr_size){    if (!lru || !arr || !arr_size || list_length(&lru->list) == 0) {        if (arr) {            *arr = NULL;        }        if (arr_size) {            *arr_size = 0;        }        return;    }    *arr_size = list_length(&lru->list);    *arr = (data_t*)malloc(sizeof(data_t) * (*arr_size));    if (!(*arr)) {        *arr_size = 0;        return;    }    int i = 0;    item_t *entry;    list_for_every_entry(&lru->list, entry, item_t, node) {        memcpy(&(*arr)[i], &entry->data, sizeof(data_t));        ++i;    }}/** * @fun lru list restore, usually called when power up */lru_t *lru_restore(void){    lru_t *lru = NULL;    FILE *fd = NULL;    lru = lru_create(LRU_CAPACITY);    if (!lru) {        printf("lru create failed\n");        goto exit;    }    fd = fopen(LRU_SAVE_FILE_PATH, "rb");    if (!fd) {        printf("lru file open failed\n");        goto exit;    }    int n;    data_t data;    while ((n = fread(&data, sizeof(data_t), 1, fd)) == 1) {        item_t *item_node = calloc(1, sizeof(item_t));        if (!item_node) {            goto exit;        }        memcpy(&item_node->data, &data, sizeof(data_t));        list_add_tail(&lru->list, &item_node->node);    }exit:    if (fd) {        fclose(fd);    }    return lru;}