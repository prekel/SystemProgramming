#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "LinkedListDeclarations.h"

typedef struct LinkedList
{
    int Count;
    LinkedListNode* pFirst;
    LinkedListNode* pLast;
} LinkedList;

LinkedList* LinkedListCreate();

void LinkedListAppendElement(LinkedList* pList, void* pElement);

void LinkedListRemoveElement(LinkedList* pList, void* pElement);

void LinkedListAppendNode(LinkedList* pList, LinkedListNode* pNode);

void LinkedListRemoveNode(LinkedList* pList, LinkedListNode* pNode);

void* LinkedListGetFirstElement(LinkedList* pList);

void* LinkedListGetLastElement(LinkedList* pList);

LinkedListNode* LinkedListGetFirstNode(LinkedList* pList);

LinkedListNode* LinkedListGetLastNode(LinkedList* pList);

LinkedListNode* LinkedListIteratorNext(LinkedListNode** ppNode);

LinkedListNode* LinkedListIteratorPrevious(LinkedListNode** ppNode);

#endif //LINKEDLIST_H
