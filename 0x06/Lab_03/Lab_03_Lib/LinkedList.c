#include "LinkedList.h"

typedef struct
{
    //Node* pFirst;
    //Node* pLast;
} LinkedListPrivate;



static void AppendLinkedList(LinkedList* pList, void* pElement)
{
    LinkedListPrivate* pPrivate = (LinkedListPrivate*)(pList->private);
    //pList->GetLast();
}

static void* GetLastLinkedList(LinkedList* pList)
{
    //return pList->pLast;
}