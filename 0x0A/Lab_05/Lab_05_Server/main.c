/// \file
/// \brief Главная функция сервера
/// \details Главная функция сервера (вариант 17).

#include <stdio.h>
#include <stdlib.h>

#include "LastErrorMessage.h"
#include "Matrix.h"
#include "Socket.h"
#include "Request.h"
#include "Server.h"
#include "ReturnCodes.h"

/// Главная функция сервера. Вариант 17.
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

    int initializeSockets = InitializeSockets();
    if (initializeSockets != NO_ERROR)
    {
        PrintErrorMessage(initializeSockets);
        DestroyArgs(pArgs);
        return EXIT_FAILURE;
    }

    printf("Сервер запущен, ожидание подключения и приёма данных на "
           "порт %d по протоколу %s...\n", pArgs->Port, pArgs->Protocol);

    Matrix* pMatrixA = NULL;
    Matrix* pMatrixB = NULL;
    Request request;
    SocketHandle socketToClose1;
    SocketHandle socketToClose2;
    int serverReturns = Server(pArgs, &request, &pMatrixA, &pMatrixB,
                               &socketToClose1,
                               &socketToClose2);
    if (serverReturns != SUCCESSFUL)
    {
        PrintReturnCodeMessage(serverReturns);
        if (closesocket(socketToClose1) == SOCKET_ERROR)
        {
            PrintLastErrorMessage();
        }
        if (closesocket(socketToClose2) == SOCKET_ERROR)
        {
            PrintLastErrorMessage();
        }
        DestroyMatrix(pMatrixA);
        DestroyMatrix(pMatrixB);
        DestroyArgs(pArgs);
        ShutdownSockets();
        return EXIT_FAILURE;
    }

    printf("Принятые матрицы: \n");
    printf("Матрица A: \n");
    PrintMatrix(pMatrixA);
    printf("Матрица B: \n");
    PrintMatrix(pMatrixB);

    Matrix* pSum = SumMatrices(NULL, pMatrixA, pMatrixB);

    printf("\nМатрица A+B: \n");
    PrintMatrix(pSum);

    int det = CalculateDeterminant(pSum);
    printf("\nОпределитель: %d\n", det);

    if (closesocket(socketToClose1) == SOCKET_ERROR)
    {
        PrintReturnCodeMessage(SOCKET_ERROR);
        DestroyMatrix(pMatrixA);
        DestroyMatrix(pMatrixB);
        DestroyMatrix(pSum);
        DestroyArgs(pArgs);
        ShutdownSockets();
        return EXIT_SUCCESS;
    }
    if (socketToClose1 != socketToClose2 &&
        closesocket(socketToClose2) == SOCKET_ERROR)
    {
        PrintReturnCodeMessage(SOCKET_ERROR);
        DestroyMatrix(pMatrixA);
        DestroyMatrix(pMatrixB);
        DestroyMatrix(pSum);
        DestroyArgs(pArgs);
        ShutdownSockets();
        return EXIT_SUCCESS;
    }

    DestroyMatrix(pMatrixA);
    DestroyMatrix(pMatrixB);
    DestroyMatrix(pSum);

    DestroyArgs(pArgs);

    ShutdownSockets();

    return EXIT_SUCCESS;
}
