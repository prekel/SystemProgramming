#include "LinkedList.h"

typedef struct
{
    Node* pFirst;
    Node* pLast;
} private;



void AppendLinkedList(LinkedList* pList, void* pElement)
{

}

static void* GetLastLinkedList(LinkedList* pList)
{
    return pList->pLast;
}