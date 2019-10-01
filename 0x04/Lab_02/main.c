/*! \file
 *  \brief Файл с функцией main
 *
 *  \details Главный файл содержащий главную функцию main.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
//#include <unistd.h>
//#include <wait.h>
#include <time.h>
#include <pthread.h>
#ifdef _WIN32
#include <windows.h>
#endif

#include "Input.h"
#include "Table.h"
#include "Utils.h"
#include "RealTimeTableStateThread.h"

/*! \brief Главная функция
 *
 *  \details Главная функция.
 *
 *  \param argc Кол-во переданных аргументов.
 *  \param argv Массив строк-аргументов.
 *  \return Целое число 0 в случае успешного завершения.
 */
int main(int argc, char** argv)
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    srand(time(NULL));

//    for (int i = 0; i < 100; i++)
//    {
//        struct timespec tw1 = RandomTime(5, 10);
//        printf("%lf\n", TimespecToDouble(&tw1));
//    }

    struct timespec twfd1 = TimespecFromDouble(1.23);
    struct timespec twfd2 = TimespecFromDouble(1.233243242);
    struct timespec twfd3 = TimespecFromDouble(0.1231);
    struct timespec twfd4 = TimespecFromDouble(0.1111111111111111111);
    struct timespec twfd5 = TimespecFromDouble(1.23456789012345);
    struct timespec twfd6 = TimespecFromDouble(0);
    struct timespec twfd7 = TimespecFromDouble(1.9999999999999999);
    struct timespec twfd8 = TimespecFromDouble(1.999999999);


    Table* pTable = CreateTable();

    struct timespec tw = {0, 200000000};
    RealTimeTableStateThreadOptions* pRealTimeTableStateOptions =
            CreateRealTimeTableStateThreadOptions(pTable, tw);
    pthread_t realTimeTableStateThreadId;
    pthread_create(
            &realTimeTableStateThreadId,
            NULL,
            RealTimeTableStateThread,
            pRealTimeTableStateOptions);

    DoEatAll(pTable);

    pthread_join(realTimeTableStateThreadId, NULL);
    DestroyRealTimeTableStateThreadOptions(pRealTimeTableStateOptions);

    DestroyTable(pTable);


//    int a = 0;
//    for (int i = 1; i <= 10; i++)
//    {
//        char* format = "%d:";
//        int len = snprintf(NULL, 0, format, a);
//        char* s = (char*) malloc(len + 1 * sizeof(char));
//        //FAILURE_IF_NULLPTR(s);
//        snprintf(s, len + 1, format, a);
//
//        a = CycleInputInt(s, 10, NULL);
//    }
//
//    CycleInputInt("Ваыва: ", 50, NULL);
//
//    //Структура содержащая время задержки
//    struct timespec tw = {5, 125000000};
//    //Структура, в которую будет помещен остаток времени
//    //задержки, если задержка будет прервана досрочно
//    struct timespec tr;
//    //Вывод сообщения о приостановки работы
//    puts("Приостановка работы на 5,125 секунды");
//    //Приостановка работы
//    nanosleep(&tw, &tr);
}