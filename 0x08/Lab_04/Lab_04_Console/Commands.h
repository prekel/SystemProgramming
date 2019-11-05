#ifndef COMMANDS_H
#define COMMANDS_H

#include "Args.h"

#define ADD_COMMAND_NAME "add"

void AddCommandExec(Args* pArgs);

#define FORMAT_COMMAND_NAME "format"

void FormatCommandExec(Args* pArgs);

#define MODIFY_COMMAND_NAME "modify"

void ModifyCommandExec(Args* pArgs);

#endif //COMMANDS_H
