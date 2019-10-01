#include <malloc.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "AutoEatThread.h"
#include "Utils.h"
#include "RealTimeTableStateThread.h"

AutoEatThreadOptions* CreateAutoEatThreadOptions(Table* pTable)
{
    AutoEatThreadOptions* pOptions = (AutoEatThreadOptions*) malloc(sizeof(AutoEatThreadOptions));
    pOptions->pTable = pTable;
    return pOptions;
}

void DestroyAutoEatThreadOptions(AutoEatThreadOptions* pOptions)
{
    free(pOptions);
}

void* AutoEatThread(void* pAutoEatThreadOptions)
{
    AutoEatThreadOptions* pOptions = (AutoEatThreadOptions*)pAutoEatThreadOptions;

    srand(time(NULL));
    pOptions->pTable->IsEatingStarted = true;

    for (int i = 0; i < 20000000; i++)
    {
        struct timespec twb = RandomTime(pOptions->pTable->MinSendIntervalDuration, pOptions->pTable->MaxSendIntervalDuration);

        int c = RandomInterval(0, PHILOSOPHERS_COUNT);
        Philosopher* ph = pOptions->pTable->ppPhilosophers[c];

        if (Eat1(pOptions->pTable, ph, twb, i) == 1)
        {

            //continue;
        }

        LogTableInfo(pOptions->pTable);
        printf("[pid: 0x%08lx, philosopherId: %d, i: %d] Задержка перед отправкой следующего %lf сек.\n",
               pthread_self(), ph->PhilosopherId, i, TimespecToDouble(&twb));
        nanosleep(&twb, NULL);
    }

    pOptions->pTable->IsEatingEnded = true;
}