#ifndef ACTIONS_H
#define ACTIONS_H

#include "ArchipelagoCollection.h"

typedef enum Action
{
    ACTION_EXIT = 0,
    ACTION_ADD = 1,
    ACTION_MODIFY_NAME,
    ACTION_MODIFY_COUNT_ISLANDS,
    ACTION_MODIFY_COUNT_INHABITED_ISLANDS,
    ACTION_DELETE,
    ACTION_PRINT,
    ACTION_PRINT_ALL,
    ACTION_HAS_ONLY_UNINHABITED,
    ACTION_PRINT_WHERE_ISLANDS_COUNT_IS,
    ACTION_HELP,
    ACTION_DEFAULT
} Action;

int ActionExec(ArchipelagoCollection* pCollection, Action action);

char* ActionInfo(Action action);

#endif //ACTIONS_H
