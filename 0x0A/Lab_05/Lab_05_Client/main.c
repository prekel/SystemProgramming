#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "Matrix.h"
#include "Socket.h"
#include "Request.h"
#include "Args.h"
#include "ParseInt.h"
#include "ReturnCodesLib.h"
#include "Input.h"
#include "LastErrorMessage.h"
#include "Client.h"

int main(int argc, char** argv)
{
    if (InitializeSockets() == SOCKET_ERROR)
    {
        PrintLastErrorMessage();
        return EXIT_FAILURE;
    }

    Args* pArgs = ParseArgs(argc, argv);
    if (pArgs == NULL)
    {
        perror(ALLOCATION_ERROR_MESSAGE);
        return EXIT_FAILURE;
    }

    if (InputAllOption(pArgs) != SUCCESSFUL)
    {
        perror(UNKNOWN_ERROR_MESSAGE);
        return EXIT_FAILURE;
    }

    Matrix* pMatrix = CreateEmptyMatrix(pArgs->Degree, pArgs->Degree);
    if (pMatrix == NULL)
    {
        perror(ALLOCATION_ERROR_MESSAGE);
        return EXIT_FAILURE;
    }

    int inputMatrix = InputOrFillMatrix(pArgs, pMatrix);
    if (inputMatrix < SUCCESSFUL)
    {
        perror(ReturnCodeLibMessage(inputMatrix));
        return EXIT_FAILURE;
    }

    int clientReturn = Client(pArgs, pMatrix);

    if (clientReturn != SUCCESSFUL)
    {
        perror(ErrorMessage(clientReturn));
        if (clientReturn == UNSUCCESSFUL)
        {
            perror(LastErrorMessage());
        }
        return EXIT_FAILURE;
    }

    DestroyMatrix(pMatrix);
    ShutdownSockets();

    return EXIT_SUCCESS;
}
