#include <unistd.h>
#include <stdio.h>
#include <limits.h>

#include "HexDump.h"

#include "File.h"

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

void HexDump(int fd)
{
    unsigned char buffer[DUMP_WIDTH];
    size_t offset = 0;
    size_t bytesRead;
    int i;

    SeekToStartRecord(fd, META_INDEX);

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
