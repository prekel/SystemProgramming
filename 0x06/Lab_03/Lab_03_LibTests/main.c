#include <stdlib.h>

#include <CUnit/Basic.h>

#include "LinkedListTests.h"
#include "ArchipelagoCollectionTests.h"
#include "Suite.h"

int main()
{
    CU_initialize_registry();

    CU_pSuite* ppSuites[] = {
            LinkedListTestsSuiteCreate(),
            ArchipelagoCollectionTestsSuiteCreate(),
            NULL};

    CU_basic_run_tests();

    CU_cleanup_registry();

    for (int i = 0; ppSuites[i] != NULL; i++)
    {
        SuiteDestroy(ppSuites[i]);
    }

    return CU_get_error();
}
