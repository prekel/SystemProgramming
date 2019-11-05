#ifndef META_H
#define META_H

#include <unistd.h>
#include <stdbool.h>

#define META_VERSION 5

typedef struct
{
    int Version;
    size_t Size;
    int Count;
} Meta;

void FillMeta(Meta* pMeta, int size);

bool CheckMetaVersion(int fd);

#endif //META_H
