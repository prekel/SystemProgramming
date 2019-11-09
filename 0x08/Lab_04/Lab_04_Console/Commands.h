#ifndef COMMANDS_H
#define COMMANDS_H

#include "Args.h"

#define ADD_COMMAND_NAME "add"

/// Команда добавления архипелага в файл с записями.
///
/// \param fd Файловый деескриптор.
/// \param pArgs Указатель на аргументы коммандной строки.
/// \return Неотрицательное число у случае успеха, или один из отрицательных
/// кодов возврата из ReturnCodes.h или ReturnCodesLib.h.
int AddCommand(int fd, Args* pArgs);

#define MODIFY_COMMAND_NAME "modify"

/// Команда изменения содержимого записи архипелага в файле с записями.
///
/// \param fd Файловый деескриптор.
/// \param pArgs Указатель на аргументы коммандной строки.
/// \return Неотрицательное число у случае успеха, или один из отрицательных
/// кодов возврата из ReturnCodes.h или ReturnCodesLib.h.
int ModifyCommand(int fd, Args* pArgs);

#define REMOVE_COMMAND_NAME "remove"

/// Команда удаления архипелага из файла с записями.
///
/// \param fd Файловый деескриптор.
/// \param pArgs Указатель на аргументы коммандной строки.
/// \return Неотрицательное число у случае успеха, или один из отрицательных
/// кодов возврата из ReturnCodes.h или ReturnCodesLib.h.
int RemoveCommand(int fd, Args* pArgs);

#define CREATE_COMMAND_NAME "create"

/// Команда создания пустого файла с записями.
///
/// \param fd Файловый деескриптор.
/// \param pArgs Указатель на аргументы коммандной строки.
/// \return Неотрицательное число у случае успеха, или один из отрицательных
/// кодов возврата из ReturnCodes.h или ReturnCodesLib.h.
int CreateCommand(int fd, Args* pArgs);

#define DELETE_COMMAND_NAME "delete"

/// Команда удаления файла с записями.
///
/// \param fd Файловый деескриптор.
/// \param pArgs Указатель на аргументы коммандной строки.
/// \return Неотрицательное число у случае успеха, или один из отрицательных
/// кодов возврата из ReturnCodes.h или ReturnCodesLib.h.
int DeleteCommand(int fd, Args* pArgs);

#define PRINT_COMMAND_NAME "print"

/// Команда вывода архипелагов по условию или без по заданнаму формату из
/// файла с записями.
///
/// \param fd Файловый деескриптор.
/// \param pArgs Указатель на аргументы коммандной строки.
/// \return Неотрицательное число у случае успеха, или один из отрицательных
/// кодов возврата из ReturnCodes.h или ReturnCodesLib.h.
int PrintCommand(int fd, Args* pArgs);

#define HAS_UNINHABITED_COMMAND_NAME "has_un"

/// Команда выполнения запроса, выясняющего имеются ли архипелаги, состоящие
/// только из необитаемых островов.
///
/// \param fd Файловый деескриптор.
/// \param pArgs Указатель на аргументы коммандной строки.
/// \return Неотрицательное число у случае успеха, или один из отрицательных
/// кодов возврата из ReturnCodes.h или ReturnCodesLib.h.
int HasUninhabitedCommand(int fd, Args* pArgs);

#define HEXDUMP_COMMAND_NAME "hexdump"

/// Команда вывода шестнадцатиричного дампа файла.
///
/// \param fd Файловый деескриптор.
/// \param pArgs Указатель на аргументы коммандной строки.
/// \return Неотрицательное число у случае успеха, или один из отрицательных
/// кодов возврата из ReturnCodes.h или ReturnCodesLib.h.
int HexdumpCommand(int fd, Args* pArgs);

#define HELP_COMMAND_NAME "help"
#define HELP_OPT_NAME "-h"

/// Команда вывода справки.
///
/// \param fd Файловый деескриптор.
/// \param pArgs Указатель на аргументы коммандной строки.
/// \return Неотрицательное число у случае успеха, или один из отрицательных
/// кодов возврата из ReturnCodes.h или ReturnCodesLib.h.
int HelpCommand(int fd, Args* pArgs);

/// Команда обработки заданного неизвестного параметра.
///
/// \param fd Файловый деескриптор.
/// \param pArgs Указатель на аргументы коммандной строки.
/// \return Неотрицательное число у случае успеха, или один из отрицательных
/// кодов возврата из ReturnCodes.h или ReturnCodesLib.h.
int UnknownOptionCommand(int fd, Args* pArgs);

/// Выполняет команду. Перед этим открывет/создаёт файл если требется и после
/// выводит содержимое и/или шестнадцатиричный дамп если требуется, а так же
/// закрывает файл.
///
/// \param pArgs Указатель на аргументы коммандной строки.
/// \param commandExec Указатель на функцию команды.
/// \param isFileRequired Требуется ли создавать/открывать/закрывать файл.
/// \return Если не удалось создать файл, то FILE_UNSUCCESSFUL. Если
/// не удалось закрыть файл, то CLOSE_UNSUCCESSFUL. Иначе результат выполнения
/// команды.
int CommandExec(Args* pArgs,
                int (* commandExec)(int, Args*),
                bool isFileRequired);

/// Выполняет команду с заданым именем и выводит сообщение об ошибке в случае
/// неудачного выполнения команды или ли верерно заданных аргументов.
///
/// \param command Название команды.
/// \param pArgs Указатель на аргументы командной строки.
/// \return EXIT_SUCCESS (0) в случае успешного завершения команды,
/// EXIT_FAILURE (1) в случае какой-либо ошибки.
int Exec(char* command, Args* pArgs);

#endif //COMMANDS_H
