//#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <string.h>

#include "Print.h"
#include "File.h"
#include "Archipelago.h"
#include "Commands.h"
#include "IOWrapper.h"
#include "ReturnCodesLib.h"

#define FIRST_NON_CONTROL_CHAR ' '

static bool IsBadCharFull(unsigned char c)
{
    return !(FIRST_NON_CONTROL_CHAR <= c && c <= CHAR_MAX);
}

static bool IsBadChar(unsigned char c)
{
    return c < FIRST_NON_CONTROL_CHAR;
}

#define DUMP_WIDTH 16

#define COLUMN_SEPARATOR "    "

#define NULL_CHAR_DISPLAY ' '

#define CONTROL_CHAR_DISPLAY '.'

#define FIRST_COLUMN_FORMAT "0x%06zx : "

#define HEX_BYTE_FORMAT "%02x "

#define HEX_BYTE_EMPTY "   "

#define CHAR_EMPTY " "

#define CHAR_FORMAT "%c"

int HexDump(int fd)
{
    unsigned char buffer[DUMP_WIDTH];
    size_t offset = 0;
    size_t bytesRead;
    int i;

    RETURN_IF_NOT_SUCCESSFUL(SeekRecord(fd, NULL, META_INDEX));
//    if (SeekRecord(fd, NULL, META_INDEX) == FILE_UNSUCCESSFUL)
//    {
//        return FILE_UNSUCCESSFUL;
//    }

    printf("\n");
    do
    {
        RETURN_IF_NOT_SUCCESSFUL(
                bytesRead = ReadWrap(fd, buffer, sizeof(buffer)));

        printf(FIRST_COLUMN_FORMAT, offset);
        for (i = 0; i < bytesRead; ++i)
        {
            printf(HEX_BYTE_FORMAT, buffer[i]);
        }

        for (i = 0; i < DUMP_WIDTH - bytesRead; i++)
        {
            printf(HEX_BYTE_EMPTY);
        }

        printf(COLUMN_SEPARATOR);
        for (i = 0; i < bytesRead; ++i)
        {
            unsigned char c;
            if (buffer[i] == '\0')
            {
                c = NULL_CHAR_DISPLAY;
            }
            else if (IsBadCharFull(buffer[i]))
            {
                c = CONTROL_CHAR_DISPLAY;
            }
            else
            {
                c = buffer[i];
            }

            printf(CHAR_FORMAT, c);
        }
        for (i = 0; i < DUMP_WIDTH - bytesRead; i++)
        {
            printf(CHAR_EMPTY);
        }

        printf(COLUMN_SEPARATOR);
        for (i = 0; i < bytesRead; ++i)
        {
            unsigned char c;
            if (buffer[i] == '\0')
            {
                c = NULL_CHAR_DISPLAY;
            }
            else if (IsBadChar(buffer[i]))
            {
                c = CONTROL_CHAR_DISPLAY;
            }
            else
            {
                c = buffer[i];
            }

            printf(CHAR_FORMAT, c);
        }

        printf("\n");

        offset += bytesRead;
    } while (bytesRead == sizeof(buffer));

    printf("\n");

    return SUCCESSFUL;
}

int Print(int fd, Args* pArgs, bool ignoreCond)
{
    Meta meta;
    RETURN_IF_NOT_SUCCESSFUL(ReadMeta(fd, &meta));
//    int readMeta = ReadMeta(fd, &meta);
//    if (readMeta == FILE_UNSUCCESSFUL)
//    {
//        return FILE_UNSUCCESSFUL;
//    }

    printf(pArgs->MetaFormat,
           meta.Version,
           meta.Count,
           meta.RecordSize,
           meta.MetaSize);
    printf("\n");

    int c = 0;
    for (int i = 0; i < meta.Count; i++)
    {
        Archipelago archipelago;
        RETURN_IF_NOT_SUCCESSFUL(ReadArchipelago(fd, &meta, &archipelago, i));
//        if (ReadArchipelago(fd, &meta, &archipelago, i) == FILE_UNSUCCESSFUL)
//        {
//            return FILE_UNSUCCESSFUL;
//        }
        RETURN_IF_NOT_SUCCESSFUL(VerifyArchipelago(&archipelago));

        bool condOrIsNameGiven =
                pArgs->IsNameGiven &&
                strcmp(archipelago.Name, pArgs->Name) == 0;
        bool condOrIsCountIslandsGiven =
                pArgs->IsCountIslandsGiven &&
                archipelago.CountIslands == pArgs->CountIslands;
        bool condOrIsCountInhabitedIslandsGiven =
                pArgs->IsCountInhabitedIslandsGiven &&
                archipelago.CountInhabitedIslands ==
                pArgs->CountInhabitedIslands;

        bool condAndIsNameGiven =
                (pArgs->IsNameGiven &&
                 strcmp(archipelago.Name, pArgs->Name) == 0) ||
                !pArgs->IsNameGiven;
        bool condAndIsCountIslandsGiven =
                (pArgs->IsCountIslandsGiven &&
                 archipelago.CountIslands == pArgs->CountIslands) ||
                !pArgs->IsCountIslandsGiven;
        bool condAndIsCountInhabitedIslandsGiven =
                (pArgs->IsCountInhabitedIslandsGiven &&
                 archipelago.CountInhabitedIslands ==
                 pArgs->CountInhabitedIslands) ||
                !pArgs->IsCountInhabitedIslandsGiven;

        if (ignoreCond ||
            (pArgs->IsOr
             ? condOrIsNameGiven ||
               condOrIsCountIslandsGiven ||
               condOrIsCountInhabitedIslandsGiven
             : condAndIsNameGiven &&
               condAndIsCountIslandsGiven &&
               condAndIsCountInhabitedIslandsGiven))
        {
            printf(pArgs->Format,
                   archipelago.Name,
                   archipelago.CountIslands,
                   archipelago.CountInhabitedIslands);
            printf("\n");
            c++;
        }
    }

    printf(pArgs->CountFormat, c);
    printf("\n");

    return SUCCESSFUL;
}
