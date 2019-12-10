#include <stdbool.h>
#include <malloc.h>

#include <CUnit/Basic.h>

#include "MatrixTests.h"
#include "Suite.h"

#include "Matrix.h"
#include "MatrixIO.h"

static void MatrixTestsAddTests(CU_pSuite* pSuite)
{
    CU_ADD_TEST(*pSuite, TestCountLineRowAndWrite);
}

CU_pSuite* MatrixTestsSuiteCreate()
{
    return SuiteCreate("MatrixTests", MatrixTestsAddTests);
}

void TestCountLineRowAndWrite()
{
    printf("%s\n", CU_get_current_test()->pName);

    CU_ASSERT_EQUAL(123,123);

    int m = 5;
    int n = 4;
    int* pMatrix = (int*) malloc(m * n * sizeof(int));
    for (int i = 0; i < m * n; i++)
    {
        pMatrix[i] = i;
    }
    CU_ASSERT_EQUAL(CountDifferentLines(pMatrix, m, n), m);
    CU_ASSERT_EQUAL(CountDifferentRows(pMatrix, m, n), n);

    WriteMatrix(pMatrix, m, n);

    free(pMatrix);
}
