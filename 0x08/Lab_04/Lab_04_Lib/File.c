#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>

#include "File.h"
#include "Meta.h"
#include "IOWrapper.h"

int OpenFile1(char* path)
{
    int fd = Open1(path, OPEN_FLAGS, READ_WRITE_MODE);

    bool checkMetaVersion = CheckMetaVersion(fd);
    if (!checkMetaVersion)
    {
        return BAD_META;
    }

    return fd;
}

int CreateOrTruncateFile(char* path, size_t size)
{
    Meta meta;
    FillMeta(&meta, size);

    int fd = Open1(path, CREATE_TRUNCATE_FLAGS, READ_WRITE_MODE);

    if (WriteMeta(fd, &meta) == FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }

    return fd;
}

int OpenOrCreateFile(char* path, size_t size)
{
    if (IsExist(path))
    {
        return OpenFile1(path);
    }
    return CreateOrTruncateFile(path, size);
}

bool IsExist(char* path)
{
    return access(path, F_OK | R_OK | W_OK) != -1;
}

int CloseFile1(int fd)
{
    return Close1(fd);
}

off_t SeekRecord(int fd, Meta* pMeta, int index)
{
    if (index == META_INDEX)
    {
        return Lseek1(fd, 0, SEEK_SET);
    }
    if (pMeta == NULL)
    {
        return FILE_UNSUCCESSFUL;
    }
    return Lseek1(fd, sizeof(Meta) + index * pMeta->Size, SEEK_SET);
}

int WriteRecord(int fd, Meta* pMeta, void* data, int n)
{
    if (SeekRecord(fd, pMeta, n) == FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }
    return Write1(fd, data, pMeta->Size);
}

int ReadRecord(int fd, Meta* pMeta, void* data, int n)
{
    if (SeekRecord(fd, pMeta, n) == FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }
    return Read1(fd, data, pMeta->Size);
}

int AddRecord(int fd, Meta* pMeta, void* data)
{
    pMeta->Count++;
    if (WriteMeta(fd, pMeta) == FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }

    return WriteRecord(fd, pMeta, data, pMeta->Count - 1);
}

int WriteMeta(int fd, Meta* pMeta)
{
    if (SeekRecord(fd, pMeta, META_INDEX) ==
        FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }
    return Write1(fd, pMeta, sizeof(Meta));
}

int ReadMeta(int fd, Meta* pMeta)
{
    if (SeekRecord(fd, pMeta, META_INDEX) ==
        FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }
    return Read1(fd, pMeta, sizeof(Meta));
}

int ChangeSize(int fd, Meta* pMeta, int n)
{
    return ftruncate(fd, sizeof(Meta) + n * pMeta->Size);
}

int RemoveSwapWithLast(int fd, Meta* pMeta, int indexToRemove)
{
    if (pMeta->Count > 1)
    {
        char data[pMeta->Size];
        if (ReadRecord(fd, pMeta, &data, pMeta->Count - 1) ==
            FILE_UNSUCCESSFUL)
        {
            return FILE_UNSUCCESSFUL;
        }
        if (WriteRecord(fd, pMeta, &data, indexToRemove) ==
            FILE_UNSUCCESSFUL)
        {
            return FILE_UNSUCCESSFUL;
        }
    }

    pMeta->Count--;
    if (WriteMeta(fd, pMeta) == FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }

    return ChangeSize(fd, pMeta, pMeta->Count);
}

int RemoveShift(int fd, Meta* pMeta, int index)
{
    if (pMeta->Count > 1)
    {
        int n = pMeta->Count - index - 1;
        char dataShift[pMeta->Size * n];
        if (ReadRecords(fd, pMeta, &dataShift, index + 1, n) ==
            FILE_UNSUCCESSFUL)
        {
            return FILE_UNSUCCESSFUL;
        }
        if (WriteRecords(fd, pMeta, &dataShift, index, n) ==
            FILE_UNSUCCESSFUL)
        {
            return FILE_UNSUCCESSFUL;
        }
    }

    pMeta->Count--;
    if (WriteMeta(fd, pMeta) == FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }

    return ChangeSize(fd, pMeta, pMeta->Count);
}

int ReadRecords(int fd, Meta* pMeta, void* pRecords, int index, int count)
{
    if (SeekRecord(fd, pMeta, index) == FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }
    return Read1(fd, pRecords, pMeta->Size * count);
}

int WriteRecords(int fd,
                 Meta* pMeta,
                 void* pRecords,
                 int index,
                 int count)
{
    if (SeekRecord(fd, pMeta, index) == FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }
    return Write1(fd, pRecords, pMeta->Size * count);
}

int DeleteFile(char* path)
{
    return Unlink1(path);
}
