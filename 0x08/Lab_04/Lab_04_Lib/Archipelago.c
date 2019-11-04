#include <string.h>
#include <assert.h>

#include "Archipelago.h"
#include "Meta.h"
#include "File.h"

void FillArchipelago(Archipelago* pArchipelago,
                     char* name,
                     int countIslands,
                     int countInhabitedIslands)
{
    assert(strlen(name) + 1 <= ARCHIPELAGO_NAME_LENGTH);
    assert(countIslands > 1);
    assert(countInhabitedIslands > 0);
    strcpy(pArchipelago->Name, name);
    pArchipelago->CountIslands = countIslands;
    pArchipelago->CountInhabitedIslands = countInhabitedIslands;
}

int IndexByName(int fd, char* name)
{
    Meta meta;
    ReadMeta(fd, &meta);

    for (int i = 0; i < meta.Count; i++)
    {
        Archipelago archipelago;
        ReadRecord(fd, &archipelago, i);
        if (strcmp(archipelago.Name, name) == 0)
        {
            return i;
        }
    }

    return NOT_FOUND;
}

int ModifyName(int fd, int index, char* newName)
{
    assert(strlen(newName) + 1 <= ARCHIPELAGO_NAME_LENGTH);
    Archipelago archipelago;
    ReadRecord(fd, &archipelago, index);
    strcpy(archipelago.Name, newName);
    WriteRecord(fd, &archipelago, index);
    return 0;
}

int ModifyCountIslands(int fd, int index, int newCountIslands)
{
    assert(newCountIslands > 1);
    Archipelago archipelago;
    ReadRecord(fd, &archipelago, index);
    archipelago.CountIslands = newCountIslands;
    WriteRecord(fd, &archipelago, index);
    return 0;
}

int ModifyCountInhabitedIslands(int fd, int index, int newCountInhabitedIslands)
{
    assert(newCountInhabitedIslands > 0);
    Archipelago archipelago;
    ReadRecord(fd, &archipelago, index);
    archipelago.CountInhabitedIslands = newCountInhabitedIslands;
    WriteRecord(fd, &archipelago, index);
    return 0;
}