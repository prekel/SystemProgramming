/// \file
/// \brief Реализация функций из Request.h
/// \details Реализация функций из Request.h.

#include <malloc.h>

#include "Socket.h"
#include "ReturnCodes.h"
#include "Matrix.h"
#include "Request.h"

void FillRequest(Request* pRequest, int degree, int count)
{
    pRequest->Degree = degree;

    pRequest->CountMatrices = count;

    pRequest->MatrixDataSize = degree * degree * count * sizeof (uint32_t);
}

void HtoNRequest(Request* pRequest)
{
    for (uint32_t* i = &(pRequest->Degree);
         i != &(pRequest->MatrixDataSize) + 1;
         i++)
    {
        *i = htonl(*i);
    }
}

void NtoHRequest(Request* pRequest)
{
    for (uint32_t* i = &(pRequest->Degree);
         i != &(pRequest->MatrixDataSize) + 1;
         i++)
    {
        *i = ntohl(*i);
    }
}

int SendRequest(SocketHandle sock, Request* pRequest)
{
    RETURN_UNSUCCESSFUL_IF_NOT_EQUAL(
            send(sock, pRequest, sizeof (Request), MSG_NOSIGNAL),
            sizeof (Request));
    return SUCCESSFUL;
}

int SendMatrix(SocketHandle sock, Request* pRequest, Matrix* pMatrix)
{
    uint32_t* pBuf = (uint32_t*) malloc(pRequest->MatrixDataSize);
    if (pBuf == NULL)
    {
        return ALLOCATION_ERROR;
    }

    int k = 0;
    for (int i = 0; i < pMatrix->FirstCount; i++)
    {
        for (int j = 0; j < pMatrix->SecondCount; j++)
        {
            pBuf[k++] = htonl(pMatrix->ppData[i][j]);
        }
    }

    RETURN_UNSUCCESSFUL_IF_NOT_EQUAL(
            send(sock, pBuf, pRequest->MatrixDataSize, MSG_NOSIGNAL),
            pRequest->MatrixDataSize);

    free(pBuf);

    return SUCCESSFUL;
}

int ReceiveRequest(SocketHandle sock, Request* pRequest)
{
    RETURN_UNSUCCESSFUL_IF_NOT_EQUAL(recv(sock, pRequest, sizeof (Request), 0),
                                     sizeof (Request));
    return SUCCESSFUL;
}

int ReceiveMatrix(SocketHandle sock, Request* pRequest, Matrix* pMatrix)
{
    uint32_t* pBuf = (uint32_t*) malloc(pRequest->MatrixDataSize);
    if (pBuf == NULL)
    {
        return ALLOCATION_ERROR;
    }
    RETURN_UNSUCCESSFUL_IF_NOT_EQUAL(
            recv(sock, pBuf, pRequest->MatrixDataSize, 0),
            pRequest->MatrixDataSize);

    pMatrix->FirstCount = pMatrix->SecondCount = pRequest->Degree;

    int k = 0;
    for (int i = 0; i < pMatrix->FirstCount; i++)
    {
        for (int j = 0; j < pMatrix->SecondCount; j++)
        {
            pMatrix->ppData[i][j] = ntohl(pBuf[k++]);
        }
    }

    free(pBuf);

    return NO_ERROR;
}
