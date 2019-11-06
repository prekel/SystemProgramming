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
    assert(countInhabitedIslands >= 0);
    assert(countIslands >= countInhabitedIslands);
    SetName(pArchipelago, name);
    pArchipelago->CountIslands = countIslands;
    pArchipelago->CountInhabitedIslands = countInhabitedIslands;
}

int SetName(Archipelago* pArchipelago, char* name)
{
    memset(pArchipelago->Name, '\0', ARCHIPELAGO_NAME_LENGTH);
    int i;
    for (i = 0; i < ARCHIPELAGO_NAME_LENGTH; i++)
    {
        if (name[i] == '\0')
        {
            break;
        }
        pArchipelago->Name[i] = name[i];
    }
    return i;
}

ssize_t ReadArchipelago(int fd,
                        Meta* pMeta,
                        Archipelago* pArchipelago,
                        int index)
{
    return ReadRecord(fd, pMeta, pArchipelago, index);
}

ssize_t WriteArchipelago(int fd,
                         Meta* pMeta,
                         Archipelago* pArchipelago,
                         int index)
{
    return WriteRecord(fd, pMeta, pArchipelago, index);
}

ssize_t AddArchipelago(int fd, Meta* pMeta, Archipelago* pArchipelago)
{
    return AddRecord(fd, pMeta, pArchipelago);
}

int IndexByName(int fd, Meta* pMeta, char* name)
{
    for (int i = 0; i < pMeta->Count; i++)
    {
        Archipelago archipelago;
        ReadArchipelago(fd, pMeta, &archipelago, i);
        if (strcmp(archipelago.Name, name) == 0)
        {
            return i;
        }
    }

    return NOT_FOUND;
}

int ModifyName(int fd, Meta* pMeta, int index, char* newName)
{
    assert(strlen(newName) + 1 <= ARCHIPELAGO_NAME_LENGTH);
    Archipelago archipelago;
    ReadArchipelago(fd, pMeta, &archipelago, index);
    SetName(&archipelago, newName);
    WriteArchipelago(fd, pMeta, &archipelago, index);
    return 0;
}

int ModifyCountIslands(int fd, Meta* pMeta, int index, int newCountIslands)
{
    assert(newCountIslands > 1);
    Archipelago archipelago;
    ReadArchipelago(fd, pMeta, &archipelago, index);
    assert(newCountIslands >= archipelago.CountInhabitedIslands);
    archipelago.CountIslands = newCountIslands;
    WriteArchipelago(fd, pMeta, &archipelago, index);
    return 0;
}

int ModifyCountInhabitedIslands(int fd,
                                Meta* pMeta,
                                int index,
                                int newCountInhabitedIslands)
{
    assert(newCountInhabitedIslands >= 0);
    Archipelago archipelago;
    ReadArchipelago(fd, pMeta, &archipelago, index);
    assert(newCountInhabitedIslands <= archipelago.CountIslands);
    archipelago.CountInhabitedIslands = newCountInhabitedIslands;
    WriteArchipelago(fd, pMeta, &archipelago, index);
    return 0;
}