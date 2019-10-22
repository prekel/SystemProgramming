/// \file
/// \brief Функции действий
/// \details Функции для действий и перечесление действий.

#ifndef ACTIONS_H
#define ACTIONS_H

#include <stdbool.h>

#include "ArchipelagoCollection.h"

#define ACTION_NUMBER_LENGTH 4

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

/// Чекер для вводимого номера действия
///
/// \param number Номер действия.
/// \return Истина если от ACTION_EXIT до ACTION_DEFAULT.
bool ActionNumberChecker(int number);

/// Исполняет действие.
///
/// \param pCollection Указатель на коллекцию архипелагов.
/// \param action Действие.
/// \return 0 если было действие выхода, 1 если действие успешно совершено,
/// -1 если неопознанное действие.
int ActionExec(ArchipelagoCollection* pCollection, Action action);

#endif //ACTIONS_H
