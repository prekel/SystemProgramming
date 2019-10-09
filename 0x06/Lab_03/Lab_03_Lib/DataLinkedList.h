#ifndef DATALINKEDLIST_H
#define DATALINKEDLIST_H

#include "LinkedList.h"
#include "Data.h"

void AppendDataLinkedList(LinkedList* pList, Data* pData);

Data* GetLastDataLinkedList(LinkedList* pList);

#endif //DATALINKEDLIST_H
