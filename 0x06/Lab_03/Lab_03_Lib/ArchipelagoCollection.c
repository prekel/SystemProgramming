#include "ArchipelagoCollection.h"
#include "LinkedListFunctions.h"

void DataCollectionAppend(LinkedList* pList, Data* pData)
{
    LinkedListAppend(pList, pData);
}

Data* GetLastDataLinkedList(LinkedList* pList)
{
    return (Data*) LinkedListGetLastElement(pList);
}