#ifndef __TEST_H__
#define __TEST_H__
#include <stdio.h>

#define     MODULE_NAME     "LOG_MODULE"
#define     LOG_D(format, ...)      printf("DEBUG[" MODULE_NAME "][%s|%d]"format, __func__, __LINE__)

//various log print format
void log_test()
{
    for(int ix = 0; ix < 10; ++ix)
    {
        LOG_D("running, %d\n", ix);
    }
}

#endif // __TEST_H__
