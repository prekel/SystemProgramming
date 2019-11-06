#ifndef ARCHIPELAGO_H
#define ARCHIPELAGO_H

#include "Meta.h"

#define ARCHIPELAGO_NAME_LENGTH 104

#define NOT_FOUND -1

/// \struct Archipelago
///
/// Архипелаг.
typedef struct
{
    /// Название архипелага.
    char Name[ARCHIPELAGO_NAME_LENGTH];
    /// Кол-во островов.
    int CountIslands;
    /// Кол-во обитаемых островов.
    int CountInhabitedIslands;
} Archipelago;

void FillArchipelago(Archipelago* pArchipelago,
                     char* name,
                     int countIslands,
                     int countInhabitedIslands);

int SetName(Archipelago* pArchipelago, char* name);

ssize_t
ReadArchipelago(int fd, Meta* pMeta, Archipelago* pArchipelago, int index);

ssize_t
WriteArchipelago(int fd, Meta* pMeta, Archipelago* pArchipelago, int index);

ssize_t AddArchipelago(int fd, Meta* pMeta, Archipelago* pArchipelago);

int IndexByName(int fd, Meta* pMeta, char* name);

int ModifyName(int fd, Meta* pMeta, int index, char* newName);

int ModifyCountIslands(int fd, Meta* pMeta, int index, int newCountIslands);

int ModifyCountInhabitedIslands(int fd,
                                int index,
                                int newCountInhabitedIslands);

#endif //ARCHIPELAGO_H
