/// \file
/// \brief Реализация функций из Server.h
/// \details Реализация функций из Server.h.

#include "Socket.h"

#include "Server.h"
#include "Request.h"
#include "ReturnCodes.h"

int Server(Args* pArgs, Request* pRequest, Matrix** ppMatrixA,
           Matrix** ppMatrixB, SocketHandle* pSocketToClose1,
           SocketHandle* pSocketToClose2)
{
    SocketHandle receiveSock;
    RETURN_IF_SOCKET_ERROR(
            receiveSock = ServerConnect(pArgs, pSocketToClose1));
    if (pSocketToClose2) *pSocketToClose2 = receiveSock;

    Request request;
    RETURN_IF_SOCKET_ERROR(ServerReceiveRequest(receiveSock, &request));

    Matrix* pMatrixA = CreateEmptyMatrix(request.Degree,
                                         request.Degree);
    Matrix* pMatrixB = CreateEmptyMatrix(request.Degree,
                                         request.Degree);

    RETURN_IF_SOCKET_ERROR(
            ServerReceiveMatrix(receiveSock, &request, pMatrixA));
    RETURN_IF_SOCKET_ERROR(
            ServerReceiveMatrix(receiveSock, &request, pMatrixB));

    *pRequest = request;
    *ppMatrixA = pMatrixA;
    *ppMatrixB = pMatrixB;

    return SUCCESSFUL;
}

SocketHandle ServerConnect(Args* pArgs, SocketHandle* pSocketToClose)
{
    SocketHandle sock;
    RETURN_IF_SOCKET_ERROR(
            sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP));
    if (pSocketToClose) *pSocketToClose = sock;

    struct sockaddr_in name;
    name.sin_family = AF_INET;
    name.sin_port = htons((u_short) pArgs->Port);
    name.sin_addr.s_addr = INADDR_ANY;

    RETURN_IF_SOCKET_ERROR(
            bind(sock, (const struct sockaddr*) &name, sizeof (name)));

    return sock;
}

int ServerReceiveRequest(SocketHandle sock, Request* pRequest)
{
    RETURN_IF_SOCKET_ERROR(ReceiveRequest(sock, pRequest));
    NtoHRequest(pRequest);
    return SUCCESSFUL;
}

int ServerReceiveMatrix(SocketHandle sock, Request* pRequest,
                        Matrix* pMatrix)
{
    RETURN_IF_NOT_SUCCESSFUL(ReceiveMatrix(sock, pRequest, pMatrix));
    return SUCCESSFUL;
}
