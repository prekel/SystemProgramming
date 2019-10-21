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