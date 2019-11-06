#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <string.h>

#include "Print.h"
#include "File.h"
#include "Archipelago.h"

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

int HexDump(int fd)
{
    unsigned char buffer[DUMP_WIDTH];
    size_t offset = 0;
    size_t bytesRead;
    int i;

    SeekRecord(fd, NULL, META_INDEX);

    printf("\n");
    do
    {
        /* Read the next lines's worth of bytes.  */
        bytesRead = read(fd, buffer, sizeof(buffer));

        /* Print the offset in the file, followed by the bytes themselves.  */
        printf("0x%06zx : ", offset);
        for (i = 0; i < bytesRead; ++i)
            printf("%02x ", buffer[i]);

        for (i = 0; i < DUMP_WIDTH - bytesRead; i++)
        {
            printf("   ");
        }

        printf("    ");
        for (i = 0; i < bytesRead; ++i)
        {
            unsigned char c;
            if (buffer[i] == '\0')
            {
                c = ' ';
            }
            else if (IsBadCharFull(buffer[i]))
            {
                c = '.';
            }
            else
            {
                c = buffer[i];
            }

            printf("%c", c);
        }
        for (i = 0; i < DUMP_WIDTH - bytesRead; i++)
        {
            printf(" ");
        }

        printf("    ");
        for (i = 0; i < bytesRead; ++i)
        {
            unsigned char c;
            if (buffer[i] == '\0')
            {
                c = ' ';
            }
            else if (IsBadChar(buffer[i]))
            {
                c = '.';
            }
            else
            {
                c = buffer[i];
            }

            printf("%c", c);
        }

        printf("\n");

        /* Keep count of our position in the file.  */
        offset += bytesRead;
    } while (bytesRead == sizeof(buffer));

    printf("\n");
}

int Print(int fd, Args* pArgs, bool ignoreCond)
{
    Meta meta;
    int readMeta = ReadMeta(fd, &meta);
    assert(readMeta != FILE_UNSUCCESSFUL);

    printf(pArgs->MetaFormat, meta.Version, meta.Size, meta.Count);
    printf("\n");

    int c = 0;
    for (int i = 0; i < meta.Count; i++)
    {
        Archipelago archipelago;
        ReadArchipelago(fd, &meta, &archipelago, i);

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
}