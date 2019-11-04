#include "Meta.h"
#include "File.h"

void FillMeta(Meta* pMeta, int size)
{
    pMeta->Version = META_VERSION;
    pMeta->Size = size;
    pMeta->Count = 0;
}

bool CheckMetaVersion(int fd)
{
    SeekToStartRecord(fd, META_INDEX);
    int actualVersion;
    read(fd, &actualVersion, sizeof(int));
    return actualVersion == META_VERSION;
}