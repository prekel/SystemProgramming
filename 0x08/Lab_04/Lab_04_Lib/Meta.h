#ifndef META_H
#define META_H

#include <unistd.h>
#include <stdbool.h>

#define META_VERSION 10
#define META_INDEX -1

#define BAD_META -7

typedef struct
{
    int Version;
    int Count;
    size_t Size;
} Meta;

void FillMeta(Meta* pMeta, int size);

bool CheckMetaVersion(int fd);

#endif //META_H
