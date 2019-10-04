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


#define _FILE strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__

#define LOG_HELPER(format, ...)      Log2(format, __VA_ARGS__)

#define LOG_FMT             "[%20s:%d] "
#define LOG_ARGS    _FILE, __LINE__

#define LOG(message, args...)     LOG_HELPER(LOG_FMT message, LOG_ARGS, ## args)

const int SCREEN_WIDTH = 512;
const int SCREEN_HEIGHT = 512;

const int MAX_INT_LENGTH = 10;

const int SEC_IN_DAY = 60 * 60 * 24;

bool TimeChecker(int time)
{
    return 0 <= time && time <= SEC_IN_DAY;
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

    printf("Для того, чтобы время приёма пищы было бесконечным, введите 0 минимальное и максимальное\n");
    printf("Для того, чтобы было постоянным, введите одинаковое максимальное и минимальное\n");
    int minDurationEat = CycleInputInt("Введите минимальное время приёма пищи: ", MAX_INT_LENGTH, TimeChecker);
    int maxDurationEat = CycleInputInt("Введите максимальное время приёма пищи: ", MAX_INT_LENGTH, TimeChecker);
    bool isInfinityDuration = minDurationEat == 0 && maxDurationEat == 0;

    printf("Для того, философы не появлялись автоматически, введите 0 и 0\n");
    printf("Для того, чтобы было постоянным, введите одинаковое максимальное и минимальное\n");
    int minSendIntervalDuration = CycleInputInt("Введите минимальное время между появлениями: ", MAX_INT_LENGTH, TimeChecker);
    int maxSendIntervalDuration = CycleInputInt("Введите максимальное время между появлениями: ", MAX_INT_LENGTH, TimeChecker);
    bool isAutoSpawnDisabled = minSendIntervalDuration == 0 && maxSendIntervalDuration == 0;


    Table* pTable = CreateTable(philosophersCount, minDurationEat, maxDurationEat,
                                isInfinityDuration);

    InitLogger(pTable);

    LOG("123");
    LOG("123 %d", 12);

    Log(FILE_NAME, "Введены данные, создание объектов, запуск потоков");

    MainWindow* pMainWindow = CreateMainWindow(
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            pTable,
            minSendIntervalDuration,
            maxSendIntervalDuration,
            isAutoSpawnDisabled);

    InitVideoMainWindow(pMainWindow);

    InitAndStartThreadsMainWindow(pMainWindow);

    Log(FILE_NAME, "Запуск главного цикла");
    return MainCycleMainWindow(pMainWindow);
}
