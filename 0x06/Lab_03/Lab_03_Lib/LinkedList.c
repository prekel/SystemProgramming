#include <malloc.h>
#include <assert.h>

#include "LinkedList.h"

LinkedList* LinkedListCreate()
{
    LinkedList* pList = (LinkedList*) malloc(sizeof(LinkedList));
    assert(pList);

    pList->Count = 0;
    pList->pFirst = NULL;
    pList->pLast = NULL;

    assert(pList);

    return pList;
}

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
