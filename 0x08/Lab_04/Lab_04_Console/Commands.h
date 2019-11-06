#ifndef COMMANDS_H
#define COMMANDS_H

#include "Args.h"

#define ADD_COMMAND_NAME "add"

void AddCommandExec(Args* pArgs);

#define MODIFY_COMMAND_NAME "modify"

void ModifyCommandExec(Args* pArgs);

#define REMOVE_COMMAND_NAME "remove"

void RemoveCommandExec(Args* pArgs);

#define DELETE_COMMAND_NAME "delete"

void DeleteCommandExec(Args* pArgs);

#define PRINT_COMMAND_NAME "print"

void PrintCommandExec(Args* pArgs);

#define HAS_UNINHABITED_COMMAND_NAME "has"

void HasUninhabitedCommandExec(Args* pArgs);

#define HEXDUMP_COMMAND_NAME "hexdump"

void HexdumpExec(Args* pArgs);

#define HELP_COMMAND_NAME "help"
#define HELP_OPT_NAME "-h"

void HelpExec(Args* pArgs);

void UnknownOptionExec(Args* pArgs);

int Exec(char* command, Args* pArgs);

#endif //COMMANDS_H
