/*! \file
 *  \brief   Main file of child program
 *
 *  \details Main file which contains the main function.
 */

#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

#include <CUnit/Basic.h>

#include "Matrix.h"
#include "Input.h"
#include "MatrixTests.h"
#include "Macro.h"

/*! \brief Check number for matrix size
 *
 *  \details Check number for matrix size which must be great than 0.
 *
 *  \param n Number to check.
 *  \return Bool.
 */
bool MatrixSizeChecker(int n)
{
    return n >= 1;
}

/*! \brief Check number for matrix element
 *
 *  \details Check number for matrix element which may be any integer.
 *
 *  \param n Number to check.
 *  \return Always true bool.
 */
bool MatrixElementChecker(int n)
{
    return true;
}

/*! \brief Main function
 *
 *  \details Main function. If one argument given, will be run unit tests.
 *  Else will be program which reads two matrices, adds them and calculates
 *  determinant of sum.
 *
 *  \param argc Count program arguments.
 *  \param argv Array string which contains args.
 *  \return Integer 0 upon exit success.
 */
int main(int argc, char** argv)
{
    if (argc == 2)
    {
        CU_pSuite suite;
        CU_initialize_registry();
        suite = CU_add_suite("main_suite", NULL, NULL);
        CU_ADD_TEST(suite, Blank3x2_MatrixTest);
        CU_ADD_TEST(suite, Sum2x2_MatrixTest);
        CU_ADD_TEST(suite, Det2x2_MatrixTest);
        CU_ADD_TEST(suite, Det3x3_MatrixTest);
        CU_ADD_TEST(suite, Det7x7_MatrixTest);
        CU_ADD_TEST(suite, Minor3x4_MatrixTest);
        CU_basic_run_tests();

        CU_cleanup_registry();
        return CU_get_error();
    }

    int firstCount = 0;
    int secondCount = 0;

    firstCount = secondCount =
            CycleInputInt("Введите порядок матриц: ", MatrixSizeChecker);

    Matrix* pMatrix1 = CreateBlankMatrix(firstCount, secondCount);
    Matrix* pMatrix2 = CreateBlankMatrix(firstCount, secondCount);

    printf("Введите матрицу pMatrix1:\n");
    fflush(stdout);
    for (int i = 0; i < firstCount; i++)
    {
        for (int j = 0; j < secondCount; j++)
        {
            char* format = "pMatrix1[%d][%d] = ";
            ssize_t len = snprintf(NULL, 0, format, i, j);
            char* s = (char*) malloc(len + 1 * sizeof(char));
            FAILURE_IF_NULLPTR(s);
            snprintf(s, len + 1, format, i, j);

            pMatrix1->pData[i][j] = CycleInputInt(s, MatrixElementChecker);

            free(s);
        }
    }
    printf("\n");
    fflush(stdout);

    printf("Введите матрицу pMatrix2:\n");
    fflush(stdout);
    for (int i = 0; i < firstCount; i++)
    {
        for (int j = 0; j < secondCount; j++)
        {
            char* format = "pMatrix2[%d][%d] = ";
            ssize_t len = snprintf(NULL, 0, format, i, j);
            char* s = (char*) malloc(len + 1 * sizeof(char));
            FAILURE_IF_NULLPTR(s);
            snprintf(s, len + 1, format, i, j);

            pMatrix2->pData[i][j] = CycleInputInt(s, MatrixElementChecker);

            free(s);
        }
    }
    printf("\n");
    fflush(stdout);

    Matrix* pSum = SumMatrices(pMatrix1, pMatrix2);

    printf("Матрица pMatrix1:\n");
    for (int i = 0; i < firstCount; i++)
    {
        for (int j = 0; j < secondCount; j++)
        {
            printf("%d ", pMatrix1->pData[i][j]);
            fflush(stdout);
        }
        printf("\n");
    }
    printf("\n");
    fflush(stdout);

    printf("Матрица pMatrix2:\n");
    for (int i = 0; i < firstCount; i++)
    {
        for (int j = 0; j < secondCount; j++)
        {
            printf("%d ", pMatrix2->pData[i][j]);
            fflush(stdout);
        }
        printf("\n");
    }
    printf("\n");
    fflush(stdout);

    printf("Сумма матриц pMatrix1 + pMatrix2:\n");
    for (int i = 0; i < firstCount; i++)
    {
        for (int j = 0; j < secondCount; j++)
        {
            printf("%d ", pSum->pData[i][j]);
            fflush(stdout);
        }
        printf("\n");
    }
    printf("\n");
    fflush(stdout);

    int det = CalculateDeterminant(pSum);
    printf("Определитель суммы матриц det = %d\n", det);
    fflush(stdout);

    FreeMatrix(pMatrix1);
    FreeMatrix(pMatrix2);
    FreeMatrix(pSum);

    return 0;
}
