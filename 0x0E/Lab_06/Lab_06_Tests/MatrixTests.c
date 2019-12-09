#include <stdbool.h>
#include <malloc.h>

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
    return SuiteCreate("MatrixTests", MatrixTestsAddTests);
}

void Test1()
{
    CU_ASSERT_EQUAL(123,123);

    int m = 5;
    int n = 4;
    int* pMatrix = (int*) malloc(m * n * sizeof(int));
    for (int i = 0; i < m * n; i++)
    {
        pMatrix[i] = i;
    }
    CU_ASSERT_EQUAL(CountLine(pMatrix, m, n), m);
    CU_ASSERT_EQUAL(CountRow(pMatrix, m, n), n);

    free(pMatrix);
}
