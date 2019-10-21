#include <malloc.h>
#include <assert.h>

#include "LinkedListNode.h"

LinkedListNode* LinkedListNodeCreate(LinkedList* pList, void* pElement)
{
    LinkedListNode* pNode = malloc(sizeof(LinkedListNode*));
    assert(pNode);

    pNode->pElement = pElement;

    assert(pList);
    pNode->pList = pList;

    return pElement;
}

void LinkedListNodeDestroy(LinkedListNode* pNode)
{
    free(pNode);
}

void LinkedListNodePutBetween(LinkedListNode* pPrevious,
                              LinkedListNode* pNode,
                              LinkedListNode* pNext)
{
    assert(pNode);
    if (pPrevious)
    {
        assert(pPrevious->pList == pNode->pList);
        pPrevious->pNext = pNode;
    }
    pNode->pPrevious = pPrevious;
    pNode->pNext = pNext;
    if (pNext)
    {
        assert(pNext->pList == pNode->pList);
        pNext->pPrevious = pNode;
    }
}

void LinkedListNodeDrop(LinkedListNode* pNode)
{
    assert(pNode);
    if (pNode->pPrevious)
    {
        assert(pNode->pPrevious->pList == pNode->pList);
        pNode->pPrevious->pNext = pNode->pNext;
    }
    if (pNode->pNext)
    {
        assert(pNode->pNext->pList == pNode->pList);
        pNode->pNext->pPrevious = pNode->pPrevious;
    }
}