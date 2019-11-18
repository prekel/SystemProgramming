/// \file
/// \brief Реализация функций из Server.h
/// \details Реализация функций из Server.h.

#include "Socket.h"

#include "Server.h"
#include "Request.h"
#include "ReturnCodes.h"

int Server(Args* pArgs, Request* pRequest, Matrix** ppMatrix)
{
    SocketHandle clientSock;
    RETURN_IF_SOCKET_ERROR(clientSock = ServerConnect(pArgs));

    Request request;
    RETURN_AND_CLOSE_SOCKET_IF_SOCKET_ERROR(
            ServerReceiveRequest(clientSock, &request), clientSock);

    Matrix* pMatrix = CreateEmptyMatrix(request.Count,
                                        request.Count);

    RETURN_AND_CLOSE_SOCKET_IF_SOCKET_ERROR(
            ServerReceiveMatrix(clientSock, &request, pMatrix), clientSock);

    RETURN_IF_SOCKET_ERROR(ServerClose(clientSock));

    *pRequest = request;
    *ppMatrix = pMatrix;

    return SUCCESSFUL;
}

#define BACKLOG 5

SocketHandle ServerConnect(Args* pArgs)
{
    SocketHandle sock;
    RETURN_IF_SOCKET_ERROR(sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP));

    struct sockaddr_in name;
    name.sin_family = AF_INET;
    name.sin_port = htons((u_short) pArgs->Port);
    name.sin_addr.s_addr = INADDR_ANY;

    RETURN_AND_CLOSE_SOCKET_IF_SOCKET_ERROR(
            bind(sock, (const struct sockaddr*) &name, sizeof(name)), sock);

    RETURN_AND_CLOSE_SOCKET_IF_SOCKET_ERROR(listen(sock, BACKLOG), sock);

    struct sockaddr_in clientName;
    unsigned int clientNameLength = sizeof(clientName);
    SocketHandle clientSock;

    RETURN_AND_CLOSE_SOCKET_IF_SOCKET_ERROR(
            clientSock =
                    accept(sock,
                           (struct sockaddr*) &clientName,
                           &clientNameLength),
            sock);

    RETURN_IF_SOCKET_ERROR(closesocket(sock));

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
    RETURN_IF_SOCKET_ERROR(ReceiveMatrix(sock, pRequest, pMatrix));
    return SUCCESSFUL;
}

int ServerClose(SocketHandle sock)
{
    RETURN_IF_SOCKET_ERROR(closesocket(sock));
    return SUCCESSFUL;
}
