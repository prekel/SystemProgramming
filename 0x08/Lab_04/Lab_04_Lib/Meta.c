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
    if (SeekRecord(fd, NULL, META_INDEX) == FILE_UNSUCCESSFUL)
    {
        return false;
    }
    int actualVersion;
    if (read(fd, &actualVersion, sizeof(int)) == FILE_UNSUCCESSFUL)
    {
        return false;
    }
    return actualVersion == META_VERSION;
}
