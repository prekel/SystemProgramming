#include <malloc.h>
#include <arpa/inet.h>

#include "Request.h"
#include "Macro.h"

Request* CreateRequest(Matrix* pMatrix, int firstIndex, int secondIndex)
{
    Request* pRequest = (Request*) malloc(sizeof(Request));
    RETURN_NULL_IF_NULLPTR(pRequest);

    pRequest->Size =
            sizeof(pRequest->NetSize) +
            sizeof(pRequest->NetFirstIndex) +
            sizeof(pRequest->NetSecondIndex) +
            sizeof(pRequest->NetCount) +
            sizeof(pRequest->NetMatrixDataSize) +
            pMatrix->FirstCount * sizeof(pRequest->pNetMatrixData[0]);

    pRequest->FirstIndex = firstIndex;
    pRequest->SecondIndex = secondIndex;

    pRequest->pMatrix = pMatrix;

    pRequest->NetSize = htonl(pRequest->Size);

    pRequest->NetFirstIndex = htonl(pRequest->FirstIndex);

    pRequest->NetSecondIndex = htonl(pRequest->SecondIndex);

    pRequest->NetCount = htonl(pRequest->pMatrix->FirstCount);

    size_t matrixDataSize =
            (pRequest->pMatrix->FirstCount * pRequest->pMatrix->SecondCount) *
            sizeof(uint32_t);
    pRequest->NetMatrixDataSize = htonl(matrixDataSize);

    pRequest->pNetMatrixData = (uint32_t*) malloc(matrixDataSize);
    RETURN_NULL_IF_NULLPTR(pRequest->pNetMatrixData);

    int k = 0;
    for (int i = 0; i < pRequest->pMatrix->FirstCount; i++)
    {
        for (int j = 0; j < pRequest->pMatrix->SecondCount; j++)
        {
            pRequest->pNetMatrixData[k++] =
                    htonl(pRequest->pMatrix->pData[i][j]);
        }
    }

    return pRequest;
}