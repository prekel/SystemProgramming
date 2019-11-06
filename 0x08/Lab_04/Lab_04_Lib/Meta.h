#ifndef META_H
#define META_H

#include <unistd.h>
#include <stdbool.h>

#define META_VERSION 9
#define META_INDEX -1

typedef struct
{
    int Version;
    int Count;
    size_t Size;
} Meta;

void FillMeta(Meta* pMeta, int size);

bool CheckMetaVersion(int fd);

#endif //META_H
