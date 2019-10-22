/// \file
/// \brief Главная функция программы
/// \details Главная функция программы.

#include <stdio.h>
#include <stdbool.h>

#ifdef WIN32
#include <Windows.h>
#endif

#include "Input.h"
#include "Actions.h"
#include "ArchipelagoCollection.h"

/// Главная функция программы.
///
/// \param argc Кол-во аргументов.
/// \param argv Массив аргументов.
/// \return 0 в случае успешного завершения программы.
int main(int argc, char** argv)
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
