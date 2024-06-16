

// 链表数据结构的测试 case
// 1.测试数据集
// 2.包含各种临界情况的测试用例

// TODO:具体该怎么实现, 还要想想
// 使用每一个链表实现都使用相同的接口(api),测试用例 函数指针
#if 0
typedef int ELemType;

typedef Status (*makenode_fun)(void **p, ELemType e);
typedef void (*freenode_fun)(void *p);


typedef struct _test_list {
    makenode_fun makenode;
    freenode_fun freenode;
    // 链表其他操作的接口
} list_t;


list_t link_list[] = {
    linklist1,
    linklist2,
    circle_list1,
    circle_list2,
    double_circle_list1,
    double_cricle_list2,
}

void auto_test(void)
{
    for (int i = 0; i < ARRAY_SIZE(link_list); ++i) {
        list_t list = link_list[i];
        do_test(list);
    }
}

void do_test(list_t)
{
    //init 
    //make node
    //....
    // 等等其他测试
}
#endif

// 代码功能测试:
// 1. 一般功能可以正常处理;
// 2. 所有的临界值都可以正常处理;
// 3. 任意输入都可以正常输入;




// TODO:
// 使用链表对数据进行管理测试
// typedef struct _node {
//     Node node;
//     int len;
//     int *p_data;
// } node_t;


//TODO: 2
// 翻转链表;