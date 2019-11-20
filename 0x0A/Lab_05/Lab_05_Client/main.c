/// \file
/// \brief Главная функция клиента
/// \details Главная функция клиента (вариант 16).

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#include "Socket.h"
#include "Matrix.h"
#include "Args.h"
#include "ReturnCodes.h"
#include "LastErrorMessage.h"
#include "Client.h"

/// Главная функция клиента. Вариант 16.
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
    if (pArgs->IsUnknownOptionGiven)
    {
        UnknownOption(pArgs);
    }

    if (InputAllOption(pArgs) != SUCCESSFUL)
    {
        PrintErrorMessage(UNSUCCESSFUL);
        DestroyArgs(pArgs);
        return EXIT_FAILURE;
    }

    Matrix* pMatrixA = CreateEmptyMatrix(pArgs->Degree, pArgs->Degree);
    Matrix* pMatrixB = CreateEmptyMatrix(pArgs->Degree, pArgs->Degree);
    if (pMatrixA == NULL || pMatrixB == NULL)
    {
        PrintErrorMessage(ALLOCATION_ERROR);
        DestroyMatrix(pMatrixA);
        DestroyMatrix(pMatrixB);
        DestroyArgs(pArgs);
        return EXIT_FAILURE;
    }

    int inputMatrix = InputOrFillMatrices(pArgs, pMatrixA, pMatrixB);
    if (inputMatrix < SUCCESSFUL)
    {
        PrintReturnCodeMessage(inputMatrix);
        DestroyMatrix(pMatrixA);
        DestroyMatrix(pMatrixB);
        DestroyArgs(pArgs);
        return EXIT_FAILURE;
    }

    int initializeSockets = InitializeSockets();
    if (initializeSockets != NO_ERROR)
    {
        PrintErrorMessage(initializeSockets);
        DestroyMatrix(pMatrixA);
        DestroyMatrix(pMatrixB);
        DestroyArgs(pArgs);
        return EXIT_FAILURE;
    }

    printf("Введённые матрицы: \n");
    printf("Матрица A: \n");
    PrintMatrix(pMatrixA);
    printf("Матрица B: \n");
    PrintMatrix(pMatrixB);

    printf("\nПередача на %s:%d по протоколу %s...\n",
           pArgs->IpAddress, pArgs->Port, pArgs->Protocol);

    SocketHandle socketToClose;
    int clientReturns = Client(pArgs, pMatrixA, pMatrixB, &socketToClose);

    if (clientReturns != SUCCESSFUL)
    {
        PrintReturnCodeMessage(clientReturns);
        closesocket(socketToClose);
        DestroyMatrix(pMatrixA);
        DestroyMatrix(pMatrixB);
        DestroyArgs(pArgs);
        ShutdownSockets();
        return EXIT_FAILURE;
    }

    printf("Успешно передано.\n");

    if (closesocket(socketToClose) == SOCKET_ERROR)
    {
        PrintLastErrorMessage();
        DestroyMatrix(pMatrixA);
        DestroyMatrix(pMatrixB);
        DestroyArgs(pArgs);
        ShutdownSockets();
        return EXIT_FAILURE;
    }
    DestroyMatrix(pMatrixA);
    DestroyMatrix(pMatrixB);
    DestroyArgs(pArgs);
    ShutdownSockets();

    return EXIT_SUCCESS;
}
