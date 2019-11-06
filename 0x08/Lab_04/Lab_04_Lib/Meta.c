#include "Meta.h"
#include "File.h"

void FillMeta(Meta* pMeta, int size)
{
    pMeta->Version = META_VERSION;
    pMeta->Size = size;
    pMeta->Count = 0;
}

ssize_t WriteMeta(int fd, Meta* meta)
{
    SeekToStartRecord(fd, META_INDEX);
    return write(fd, meta, sizeof(Meta));
}

ssize_t ReadMeta(int fd, Meta* meta)
{
    SeekToStartRecord(fd, META_INDEX);
    return read(fd, meta, sizeof(Meta));
}

bool CheckMetaVersion(int fd)
{
    SeekToStartRecord(fd, META_INDEX);
    int actualVersion;
    read(fd, &actualVersion, sizeof(int));
    return actualVersion == META_VERSION;
}
