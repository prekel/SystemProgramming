#ifndef FILE_H
#define FILE_H

#include "Meta.h"

#define FILE_UNSUCCESSFUL -1

int OpenFile1(char* path);

int CloseFile1(int fd);

int CreateOrTruncateFile(char* path, size_t size);

int OpenOrCreateFile(char* path, size_t size);

bool IsExist(char* path);

off_t SeekRecord(int fd, Meta* pMeta, int index);

int WriteRecord(int fd, Meta* pMeta, void* data, int n);

int ReadRecord(int fd, Meta* pMeta, void* data, int n);

int AddRecord(int fd, Meta* pMeta, void* data);

int WriteMeta(int fd, Meta* pMeta);

int ReadMeta(int fd, Meta* pMeta);

int ChangeSize(int fd, Meta* pMeta, int n);

int RemoveSwapWithLast(int fd, Meta* pMeta, int indexToRemove);

int RemoveShift(int fd, Meta* pMeta, int index);

int ReadRecords(int fd, Meta* pMeta, void* pRecords, int index, int count);

int WriteRecords(int fd, Meta* pMeta, void* pRecords, int index, int count);

int DeleteFile(char* path);

#endif //FILE_H
