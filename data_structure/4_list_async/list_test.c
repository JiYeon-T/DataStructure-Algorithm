#include "list_test.h"
#include "list.h"
#include "util.h"
/*************************************************************************************
 * offsetof & container_of
 *************************************************************************************/
typedef struct _test_a {
    char a;
    short b;
    int c;
    long long d;
    /* data */
} test_a;

/**
 * @brief container_of 通过结构体成员可以获取到包含该成员的结构体的地址
 * 
 * @note 广泛用于链表操作中
 * TODO: 其他数据结构中是不是也是广泛使用????????????????????
*/
void offset_container_test(void)
{
    printf("offset a:%d b:%d c:%d d:%d\n", offsetof(test_a, a), offsetof(test_a, b), offsetof(test_a, c), offsetof(test_a, d));
    test_a test = {1, 2, 3, 4};
    printf("address test:%#08X\n", &test);
    printf("address a:%#08X\n", &test.a);
    printf("address b:%#08X\n", &test.b);
    printf("address c:%#08X\n", &test.c);
    printf("address d:%#08X\n", &test.d);

    //container_of, 通过结构体成员 d 的地址获取结构体 test 的地址
    test_a *ptr = (test_a*)container_of(&test.d, test_a, d);
    printf("\n\naddress ptr:%#08X\n", ptr);
    // 然后通过指针可以获取到结构体成员的值
    printf("value a:%d\n", ptr->a);
    printf("value b:%d\n", ptr->b);
    printf("value c:%d\n", ptr->c);
    printf("value d:%d\n", ptr->d);
}


typedef int test_node_t;

typedef struct {
    test_node_t node;
    char *name;
    char a;
    int b;
    int c;
} test_t;

/**
 * @brief container_of macro test
 * 
*/
void container_of_test(void)
{
    // byte alliance
    LOG_D("offset node:%d name:%d a:%d b:%d c:%d\n", offsetof(test_t, node),
                offsetof(test_t, name),
                offsetof(test_t, a), offsetof(test_t, b), offsetof(test_t, c));

    test_t temp = {1, NULL, 2, 3, 4};
    char *pStr = (char*)malloc(100);

    strcpy(pStr, "hello");
    temp.name = pStr;
    LOG_D("temp.name address:%#X", &temp.name);
    // get containing structure's address according to the struct member address
    /** 通过已知的结构体成员的地址, 获得包含该成员得结构体得地址**/
    // container_of 已经进行了强制类型转换
    test_t *p = container_of(&temp.name, test_t, name);
    LOG_D("p address:%#X", p);

    LOG_D("name:%s\n", p->name);
}

/*************************************************************************************
 * list api test1
 *************************************************************************************/
typedef int data_type_t;

//TOOD:
// 进阶, 指针
// typedef int* data_type_t;

typedef struct _app_list_node {
    struct list_node node;
    //TODO:
    //1.进阶 void * 类型参数, 通过宏传递可变参数过来
    //2.hid_cb_list
    // 链表数据域:是一个固定大小的数据
    
    //TODO:
    // char a;
    // short b;
    // int c;
    // long long d;

    // 测试:数据域部分仅仅保存一个整数
    //TODO: 进阶为指针
    data_type_t data;
} app_list_node_t;

// static list_test_t test_list;
static struct list_node app_list = LIST_INITIAL_VALUE(app_list);

//双向链表插入 O(1)
static void app_list_add(data_type_t data)
{
    app_list_node_t *node = (app_list_node_t*)malloc(sizeof(app_list_node_t));
    
    LOG_D("add node address:%p val:%d\n", &node->node, data);
    node->data = data;
    list_add_tail(&app_list, &node->node);
}

//双向链表遍历查找, 然后删除 O(1)
static void app_list_del(data_type_t data)
{
    app_list_node_t *entry;

    list_for_every_entry(&app_list, entry, app_list_node_t, node) {
        if (entry->data == data) {
            LOG_D("del node address:%p val:%d\n", &entry->node, data);
            list_delete(&entry->node);
            free(entry);
            return;
        }
    }
}

static void app_list_traverse(void)
{
    app_list_node_t *entry;
    uint8_t idx = 0;
    LOG_D("traverse:\n");
    list_for_every_entry(&app_list, entry, app_list_node_t, node) {
        LOG_D("node[%d]=%d node address:%p\n", idx++, entry->data, &entry->node);
    }

    LOG_D("\n\n");
}

static void app_list_clear(void)
{
    app_list_node_t *entry, *tmp;

    printf("clear\n");
    list_for_every_entry_safe(&app_list, entry, tmp, app_list_node_t, node) {
        list_delete(&entry->node);
        free(entry);
    }
}

void list_test(void)
{
    app_list_traverse();
    app_list_add(1);
    app_list_traverse();
    app_list_add(2);
    app_list_traverse();
    app_list_add(3);
    app_list_traverse();
    app_list_del(2);
    app_list_traverse();
    app_list_clear();
    app_list_traverse();

    // for (int i = 0; i < 10; i++) {
    //     app_list_add(100 + i);
    // }
    // app_list_traverse();
    // app_list_del(105);
    // app_list_traverse();

}