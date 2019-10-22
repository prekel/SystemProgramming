/// \file
/// \brief Архипелаг
/// \details Архипелаг, его струкрура, функции для создания итд.

#ifndef ARCHIPELAGO_H
#define ARCHIPELAGO_H

/// \struct Archipelago
///
/// Архипелаг.
typedef struct
{
    /// Название архипелага.
    char* Name;
    /// Кол-во островов.
    int CountIslands;
    /// Кол-во обитаемых островов.
    int CountInhabitedIslands;
} Archipelago;

/// Создаёт архипелаг. Требуется очистка с помощью ArchipelagoDestroy()
/// или ArchipelagoCollectionDestroyArchipelagos()ю
///
/// \param name Название архипелага.
/// \param countIslands Кол-во островов.
/// \param countInhabitedIslands Кол-во обитаемых островов.
/// \return Указатель на созданны1 архипелаг.
Archipelago* ArchipelagoCreate(char* name,
                               int countIslands,
                               int countInhabitedIslands);

/// Уничтожет архипелаг.
///
/// \param pArchipelago Указатель на архипелаг.
void ArchipelagoDestroy(Archipelago* pArchipelago);

/// Изменяет название архипелага.
///
/// \param pArchipelago Указатель на архипелаг.
/// \param newName Новое название архипелага.
void ArchipelagoSetName(Archipelago* pArchipelago, char* newName);

/// Создаёт строку с информацией об архипелаге. Требуется очистка с
/// помощью free().
///
/// \param pArchipelago Указатель на архипелаг.
/// \return Строка с информацией.
char* ArchipelagoToString(Archipelago* pArchipelago);

#endif //ARCHIPELAGO_H
