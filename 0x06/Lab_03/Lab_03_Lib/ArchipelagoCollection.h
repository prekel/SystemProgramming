/// \file
/// \brief Коллекция архипелагов
/// \details Коллекция архипелагов, её струкрура, функции для создания итд.

#ifndef ARCHIPELAGOCOLLECTION_H
#define ARCHIPELAGOCOLLECTION_H

#include "LinkedList.h"
#include "Archipelago.h"
#include "LinkedListNode.h"

/// \struct ArchipelagoCollection
///
/// Коллекция архипелагов.
typedef struct
{
    /// Указатель на связный список.
    LinkedList* pList;
} ArchipelagoCollection;

/// Создаёт новую коххекцию архипелагов. Требудется очистка с
/// помощью ArchipelagoCollectionDestroy().
///
/// \return Указатель на созданную коллекцию.
ArchipelagoCollection* ArchipelagoCollectionCreate();

/// Уничтожает коллекцию архипелагов. Добавленные архипелаги не трогаются.
///
/// \param pCollection Указатель на коллекцию архипелагов.
void ArchipelagoCollectionDestroy(ArchipelagoCollection* pCollection);

/// Уничтожает архипелаги в коллекции.
///
/// \param pCollection
void ArchipelagoCollectionDestroyArchipelagos(
        ArchipelagoCollection* pCollection);

/// Добавляет архипелаг в коллекцию.
///
/// \param pCollection Указатель на коллекцию архипелагов.
/// \param pArchipelago Указатель на архипелаг.
void ArchipelagoCollectionAdd(ArchipelagoCollection* pCollection,
                              Archipelago* pArchipelago);

/// Удаляет архипелаг из коллекции. Если такого в коллекции не существует,
/// ничего не происходит.
///
/// \param pCollection Указатель на коллекцию архипелагов.
/// \param pArchipelago Указатель на архипелаг.
void ArchipelagoCollectionRemove(ArchipelagoCollection* pCollection,
                                 Archipelago* pArchipelago);

/// Ищет архипелаг по его названию.
///
/// \param pCollection Указатель на коллекцию архипелагов.
/// \param name Название искомого архипелага.
/// \return Указатель на искомый архипелаг если найден, NULL если не найден.
Archipelago* ArchipelagoCollectionFindByName(
        ArchipelagoCollection* pCollection,
        char* name);

/// Возвращает первый архипелаг в коллекции.
///
/// \param pCollection Указатель на коллекцию архипелагов.
/// \return Указатель на первый архипелаг в коллекции.
Archipelago* ArchipelagoCollectionGetFirst(
        ArchipelagoCollection* pCollection);

/// Возвращает итератор по которому можно пройтись по списку с помощью
/// цикла for.
///
/// \param pCollection Указатель на коллекцию архипелагов.
/// \return Указатель на итератор (узел связного списка).
LinkedListNode* ArchipelagoCollectionGetIterator(
        ArchipelagoCollection* pCollection);

/// Переключает итератор на следующий элемент. Если элемент был последним, итератор переключается на NULL.
///
/// \param ppArchipelagoIterator Указатель на указатель на итератор.
/// \return Указатель на архипелаг итератора до переключения.
Archipelago* ArchipelagoCollectionIteratorNext(
        LinkedListNode** ppArchipelagoIterator);

/// Возвращает указатель на архипелаг по итератору.
///
/// \param pArchipelagoIterator Указатель на итератор.
/// \return Указатель на архипелаг итератора.
Archipelago* ArchipelagoCollectionGetByIterator(
        LinkedListNode* pArchipelagoIterator);

#endif //ARCHIPELAGOCOLLECTION_H
