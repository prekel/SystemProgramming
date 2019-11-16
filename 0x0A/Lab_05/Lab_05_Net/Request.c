#include <malloc.h>

#include "Socket.h"
#include "Macro.h"
#include "Matrix.h"
#include "Request.h"

void FillRequest(Request* pRequest, Matrix* pMatrix, int firstIndex,
                  int secondIndex)
{
    pRequest->NetFirstIndex = htonl(firstIndex);

    pRequest->NetSecondIndex = htonl(secondIndex);

    pRequest->NetCount = htonl(pMatrix->FirstCount);

    size_t matrixDataSize =
            (pMatrix->FirstCount * pMatrix->SecondCount) * sizeof(uint32_t);
    pRequest->NetMatrixDataSize = htonl(matrixDataSize);
}

int SendRequest(SocketHandle socket, Request* pRequest)
{
    return send(socket, pRequest, sizeof(Request), 0);
}

int SendMatrix(SocketHandle socket, Request* pRequest, Matrix* pMatrix)
{
    size_t size = pMatrix->FirstCount * pMatrix->SecondCount * sizeof(uint32_t);
    uint32_t* pBuf = (uint32_t*) malloc(size);

    int k = 0;
    for (int i = 0; i < pMatrix->FirstCount; i++)
    {
        for (int j = 0; j < pMatrix->SecondCount; j++)
        {
            pBuf[k++] = htonl(pMatrix->pData[i][j]);
        }
    }

    free(pBuf);

    return send(socket, pBuf, size, 0);
}

int ReceiveRequest(SocketHandle socket, Request* pRequest)
{
    return recv(socket, pRequest, sizeof(Request), 0);
}

int ReceiveMatrix(SocketHandle socket, Request* pRequest, Matrix* pMatrix)
{
    size_t size = ntohl(pRequest->NetMatrixDataSize);
    uint32_t* pBuf = (uint32_t*) malloc(size);
    recv(socket, pBuf, size, 0);

    pMatrix->FirstCount = pMatrix->SecondCount = ntohl(pRequest->NetCount);

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
