#include "DataLinkedList.h"
#include "LinkedListFunctions.h"

void AppendDataLinkedList(LinkedList* pList, Data* pData)
{
    AppendLinkedList(pList, pData);
}

Data* GetLastDataLinkedList(LinkedList* pList)
{
    return (Data*) GetLastLinkedList(pList);
}