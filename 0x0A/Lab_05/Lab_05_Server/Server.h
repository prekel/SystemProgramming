#ifndef SERVER_H
#define SERVER_H

#include "Args.h"
#include "Matrix.h"
#include "Request.h"

int Server(Args* pArgs, Request* pRequest, Matrix** ppMatrix);

SocketHandle ServerConnect(Args* pArgs);

int ServerReceiveRequest(SocketHandle sock, Request* pRequest);

int ServerReceiveMatrix(SocketHandle sock, Request* pRequest,
                        Matrix* pMatrix);

int ServerClose(SocketHandle sock);

#endif //SERVER_H
