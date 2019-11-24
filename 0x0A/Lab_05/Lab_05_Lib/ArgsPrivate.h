#ifndef ARGS_PRIVATE_H
#define ARGS_PRIVATE_H

#include "Args.h"

#define DEFAULT_IP_ADDRESS "127.0.0.1"
#define DEFAULT_PORT 20522
#define DEFAULT_PORT_STR "20522"


#define OPT_PORT 'p'
#define OPT_PORT_USAGE "-p целое"
#define OPT_PORT_DESCRIPTION "Порт. По умолчанию " DEFAULT_PORT_STR "."

#define OPT_HELP 'h'
#define OPT_HELP_USAGE "-h"
#define OPT_HELP_DESCRIPTION "Требуется ли вывод справки."

#define OPT_UNKNOWN '?'


#define HELP_SEP ": "
#define HELP_SUFFIX "\n"

void UnknownOptionInternal(char unknownOption);

#endif //ARGS_PRIVATE_H
