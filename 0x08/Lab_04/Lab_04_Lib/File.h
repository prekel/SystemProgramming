#ifndef FILE_H
#define FILE_H

#include "Meta.h"

#define FILE_UNSUCCESSFUL -1

int OpenFile1(char* path);

int CloseFile1(int fd);

int CreateFile1(char* path, size_t size);

int OpenOrCreateFile(char* path, size_t size);

bool IsExist(char* path);

off_t SeekRecord(int fd, Meta* pMeta, int index);

ssize_t WriteRecord(int fd, Meta* pMeta, void* data, int n);

ssize_t ReadRecord(int fd, Meta* pMeta, void* data, int n);

ssize_t AddRecord(int fd, Meta* pMeta, void* data);

ssize_t WriteMeta(int fd, Meta* meta);

ssize_t ReadMeta(int fd, Meta* meta);

int ChangeSize(int fd, Meta* pMeta, int n);

int RemoveSwapWithLast(int fd, Meta* pMeta, int indexToRemove);

int RemoveShift(int fd, Meta* pMeta, int index);

size_t CalculatedFileSize(Meta* pMeta);

ssize_t ReadRecords(int fd, Meta* pMeta, void* pRecords, int index, int count);

ssize_t WriteRecords(int fd, Meta* pMeta, void* pRecords, int index, int count);

int DeleteFile(char* path);

#endif //FILE_H
