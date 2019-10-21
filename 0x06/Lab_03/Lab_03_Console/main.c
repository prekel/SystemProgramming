#include <stdio.h>
#include <malloc.h>
#include <limits.h>

#include "Input.h"
#include "Actions.h"
#include "ArchipelagoCollection.h"

#define M_1E9 1000000000

bool check1(int n)
{
    return 2 <= n && n < M_1E9;
}

int main()
{

    ArchipelagoCollection* pCollection = ArchipelagoCollectionCreate();
    Action action;
    do
    {
        action = (Action) CycleInputInt("Введите номер действия: ", 3, NULL);
    } while (ActionsHandler(pCollection, action));
    return 0;
}
