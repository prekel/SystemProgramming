/// \file
/// \brief Функции для ввода с проверкой
/// \details Функции для ввода с проверками.

#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

/// Считывает строку до передода строки в динамическую строку. Требуется
/// очистка с помощью free().
///
/// \param stepSize Шаг, с которым считывается строка. Должен быть не менее 2.
/// Рекомендуется 10.
/// \param isFinalReallocRequired Требуется ли уменьшать выделенную память до
/// размера считанной строки. Иначе выделенная память будет кратна stepSize.
/// \return Указатель на считанную строку.
char* InputLineRealloc(int stepSize, bool isFinalReallocRequired);

/// Считывает строку до перевода строки.
///
/// \param stringToInput Указатель на считываемую строку.
/// \param maxStringLength Размер максимально возможной для использования
/// памяти через указатель.
/// \return Неотрицательное число в случае успеха - длина считанной строки,
/// -1 если строка не влезла в maxStringLength.
int InputLine(char* stringToInput, int maxStringLength);

/// Выводит выходную фразу и считывает целое число. Если из считанной
/// строки не получается получить число, или оно не удолетворяет условию
/// чекера pChecker, то число считывается занаво.
///
/// \param maxIntLength Максимальная длина считываемого числа.
/// \param pChecker Указател на функцию-чекер. Если равен NULL, проверка через
/// чекер не проводится.
/// \param formatToOutput Строка для вывода перед вводом.
/// \param ... Параметры для вывода.
/// \return Считанное число.
int CycleInputInt(int maxIntLength,
                  bool(* pChecker)(int),
                  char* formatToOutput,
                  ...);

/// Считывает строку, проверяя её функцией-чекером. Требуется очистка с
/// помощью free().
///
/// \param pChecker Указател на функцию-чекер. Если равен NULL, проверка через
///// чекер не проводится.
/// \param formatToOutput Строка для вывода перед вводом.
/// \param ... Параметры для вывода.
/// \return Указатель на считанную строку.
char* CycleInputString(bool (* pChecker)(char*), char* formatToOutput, ...);

#endif //INPUT_H
