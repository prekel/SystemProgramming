/// \file
/// \brief Функции для считывания целых чисел из строки
/// \details Функции для считывания целых чисел из строки.

#ifndef PARSEINT_H
#define PARSEINT_H

#include <stdbool.h>

/// Пытается считать число из строки.
///
/// \param string Строка, из которой считывается число.
/// \param pResult Указатель, куда записывается результат.
/// \return Истина если удалось считать, ложб если не удалось.
bool TryParseInt(char* string, int* pResult);

/// Считывает целое число из строки. Если удалось считать, инкрементируется
/// счётчик по указателю pSuccessfulCount.
///
/// \param string Строка, из которой считывается число.
/// \param pSuccessfulCount Указатель на счётчик успешных считываний.
/// \return Считанное число. 0, если не удалось считать.
int ParseInt(char* string, int* pSuccessfulCount);

#endif //PARSEINT_H
