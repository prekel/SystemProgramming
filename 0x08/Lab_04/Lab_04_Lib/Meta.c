#include "Meta.h"
#include "File.h"

void FillMeta(Meta* meta, int size)
{
    meta->Version = META_VERSION;
    meta->Size = size;
    meta->Count = 0;
}

bool CheckMetaVersion(int fd)
{
    SeekToStartRecord(fd, META_INDEX);
    int actualVersion;
    read(fd, &actualVersion, sizeof(int));
    return actualVersion == META_VERSION;
}