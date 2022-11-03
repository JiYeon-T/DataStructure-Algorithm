#include <stdio.h>
#include <stdlib.h>
#include "head.h"
#include "config.h"

int main()
{
//    TripletTest();
#if LINEAR_LIST
    ListTest_L();
#endif // LINEAR_LIST

#if LINK_LIST
//    linklist_test();
//    LinkListTest2();
    LinkListTest3();
#endif // LINK_LIST

#if STATIC_LINK_LIST
    // test_SL();
    SL_test2();
#endif


#if CACHE_TEST
    list_test();
#endif

#if CIRCLE_LINK_LIST
    // test_CL();
    Test2_CL();
#endif

#if DOUBLE_LINK_LIST
#if WITHOUT_TAIL_POINTER
    DoubleListTest();
#else // WITHOUT_TAIL_POINTER
    DoubleListTest_v2();
#endif // WITHOUT_TAIL_POINTER
#endif // DOUBLE_LINK_LIST



    return 0;
}
