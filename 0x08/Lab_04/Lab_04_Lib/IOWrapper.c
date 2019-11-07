#ifdef _MSC_VER

#include <io.h>
#include <fcntl.h>
#include <sys\types.h>
#include <sys\stat.h>


#else

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#endif


#include "IOWrapper.h"

int Open1(char* path, int flags, int mode)
{
#ifdef _MSC_VER
    return _open(path, flags, mode);
#else
    return open(path, flags, mode);
#endif
}

int Close1(int fd)
{
#ifdef _MSC_VER
    return _close(fd);
#else
    return close(fd);
#endif
}

int Read1(int fd, void* buf, unsigned int size)
{
#ifdef _MSC_VER
    return _read(fd, buf, size);
#else
    return read(fd, buf, size);
#endif
}

int Write1(int fd, void* buf, unsigned size)
{
#ifdef _MSC_VER
    return _write(fd, buf, size);
#else
    return write(fd, buf, size);
#endif
}

int Unlink1(char* path)
{
#ifdef _MSC_VER
    return _unlink(path);
#else
    return unlink(path);
#endif
}

int Lseek1(int fd, unsigned int offset, int whence)
{
#ifdef _MSC_VER
    return _lseek(fd, offset, whence);
#else
    return lseek(fd, offset, whence);
#endif
}

int Ftruncate1(int fd, unsigned int length)
{
#ifdef _MSC_VER
    return _ftruncate(fd, length);
#else
    return ftruncate(fd, length);
#endif
}

int Access1(char* path, int mode)
{
#ifdef _MSC_VER
    return _access(path, mode);
#else
    return access(path, mode);
#endif
}