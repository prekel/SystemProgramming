/// \file
/// \brief Реализация функций из Client.h
/// \details Реализация функций из Client.h.

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
#include "Client.h"

int Client(Args* pArgs, Matrix* pMatrix)
{
    Request request;
    FillRequest(&request, pMatrix, pArgs->FirstIndex, pArgs->SecondIndex);

    RETURN_IF_SOCKET_ERROR(InitializeSockets());

    SocketHandle sock;
    RETURN_IF_SOCKET_ERROR(sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP));

    struct sockaddr_in name;
    name.sin_family = AF_INET;
    name.sin_port = htons((uint16_t) pArgs->Port);
    name.sin_addr.s_addr = inet_addr(pArgs->IpAddress);

    if (name.sin_addr.s_addr == INADDR_NONE)
    {
        return BAD_VALUE;
    }

    RETURN_AND_CLOSE_SOCKET_IF_SOCKET_ERROR(
            connect(sock,
                    (struct sockaddr*) &name,
                    sizeof(name)),
            sock);

    HtoNRequest(&request);
    RETURN_AND_CLOSE_SOCKET_IF_SOCKET_ERROR(
            SendRequest(sock, &request), sock);
    NtoHRequest(&request);

    RETURN_AND_CLOSE_SOCKET_IF_UNSUCCESSFUL(
            SendMatrix(sock, &request, pMatrix), sock);

    RETURN_IF_SOCKET_ERROR(closesocket(sock));

    ShutdownSockets();

    return SUCCESSFUL;
}
