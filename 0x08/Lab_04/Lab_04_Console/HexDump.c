#include <unistd.h>
#include <stdio.h>

#include "HexDump.h"

#include "File.h"

void HexDump(int fd)
{
    unsigned char buffer[16];
    size_t offset = 0;
    size_t bytesRead;
    int i;

    SeekToStartRecord(fd, -1);

    do
    {
        /* Read the next lines's worth of bytes.  */
        bytesRead = read(fd, buffer, sizeof (buffer));

        /* Print the offset in the file, followed by the bytes themselves.  */
        printf("0x%06zx : ", offset);
        for (i = 0; i < bytesRead; ++i)
            printf ("%02x ", buffer[i]);

        printf("    ");
        for (i = 0; i < bytesRead; ++i)
            printf ("%c", buffer[i]);

        printf ("\n");

        /* Keep count of our position in the file.  */
        offset += bytesRead;
    }
    while (bytesRead == sizeof (buffer));

    printf("\n");
}