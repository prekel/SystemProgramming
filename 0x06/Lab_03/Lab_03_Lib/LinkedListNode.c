#include "LinkedListNode.h"

typedef struct
{
    void* pElement;
    LinkedListNode* pNext;
    LinkedListNode* pPrevious;
} PrivateLinkedListNode;

static LinkedListNode* GetNext()
{
    //PrivateLinkedListNode* = (PrivateLinkedListNode*)
}