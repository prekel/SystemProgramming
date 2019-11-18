#include <stdbool.h>

#include <CUnit/Basic.h>

#include "Matrix.h"
#include "MatrixTests.h"
#include "Suite.h"

static void MatrixTestsAddTests(CU_pSuite* pSuite)
{
    CU_ADD_TEST(*pSuite, Test1);
}

CU_pSuite* MatrixTestsSuiteCreate()
{
    return SuiteCreate("MatrixTests",
                       MatrixTestsAddTests);
}

void Test1(void)
{
    int n, e, d;

    CU_ASSERT_EQUAL(1, 1);
}
