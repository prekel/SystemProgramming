/// \file
/// \brief Главная функция сервера
/// \details Главная функция сервера (вариант 17).

#include <stdio.h>
#include <stdlib.h>

//#ifdef _MSC_VER
//#include <Windows.h>
//#elif _WIN32
//#include <windows.h>
//#endif

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

    int initializeSockets = InitializeSockets();
    if (initializeSockets != NO_ERROR)
    {
        PrintErrorMessage(initializeSockets);
        DestroyArgs(pArgs);
        return EXIT_FAILURE;
    }

    Matrix* pMatrix = NULL;
    Request request;
    SocketHandle socketToClose1;
    SocketHandle socketToClose2;
    if (Server(pArgs, &request, &pMatrix, &socketToClose1, &socketToClose2)
        != SUCCESSFUL)
    {
        PrintLastErrorMessage();
        closesocket(socketToClose1);
        closesocket(socketToClose2);
        DestroyMatrix(pMatrix);
        DestroyArgs(pArgs);
        ShutdownSockets();
        return EXIT_FAILURE;
    }

    Matrix* pMinor = GetMinor(NULL,
                              pMatrix,
                              request.FirstIndex,
                              request.SecondIndex);

    int det = CalculateDeterminant(pMinor);

    for (int i = 0; i < pMinor->FirstCount; i++)
    {
        for (int j = 0; j < pMinor->SecondCount; j++)
        {
            printf("%d ", pMinor->pData[i][j]);
        }
        printf("\n");
    }
    printf("Определитель: %d\n", det);

    closesocket(socketToClose1);
    closesocket(socketToClose2);

    DestroyMatrix(pMatrix);
    DestroyMatrix(pMinor);

    DestroyArgs(pArgs);

    ShutdownSockets();

    return 0;
}
