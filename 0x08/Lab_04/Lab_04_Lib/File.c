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

    int writeMeta = WriteMeta(fd, &meta);
    assert(writeMeta != -1);

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

off_t SeekToStartRecord(int fd, int n)
{
    if (n == -1)
    {
        return lseek(fd, 0, SEEK_SET);
    }

    Meta meta;
    int readMeta = ReadMeta(fd, &meta);
    assert(readMeta != -1);
    return lseek(fd, sizeof(meta) + n * meta.Size, SEEK_SET);
}

ssize_t WriteRecord(int fd, Meta* pMeta, void* data, int n)
{
    SeekToStartRecord(fd, n);
    return write(fd, data, pMeta->Size);
}

ssize_t ReadRecord(int fd, Meta* pMeta, void* data, int n)
{
    SeekToStartRecord(fd, n);
    return read(fd, data, pMeta->Size);
}

ssize_t AddRecord(int fd, Meta* pMeta, void* data)
{
    pMeta->Count++;
    WriteMeta(fd, pMeta);

    return WriteRecord(fd, pMeta, data, pMeta->Count - 1);
}

int ChangeSize(int fd, int n)
{
    Meta meta;
    int readMeta = ReadMeta(fd, &meta);
    assert(readMeta != -1);

    return ftruncate(fd, sizeof(Meta) + n * meta.Size);
}

void RemoveSwapWithLast(int fd, Meta* pMeta, int indexToRemove)
{
    pMeta->Count--;
    WriteMeta(fd, pMeta);

    if (pMeta->Count > 0)
    {
        char data[pMeta->Size];
        ReadRecord(fd, pMeta, &data, pMeta->Count);
        WriteRecord(fd, pMeta, &data, indexToRemove);
    }

    ChangeSize(fd, pMeta->Count);
}

void RemoveShift(int fd, Meta* pMeta, int index)
{
    if (pMeta->Count > 1)
    {
        int n = pMeta->Count - index - 1;
        char dataShift[pMeta->Size * n];
        ReadRecords(fd, pMeta, &dataShift, index + 1, n);
        WriteRecords(fd, pMeta, &dataShift, index, n);
    }

    pMeta->Count--;
    WriteMeta(fd, pMeta);

    ChangeSize(fd, pMeta->Count);
}

size_t CalculatedFileSize(Meta* pMeta)
{
    return sizeof(Meta) + pMeta->Count * pMeta->Count;
}

ssize_t ReadRecords(int fd, Meta* pMeta, void* allData, int index, int count)
{
    SeekToStartRecord(fd, index);
    return read(fd, allData, pMeta->Size * count);
}

ssize_t WriteRecords(int fd, Meta* pMeta, void* allData, int index, int count)
{
    SeekToStartRecord(fd, index);
    return write(fd, allData, pMeta->Size * count);
}

int DeleteFile(char* path)
{
    return unlink(path);
}
