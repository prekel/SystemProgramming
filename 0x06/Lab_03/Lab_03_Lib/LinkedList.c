#include "LinkedList.h"

typedef struct
{
    //Node* pFirst;
    //Node* pLast;
} LinkedListPrivate;



static void LinkedListAppend(LinkedList* pList, void* pElement)
{
    LinkedListPrivate* pPrivate = (LinkedListPrivate*)(pList->private);
    //pList->GetLast();
}

static void* LinkedListGetLast(LinkedList* pList)
{
    //return pList->pLast;
}