#ifndef LINKEDLISTNODE_H
#define LINKEDLISTNODE_H

#include "LinkedListDeclarations.h"

typedef struct LinkedListNode
{
    void* pElement;
    LinkedListNode* pNext;
    LinkedListNode* pPrevious;
    LinkedList* pList;
} LinkedListNode;

LinkedListNode* LinkedListNodeCreate(void* pElement, LinkedList* pList);

void LinkedListNodeDestroy(LinkedListNode* pNode);

void LinkedListNodePutBetween(LinkedListNode* pPrevious,
                              LinkedListNode* pNode,
                              LinkedListNode* pNext);

#endif //LINKEDLISTNODE_H
          