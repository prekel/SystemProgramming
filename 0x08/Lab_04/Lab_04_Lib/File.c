#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>

#include "File.h"
#include "Meta.h"

int OpenFile1(char* path)
{
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
    int fd = open(path, O_RDWR, mode);


    bool checkMetaVersion = CheckMetaVersion(fd);
    assert(checkMetaVersion);

    return fd;
}

int CreateFile1(char* path, size_t size)
{
    Meta meta;
    FillMeta(&meta, size);

    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
    int fd = open(path, O_RDWR | O_CREAT | O_TRUNC, mode);

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
    return CreateFile1(path, size);
}

bool IsExist(char* path)
{
    return access(path, F_OK | R_OK | W_OK) != -1;
}

int CloseFile1(int fd)
{
    return close(fd);
}

off_t SeekRecord(int fd, Meta* pMeta, int index)
{
    if (index == META_INDEX)
    {
        return lseek(fd, 0, SEEK_SET);
    }
    if (pMeta == NULL)
    {
        return FILE_UNSUCCESSFUL;
    }
    return lseek(fd, sizeof(Meta) + index * pMeta->Size, SEEK_SET);
}

ssize_t WriteRecord(int fd, Meta* pMeta, void* data, int n)
{
    if (SeekRecord(fd, pMeta, n) == FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }
    return write(fd, data, pMeta->Size);
}

ssize_t ReadRecord(int fd, Meta* pMeta, void* data, int n)
{
    if (SeekRecord(fd, pMeta, n) == FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }
    return read(fd, data, pMeta->Size);
}

ssize_t AddRecord(int fd, Meta* pMeta, void* data)
{
    pMeta->Count++;
    if (WriteMeta(fd, pMeta) == FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }

    return WriteRecord(fd, pMeta, data, pMeta->Count - 1);
}

ssize_t WriteMeta(int fd, Meta* pMeta)
{
    if (SeekRecord(fd, pMeta, META_INDEX) ==
        FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }
    return write(fd, pMeta, sizeof(Meta));
}

ssize_t ReadMeta(int fd, Meta* pMeta)
{
    if (SeekRecord(fd, pMeta, META_INDEX) ==
        FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }
    return read(fd, pMeta, sizeof(Meta));
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

size_t CalculatedFileSize(Meta* pMeta)
{
    return sizeof(Meta) + pMeta->Count * pMeta->Count;
}

ssize_t ReadRecords(int fd, Meta* pMeta, void* pRecords, int index, int count)
{
    if (SeekRecord(fd, pMeta, index) == FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }
    return read(fd, pRecords, pMeta->Size * count);
}

ssize_t WriteRecords(int fd,
                     Meta* pMeta,
                     void* pRecords,
                     int index,
                     int count)
{
    if (SeekRecord(fd, pMeta, index) == FILE_UNSUCCESSFUL)
    {
        return FILE_UNSUCCESSFUL;
    }
    return write(fd, pRecords, pMeta->Size * count);
}

int DeleteFile(char* path)
{
    return unlink(path);
}
