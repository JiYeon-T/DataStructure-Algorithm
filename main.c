#include <stdio.h>
#include <stdlib.h>

#include "build_config.h"


int main()
{
#if defined(DataStructADT) && (DataStructADT == 1)
    TripletTest();
#endif

#if defined(DataStructLinearListV1) && (DataStructLinearListV1 == 1)
    LinearListV1Test();
#endif


#if defined(DataStructLinearListV2) && (DataStructLinearListV2 == 1)
    LinearListTest_L();
#endif

#if defined(DataStructLinkListV2) && (DataStructLinkListV2 == 1)
    // linklist_api_test();
    // linklist_api_test_v2();
    LinkListTest3();
#endif

#if defined(DataStructLinkListV3) && (DataStructLinkListV3 == 1)
    linklist_api_test_v3();
#endif

#if defined(DataStructLinkListV4) && (DataStructLinkListV4 == 1)
    // struct_member_size_test();
    // LinkListTest3();
    // linklist_api_test4();    
    // LinkListTest5();
    // LinkListTest6();
    LinkListTest7();
#endif

#if defined(STATIC_LINK_LIST_V1) && (STATIC_LINK_LIST_V1 == 1)
    static_link_list_test();
#endif

#if defined(DataStructDoubleLinkListV1) && (DataStructDoubleLinkListV1 == 1)
    DoubleListTest();
#endif

#if CIRCLE_LINK_LIST
    // test_CL();
    CircleLinkListTestV2();
#endif

#if defined(DOUBLE_CIRCLE_LINKLIST) && (DOUBLE_CIRCLE_LINKLIST == 1)
    LinkListTest_DCL2();
#endif

#if defined(DATA_STRUCTURE_POLYNOMAIL) && (DATA_STRUCTURE_POLYNOMAIL == 1)
    PolynTest1();
#endif

#if CACHE_TEST
    list_test();
#endif

#if APP_LINKLIST
#endif


    return 0;
}
