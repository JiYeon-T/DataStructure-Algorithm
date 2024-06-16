#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "ringbuffer.h"
#include <limits.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include  <stddef.h>

#include "kv.h"
#include "list.h"
#include "list_test.h"
#include "app_list.h"
#include "struct_test.h"
#include "state_machine_test.h"

#define XNAME(n)	x##n




#define P(A) printf("%s""what", #A)

typedef struct
{
    char c;
    int a;
    int b;
} A;

double average(int num, ...)
{
    va_list valist;
    double sum = 0.0;
    int i;
    int ix;
    printf("enter\n");
    va_start(valist, num); // va_start Ϊ num ��������ʼ�� va_list

    for(int ix = 0; ix < num; ++ix){
        sum += va_arg(valist, int); // va_arg ���� va_list
    }

    va_end(valist); // va_end ����Ϊ va_list ������ڴ�

    return sum / num;
}

typedef struct
{
    uint8_t a 		: 3;
    uint8_t b		: 1;
    uint8_t c 		: 2;
    uint8_t d		: 2;
} AT;

typedef struct {
    uint8_t item;
    uint8_t valid_flag;
    uint16_t save_index;
    uint16_t len;
} kv_head_t; // 5 bytes


int main(int argc, char *argv[])
{
//        A a;
//        a.a = 1;
//        memset(&a, 0, sizeof(A));
//        a.a = 2;
//        printf("%d %d", sizeof(a), sizeof(A));
    //    int a = 1, b = 2, c = 3;
    //    int XNAME(1);
    //    printf("aver = %f\n, a=%s\n", average(3, a, b, c), a);
//        P(a);
//        printf("hello"",world\n");
//
//        printf("x1 = %d\n", XNAME(1));

//        log_test();
//
//        AT at;
//        at
//        int8_t ch;
//        for(uint32_t ix = 0; ix < INT_MAX; ++ix){
//            if(ix % 30)
//                printf("%d ", ch++);
//            else
//                printf("%d \n", ch++);
//        }

        // struct intialization
//        typedef struct Student{
//                int ID;
//                char name[20];
//        } Student;
//
//        Student xiaoming = {1234, "xiaoming"};
//        printf("name:%s, ID:%d", xiaoming.name, xiaoming.ID);

//        printf("argc:%d\n", argc);
//        for(int ix = 0; ix < argc; ++ix) {
//                printf("%s\n", argv[ix]);
//        }

        // strtok() test
        // AT command parse
//        if(argc < 2) {
//                printf("error\r\n");
//                return 0;
//        }
//        const char delim[2] = "=";
//        char temp_para[3][128];
//        char *token;
//        uint8_t delimnum = 0;
//        char sourceStr[128] = "AT^BTRF=BNSG -m1 -b2 -c39 -l5 -t15 -p4";
//        char sourceStr[128]  = "AT^START";
//        char sourceStr[128]  = "AT^START=1";
//        char sourceStr[128]  = "AT^START=1 .2=2 .3 .3";

//        printf("sourceStr:%s\n", sourceStr);
//        memset(temp_para, 0, sizeof(temp_para));
//
//        token = strtok((char*)sourceStr, delim);
//
//        while(token != NULL && delimnum <=2) { //
//                snprintf((char*)temp_para[delimnum], 128, "%s", token);
//                printf("token:%s\n", token);
//                printf("delimnum:%d\ntemp_para[%d]:%s\n", delimnum, delimnum, temp_para[delimnum]);
//                delimnum++;
//                token = strtok(NULL, delim);
//        }
//        timer_t timerid;
//        printf("size:%d\n", sizeof(kv_head_t));
//        printf("Hello world\n");

        // pointer
//        uint8_t *a, *b;
//        uint8_t val;
//
//        a = &val;
//        b = &val;
//
//        if (a == b) {
//                printf("equal\n");
//        } else {
//                printf("not equal\n");
//        }

//    kv_test(argc, argv);

    // container_of_test();
    // offset_container_test();
    // list_test();
    // app_list_test1();
    // lru_test();
//    train_list_test();


    //var
    // var_array_test_struct1();
    // struct_test();
//    struct_test2();
//    macro_test1();
    // macro_test2();
//    var_num_arg_test1();
    // var_num_arg_test2();

//    async_size_test();

    // wchar_size_test();
    struct_pointer_member_test();
    //state_machine test
    // state_machine_test();

    return 0;
}

