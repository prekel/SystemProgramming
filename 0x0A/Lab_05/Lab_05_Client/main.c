/// \file
/// \brief Главная функция клиента
/// \details Главная функция клиента (вариант 17).

#include <errno.h>
#include <stdlib.h>

#include "Socket.h"
#include "Matrix.h"
#include "Args.h"
#include "ReturnCodes.h"
#include "LastErrorMessage.h"
#include "Client.h"

/// Главная функция клиента. Вариант 17.
///
/// \param argc Кол-во аргументов.
/// \param argv Массив аргументов.
/// \return EXIT_SUCCESS (0) в случае успеха,
/// EXIT_FAILURE (1) в случае неудачи.
int main(int argc, char** argv)
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    Args* pArgs = ParseArgs(argc, argv);
    if (pArgs == NULL)
    {
        PrintErrorMessage(ALLOCATION_ERROR);
        return EXIT_FAILURE;
    }
    if (pArgs->IsHelpGiven)
    {
        PrintHelp();
        DestroyArgs(pArgs);
        return EXIT_SUCCESS;
    }

    if (InputAllOption(pArgs) != SUCCESSFUL)
    {
        PrintErrorMessage(UNSUCCESSFUL);
        DestroyArgs(pArgs);
        return EXIT_FAILURE;
    }

    Matrix* pMatrix = CreateEmptyMatrix(pArgs->Degree, pArgs->Degree);
    if (pMatrix == NULL)
    {
        PrintErrorMessage(ALLOCATION_ERROR);
        DestroyArgs(pArgs);
        return EXIT_FAILURE;
    }

    int inputMatrix = InputOrFillMatrix(pArgs, pMatrix);
    if (inputMatrix < SUCCESSFUL)
    {
        PrintReturnCodeMessage(inputMatrix);
        DestroyMatrix(pMatrix);
        DestroyArgs(pArgs);
        return EXIT_FAILURE;
    }

    int initializeSockets = InitializeSockets();
    if (initializeSockets != NO_ERROR)
    {
        PrintErrorMessage(initializeSockets);
        DestroyMatrix(pMatrix);
        DestroyArgs(pArgs);
        return EXIT_FAILURE;
    }

    SocketHandle socketToClose;
    int clientReturn = Client(pArgs, pMatrix, &socketToClose);

    if (clientReturn != SUCCESSFUL)
    {
        PrintReturnCodeMessage(clientReturn);
        closesocket(socketToClose);
        DestroyMatrix(pMatrix);
        DestroyArgs(pArgs);
        ShutdownSockets();
        return EXIT_FAILURE;
    }

    closesocket(socketToClose);
    DestroyMatrix(pMatrix);
    DestroyArgs(pArgs);
    ShutdownSockets();

    return EXIT_SUCCESS;
}
