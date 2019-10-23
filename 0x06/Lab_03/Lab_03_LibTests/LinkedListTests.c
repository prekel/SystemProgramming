#include <stdbool.h>

#include <CUnit/Basic.h>

#include "LinkedList.h"
#include "LinkedListNode.h"

#include "Suite.h"
#include "LinkedListTests.h"

static void LinkedListTestsAddTests(CU_pSuite* pSuite)
{
    CU_ADD_TEST(*pSuite, LinkedListTest_Create1);
    CU_ADD_TEST(*pSuite, LinkedListTest_Append1);
    CU_ADD_TEST(*pSuite, LinkedListTest_Append2);
}

CU_pSuite* LinkedListTestsSuiteCreate()
{
    return SuiteCreate("LinkedListTests", LinkedListTestsAddTests);
}

void LinkedListTest_Create1(void)
{
    LinkedList* pList = LinkedListCreate();
    CU_ASSERT_EQUAL(pList->Count, 0);
    CU_ASSERT_EQUAL(pList->pFirst, NULL);
    CU_ASSERT_EQUAL(pList->pLast, NULL);

    LinkedListDestroy(pList);
}

void LinkedListTest_Append1(void)
{
    LinkedList* pList = LinkedListCreate();
    CU_ASSERT_EQUAL(pList->Count, 0);
    CU_ASSERT_EQUAL(pList->pFirst, NULL);
    CU_ASSERT_EQUAL(pList->pLast, NULL);

    int array[] = {1, 2, 3, 4, 5};

    LinkedListAppendElement(pList, &array[0]);

    CU_ASSERT_EQUAL(pList->Count, 1);
    CU_ASSERT_EQUAL(pList->pFirst, pList->pLast);
    CU_ASSERT_EQUAL(pList->pFirst->pElement, &array[0]);
    CU_ASSERT_EQUAL(pList->pLast->pElement, &array[0]);
    CU_ASSERT_EQUAL(pList->pFirst->pList, pList);
    CU_ASSERT_EQUAL(pList->pLast->pList, pList);
    CU_ASSERT_EQUAL(pList->pFirst->pPrevious, NULL);
    CU_ASSERT_EQUAL(pList->pFirst->pNext, NULL);
    CU_ASSERT_EQUAL(pList->pLast->pPrevious, NULL);
    CU_ASSERT_EQUAL(pList->pLast->pNext, NULL);

    LinkedListDestroy(pList);
}

void LinkedListTest_Append2(void)
{
    LinkedList* pList = LinkedListCreate();
    CU_ASSERT_EQUAL(pList->Count, 0);
    CU_ASSERT_EQUAL(pList->pFirst, NULL);
    CU_ASSERT_EQUAL(pList->pLast, NULL);

    int array[] = {1, 2, 3, 4, 5};

    LinkedListAppendElement(pList, &array[0]);

    CU_ASSERT_EQUAL(pList->Count, 1);
    CU_ASSERT_EQUAL(pList->pFirst, pList->pLast);
    CU_ASSERT_EQUAL(pList->pFirst->pElement, &array[0]);
    CU_ASSERT_EQUAL(pList->pLast->pElement, &array[0]);
    CU_ASSERT_EQUAL(pList->pFirst->pList, pList);
    CU_ASSERT_EQUAL(pList->pLast->pList, pList);
    CU_ASSERT_EQUAL(pList->pFirst->pPrevious, NULL);
    CU_ASSERT_EQUAL(pList->pFirst->pNext, NULL);
    CU_ASSERT_EQUAL(pList->pLast->pPrevious, NULL);
    CU_ASSERT_EQUAL(pList->pLast->pNext, NULL);

    LinkedListAppendElement(pList, &array[1]);

    CU_ASSERT_EQUAL(pList->Count, 2);
    CU_ASSERT_NOT_EQUAL(pList->pFirst, pList->pLast);
    CU_ASSERT_EQUAL(pList->pFirst->pElement, &array[0]);
    CU_ASSERT_EQUAL(pList->pLast->pElement, &array[1]);
    CU_ASSERT_EQUAL(pList->pFirst->pList, pList);
    CU_ASSERT_EQUAL(pList->pLast->pList, pList);
    CU_ASSERT_EQUAL(pList->pFirst->pPrevious, NULL);
    CU_ASSERT_EQUAL(pList->pFirst->pNext, pList->pLast);
    CU_ASSERT_EQUAL(pList->pLast->pPrevious, pList->pFirst);
    CU_ASSERT_EQUAL(pList->pLast->pNext, NULL);

    LinkedListDestroy(pList);
}
