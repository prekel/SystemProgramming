#ifndef AUTOEATTHREAD_H
#define AUTOEATTHREAD_H

#include <stdbool.h>

#include "Table.h"

typedef struct
{
    Table* pTable;
    //bool IsMustStop;
} AutoEatThreadOptions;

AutoEatThreadOptions* CreateAutoEatThreadOptions(Table* pTable);

void DestroyAutoEatThreadOptions(AutoEatThreadOptions* pOptions);

void* AutoEatThread(void* pAutoEatThreadOptions);

#endif // AUTOEATTHREAD_H
