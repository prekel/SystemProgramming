#include <malloc.h>

#include "Socket.h"
#include "ReturnCodes.h"
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

int SendRequest(SocketHandle sock, Request* pRequest)
{
    RETURN_IF_SOCKET_ERROR(send(sock, pRequest, sizeof(Request), MSG_NOSIGNAL));
    return SUCCESSFUL;
}

int SendMatrix(SocketHandle sock, Request* pRequest, Matrix* pMatrix)
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

    RETURN_IF_NOT_SUCCESSFUL(send(sock, pBuf, size, MSG_NOSIGNAL));

    free(pBuf);

    return SUCCESSFUL;
}

int ReceiveRequest(SocketHandle sock, Request* pRequest)
{
    RETURN_IF_SOCKET_ERROR(recv(sock, pRequest, sizeof(Request), 0));
    return SUCCESSFUL;
}

int ReceiveMatrix(SocketHandle sock, Request* pRequest, Matrix* pMatrix)
{
    size_t size = pRequest->MatrixDataSize;
    uint32_t* pBuf = (uint32_t*) malloc(size);
    RETURN_IF_SOCKET_ERROR(recv(sock, pBuf, size, 0));

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
