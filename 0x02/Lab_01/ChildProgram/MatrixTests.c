#include "MatrixTests.h"

void Empty3x2_MatrixTest(void)
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

    FreeMatrix(matrix);
}

void Sum2x2_MatrixTest(void)
{
    Matrix* matrix1 = CreateEmptyMatrix(2, 2);
    Matrix* matrix2 = CreateEmptyMatrix(2, 2);

//    CU_ASSERT_EQUAL(matrix1->FirstCount, 2);
//    CU_ASSERT_EQUAL(matrix1->SecondCount, 2);
//    CU_ASSERT_EQUAL(matrix2->FirstCount, 2);
//    CU_ASSERT_EQUAL(matrix2->SecondCount, 2);

//    CU_ASSERT_EQUAL(matrix1->pData[0][0], 0);
//    CU_ASSERT_EQUAL(matrix1->pData[0][1], 0);
//    CU_ASSERT_EQUAL(matrix1->pData[1][0], 0);
//    CU_ASSERT_EQUAL(matrix1->pData[1][1], 0);
//    CU_ASSERT_EQUAL(matrix2->pData[0][0], 0);
//    CU_ASSERT_EQUAL(matrix2->pData[0][1], 0);
//    CU_ASSERT_EQUAL(matrix2->pData[1][0], 0);
//    CU_ASSERT_EQUAL(matrix2->pData[1][1], 0);

    matrix1->pData[0][0] = 1;
    matrix1->pData[0][1] = -65;
    matrix1->pData[1][0] = 33;
    matrix1->pData[1][1] = -33;
    matrix2->pData[0][0] = 1;
    matrix2->pData[0][1] = 12;
    matrix2->pData[1][0] = -8;
    matrix2->pData[1][1] = 3;

    Matrix* sum = SumMatrices(matrix1, matrix2);

    CU_ASSERT_EQUAL(sum->pData[0][0], 2);
    CU_ASSERT_EQUAL(sum->pData[0][1], -53);
    CU_ASSERT_EQUAL(sum->pData[1][0], 25);
    CU_ASSERT_EQUAL(sum->pData[1][1], -30);

    FreeMatrix(matrix1);
    FreeMatrix(matrix2);
    FreeMatrix(sum);
}
