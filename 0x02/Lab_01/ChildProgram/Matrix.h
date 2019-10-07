/*! \file

 *  \brief   Matrix structure and functions to use it
 *
 *  \details Matrix structure and functions to calculate sum, determinant,
 *           etc...
 *  \bug     Unclear first and second indices are row or column.
 */

#ifndef MATRIX_H
#define MATRIX_H

/*! \struct Matrix
 *  \brief Matrix struct
 *
 *  \details Matrix structure. Uses memory allocation, needs frees up memory.
 */
typedef struct
{
    /*!
     * Maximum 1st index.
     */
    int FirstCount;
    /*!
     * SecondCount Maximum 2nd index.
     */
    int SecondCount;
    /*!
     * pData Matrix array. To get element use
     * matrix->pData[firstindex][secondindex].
     */
    int** pData;
} Matrix;

/*! \brief Create matrix filled with zeros
 *
 *  \details Allocate memory for new matrix and initialize with zeros.
 *
 *  \param firstCount Maximum 1st index.
 *  \param secondCount Maximum 2nd index.
 *  \return Pointer to new matrix.
 */
Matrix* CreateBlankMatrix(int firstCount, int secondCount);

/*! \brief Create non-initialized matrix
 *
 *  \details Allocate memory for new matrix. Matrix filled with garbage.
 *
 *  \param firstCount Maximum 1st index.
 *  \param secondCount Maximum 2nd index.
 *  \return Pointer to new matrix.
 */
Matrix* CreateEmptyMatrix(int firstCount, int secondCount);

/*! \brief Adds matrices
 *
 *  \details Allocate memory for new matrix equals to matrixA + matrixB.
 *
 *  \param pMatrixA 1st matrix to add.
 *  \param pMatrixB 2nd matrix to add.
 *  \return Pointer to sum.
 */
Matrix* SumMatrices(Matrix* pMatrixA, Matrix* pMatrixB);

/*! \brief Calculates minor of matrix
 *
 *  \details Allocate memory for new matrix which has't specified row and
 *           column.
 *
 *  \param pMatrix Matrix to create minor.
 *  \param firstIndex 1st-dimension to exclude (column).
 *  \param secondIndex 2nd-dimension to exclude (row).
 *  \return Pointer to created minor.
 */
Matrix* GetMinor(Matrix* pMatrix, int firstIndex, int secondIndex);

/*! \brief Calculates determinant of 2x2 matrix
 *
 *  \details Calculates determinant only for 2x2 matrices.
 *
 *  \param pMatrix 2x2 matrix to calculate determinant.
 *  \return Determinant integer.
 */
int CalculateDeterminant2x2(Matrix* pMatrix);

/*! \brief Calculates determinant matrix
 *
 *  \details Calculates matrix determinant.
 *
 *  \param pMatrix Matrix to calculate determinant.
 *  \return Determinant integer.
 */
int CalculateDeterminant(Matrix* pMatrix);

/*! \brief Frees up matrix memory
 *
 *  \details Frees up memory to destroy matrix
 *
 *  \param pMatrix Matrix to free.
 */
void FreeMatrix(Matrix* pMatrix);

#endif // MATRIX_H
