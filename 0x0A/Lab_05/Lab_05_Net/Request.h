#ifndef REQUEST_H
#define REQUEST_H

#include <stdint.h>

#include "Matrix.h"

typedef struct
{
    uint32_t FirstIndex;
    uint32_t SecondIndex;
    uint32_t Count;
    uint32_t MatrixDataSize;
} Request;

void HtoNRequest(Request* pRequest);

void NtoHRequest(Request* pRequest);

void FillRequest(Request* pRequest, Matrix* pMatrix, int firstIndex,
                 int secondIndex);

int SendRequest(SocketHandle sock, Request* pRequest);

int SendMatrix(SocketHandle sock, Request* pRequest, Matrix* pMatrix);

int ReceiveRequest(SocketHandle sock, Request* pRequest);

int ReceiveMatrix(SocketHandle sock, Request* pRequest, Matrix* pMatrix);

#endif //REQUEST_H
