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

int main(int argc, char** argv)
{
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

    Request request;
    FillRequest(&request, pMatrix, pArgs->FirstIndex, pArgs->SecondIndex);

    if (InitializeSockets() == SOCKET_ERROR)
    {
        perror(LastErrorMessage());
        return EXIT_FAILURE;
    }

    SocketHandle sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == SOCKET_ERROR)
    {
        perror(LastErrorMessage());
        ShutdownSockets();
        return EXIT_FAILURE;
    }

    struct sockaddr_in name;
    name.sin_family = AF_INET;
    name.sin_port = htons((uint16_t) pArgs->Port);
    name.sin_addr.s_addr = inet_addr(pArgs->IpAddress);

    if (name.sin_addr.s_addr == INADDR_NONE)
    {
        perror(ErrorMessage(BAD_VALUE));
        closesocket(sock);
        ShutdownSockets();
        return EXIT_FAILURE;
    }

    if (connect(sock, (struct sockaddr*) &name, sizeof(name)) == SOCKET_ERROR)
    {
        perror(LastErrorMessage());
        closesocket(sock);
        ShutdownSockets();
        return EXIT_FAILURE;
    }

    HtoNRequest(&request);
    SendRequest(sock, &request);
    NtoHRequest(&request);

    SendMatrix(sock, &request, pMatrix);

    closesocket(sock);
    ShutdownSockets();

    return EXIT_SUCCESS;
}
