#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#ifdef __MINGW32__
#include <windows.h>
#endif

#include "Input.h"
#include "Table.h"
#include "Log.h"

#include "MainWindow.h"

#define FILE_NAME "main"

const int SCREEN_WIDTH = 512;
const int SCREEN_HEIGHT = 512;

const int MAX_INT_LENGTH = 20;

const int SEC_IN_DAY = 60 * 60 * 24;

bool TimeChecker(int time)
{
    return 0 <= time;// && time <= SEC_IN_DAY;
}

bool PhilosophersCountChecker(int philosophersCount)
{
    return 2 <= philosophersCount;// && philosophersCount <= 10000;
}

int main(int argc, char** args)
{
#ifdef __MINGW32__
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    printf("Минимальное количество философов 2, желательно не больше 9, "
           "рекомендуется 5\n");
    int philosophersCount = CycleInputInt("Введите кол-во философов: ", MAX_INT_LENGTH, PhilosophersCountChecker);
    printf("\n");

    printf("Время вводится в миллисекундах\n");
    printf("Разность между верхней границей и нижней должна быть не меньше 0 и не больше %d\n\n", RAND_MAX);

    int minDurationEat;
    int maxDurationEat;
    do
    {
        printf("Для того, чтобы время приёма пищы было бесконечным, введите 0 и 0\n");
        printf("Для того, чтобы было постоянным, введите одинаковые числа\n");
        minDurationEat = CycleInputInt(
                "Введите минимальное время приёма пищи (например 1000): ",
                MAX_INT_LENGTH, TimeChecker);
        maxDurationEat = CycleInputInt(
                "Введите максимальное время приёма пищи (например 5000): ",
                MAX_INT_LENGTH, TimeChecker);
    } while (maxDurationEat < minDurationEat || maxDurationEat - minDurationEat > RAND_MAX);
    bool isInfinityDuration = minDurationEat == 0 && maxDurationEat == 0;
    printf("\n");

    int minSendIntervalDuration;
    int maxSendIntervalDuration;
    do
    {
        printf("Для того, философы не появлялись автоматически, введите 0 и 0\n");
        printf("Для того, чтобы было постоянным, введите одинаковые числа\n");
        minSendIntervalDuration = CycleInputInt(
                "Введите минимальное время между появлениями (например 500): ",
                MAX_INT_LENGTH, TimeChecker);
        maxSendIntervalDuration = CycleInputInt(
                "Введите максимальное время между появлениями (например 1500): ",
                MAX_INT_LENGTH, TimeChecker);
    } while (maxSendIntervalDuration < minSendIntervalDuration || maxSendIntervalDuration - minSendIntervalDuration > RAND_MAX);
    bool isAutoSpawnDisabled = minSendIntervalDuration == 0 && maxSendIntervalDuration == 0;
    printf("\n");

    printf("Управление: [1-9]      - отправить философа есть\n");
    printf("            Alt+[1-9]  - прекратить приём пищи или ожидание\n");
    printf("            Ctrl+[1-9] - переключение метки бесконечного приёма пищи\n");
    printf("            Esc        - выход из программы с ожиданием завершения всех потоков\n");
    printf("\n");

    Table* pTable = CreateTable(philosophersCount, minDurationEat, maxDurationEat,
                                isInfinityDuration);

    //InitLogger(pTable, stdout, false, fopen("5.txt", "w+"), false);
    InitLogger(pTable, stdout, true, NULL, false);
    LOG("Введены данные, создание объектов, запуск потоков");

    MainWindow* pMainWindow = CreateMainWindow(
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            pTable,
            minSendIntervalDuration,
            maxSendIntervalDuration,
            isAutoSpawnDisabled);

    InitVideoMainWindow(pMainWindow);

    InitAndStartThreadsMainWindow(pMainWindow);

    LOG("Запуск главного цикла");
    return MainCycleMainWindow(pMainWindow);
}
