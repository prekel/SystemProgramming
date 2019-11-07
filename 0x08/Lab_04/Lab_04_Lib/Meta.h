#ifndef META_H
#define META_H

#include <stdbool.h>
#include <stdint.h>

#define META_VERSION 13
#define META_INDEX (-1)

#define BAD_META (-7)

typedef struct
{
    int32_t Version;
    int32_t Count;
    uint32_t RecordSize;
    uint32_t MetaSize;
} Meta;

void FillMeta(Meta* pMeta, int size);

#endif //META_H
