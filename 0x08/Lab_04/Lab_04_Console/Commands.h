#ifndef COMMANDS_H
#define COMMANDS_H

#include "Args.h"

#define ADD_COMMAND_NAME "add"

void AddCommandExec(Args* pArgs);

#define FORMAT_COMMAND_NAME "format"

void FormatCommandExec(Args* pArgs);

#define MODIFY_COMMAND_NAME "modify"

void ModifyCommandExec(Args* pArgs);

#define REMOVE_COMMAND_NAME "remove"

void RemoveCommandExec(Args* pArgs);

#define HAS_UNINHABITED_COMMAND_NAME "has"

void HasUninhabitedCommandExec(Args* pArgs);

#define WHERE_COUNT_ISLANDS_COMMAND_NAME "wherecount"

void WhereCountIslandsCommandExec(Args* pArgs);

#endif //COMMANDS_H
