#ifndef PRINT_H
#define PRINT_H

#include <stdbool.h>

#include "Args.h"

int HexDump(int fd);

int Print(int fd, Args* pArgs, bool ignoreCond);

#endif //PRINT_H
