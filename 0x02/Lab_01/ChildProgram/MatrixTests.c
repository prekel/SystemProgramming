#include "MatrixTests.h"

void test1(void)
{
    Matrix* matrix = CreateEmptyMatrix(3, 2);

    CU_ASSERT_EQUAL(matrix->FirstCount, 3);
    CU_ASSERT_EQUAL(matrix->SecondCount, 2);

    CU_ASSERT_EQUAL(matrix->pData[0][0], 0);
    CU_ASSERT_EQUAL(matrix->pData[1][1], 0);
    CU_ASSERT_EQUAL(matrix->pData[2][0], 0);
    CU_ASSERT_EQUAL(matrix->pData[0][1], 0);
    CU_ASSERT_EQUAL(matrix->pData[1][0], 0);
    CU_ASSERT_EQUAL(matrix->pData[2][1], 0);
}