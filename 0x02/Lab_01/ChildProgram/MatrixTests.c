/*! \file MatrixTests.c
 *
 *  \brief Implements tests of MatrixTests.h
 */

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

void Det2x2_MatrixTest(void)
{
    Matrix* matrix = CreateEmptyMatrix(2, 2);

    matrix->pData[0][0] = 1;
    matrix->pData[0][1] = -65;
    matrix->pData[1][0] = 33;
    matrix->pData[1][1] = -33;

    int det = CalculateDeterminant(matrix);
    int det1 = CalculateDeterminant2x2(matrix);

    CU_ASSERT_EQUAL(det, det1);

    CU_ASSERT_EQUAL(det, 2112);

    FreeMatrix(matrix);
}

void Det3x3_MatrixTest(void)
{
    Matrix* matrix = CreateEmptyMatrix(3, 3);

    matrix->pData[0][0] = 1;
    matrix->pData[0][1] = -65;
    matrix->pData[0][2] = -2;
    matrix->pData[1][0] = 33;
    matrix->pData[1][1] = -33;
    matrix->pData[1][2] = -6;
    matrix->pData[2][0] = 33;
    matrix->pData[2][1] = 4;
    matrix->pData[2][2] = -65;

    int det = CalculateDeterminant(matrix);

    CU_ASSERT_EQUAL(det, -126828);

    FreeMatrix(matrix);
}

void Det7x7_MatrixTest(void)
{

    Matrix* matrix = CreateEmptyMatrix(7, 7);

    matrix->pData[0][0] = 1;
    matrix->pData[0][1] = 6;
    matrix->pData[0][2] = -2;
    matrix->pData[0][3] = 2;
    matrix->pData[0][4] = 1;
    matrix->pData[0][5] = 6;
    matrix->pData[0][6] = 2;

    matrix->pData[1][0] = 3;
    matrix->pData[1][1] = 3;
    matrix->pData[1][2] = 6;
    matrix->pData[1][3] = 3;
    matrix->pData[1][4] = 3;
    matrix->pData[1][5] = -6;
    matrix->pData[1][6] = 6;

    matrix->pData[2][0] = 3;
    matrix->pData[2][1] = -4;
    matrix->pData[2][2] = 6;
    matrix->pData[2][3] = 3;
    matrix->pData[2][4] = 4;
    matrix->pData[2][5] = 6;
    matrix->pData[2][6] = 3;

    matrix->pData[3][0] = -3;
    matrix->pData[3][1] = 4;
    matrix->pData[3][2] = -6;
    matrix->pData[3][3] = 3;
    matrix->pData[3][4] = 4;
    matrix->pData[3][5] = -6;
    matrix->pData[3][6] = 3;

    matrix->pData[4][0] = 3;
    matrix->pData[4][1] = -3;
    matrix->pData[4][2] = 6;
    matrix->pData[4][3] = 3;
    matrix->pData[4][4] = -3;
    matrix->pData[4][5] = 6;
    matrix->pData[4][6] = 6;

    matrix->pData[5][0] = 1;
    matrix->pData[5][1] = 6;
    matrix->pData[5][2] = 2;
    matrix->pData[5][3] = -2;
    matrix->pData[5][4] = 1;
    matrix->pData[5][5] = 6;
    matrix->pData[5][6] = 2;

    matrix->pData[6][0] = 1;
    matrix->pData[6][1] = 6;
    matrix->pData[6][2] = 2;
    matrix->pData[6][3] = 2;
    matrix->pData[6][4] = 1;
    matrix->pData[6][5] = 6;
    matrix->pData[6][6] = 2;

    int det = CalculateDeterminant(matrix);

    CU_ASSERT_EQUAL(det, 355968);

    FreeMatrix(matrix);
}