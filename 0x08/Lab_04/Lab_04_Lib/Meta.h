#ifndef META_H
#define META_H

#include <unistd.h>
#include <stdbool.h>

#define META_VERSION 1

typedef struct
{
    int Version;
    size_t Size;
    int Count;
} Meta;

void FillMeta(Meta* meta, int size);

bool CheckMetaVersion(int fd);

#endif //META_H
