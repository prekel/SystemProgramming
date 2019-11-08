#include <string.h>
#include <assert.h>

#include "Archipelago.h"
#include "Meta.h"
#include "RecordFile.h"
#include "ReturnCodesLib.h"

int FillArchipelago(Archipelago* pArchipelago,
                    char* name,
                    int countIslands,
                    int countInhabitedIslands)
{
    if (!(strlen(name) + 1 <= ARCHIPELAGO_NAME_LENGTH &&
          countIslands > 1 &&
          countInhabitedIslands >= 0 &&
          countIslands >= countInhabitedIslands))
    {
        return BAD_VALUE;
    }
    RETURN_IF_NOT_SUCCESSFUL(SetName(pArchipelago, name));
//    int setName = SetName(pArchipelago, name);
//    if (setName < 0)
//    {
//        return setName;
//    }
    pArchipelago->CountIslands = countIslands;
    pArchipelago->CountInhabitedIslands = countInhabitedIslands;
    return SUCCESSFUL;
}

int VerifyArchipelago(Archipelago* pArchipelago)
{
    if (pArchipelago->Name[ARCHIPELAGO_NAME_LENGTH - 1] != '\0' ||
        pArchipelago->CountIslands < 2 ||
        pArchipelago->CountIslands < pArchipelago->CountInhabitedIslands ||
        pArchipelago->CountInhabitedIslands < 0)
    {
        return BAD_RECORD;
    }
    return SUCCESSFUL;
}

int SetName(Archipelago* pArchipelago, char* name)
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

int ReadArchipelago(int fd,
                    Meta* pMeta,
                    Archipelago* pArchipelago,
                    int index)
{
    return ReadRecord(fd, pMeta, pArchipelago, index);
}

int WriteArchipelago(int fd,
                     Meta* pMeta,
                     Archipelago* pArchipelago,
                     int index)
{
    return WriteRecord(fd, pMeta, pArchipelago, index);
}

int AddArchipelago(int fd, Meta* pMeta, Archipelago* pArchipelago)
{
    return AddRecord(fd, pMeta, pArchipelago);
}

int IndexByName(int fd, Meta* pMeta, char* name)
{
    for (int i = 0; i < pMeta->Count; i++)
    {
        Archipelago archipelago;
        RETURN_IF_NOT_SUCCESSFUL(ReadArchipelago(fd, pMeta, &archipelago, i));
//        if (ReadArchipelago(fd, pMeta, &archipelago, i) ==
//            FILE_UNSUCCESSFUL)
//        {
//            return NOT_FOUND;
//        }
        RETURN_IF_NOT_SUCCESSFUL(VerifyArchipelago(&archipelago));
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
    RETURN_IF_NOT_SUCCESSFUL(ReadArchipelago(fd, pMeta, &archipelago, index));
//    if (ReadArchipelago(fd, pMeta, &archipelago, index) ==
//        FILE_UNSUCCESSFUL)
//    {
//        return FILE_UNSUCCESSFUL;
//    }
    RETURN_IF_NOT_SUCCESSFUL(VerifyArchipelago(&archipelago));
    RETURN_IF_NOT_SUCCESSFUL(SetName(&archipelago, newName));
//    int setName = SetName(&archipelago, newName);
//    if (setName < 0)
//    {
//        return setName;
//    }
    return WriteArchipelago(fd, pMeta, &archipelago, index);
}

int ModifyCountIslands(int fd, Meta* pMeta, int index, int newCountIslands)
{
    if (newCountIslands <= 1)
    {
        return BAD_VALUE;
    }
    Archipelago archipelago;
    RETURN_IF_NOT_SUCCESSFUL(ReadArchipelago(fd, pMeta, &archipelago, index));
//    if (ReadArchipelago(fd, pMeta, &archipelago, index) ==
//        FILE_UNSUCCESSFUL)
//    {
//        return FILE_UNSUCCESSFUL;
//    }
    RETURN_IF_NOT_SUCCESSFUL(VerifyArchipelago(&archipelago));
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
    RETURN_IF_NOT_SUCCESSFUL(ReadArchipelago(fd, pMeta, &archipelago, index));
//    if (ReadArchipelago(fd, pMeta, &archipelago, index) ==
//        FILE_UNSUCCESSFUL)
//    {
//        return FILE_UNSUCCESSFUL;
//    }
    RETURN_IF_NOT_SUCCESSFUL(VerifyArchipelago(&archipelago));
    if (newCountInhabitedIslands > archipelago.CountIslands)
    {
        return BAD_VALUE;
    }
    archipelago.CountInhabitedIslands = newCountInhabitedIslands;
    return WriteArchipelago(fd, pMeta, &archipelago, index);
}
