#include <stdbool.h>

#include <CUnit/Basic.h>

#include "ArchipelagoCollection.h"

#include "ArchipelagoCollectionTests.h"
#include "Suite.h"

static void ArchipelagoCollectionTestsAddTests(CU_pSuite* pSuite)
{
    CU_ADD_TEST(*pSuite, ArchipelagoCollectionTest_Append1);
}

CU_pSuite* ArchipelagoCollectionTestsSuiteCreate()
{
    return SuiteCreate("ArchipelagoCollectionTests",
            ArchipelagoCollectionTestsAddTests);
}

void ArchipelagoCollectionTest_Append1(void)
{

}