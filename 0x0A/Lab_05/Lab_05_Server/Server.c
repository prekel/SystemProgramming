/// \file
/// \brief Реализация функций из Server.h
/// \details Реализация функций из Server.h.

#include <malloc.h>
#include <assert.h>

#include "Socket.h"

#include "Server.h"
#include "Request.h"
#include "ReturnCodes.h"

int Server(Args* pArgs, Request* pRequest, Matrix** ppMatrixA,
           Matrix** ppMatrixB, char** pClientAddressStr,
           SocketHandle* pSocketToClose)
{
    SocketHandle receiveSock;
    RETURN_IF_SOCKET_ERROR(
            receiveSock = ServerConnect(pArgs));
    if (pSocketToClose) *pSocketToClose = receiveSock;

    struct sockaddr clientAddress;
    socklen_t addressLength;

    Request request;
    RETURN_IF_SOCKET_ERROR(ServerReceiveRequest(receiveSock,
                                                &request,
                                                &clientAddress,
                                                &addressLength));

    struct sockaddr_in* clientAddressIn =
            (struct sockaddr_in*) &clientAddress;

    assert(pClientAddressStr);
    *pClientAddressStr = (char*) malloc(INET_ADDRSTRLEN);
    if (*pClientAddressStr == NULL)
    {
        return ALLOCATION_ERROR;
    }
    if (inet_ntop(clientAddressIn->sin_family,
                  &clientAddressIn->sin_addr,
                  *pClientAddressStr,
                  addressLength) == NULL)
    {
        return UNSUCCESSFUL;
    }

    Matrix* pMatrixA = CreateEmptyMatrix(request.Degree, request.Degree);
    Matrix* pMatrixB = CreateEmptyMatrix(request.Degree, request.Degree);

    RETURN_IF_SOCKET_ERROR(
            ServerReceiveMatrix(receiveSock, &request, pMatrixA));
    RETURN_IF_SOCKET_ERROR(
            ServerReceiveMatrix(receiveSock, &request, pMatrixB));

    assert(pRequest);
    *pRequest = request;
    assert(ppMatrixA);
    *ppMatrixA = pMatrixA;
    assert(ppMatrixB);
    *ppMatrixB = pMatrixB;

    return SUCCESSFUL;
}

SocketHandle ServerConnect(Args* pArgs)
{
    SocketHandle sock;
    RETURN_IF_SOCKET_ERROR(
            sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP));

    struct sockaddr_in name;
    name.sin_family = AF_INET;
    name.sin_port = htons((u_short) pArgs->Port);
    name.sin_addr.s_addr = INADDR_ANY;

    RETURN_IF_SOCKET_ERROR(
            bind(sock, (const struct sockaddr*) &name, sizeof(name)));

    return sock;
}

int ServerReceiveRequest(SocketHandle sock, Request* pRequest,
                         struct sockaddr* pClientAddress,
                         socklen_t* pAddressLength)
{
    RETURN_IF_SOCKET_ERROR(
            ReceiveRequest(sock, pRequest, pClientAddress,
                           pAddressLength));
    NtoHRequest(pRequest);
    return SUCCESSFUL;
}

int ServerReceiveMatrix(SocketHandle sock, Request* pRequest,
                        Matrix* pMatrix)
{
    RETURN_IF_NOT_SUCCESSFUL(ReceiveMatrix(sock, pRequest, pMatrix));
    return SUCCESSFUL;
}
