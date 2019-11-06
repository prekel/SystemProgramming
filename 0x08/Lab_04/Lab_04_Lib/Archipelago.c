#include <string.h>
#include <assert.h>

#include "Archipelago.h"
#include "Meta.h"
#include "File.h"

int FillArchipelago(Archipelago* pArchipelago,
                    char* name,
                    int countIslands,
                    int countInhabitedIslands)
{
    if (!(strlen(name) + 1 <= ARCHIPELAGO_NAME_LENGTH && countIslands > 1 &&
          countInhabitedIslands >= 0 &&
          countIslands >= countInhabitedIslands))
    {
        return BAD_VALUE;
    }
    int setName = SetName(pArchipelago, name);
    if (setName < 0)
    {
        return setName;
    }
    pArchipelago->CountIslands = countIslands;
    pArchipelago->CountInhabitedIslands = countInhabitedIslands;
    return 0;
}

int SetName(Archipelago* pArchipelago, const char* name)
{
    if (name == NULL || name[0] == '\0')
    {
        return BAD_VALUE;
    }
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
        if (ReadArchipelago(fd, pMeta, &archipelago, i) ==
            FILE_UNSUCCESSFUL)
        {
            return NOT_FOUND;
        }
        if (strcmp(archipelago.Name, name) == 0)
        {
            return i;
        }
    }
    return NOT_FOUND;
}

int ModifyName(int fd, Meta* pMeta, int index, char* newName)
{
    if (strlen(newName) + 1 > ARCHIPELAGO_NAME_LENGTH)
    {
        return BAD_VALUE;
    }
    Archipelago archipelago;
    if (ReadArchipelago(fd, pMeta, &archipelago, index) ==
        FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }
    int setName = SetName(&archipelago, newName);
    if (setName < 0)
    {
        return setName;
    }
    return WriteArchipelago(fd, pMeta, &archipelago, index);
}

int ModifyCountIslands(int fd, Meta* pMeta, int index, int newCountIslands)
{
    if (newCountIslands <= 1)
    {
        return BAD_VALUE;
    }
    Archipelago archipelago;
    if (ReadArchipelago(fd, pMeta, &archipelago, index) ==
        FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }
    if (newCountIslands < archipelago.CountInhabitedIslands)
    {
        return BAD_VALUE;
    }
    archipelago.CountIslands = newCountIslands;
    return WriteArchipelago(fd, pMeta, &archipelago, index);
}

int ModifyCountInhabitedIslands(int fd,
                                Meta* pMeta,
                                int index,
                                int newCountInhabitedIslands)
{
    if (newCountInhabitedIslands < 0)
    {
        return BAD_VALUE;
    }
    Archipelago archipelago;
    if (ReadArchipelago(fd, pMeta, &archipelago, index) ==
        FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }
    if (newCountInhabitedIslands > archipelago.CountIslands)
    {
        return BAD_VALUE;
    }
    archipelago.CountInhabitedIslands = newCountInhabitedIslands;
    return WriteArchipelago(fd, pMeta, &archipelago, index);
}
