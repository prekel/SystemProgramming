#include <stdio.h>
#include <stdlib.h>

#include "LastErrorMessage.h"
#include "Matrix.h"
#include "Socket.h"
#include "Request.h"
#include "Server.h"
#include "ReturnCodesLib.h"

int main(int argc, char** argv)
{
    int initializeSockets = InitializeSockets();
    if (initializeSockets != NO_ERROR)
    {
        PrintErrorMessage(initializeSockets);
        return EXIT_FAILURE;
    }

    Args* pArgs = ParseArgs(argc, argv);

    Matrix* pMatrix = NULL;
    Request request;
    if (Server(pArgs, &request, &pMatrix) != SUCCESSFUL)
    {
        PrintLastErrorMessage();
        DestroyMatrix(pMatrix);
        DestroyArgs(pArgs);
        ShutdownSockets();
        return EXIT_FAILURE;
    }

    Matrix* pMinor = GetMinor(NULL, pMatrix, request.FirstIndex, request.SecondIndex);

    int det = CalculateDeterminant(pMinor);

    for (int i = 0; i < pMinor->FirstCount; i++)
    {
        for (int j = 0; j < pMinor->SecondCount; j++)
        {
            printf("%d ", pMinor->pData[i][j]);
        }
        printf("\n");
    }
    printf("Определитель: %d", det);

    DestroyMatrix(pMatrix);
    DestroyMatrix(pMinor);

    DestroyArgs(pArgs);

    ShutdownSockets();

    return 0;
}
