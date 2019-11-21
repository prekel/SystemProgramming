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

#define BACKLOG 5

SocketHandle ServerConnect(Args* pArgs, SocketHandle* pSocketToClose)
{
    SocketHandle sock;
    RETURN_IF_SOCKET_ERROR(
            sock = socket(AF_INET, pArgs->SocketType, pArgs->IpProto));
    if (pSocketToClose) *pSocketToClose = sock;

    struct sockaddr_in name;
    name.sin_family = AF_INET;
    name.sin_port = htons((u_short) pArgs->Port);
    name.sin_addr.s_addr = INADDR_ANY;

    RETURN_IF_SOCKET_ERROR(
            bind(sock, (const struct sockaddr*) &name, sizeof (name)));

    if (!pArgs->IsTcp)
    {
        return sock;
    }

    RETURN_IF_SOCKET_ERROR(listen(sock, BACKLOG));

    struct sockaddr_in clientName;
#ifdef _WIN32
    int clientNameLength;
#else
    unsigned int clientNameLength;
#endif
    clientNameLength = sizeof (clientName);
    SocketHandle clientSock;

    RETURN_IF_SOCKET_ERROR(
            clientSock = accept(sock,
                                (struct sockaddr*) &clientName,
                                &clientNameLength));

    return clientSock;
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
