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
    int initializeSockets = InitializeSockets();
    if (initializeSockets != NO_ERROR)
    {
        PrintErrorMessage(initializeSockets);
        return EXIT_FAILURE;
    }

    Args* pArgs = ParseArgs(argc, argv);
    if (pArgs == NULL)
    {
        PrintErrorMessage(ALLOCATION_ERROR);
        ShutdownSockets();
        return EXIT_FAILURE;
    }

    if (InputAllOption(pArgs) != SUCCESSFUL)
    {
        PrintErrorMessage(UNSUCCESSFUL);
        DestroyArgs(pArgs);
        ShutdownSockets();
        return EXIT_FAILURE;
    }

    Matrix* pMatrix = CreateEmptyMatrix(pArgs->Degree, pArgs->Degree);
    if (pMatrix == NULL)
    {
        PrintErrorMessage(ALLOCATION_ERROR);
        DestroyArgs(pArgs);
        ShutdownSockets();
        return EXIT_FAILURE;
    }

    int inputMatrix = InputOrFillMatrix(pArgs, pMatrix);
    if (inputMatrix < SUCCESSFUL)
    {
        perror(ReturnCodeLibMessage(inputMatrix));
        DestroyMatrix(pMatrix);
        DestroyArgs(pArgs);
        ShutdownSockets();
        return EXIT_FAILURE;
    }

    int clientReturn = Client(pArgs, pMatrix);

    if (clientReturn != SUCCESSFUL)
    {
        perror(ReturnCodeLibMessage(clientReturn));
        if (clientReturn == UNSUCCESSFUL)
        {
            PrintLastErrorMessage();
        }
        DestroyMatrix(pMatrix);
        DestroyArgs(pArgs);
        ShutdownSockets();
        return EXIT_FAILURE;
    }

    DestroyMatrix(pMatrix);
    DestroyArgs(pArgs);
    ShutdownSockets();

    return EXIT_SUCCESS;
}
