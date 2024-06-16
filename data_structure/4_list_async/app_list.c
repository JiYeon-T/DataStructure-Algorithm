#include "list.h"
#include "app_list.h"

// linklist application

// linklist usage:
// 1. list node as save value's member, e.g. lru.c, conn_dev_list;
// 2. save value save as list node's member;

typedef uint8_t bt_address_t[6];

typedef struct {
    struct list_node node;
    bt_address_t addr; // 链表数据域:是一个固定大小的数据
} conndev_t;


static struct list_node ble_conndev_list = LIST_INITIAL_VALUE(ble_conndev_list); // linklist head node



static bool same_addr(bt_address_t a, bt_address_t b)
{
    return (memcmp(a, b, sizeof(bt_address_t)) == 0 ? true : false);
}

static void traverse_list(struct list_node *list)
{
    struct list_node *node = list;
    size_t cnt = 0;
    conndev_t *dev_tmp;

//    list_for_every(list, node) {
//        dev_tmp = (conndev_t*)node;
//        printf("[%d]:%02X:%02X:%02X:%02X:%02X:%02X\n", cnt, dev_tmp->addr[0], dev_tmp->addr[1],
//                dev_tmp->addr[2], dev_tmp->addr[3], dev_tmp->addr[4], dev_tmp->addr[5]);
//        ++cnt;
//    }

    // compile error??????????????????????????????????????
    LOG_D("list address:%#X", list);
    list_for_every_entry(list, dev_tmp, conndev_t, node)
    {
        LOG_D("[%d] address:%#X val:%02X:%02X:%02X:%02X:%02X:%02X\n", cnt, dev_tmp,
                dev_tmp->addr[0], dev_tmp->addr[1], dev_tmp->addr[2],
                dev_tmp->addr[3], dev_tmp->addr[4], dev_tmp->addr[5]);
        ++cnt;
    }
    LOG_D("\n\n");
}

static bool conn_dev_find(struct list_node *list, bt_address_t addr)
{
    conndev_t *dev_tmp;
    struct list_node *node;
    struct list_node *tmp;

    LOG_D("list address:%#X", list);
    list_for_every_safe(list, node, tmp) {
        LOG_D("node addr:%#X tmp:%#X", node, tmp);
        dev_tmp = (conndev_t*)node;
        if (same_addr(dev_tmp->addr, addr))
            return true;
    }

    // list_for_every_entry_safe()

    return false;
}

