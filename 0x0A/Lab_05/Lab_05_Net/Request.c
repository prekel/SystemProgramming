#include <malloc.h>

#include "Socket.h"
#include "ReturnCodesLib.h"
#include "Matrix.h"
#include "Request.h"

void FillRequest(Request* pRequest, Matrix* pMatrix, int firstIndex,
                 int secondIndex)
{
    pRequest->FirstIndex = firstIndex;

    pRequest->SecondIndex = secondIndex;

    pRequest->Count = pMatrix->FirstCount;

    size_t matrixDataSize =
            (pMatrix->FirstCount * pMatrix->SecondCount) * sizeof(uint32_t);
    pRequest->MatrixDataSize = matrixDataSize;
}

void HtoNRequest(Request* pRequest)
{
    for (uint32_t* i = &(pRequest->FirstIndex);
         i != &(pRequest->MatrixDataSize) + 1;
         i++)
    {
        *i = htonl(*i);
    }
}

void NtoHRequest(Request* pRequest)
{
    for (uint32_t* i = &(pRequest->FirstIndex);
         i != &(pRequest->MatrixDataSize) + 1;
         i++)
    {
        *i = ntohl(*i);
    }
}

int SendRequest(SocketHandle socket, Request* pRequest)
{
    return send(socket, pRequest, sizeof(Request), 0);
}

int SendMatrix(SocketHandle socket, Request* pRequest, Matrix* pMatrix)
{
    size_t size =
            pMatrix->FirstCount * pMatrix->SecondCount * sizeof(uint32_t);
    uint32_t* pBuf = (uint32_t*) malloc(size);

    int k = 0;
    for (int i = 0; i < pMatrix->FirstCount; i++)
    {
        for (int j = 0; j < pMatrix->SecondCount; j++)
        {
            pBuf[k++] = htonl(pMatrix->pData[i][j]);
        }
    }

    RETURN_IF_NOT_SUCCESSFUL(send(socket, pBuf, size, 0));

    free(pBuf);

    return SUCCESSFUL;
}

int ReceiveRequest(SocketHandle socket, Request* pRequest)
{
    return recv(socket, pRequest, sizeof(Request), 0);
}

int ReceiveMatrix(SocketHandle socket, Request* pRequest, Matrix* pMatrix)
{
    size_t size = pRequest->MatrixDataSize;
    uint32_t* pBuf = (uint32_t*) malloc(size);
    recv(socket, pBuf, size, 0);

    pMatrix->FirstCount = pMatrix->SecondCount = pRequest->Count;

    int k = 0;
    for (int i = 0; i < pMatrix->FirstCount; i++)
    {
        for (int j = 0; j < pMatrix->SecondCount; j++)
        {
            pMatrix->pData[i][j] = ntohl(pBuf[k++]);
        }
    }

    free(pBuf);

    return NO_ERROR;
}
