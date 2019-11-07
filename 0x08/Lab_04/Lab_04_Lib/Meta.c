#include "Meta.h"
#include "File.h"

void FillMeta(Meta* pMeta, int size)
{
    pMeta->Version = META_VERSION;
    pMeta->Count = 0;
    pMeta->RecordSize = size;
    pMeta->MetaSize = sizeof(Meta);
}
