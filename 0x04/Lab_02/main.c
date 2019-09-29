/*! \file
 *  \brief Файл с функцией main
 *
 *  \details Главный файл содержащий главную функцию main.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>
#include <pthread.h>

#include "Input.h"
#include "Table.h"
#include "Utils.h"

Table* g_pTable;

char ForkToChar(Fork* fork)
{
    if (fork->IsInUse)
        return ',';
    else
        return '.';
}
char PhToChar(Philosopher* fork)
{
    if (fork->IsEating)
        return '=';
    if (fork->IsWaiting)
        return '?';
    else
        return '_';
}

void* outinfo(void* _)
{
    struct timespec tw = {0, 200000000};
    int k = 0;
    while (k <= 10)
    {
        if (g_pTable->IsEatingEnded)
        {
            k++;
        }
        nanosleep(&tw, NULL);
        for (int i = 0; i < 5; i++)
        {
            fprintf(stderr, "%c%c", PhToChar
            (g_pTable->Philosophers[i]),
                    ForkToChar(g_pTable->Forks[i]));
        }
        fprintf(stderr, "\n");
    }
    return NULL;
}

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
    srand(time(NULL));

//    for (int i = 0; i < 100; i++)
//    {
//        struct timespec tw1 = RandomTime(5, 10);
//        printf("%lf\n", TimespecToDouble(&tw1));
//    }


    Table* pTable = CreateTable();

    g_pTable = pTable;
    pthread_t threadId;
    pthread_create(&threadId, NULL, outinfo, NULL);

    DoEatAll1(pTable);

    pthread_join(threadId, NULL);

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