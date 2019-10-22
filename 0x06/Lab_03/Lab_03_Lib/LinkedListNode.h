/// \file
/// \brief Узел связного список.
/// \details Узел связного списока, его структура, функции для создания итд.

#ifndef LINKEDLISTNODE_H
#define LINKEDLISTNODE_H

#include "LinkedListDeclarations.h"

/// \struct LinkedListNode
///
/// Узел связного списка.
typedef struct LinkedListNode
{
    /// Указатель на элемент узла.
    void* pElement;
    /// Указатель на предыдущий узел.
    LinkedListNode* pPrevious;
    /// Указатель на следующий узел.
    LinkedListNode* pNext;
    /// Указатель на связный список.
    LinkedList* pList;
} LinkedListNode;

/// Создаёт узел связного списка. Требудется очистка с
/// помощью LinkedListNodeDestroy().
///
/// \param pList Указатель на связный список.
/// \param pElement Указатель на элемент.
/// \return Указатель на созданный узел.
LinkedListNode* LinkedListNodeCreate(LinkedList* pList, void* pElement);

/// Уничтожает узел связного списка.
///
/// \param pNode Указатель на узел связого списка.
void LinkedListNodeDestroy(LinkedListNode* pNode);

/// Помещает узел между узлами pPrevious и pNext.
///
/// \param pPrevious Узел, который должен идти до узла pNode в списке.
/// Может быть NULL.
/// \param pNode Узел, который следует поместить между узлами.
/// \param pNext Узел, который должен идти после узла pNode в списке.
/// Может быть NULL.
void LinkedListNodePutBetween(LinkedListNode* pPrevious,
                              LinkedListNode* pNode,
                              LinkedListNode* pNext);

/// Убирает узел из списка, связывая между собой предыдущий и следующий узел.
///
/// \param pNode Указатель на узел для убирания из списка.
void LinkedListNodeDrop(LinkedListNode* pNode);

#endif //LINKEDLISTNODE_H
