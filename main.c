#include <stdio.h>
#include <stdlib.h>
#include "head.h"


int main()
{
//    TripletTest();
#if LINEAR_LIST
    ListTest_L();
#endif // LINEAR_LIST

#if LINK_LIST
//    linklist_test();
    LinkListTest2();
#endif // LINK_LIST

    return 0;
}
