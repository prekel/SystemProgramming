#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct
{
    void* private;

    Node* (* GetFirst)();
    Node* (* GetLast)();
} LinkedList;

enum {
    Successful = 1,

} LinkedListOperationResult;

#endif //LINKEDLIST_H
