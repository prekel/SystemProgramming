#include <stdbool.h>

#include <CUnit/Basic.h>

#include "ArchipelagoCollection.h"
#include "Archipelago.h"

#include "ArchipelagoCollectionTests.h"
#include "Suite.h"

static void ArchipelagoCollectionTestsAddTests(CU_pSuite* pSuite)
{
    CU_ADD_TEST(*pSuite, ArchipelagoCollectionTest_Add1);
}

CU_pSuite* ArchipelagoCollectionTestsSuiteCreate()
{
    return SuiteCreate("ArchipelagoCollectionTests",
            ArchipelagoCollectionTestsAddTests);
}

#define Add1_NAME "name1"
#define Add1_NAMELEN 5
#define Add1_COUNT 12
#define Add1_COUNTINH 3

#define Add1_NAME2 "имя2"
#define Add1_NAMELEN2 7
#define Add1_COUNT2 12
#define Add1_COUNTINH2 3

void ArchipelagoCollectionTest_Add1(void)
{
    ArchipelagoCollection* pCollection = ArchipelagoCollectionCreate();
    CU_ASSERT_PTR_NOT_NULL(pCollection);
    CU_ASSERT_PTR_NOT_NULL(pCollection->pList);
    CU_ASSERT_PTR_NULL(pCollection->pList->pFirst);
    CU_ASSERT_PTR_NULL(pCollection->pList->pLast);
    CU_ASSERT_EQUAL(pCollection->pList->Count, 0);

    Archipelago* pArchipelago = ArchipelagoCreate(Add1_NAME, Add1_COUNT, Add1_COUNTINH);
    CU_ASSERT_PTR_NOT_NULL(pArchipelago);
    CU_ASSERT_PTR_NOT_NULL(pArchipelago->Name);
    CU_ASSERT_EQUAL(strlen(pArchipelago->Name), Add1_NAMELEN);
    CU_ASSERT_EQUAL(strcmp(pArchipelago->Name, Add1_NAME), 0);
    CU_ASSERT_EQUAL(pArchipelago->CountIslands, Add1_COUNT);
    CU_ASSERT_EQUAL(pArchipelago->CountInhabitedIslands, Add1_COUNTINH);

    ArchipelagoCollectionAdd(pCollection, pArchipelago);
    CU_ASSERT_EQUAL(pCollection->pList->Count, 1);
    CU_ASSERT_PTR_EQUAL(pCollection->pList->pFirst->pElement, pArchipelago);
    CU_ASSERT_PTR_EQUAL(pCollection->pList->pFirst, pCollection->pList->pLast);
    CU_ASSERT_PTR_EQUAL(ArchipelagoCollectionGetFirst(pCollection), pArchipelago);

    Archipelago* pArchipelago2 = ArchipelagoCreate(Add1_NAME2, Add1_COUNT2, Add1_COUNTINH2);
    CU_ASSERT_PTR_NOT_NULL(pArchipelago2);
    CU_ASSERT_PTR_NOT_NULL(pArchipelago2->Name);
    CU_ASSERT_EQUAL(strlen(pArchipelago2->Name), Add1_NAMELEN2);
    CU_ASSERT_EQUAL(strcmp(pArchipelago2->Name, Add1_NAME2), 0);
    CU_ASSERT_EQUAL(pArchipelago2->CountIslands, Add1_COUNT2);
    CU_ASSERT_EQUAL(pArchipelago2->CountInhabitedIslands, Add1_COUNTINH2);

    ArchipelagoCollectionAdd(pCollection, pArchipelago2);
    CU_ASSERT_EQUAL(pCollection->pList->Count, 2);
    CU_ASSERT_PTR_EQUAL(pCollection->pList->pLast->pElement, pArchipelago2);
    CU_ASSERT_PTR_NOT_EQUAL(pCollection->pList->pFirst, pCollection->pList->pLast);
    CU_ASSERT_PTR_NOT_EQUAL(ArchipelagoCollectionGetFirst(pCollection), pArchipelago2);

    ArchipelagoDestroy(pArchipelago);
    ArchipelagoDestroy(pArchipelago2);
    ArchipelagoCollectionDestroy(pCollection);
}
