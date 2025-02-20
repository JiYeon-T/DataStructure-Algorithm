/**
 * @file app_stack.c
 * @author your name (you@domain.com)
 * @brief 栈的使用
 * @version 0.1
 * @date 2022-11-15
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "app_stack.h"
#include "stack_v1.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include "maze_test.h"


/**
 * @brief 打印函数
 *
 * @param param
 */
static void print_int_elem(void *param)
{
    printf("    %d\r\n", *(ElemType*)(param));
}

static void print_char_elem(void *param)
{
    printf("    %c\r\n", *(char*)(param));

}

static void print_char_elem_without_spacec(void *param)
{
    printf("%c", *(char*)(param));

}

// 1:进制转换
/**
 * @brief 讲一个十进制数转换成任意进制
 *
 * @param num
 * @param scale 进制
 * @return int
 */
void conversion(int num, int scale)
{
    Stack s;
    InitStack(&s);
    ElemType data;

    SetPrintFormat(print_int_elem);

    printf("push:\r\n");
    while(num){
        data = num % scale;
        print_int_elem(&data);
        Push(&s, &data);
        num = num / scale;
    }

    printf("pop:\r\n");
    // char arr[10];
    // ix = 0;
    while(!EmptyStack(&s)){
        Pop(&s, &data);

        // itoa(data, &arr[ix++]);
        print_int_elem(&data);
    }

    // snprintf()
    // return "027";
    return;
}


// 2. 括号匹配:
// 算法:传入字符和栈顶字符比较:匹配出栈; 不匹配:入栈
/**
 * @brief 判断两个字符是否匹配
 *        (), [], {}, 都是匹配的
 *
 * @param ch1 栈顶元素
 * @param ch2 判断是否入栈的元素
 * @return true/false
 */
bool bracketMatch(char stackTopElem, char ch)
{
    bool ret = false;

    switch(stackTopElem){
        case '(':
            ret = ch == ')';
            break;
        case '[':
            ret = ch == ']';
            break;
        case '{':
            ret = ch == '}';
            break;
        default: // ret = false;
            break;
    }

    return ret;
}

/**
 * @brief 判断字符是否是括号
 *
 * @param ch
 * @return true/false
 */
static bool isBracket(char ch)
{
    char *str = "([{)]}";
    size_t ix = 0;

    while(str[ix] != '\0'){
        if(ch == str[ix])
            return true;
        ++ix;
    }

    return false;
}

static void bracketMatchTest(char *str1)
{
    size_t ix = 0;
    Status ret;
    Stack s;

    InitStack(&s);
    SetPrintFormat(print_char_elem);

    while(str1[ix] != '\0'){
        // if(GetTop(&s, &data) != OK) // 空; 直接入栈
        //     Push(&s, &str1[ix]);
        // 跳过除括号外的其他所有字符
        if(isBracket(str1[ix])){
            ElemType data;
            ret = GetTop(&s, &data);
            // 空栈
            if(ret != OK){
                Push(&s, &str1[ix]);
            }
            else{
                // 栈顶元素和当前元素比较
                if(bracketMatch(data, str1[ix])){
                    Pop(&s, &data);
                }
                else{
                    Push(&s, &str1[ix]);
                }
            }
        }
        ++ix;
    }

    StackTraverse(&s);

    if(EmptyStack(&s)){
        printf("str:%s match!\r\n\r\n", str1);
    }
    else{
        printf("str:%s does not match!\r\n\r\n", str1);
    }

    return;
}

void bracketMatchPressureTest()
{
    char *str1 = "abcdef[]dddfdfad[[[[[";
    char *str2 = "[[[]]][]{}()";
    char *str3 = "{[()]}";

    bracketMatchTest(str1);
    bracketMatchTest(str2);
    bracketMatchTest(str3);
}

// 3. 行编辑程序
// 使用用户输入缓冲区,纠错功能
// 1. 用户输入 #, 删除前一个元素
// 2. 用户输入 @, 删除整行
void shell_test()
{
    Stack s;
    char ch;
    ElemType tempData;

    InitStack(&s);
    SetPrintFormat(print_char_elem_without_spacec);
    // InverseTraverseStack(&s);

    while((ch = getchar()) != 'Q'){
        switch(ch){
            // 退格符
            case '#':
                Pop(&s, &tempData);
                break;
            // 删除整行
            case '@':
                ClearStack(&s);
                break;
            // 回车换行打印并另起一行
            case '\r':
            case '\n':
                InverseTraverseStack(&s);
                ClearStack(&s);
                break;
            default:
                Push(&s, (ElemType*)&ch);
                break;
        }
        // InverseTraverseStack(&s);
    }

    // 需要重新写一个 Traverse, 否则打印顺序和输入顺序是相反的
    InverseTraverseStack(&s);

    return;
}

