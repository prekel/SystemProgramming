#include <malloc.h>
#include <assert.h>
#include <stdbool.h>

#include "LinkedList.h"
#include "LinkedListNode.h"

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

void LinkedListDestroy(LinkedList* pList)
{
    if (pList->Count == 1)
    {
        LinkedListRemoveNode(pList, pList->pFirst);
    }
    else if (pList->Count > 1)
    {
        for (LinkedListNode* pIterator = LinkedListGetFirstNode(pList);
             pIterator != NULL;
             LinkedListIteratorNext(&pIterator))
        {
            if (pIterator->pPrevious)
            {
                LinkedListRemoveNode(pList, pIterator->pPrevious);
            }
        }
    }
    free(pList);
}

void LinkedListAppendElement(LinkedList* pList, void* pElement)
{
    LinkedListAppendNode(pList, LinkedListNodeCreate(pList, pElement));
}

void LinkedListRemoveElement(LinkedList* pList, void* pElement)
{
    for (LinkedListNode* pIterator = LinkedListGetFirstNode(pList);
         pIterator != NULL;
         LinkedListIteratorNext(&pIterator))
    {
        if (pIterator->pElement == pElement)
        {
            LinkedListRemoveNode(pList, pIterator);
            break;
        }
    }
}

void LinkedListAppendNode(LinkedList* pList, LinkedListNode* pNode)
{
    LinkedListNodePutBetween(pList->pLast, pNode, NULL);
    if (pList->Count == 0)
    {
        pList ->pFirst = pNode;
    }
    pList->pLast = pNode;
    pList->Count++;
}

void LinkedListRemoveNode(LinkedList* pList, LinkedListNode* pNode)
{
    assert(pList);
    assert(pNode);
    assert(pNode->pList == pList);
    assert(pList->Count > 0);
    if (pList->Count == 1)
    {
        pList->pFirst = NULL;
        pList->pLast = NULL;
    }
    else if (pList->pFirst == pNode)
    {
        pList->pFirst = pNode->pNext;
    } if (pList->pLast == pNode)
    {
        pList->pLast = pNode->pPrevious;
    }
    LinkedListNodeDrop(pNode);
    LinkedListNodeDestroy(pNode);
    pList->Count--;
}

void* LinkedListGetFirstElement(LinkedList* pList)
{
    return LinkedListGetFirstNode(pList)->pElement;
}

void* LinkedListGetLastElement(LinkedList* pList)
{
    return LinkedListGetLastNode(pList)->pElement;
}

LinkedListNode* LinkedListGetFirstNode(LinkedList* pList)
{
    return pList->pFirst;
}

LinkedListNode* LinkedListGetLastNode(LinkedList* pList)
{
    return pList->pLast;
}

LinkedListNode* LinkedListIteratorNext(LinkedListNode** ppNode)
{
    if (*ppNode == NULL)
    {
        return NULL;
    }
    LinkedListNode* pCurrentNode = *ppNode;
    *ppNode = (*ppNode)->pNext;
    return pCurrentNode;
}

LinkedListNode* LinkedListIteratorPrevious(LinkedListNode** ppNode)
{
    if (*ppNode == NULL)
    {
        return NULL;
    }
    LinkedListNode* pCurrentNode = *ppNode;
    *ppNode = (*ppNode)->pPrevious;
    return pCurrentNode;
}
