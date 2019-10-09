#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct StructNode;
typedef struct StructNode Node;

struct StructNode
{
    void* pElement;
    Node* pNext;
    Node* pPrev;
};

typedef struct
{
    Node* pFirst;
    Node* pLast;
} LinkedList;

enum {
    Successful = 1,

} LinkedListOperationResult;

#endif //LINKEDLIST_H
