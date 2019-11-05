#ifndef ARCHIPELAGO_H
#define ARCHIPELAGO_H

#define ARCHIPELAGO_NAME_LENGTH 100

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

int IndexByName(int fd, char* name);

int ModifyName(int fd, int index, char* newName);

int ModifyCountIslands(int fd, int index, int newCountIslands);

int ModifyCountInhabitedIslands(int fd,
                                int index,
                                int newCountInhabitedIslands);

#endif //ARCHIPELAGO_H
