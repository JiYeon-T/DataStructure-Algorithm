#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "build_config.h"

#include "CircleLinkList.h"


static void data_structure_test(void);
static void algorithm_test(void);

int main()
{

#if 0 // util test
    log_test();
    exit(0);
#endif

    data_structure_test();
    algorithm_test();

    return 0;
}


static void data_structure_test(void)
{

#if defined(DataStructADT) && (DataStructADT == 1)
    TripletTest();
#endif

#if defined(DataStructLinearListV1) && (DataStructLinearListV1 == 1)
    // LinearListV1Test();
    LinearListV1Test2();
#endif


#if defined(DataStructLinearListV2) && (DataStructLinearListV2 == 1)
    // LinearListV2Test();
    LinearListV2Test2();
#endif

#if defined(DataStructLinkListV2) && (DataStructLinkListV2 == 1)
    // linklist_api_test();
    linklist_api_test2();
    // LinkListTest3();
#endif

#if defined(DataStructLinkListV3) && (DataStructLinkListV3 == 1)
    // linklist_api_test();
    linklist_api_test2();
#endif

#if defined(DataStructLinkListV4) && (DataStructLinkListV4 == 1)
    // struct_member_size_test();
    // LinkListTest3();
    // linklist_api_test4();    
    // LinkListTest5();
    // LinkListTest6();
    // LinkListTest7();
    // LinkListTest8();
#endif

#if defined(STATIC_LINK_LIST_V1) && (STATIC_LINK_LIST_V1 == 1)
    static_link_list_test();
#endif

#if defined(DataStructCircleLinkList) && (DataStructCircleLinkList == 1)
    // test_CL();
    TestCL();
#endif

#if defined(DataStructCircleLinkList) && (DataStructCircleLinkList == 1)
    // test_CL();
    TestCL();
#endif

#if defined(DataStructCircleLinkListv2) && (DataStructCircleLinkListv2 == 1)
    // CircleListTest1();
    CircleListTest2();
#endif

#if defined(DataStructDoubleLinkListV1) && (DataStructDoubleLinkListV1 == 1)
    DoubleListTest();
#endif

#if defined(DOUBLE_CIRCLE_LINKLIST) && (DOUBLE_CIRCLE_LINKLIST == 1)
    // LinkListTest_DCL2();
    DoubleCircleListTest1();
#endif

#if defined(DATA_STRUCTURE_POLYNOMAIL) && (DATA_STRUCTURE_POLYNOMAIL == 1)
    // PolynTest1();
    PolynTest2();
#endif

#if CACHE_TEST
    list_test();
#endif

#if APP_LINKLIST
#endif

}

static void algorithm_test(void)
{
    
}