static bool conn_dev_add(struct list_node *list, bt_address_t addr)
{
    if (conn_dev_find(list, addr)) {
        printf("address:%2X:%2X:%2X:%2X:%2X:%2X already exist, ignore\n",
                addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
        return false;
    }

    conndev_t *dev = malloc(sizeof(conndev_t));
    if (!dev)
        return false;
    memcpy(dev->addr, addr, sizeof(bt_address_t));
    LOG_D("add a new node address:%#X val:%02X%02X%02X%02X%02X%02X", &dev->node,
        addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
    list_add_tail(list, &dev->node);
    LOG_D("\n");

    return true;
}

static void conn_dev_remove(struct list_node *list, bt_address_t addr)
{
    conndev_t *dev;
    struct list_node *node;
    struct list_node *tmp;

    list_for_every_safe(list, node, tmp) {
        LOG_D("node:%#X tmp:%#X", node, tmp);
        dev = (conndev_t*)node;
        if (same_addr(dev->addr, addr)) {
            LOG_D("delete a node:%#X val:%X%X%X%X%X%X", &dev->node,
                addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
            list_delete(&dev->node);
            free(dev);
            break;
        }
    }
    LOG_D("\n");
}


void app_list_test1(void)
{
    LOG_D("%s:", __func__);
    bt_address_t dev_a = {1, 1, 1, 1, 1, 1};
    LOG_D("list address:%#X", &ble_conndev_list);
    conn_dev_add(&ble_conndev_list, dev_a);
    traverse_list(&ble_conndev_list);

    bt_address_t dev_b = {2, 2, 2, 2, 2, 2};
    conn_dev_add(&ble_conndev_list, dev_b);
    traverse_list(&ble_conndev_list);

    bt_address_t dev_c = {3, 3, 3, 3, 3, 3};
    conn_dev_add(&ble_conndev_list, dev_c);
    traverse_list(&ble_conndev_list);

    conn_dev_add(&ble_conndev_list, dev_c);
    traverse_list(&ble_conndev_list);

    conn_dev_remove(&ble_conndev_list, dev_c);
    traverse_list(&ble_conndev_list);
}

/****************************************************************************
 * app_list_test2
 ****************************************************************************/
typedef struct {
    struct list_node node;
    char *name;
    long long id;
    int weight;
    int size;
    int color;
    //NOTE:
    // 柔性数组, 不占用结构体大小, 但是可以给他动态分配内存
    uint8_t material[]; //拉的货
} train_node_t; // 火车车厢

static struct list_node train_head = LIST_INITIAL_VALUE(train_head); // 火车头

static bool same_id(long long id1, long long id2)
{
    return (id1 == id2);
}

static train_node_t *train_find_node(long long id)
{
    train_node_t *entry;
    train_node_t *result = NULL;

    list_for_every_entry(&train_head, entry, train_node_t, node)
    {
        if (same_id(entry->id, id)) {
            result = entry;
            break;
        }
    }

    if (!result)
        LOG_E("can't find node:%ld", id);

    return result;
}

/**
 * @brief
 *
 * @param[in] name
 * @param[in] id
 * @param[in] material 这里 material 传入带有 '\0' 的字符串, 方便打印
 * @param[in] material_size 包含 '\0'
 * @ret
*/
static void train_add_node(char *name, long long id, uint8_t *material, uint16_t material_size)
{
    //NOTE:
    // 分配内存的时候就为 material 分配好内存:
    train_node_t *node = (train_node_t*)malloc(sizeof(train_node_t) + material_size);
    if (!node)
        return;
    node->name = name;
    node->id = id;
    /** node->material 就是数组地址 **/
    memcpy(node->material, material, material_size);
    LOG_D("add node name:%s id:%ld len:%d material:%s", name, id, material_size, material);
    list_add_tail(&train_head, node);
}

static void train_delte_node(long long id)
{
    train_node_t *node = train_find_node(id);
    if (!node)
        return;
    LOG_D("del node name:%s id:%ld material:%s", node->name, node->id, node->material);
    list_delete(node);
    free(node);
}

static void train_traverse(void)
{
    train_node_t *entry;
    int i = 0;
    LOG_D("\ntraverse:");
    list_for_every_entry(&train_head, entry, train_node_t, node)
    {
        LOG_D("node[%d] name:%s id:%d material:%s", i++, entry->name, entry->id, (char*)entry->material);
    }
    LOG_D("");

    return;
}



void train_list_test(void)
{
    static int id = 1;
    train_traverse();
    //仅用于测试, material 中也保存名字
    char *name1 = "train1";
    char *material1 = "orange";
    train_add_node(name1, id++, material1, strlen(material1) + 1);
    char *name2 = "train2";
    char *material2 = "watermalenon";
    train_add_node(name2, id++, material2, strlen(material2) + 1);
    char *name3 = "train3";
    char *material3 = "Apple";
    train_add_node(name3, id++, material3, strlen(material3) + 1);
    char *name4 = "train4";
    char *material4 = "Cucumber";
    train_add_node(name4, id++, material4, strlen(material4) + 1);
    char *name5 = "train5";
    char *material5 = "Ice cream";
    train_add_node(name5, id++, material5, strlen(material5) + 1);
    train_traverse();

    train_delte_node(3);
    train_traverse();

    train_delte_node(9);
    train_traverse();
}
