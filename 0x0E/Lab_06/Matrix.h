/// \file
/// \brief Функции, подсчитывающие матрицу
/// \details Функции, подсчитывающие матрицу.

#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>

/// Проверяет ряд или строку матрицы, хрянящейнся в одномерном массиве
/// на различие всех элементов.
///
/// \param pArray Указатель на первый элемент ряда или строки
/// \param step 1 для строки, кол-во столбцов (n) для столбца.
/// \param size Кол-во столбцов (n) для строки, кол-во строк (m) для столбца.
/// \return Истина если все элементы различны.
bool CheckAllDifferent(int* pArray, int step, int size);

/// Подсчитывает кол-во строк в матрице, хранящейся в одномерном массиве,
/// в которых все элементы различны.
///
/// \param pMatrix Указатель на первый элемент массива, в котором хранится
/// матрица.
/// \param m Кол-во строк.
/// \param n Кол-во столбцов.
/// \return Кол-во строк в матрице, все элементы которых различны.
int CountDifferentLines(int* pMatrix, int m, int n);

/// Подсчитывает кол-во столбцов в матрице, хранящейся в одномерном массиве,
/// в которых все элементы различны.
///
/// \param pMatrix Указатель на первый элемент массива, в котором хранится
/// матрица.
/// \param m Кол-во строк.
/// \param n Кол-во столбцов.
/// \return Кол-во столбцов в матрице, все элементы которых различны.
int CountDifferentRows(int* pMatrix, int m, int n);

#endif //MATRIX_H
