#include "IOWrapper.h"

int OpenWrap(char* path, int flags, int mode)
{
#ifdef _MSC_VER
    return _open(path, flags, mode);
#else
    return open(path, flags, mode);
#endif
}

int CloseWrap(int fd)
{
#ifdef _MSC_VER
    return _close(fd);
#else
    return close(fd);
#endif
}

int ReadWrap(int fd, void* buf, unsigned int size)
{
#ifdef _MSC_VER
    return _read(fd, buf, size);
#else
    return read(fd, buf, size);
#endif
}

int WriteWrap(int fd, void* buf, unsigned int size)
{
#ifdef _MSC_VER
    return _write(fd, buf, size);
#else
    return write(fd, buf, size);
#endif
}

int UnlinkWrap(char* path)
{
#ifdef _MSC_VER
    return _unlink(path);
#else
    return unlink(path);
#endif
}

int LseekWrap(int fd, unsigned int offset, int whence)
{
#ifdef _MSC_VER
    return _lseek(fd, offset, whence);
#else
    return lseek(fd, offset, whence);
#endif
}

int FtruncateWrap(int fd, unsigned int length)
{
#ifdef _MSC_VER
    return _ftruncate(fd, length);
#else
    return ftruncate(fd, length);
#endif
}

int AccessWrap(char* path, int mode)
{
#ifdef _MSC_VER
    return _access(path, mode);
#else
    return access(path, mode);
#endif
}