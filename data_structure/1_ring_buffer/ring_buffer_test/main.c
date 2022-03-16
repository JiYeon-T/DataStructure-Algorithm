#include <stdio.h>
#include <stdlib.h>
#include "ringbuffer.h"

/*
* @fun 枚举类型的使用
*/
typedef enum{
    TEST_MODE_DEFAULT   = 0,
    TEST_MODE_A         = 0,
    TEST_MODE_B         = 1,
    TEST_MODE_MAX
} test_mode_t;
void print(test_mode_t args)
{
    printf("%d\r\n", args);
    return;
}

void enum_type_test()
{
    print(TEST_MODE_DEFAULT);
    print(TEST_MODE_A);
    print(TEST_MODE_B);
    print(TEST_MODE_MAX);
}
int main()
{
//    test();
//    for(test_mode_t ix = 0; ix < TEST_MODE_MAX; ++ix){
//        print(ix);
//    }


    return 0;
}
