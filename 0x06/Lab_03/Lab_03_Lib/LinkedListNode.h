#ifndef LINKEDLISTNODE_H
#define LINKEDLISTNODE_H

typedef struct StructLinkedListNode LinkedListNode;
typedef struct StructLinkedListNode
{
    void* pElement;
    LinkedListNode* pNext;
    LinkedListNode* pPrevious;
} LinkedListNode;

#endif //LINKEDLISTNODE_H