// TODO:
// 4. 迷宫求解:深度优先算法以及广度优先算法


//5 . 计算器, 带有权重(运算优先级)的计算
// 表达式求值、
// 从左向右计算, 先乘除后加减;
// 先括号内, 后括号外
typedef enum{
    ADD = 0,
    SUBTRACT,
    MUL,
    DIV,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    JING, // #
    OPTR_NUM // 操作符个数
} OPTR_E;
const char optr_priority[OPTR_NUM][OPTR_NUM] = {
    {'>', '>', '<', '<', '<', '>', '>'},
    {'>', '>', '<', '<', '<', '>', '>'},
    {'>', '>', '>', '>', '<', '>', '>'},
    {'>', '>', '>', '>', '<', '>', '>'},
    {'<', '<', '<', '<', '<', '=', ' '},
    {'>', '>', '>', '>', ' ', '>', '>'},
    {'<', '<', '<', '<', '<', ' ', '='}
};

#define CHAR_OPTR_TO_ENUM(op, op_e) {            \
        switch(op){                              \
            case '+': op_e = ADD; break;         \
            case '-': op_e = SUBTRACT; break;    \
            case '*': op_e = MUL; break;         \
            case '/': op_e = DIV; break;         \
            case '(': op_e = LEFT_BRACKET; break;\
            case ')': op_e = RIGHT_BRACKET; break;\
            case '#': op_e = JING; break;        \
        }                                        \
    }
/**
 * @brief 通过优先级表计算当前元素和栈顶元素之前的运算符的优先级
 *
 * @param a 操作符栈顶运算符
 * @param b 当前运算符
 * @return char
 */
static char Precede(char a, char b)
{
    OPTR_E _a, _b;
    CHAR_OPTR_TO_ENUM(a, _a);
    CHAR_OPTR_TO_ENUM(b, _b);
    printf("%d %d\r\n", _a, _b);
    return optr_priority[_a][_b];
}

/**
 * @brief 判断当前字符是操作符或者操作数
 *
 * @param ch
 * @return true
 * @return false
 */
static bool isOptr(char ch)
{
    bool ret = false;

    switch (ch){
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
        case ')':
        case '#':
            ret = true;
            break;
        default:
            break;
    }

    return ret;
}

/**
 * @brief 计算运算结果
 *
 * @param a
 * @param op
 * @param b
 * @return int
 */
static int operate(int a, char op, int b)
{
    int result = INT_MAX;

    switch(op){
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            result = a / b;
            break;
        default:
            printf("unsupport op:%c\r\n", op);
            break;
    }

    return result;
}

/**
 * @brief 只能计算输入为 10 以内的, 因为输入为字符串, 否则就要对输入组合为整数
 *
 * @param input
 * @return int
 */
int EvaluateExpression(char* input)
{
    // printf("%s:%c",__func__, Precede('+', '-'));
    Stack OPTR, OPND; // 操作符栈, 操作数栈
    char *temp = input;
    char optrTop = '#';

    InitStack(&OPTR);
    InitStack(&OPND);

    StackTraverse(&OPTR);
    StackTraverse(&OPND);

    Push(&OPTR, &optrTop); // 先入栈一个 '#'
    StackTraverse(&OPTR);
    StackTraverse(&OPND);
    optrTop = ' ';
    GetTop(&OPTR, &optrTop);

    while(*temp != '#' || optrTop != '#'){
        // 操作数直接入栈
        if(!isOptr(*temp)){
            Push(&OPND, temp);
            ++temp; // 获取下一个元素
        }
        else{
            // 操作符:栈顶元素和将要入栈元素优先级比较
            switch(Precede(optrTop, *temp)){
                case '>':  // 栈顶元素优先级高, 运算符出栈并将计算结果入操作数栈
                {
                    char data1, data2, result;
                    Pop(&OPND, &data1);
                    Pop(&OPND, &data2);
                    result = operate(data1, *temp, data2);
                    Push(&OPND, &result);
                }
                break;
                case '=': // 仅有括号有相等优先级, 脱括号并接收下一个元素
                {
                    Pop(&OPTR, &optrTop);
                    ++temp;
                }
                break;
                case '<': // 栈顶元素优先权低, 直接入栈操作符
                {
                    Push(&OPTR, temp);
                    ++temp;
                }
                break;
            }
            GetTop(&OPTR, &optrTop);
        }

    }
}

/**
 * @brief 压测
 *
 */
void ComputerTest()
{
    char *str1 = "1+2#";
    EvaluateExpression(str1);

}





// 6. 递归:汉诺塔

void stack_application()
{
    // conversion(23, 8);
    // bracketMatchPressureTest();
    // shell_test();

    // TODO:
    // maze_test();

    ComputerTest();
}
