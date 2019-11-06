#ifndef COMMANDS_H
#define COMMANDS_H

#include "Args.h"

#define BAD_ARGS -4
#define FILE_NOT_EXIST -5
#define CLOSE_UNSUCCESSFUL -6

#define ADD_COMMAND_NAME "add"

int AddCommandExec(int fd, Args* pArgs);

#define MODIFY_COMMAND_NAME "modify"

int ModifyCommandExec(Args* pArgs);

#define REMOVE_COMMAND_NAME "remove"

int RemoveCommandExec(Args* pArgs);

#define DELETE_COMMAND_NAME "delete"

void DeleteCommandExec(Args* pArgs);

#define PRINT_COMMAND_NAME "print"

int PrintCommandExec(Args* pArgs);

#define HAS_UNINHABITED_COMMAND_NAME "has"

int HasUninhabitedCommandExec(Args* pArgs);

#define HEXDUMP_COMMAND_NAME "hexdump"

int HexdumpCommandExec(Args* pArgs);

#define HELP_COMMAND_NAME "help"
#define HELP_OPT_NAME "-h"

int HelpCommandExec(Args* pArgs);

int UnknownOptionCommandExec(Args* pArgs);

int Exec(char* command, Args* pArgs);

#endif //COMMANDS_H
