/// \file
/// \brief Запросы к коллекции архипелагов
/// \details Запросы к коллекции архипелагов.

#ifndef ARCHIPELAGOCOLLECTIONQUERY_H
#define ARCHIPELAGOCOLLECTIONQUERY_H

#include <stdbool.h>
#include "ArchipelagoCollection.h"

/// Есть ли в коллекции архипелаг, удолетворяющих условию pPredicate.
///
/// \param pCollection Указатель на колекцию архипелагов.
/// \param pPredicate Указатель на функцию-условие.
/// \return Результат запроса.
bool ArchipelagoCollectionQueryHas(
        ArchipelagoCollection* pCollection,
        bool pPredicate(Archipelago*));

/// Создаёт коллекцию архипелагов из коллекции архипелагов pCollection.
/// Выбираются архипелаги, удолетворяющие устловию pPredicate.
/// Требуется очистка с помощью ArchipelagoCollectionDestroy().
///
/// \param pCollection Указатель на коллекцию архипелагов.
/// \param n Вспомогательный параметр, передающийся в функцию-условие.
/// \param pPredicate Указатель на функцию-условие.
/// \return Результат запроса.
ArchipelagoCollection* ArchipelagoCollectionQuerySelectWhereIsN(
        ArchipelagoCollection* pCollection, int n,
        bool pPredicate(Archipelago* pArchipelago, int n));

/// Есть ли в коллекции хотя бы 1 полностью необитаемый архипелаг.
///
/// \param pCollection Указатель на коллекцию архипелагов.
/// \return Результат запроса.
bool ArchipelagoCollectionQueryHasOnlyUninhabited(
        ArchipelagoCollection* pCollection);

/// Выбирает архипелаги с заданным кол-вом островов. Требуется очистка с
/// помощью ArchipelagoCollectionDestroy().
///
/// \param pCollection Указатель на коллекцию архипелагов.
/// \param islandsCount Кол-во островов.
/// \return Результат запроса.
ArchipelagoCollection* ArchipelagoCollectionQuerySelectWhereIslandsCountIs(
        ArchipelagoCollection* pCollection, int islandsCount);

#endif //ARCHIPELAGOCOLLECTIONQUERY_H
