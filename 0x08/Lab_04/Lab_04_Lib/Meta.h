#ifndef META_H
#define META_H

#include <unistd.h>
#include <stdbool.h>

#define META_VERSION 8
#define META_INDEX -1

typedef struct
{
    int Version;
    int Count;
    size_t Size;
} Meta;

void FillMeta(Meta* pMeta, int size);

ssize_t ReadMeta(int fd, Meta* meta);

ssize_t WriteMeta(int fd, Meta* meta);

bool CheckMetaVersion(int fd);

#endif //META_H
