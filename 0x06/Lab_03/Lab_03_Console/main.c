#include <stdio.h>
#include <stdbool.h>

#ifdef WIN32
#include <Windows.h>
#endif

#include "Input.h"
#include "Actions.h"
#include "ArchipelagoCollection.h"

bool ActionNumberChecker(int number)
{
    return ACTION_EXIT <= number && number < ACTION_DEFAULT;
}

#define ACTION_NUMBER_LENGTH 4

int main()
{
#ifdef WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    ActionExec(NULL, ACTION_HELP);

    ArchipelagoCollection* pCollection = ArchipelagoCollectionCreate();

    Action action;
    do
    {
        action = (Action) CycleInputInt(
                ACTION_NUMBER_LENGTH,
                ActionNumberChecker, "Введите номер действия: ");
    } while (ActionExec(pCollection, action));

    ArchipelagoCollectionDestroyArchipelagos(pCollection);
    ArchipelagoCollectionDestroy(pCollection);

    return 0;
}
