/// \file
/// \brief Матрица.
/// \details Матрица, её структура, функции для создания, использования итд.

#ifndef MATRIX_H
#define MATRIX_H

/// \struct Matrix
///
/// Матрица.
typedef struct
{
    /// Кол-во столбцов.
    int FirstCount;
    /// Кол-во строк.
    int SecondCount;
    /// Элементы матрицы.
    int** ppData;
} Matrix;

/// Создаёт матрицу, заполенную нулями. Требуется очистка с
/// помощью DestroyMatrix(). В случае ошибки аллокации или неположительных
/// входных значениях срабатывает assert().
///
/// \param firstCount Кол-во строк
/// \param secondCount Кол-во столбцов
/// \return Указатель на матрицу.
Matrix* CreateBlankMatrix(int firstCount, int secondCount);

/// Создаёт матрицу с неинициализированными элементами. Требуется очистка с
/// помощью DestroyMatrix(). В случае ошибки аллокации или неположительных
/// входных значениях срабатывает assert().
///
/// \param firstCount Кол-во строк
/// \param secondCount Кол-во столбцов
/// \return Указатель на матрицу.
Matrix* CreateEmptyMatrix(int firstCount, int secondCount);

/// Выводит матрицу.
///
/// \param pMatrix Указатель на матрицу.
void PrintMatrix(Matrix* pMatrix);

/// Складывает матрицы Sum = A + B. Если pSumResult == NULL, то выделяется память и требуется очистка с
/// помощью DestroyMatrix(). В случае ошибки аллокации или неверных входных
/// данных срабатывает assert().
/// \param pSumResult Указтель на матрицу Sum, в которую записывается результат.
/// \param pMatrixA Указатель на матрицу A.
/// \param pMatrixB Указатель на матрицу B.
/// \return Указатель на матрицу-результат Sum. Если pSumResult != NULL,
/// то pSumResult.
Matrix* SumMatrices(Matrix* pSumResult, Matrix* pMatrixA, Matrix* pMatrixB);

/// Вычисляет матрицу, в которой отсутствует заданная строка и ряд.
/// Если pMinorResult == NULL, то выделяется память и требуется очистка с
/// помощью DestroyMatrix(). В случае ошибки аллокации или неверных входных
/// данных срабатывает assert().
///
/// \param pMinorResult Указатель на матрицу, в которую записывается
/// результат. Должна быть степенью на 1 меньше чем pMatrix.
/// \param pMatrix Указатель на матрицу.
/// \param firstIndex Индекс строки.
/// \param secondIndex Индекс ряда.
/// \return Указатель на матрицу-результат. Если pMinorResult != NULL,
/// то pMinorResult.
Matrix* GetMinor(Matrix* pMinorResult, Matrix* pMatrix, int firstIndex,
                 int secondIndex);

/// Вычисляет опредеитель для матрицы с порядком 2. Срабатывает assert(),
/// если порядок не 2.
///
/// \param pMatrix Указатель на матрицу.
/// \return Определитель.
int CalculateDeterminant2x2(Matrix* pMatrix);

/// Вычисляет определитель матрицы. Срабатывает assert() если, матрица не
/// квадратная или в случае ошибки аллокации.
///
/// \param pMatrix Указатель на матрицу.
/// \return Определитель матрицы.
int CalculateDeterminant(Matrix* pMatrix);

/// Уничтожает матрицу.
///
/// \param pMatrix Указатель на матрицу.
void DestroyMatrix(Matrix* pMatrix);

#endif // MATRIX_H
