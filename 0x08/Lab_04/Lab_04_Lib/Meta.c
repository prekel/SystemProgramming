/// \file
/// \brief Реализация функций из Meta.h
/// \details Реализация функций из Meta.h.

#include "Meta.h"
#include "RecordFile.h"

void FillMeta(Meta* pMeta, int recordSize)
{
    pMeta->Version = META_VERSION;
    pMeta->Count = 0;
    pMeta->RecordSize = recordSize;
    pMeta->MetaSize = sizeof(Meta);
}
