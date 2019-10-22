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

    for (Action i = ACTION_EXIT; i < ACTION_DEFAULT; i++)
    {
        printf("Введите %d %s\n", i, ActionInfo(i));
    }
    printf("\n");
    fflush(stdout);

    ArchipelagoCollection* pCollection = ArchipelagoCollectionCreate();
    Action action;
    do
    {
        fflush(stdout);
        action = (Action) CycleInputInt("Введите номер действия: ",
                                        4,
                                        NULL);
        fflush(stdout);
    } while (ActionsHandler(pCollection, action));
    fflush(stdout);
    ArchipelagoCollectionDestroy(pCollection);
    return 0;
}
