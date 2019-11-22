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

int Client(Args* pArgs, Matrix* pMatrixA, Matrix* pMatrixB,
           SocketHandle* pSocketToClose)
{
    Request request;
    FillRequest(&request, pMatrixA->FirstCount, MATRICES_COUNT);

    RETURN_IF_SOCKET_ERROR(InitializeSockets());

    SocketHandle sock;
    RETURN_IF_SOCKET_ERROR(
            sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP));
    if (pSocketToClose) *pSocketToClose = sock;

    struct sockaddr_in name;
    name.sin_family = AF_INET;
    name.sin_port = htons((uint16_t) pArgs->Port);
    name.sin_addr.s_addr = inet_addr(pArgs->IpAddress);

    if (name.sin_addr.s_addr == INADDR_NONE)
    {
        return BAD_VALUE;
    }

    RETURN_IF_SOCKET_ERROR(connect(sock,
                                   (struct sockaddr*) &name,
                                   sizeof(name)));

    HtoNRequest(&request);
    RETURN_IF_SOCKET_ERROR(SendRequest(sock, &request));
    NtoHRequest(&request);

    RETURN_IF_SOCKET_ERROR(SendMatrix(sock, &request, pMatrixA));
    RETURN_IF_SOCKET_ERROR(SendMatrix(sock, &request, pMatrixB));

    return SUCCESSFUL;
}
