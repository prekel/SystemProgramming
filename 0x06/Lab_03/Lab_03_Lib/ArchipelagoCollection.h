#ifndef ARCHIPELAGOCOLLECTION_H
#define ARCHIPELAGOCOLLECTION_H

#include "LinkedList.h"
#include "Data.h"

typedef struct
{
    LinkedList* pList;
} ArchipelagoCollection;

void ArchipelagoCollectionAppend(ArchipelagoCollection* pList, Data* pData);



#endif //ARCHIPELAGOCOLLECTION_H
