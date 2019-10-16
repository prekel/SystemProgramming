/// \file
/// \brief Главная функция
/// \details Файл с главной функцией интерактивной программы.

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#ifdef __MINGW32__
#include <windows.h>
#endif

#include "Input.h"
#include "Table.h"
#include "Logger.h"

#include "MainWindow.h"

/// Ширина окна
const int SCREEN_WIDTH = 512;
/// Высота окна
const int SCREEN_HEIGHT = 512;

/// Максимальная длина для считывания целого числа
const int MAX_INT_LENGTH = 20;

/// Проверяет введённое время на неотрицательность.
///
/// \param time Время для проверки в миллисекундах.
/// \return Логическое значение - результат проверки.
bool TimeChecker(int time)
{
    return 0 <= time;
}

/// Проверяет введёное число философ чтобы было не меньше двух.
///
/// \param philosophersCount Число философов для проверки.
/// \return Логическое значение - результат проверки.
bool PhilosophersCountChecker(int philosophersCount)
{
    return 2 <= philosophersCount;
}

static FILE* g_pOutputFile;

//int PrintToFile(char* format)
//{
//    //int ret = fprintf(g_pOutputFile, format);
//    //fflush(g_pOutputFile);
//    //return ret;
//}

//int SdlLog(char* format)
//{
//    //SDL_Log(format);
//}

/// Главная функция программы, считывающая данные и запускающая главное окно
/// с главным циклом.
///
/// \param argc Число аргументов переданное программе.
/// \param args Массив строк аргументов.
/// \return Возвращает результат выполнения главного цикла - 0 в случае
/// успешного завершения, 1 в случае принудительного.
int main(int argc, char** args)
{
#ifdef __MINGW32__
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    printf("Обозначения: Большой квадрат - философ:\n");
    printf("              -  тёмно-серый - поток ещё не запущен или "
           "уже завершён;\n");
    printf("              _        белый - ничего не делает;\n");
    printf("              =      красный - ест;\n");
    printf("              ?      зелёный - ожидает.\n");
    printf("             Маленький квадрат - вилка:\n");
    printf("              ,      оранжевый - занята;\n");
    printf("              .   светло-серый - свободна.\n");
    printf("\n");

    printf("Управление: [1-9]      - отправить философа "
           "есть;\n");
    printf("            Alt+[1-9]  - прекратить приём пищи или "
           "ожидание;\n");
    printf("            Ctrl+[1-9] - переключение метки бесконечного "
           "приёма пищи;\n");
    printf("            Esc        - выход из программы с ожиданием "
           "завершения всех потоков.\n");
    printf("\n\n");

    printf("Минимальное количество философов 2, "
           "желательно не больше 9, рекомендуется 5.\n");
    int philosophersCount =
            CycleInputInt("Введите кол-во философов: ",
                          MAX_INT_LENGTH,
                          PhilosophersCountChecker);
    printf("\n");

    printf("Время вводится в миллисекундах.\n");
    printf("Разность между верхней границей и нижней должна быть "
           "не меньше 0 и не больше %d.\n",
           RAND_MAX);
    printf("Время будет генерироватся в полуинтервале "
           "[нижняя граница; верхняя граница).\n\n");

    int minDurationEat;
    int maxDurationEat;
    do
    {
        printf("Для того, чтобы время приёма пищы было бесконечным, "
               "введите 0 и 0.\n");
        printf("Для того, чтобы было постоянным, введите одинаковые "
               "числа.\n");
        minDurationEat = CycleInputInt(
                "Введите нижнию границу времени приёма пищи "
                "(например 1000): ",
                MAX_INT_LENGTH, TimeChecker);
        maxDurationEat = CycleInputInt(
                "Введите верхнюю границу времени приёма пищи "
                "(например 5000): ",
                MAX_INT_LENGTH, TimeChecker);
    } while (maxDurationEat < minDurationEat ||
             maxDurationEat - minDurationEat > RAND_MAX);
    bool isInfinityDuration = minDurationEat == 0 && maxDurationEat == 0;
    printf("\n");

    int minSendIntervalDuration;
    int maxSendIntervalDuration;
    do
    {
        printf("Для того, философы не появлялись автоматически, "
               "введите 0 и 0.\n");
        printf("Для того, чтобы было постоянным, введите одинаковые "
               "числа.\n");
        minSendIntervalDuration = CycleInputInt(
                "Введите нижнию границу времени между "
                "появлениями (например 500): ",
                MAX_INT_LENGTH, TimeChecker);
        maxSendIntervalDuration = CycleInputInt(
                "Введите верхнюю границу времени между "
                "появлениями (например 1500): ",
                MAX_INT_LENGTH, TimeChecker);
    } while (maxSendIntervalDuration < minSendIntervalDuration ||
             maxSendIntervalDuration - minSendIntervalDuration > RAND_MAX);
    bool isAutoSpawnDisabled =
            minSendIntervalDuration == 0 && maxSendIntervalDuration == 0;
    printf("\n");

    Table* pTable = CreateTable(philosophersCount, minDurationEat,
                                maxDurationEat,
                                isInfinityDuration);

    //InitLogger(pTable, stdout, false, fopen("5.txt", "w+"), false);
    g_pOutputFile = fopen("3.log", "w+");
    FILE* file2 = fopen("4.log", "w+");
    InitLogger(pTable, true, stdout, file2, NULL, NULL);
    LOG("Введены данные, создание объектов, запуск потоков");

    MainWindow* pMainWindow = CreateMainWindow(
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            pTable,
            minSendIntervalDuration,
            maxSendIntervalDuration,
            isAutoSpawnDisabled,
            true,
            false);

    InitVideoMainWindow(pMainWindow);

    StartThreadsMainWindow(pMainWindow);

    LOG("Запуск главного цикла");
    int ret = MainCycleMainWindow(pMainWindow);

    DestroyMainWindow(pMainWindow);
    DestroyTable(pTable);

    fclose(g_pOutputFile);
    fclose(file2);

    return ret;
}
