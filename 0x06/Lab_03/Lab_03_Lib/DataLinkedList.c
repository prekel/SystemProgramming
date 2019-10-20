#include "DataLinkedList.h"
#include "LinkedListFunctions.h"

void AppendDataLinkedList(LinkedList* pList, Data* pData)
{
    LinkedListAppend(pList, pData);
}

Data* GetLastDataLinkedList(LinkedList* pList)
{
    return (Data*) LinkedListGetLast(pList);
}