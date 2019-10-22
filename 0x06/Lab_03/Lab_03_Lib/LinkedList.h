/// \file
/// \brief Связный список.
/// \details Связный список, его структура, функции для создания итд.

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "LinkedListDeclarations.h"

/// \struct LinkedList
///
/// Связный список.
typedef struct LinkedList
{
    /// Кол-во элементов.
    int Count;
    /// Указатель на первый узел.
    LinkedListNode* pFirst;
    /// Указатель на последний узел.
    LinkedListNode* pLast;
} LinkedList;

/// Создаёт новый связный список. Требуется очистка с
/// помощью LinkedListDestroy().
///
/// \return Указатель на созданный связный список.
LinkedList* LinkedListCreate();

/// Уничтожает связный список.
///
/// \param pList Указатель на связный список.
void LinkedListDestroy(LinkedList* pList);

/// Добавляет элемент в конец списка.
///
/// \param pList Указатель на связный список.
/// \param pElement Указатель на добавляемый элемент.
void LinkedListAppendElement(LinkedList* pList, void* pElement);

/// Удаляет элемент из связного списка. Если он не существует, ничего не происходит.
///
/// \param pList Указатель на связный список.
/// \param pElement Указатель на удаляемый элемент.
void LinkedListRemoveElement(LinkedList* pList, void* pElement);

/// Добавляет узел в конец списка.
///
/// \param pList Указатель на связный список.
/// \param pNode Указатель на добавляемый узел.
void LinkedListAppendNode(LinkedList* pList, LinkedListNode* pNode);

/// Удаляет узел из списка.
///
/// \param pList Указатель на связный список.
/// \param pNode Указатель на удаляемый узел.
void LinkedListRemoveNode(LinkedList* pList, LinkedListNode* pNode);

/// Возвращает первый элемент.
///
/// \param pList Указатель на связный список.
/// \return Указатель на первый элемент.
void* LinkedListGetFirstElement(LinkedList* pList);

/// Возвращает последний элемент.
///
/// \param pList Указатель на связный список.
/// \return Указатель на последный элемент.
void* LinkedListGetLastElement(LinkedList* pList);

/// Возвращает первый узел.
///
/// \param pList Указатель на связный список.
/// \return Указатель на первый узел.
LinkedListNode* LinkedListGetFirstNode(LinkedList* pList);

/// Возвращает последний узел.
///
/// \param pList Указатель на связный список.
/// \return Указатель на последний узел.
LinkedListNode* LinkedListGetLastNode(LinkedList* pList);

/// Переключает узел на следующий.
///
/// \param ppNode Указатель на указатель на узел.
/// \return Указатель на узел до переключения.
LinkedListNode* LinkedListIteratorNext(LinkedListNode** ppNode);

/// Переклчает узел на предыдущий.
///
/// \param ppNode Указатель на указатель на узел.
/// \return Указатель на узел до переключения.
LinkedListNode* LinkedListIteratorPrevious(LinkedListNode** ppNode);

#endif //LINKEDLIST_H
