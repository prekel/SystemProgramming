#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "Matrix.h"
#include "Socket.h"
#include "Request.h"
#include "Args.h"
#include "ParseInt.h"
#include "ReturnCodes.h"
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

    if (InputOrFillMatrix(pArgs, pMatrix))

    Request request;
    FillRequest(&request, pMatrix, pArgs->FirstIndex, pArgs->SecondIndex);

    InitializeSockets();

    SocketHandle sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in name;
    name.sin_family = AF_INET;
    name.sin_port = htons((uint16_t) pArgs->Port);
    name.sin_addr.s_addr = inet_addr(pArgs->IpAddress);

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
