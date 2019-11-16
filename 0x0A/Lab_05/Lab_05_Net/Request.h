#ifndef REQUEST_H
#define REQUEST_H

#include <stdint.h>

#include "Matrix.h"

typedef struct
{
    uint32_t NetFirstIndex;
    uint32_t NetSecondIndex;
    uint32_t NetCount;
    uint32_t NetMatrixDataSize;
} Request;

void FillRequest(Request* pRequest, Matrix* pMatrix, int firstIndex,
                 int secondIndex);

int SendRequest(SocketHandle socket, Request* pRequest);

int SendMatrix(SocketHandle socket, Request* pRequest, Matrix* pMatrix);

int ReceiveRequest(SocketHandle socket, Request* pRequest);

int ReceiveMatrix(SocketHandle socket, Request* pRequest, Matrix* pMatrix);

#endif //REQUEST_H
