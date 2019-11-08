#ifndef ARCHIPELAGO_H
#define ARCHIPELAGO_H

#include <stdint.h>

#include "Meta.h"

#define ARCHIPELAGO_NAME_LENGTH 120

/// \struct Archipelago
///
/// Архипелаг.
typedef struct
{
    /// Название архипелага.
    char Name[ARCHIPELAGO_NAME_LENGTH];
    /// Кол-во островов.
    int32_t CountIslands;
    /// Кол-во обитаемых островов.
    int32_t CountInhabitedIslands;
} Archipelago;

int FillArchipelago(Archipelago* pArchipelago,
                    char* name,
                    int countIslands,
                    int countInhabitedIslands);

int VerifyArchipelago(Archipelago* pArchipelago);

int SetName(Archipelago* pArchipelago, const char* name);

int ReadArchipelago(int fd,
                    Meta* pMeta,
                    Archipelago* pArchipelago,
                    int index);

int WriteArchipelago(int fd,
                     Meta* pMeta,
                     Archipelago* pArchipelago,
                     int index);

int AddArchipelago(int fd, Meta* pMeta, Archipelago* pArchipelago);

int IndexByName(int fd, Meta* pMeta, char* name);

int ModifyName(int fd, Meta* pMeta, int index, char* newName);

int ModifyCountIslands(int fd, Meta* pMeta, int index, int newCountIslands);

int ModifyCountInhabitedIslands(int fd, Meta* pMeta, int index,
                                int newCountInhabitedIslands);

#endif //ARCHIPELAGO_H
