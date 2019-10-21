#include <stdio.h>
#include <malloc.h>
#include <limits.h>

#ifdef WIN32
#include <Windows.h>
#endif

#include "Input.h"
#include "Actions.h"
#include "ArchipelagoCollection.h"

int main()
{
#ifdef WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    ArchipelagoCollection* pCollection = ArchipelagoCollectionCreate();
    Action action;
    do
    {
        action = (Action) CycleInputInt("Введите номер действия: ", 4, NULL);
    } while (ActionsHandler(pCollection, action));
    ArchipelagoCollectionDestroy(pCollection);
    return 0;
}
