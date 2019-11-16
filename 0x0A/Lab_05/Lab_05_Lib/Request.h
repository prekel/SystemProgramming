#ifndef REQUEST_H
#define REQUEST_H

#include <stdint.h>

#include "Matrix.h"

typedef struct
{
    size_t Size;
    uint32_t NetSize;
    int FirstIndex;
    int SecondIndex;
    uint32_t NetFirstIndex;
    uint32_t NetSecondIndex;
    Matrix* pMatrix;
    uint32_t NetCount;
    uint32_t NetMatrixDataSize;
    uint32_t* pNetMatrixData;
} Request;

Request* CreateRequest(Matrix* pMatrix, int firstIndex, int secondIndex);

#endif //REQUEST_H
