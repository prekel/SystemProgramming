/// \file
/// \brief Функции для ввода с проверкой
/// \details Функции для ввода с проверками.

#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

char* InputLineRealloc(int stepSize, bool isFinalReallocRequired);

/// Считывает строку до перевода строки.
///
/// \param stringToInput Указатель на считываемую строку.
/// \param maxStringLength Размер максимально возможной для использования
/// памяти через указатель.
/// \return Неотрицательное число в случае успеха - длина строки,
/// -1 если строка не влезла в maxStringLength,
/// число меньшее -1 если EOF или другая ошибка.
int InputLine(char* stringToInput, int maxStringLength);

/// Выводит выходную фразу и считывает целое число. Если из считанной
/// строки не получается получить число, или оно не удотворяет условию чекера
/// pChecker, то число считывается занаго. Если был получен EOF или другая
/// ошибка, программа аварийно завершается.
///
/// \param stringToOutput Строка для вывода перед вводом.
/// \param maxStringLength Максимальная длина считываемого числа.
/// \param pChecker Указател на функцию-чекер. Если равер NULL, проверка через
/// чекер не проводится.
/// \return Считанное число.
int CycleInputInt(char* stringToOutput, bool (* pChecker)(int));

#endif //INPUT_H
