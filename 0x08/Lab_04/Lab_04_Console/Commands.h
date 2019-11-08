#ifndef COMMANDS_H
#define COMMANDS_H

#include "Args.h"

#define ADD_COMMAND_NAME "add"

int AddCommandExec(int fd, Args* pArgs);

#define MODIFY_COMMAND_NAME "modify"

int ModifyCommandExec(int fd, Args* pArgs);

#define REMOVE_COMMAND_NAME "remove"

int RemoveCommandExec(int fd, Args* pArgs);

#define CREATE_COMMAND_NAME "create"

int CreateCommandExec(int fd, Args* pArgs);

#define DELETE_COMMAND_NAME "delete"

int DeleteCommandExec(int fd, Args* pArgs);

#define PRINT_COMMAND_NAME "print"

int PrintCommandExec(int fd, Args* pArgs);

#define HAS_UNINHABITED_COMMAND_NAME "has"

int HasUninhabitedCommandExec(int fd, Args* pArgs);

#define HEXDUMP_COMMAND_NAME "hexdump"

int HexdumpCommandExec(int fd, Args* pArgs);

#define HELP_COMMAND_NAME "help"
#define HELP_OPT_NAME "-h"

int HelpCommandExec(int fd, Args* pArgs);

int UnknownOptionCommandExec(int fd, Args* pArgs);

int Exec1(Args* pArgs, int (* commandExec)(int, Args*), bool isFileRequired);

int Exec(char* command, Args* pArgs);

#endif //COMMANDS_H
