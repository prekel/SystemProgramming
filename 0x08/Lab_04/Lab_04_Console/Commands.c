#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>

#include "Archipelago.h"
#include "Commands.h"
#include "File.h"

void AddCommandExec(int argc, char** argv)
{
    bool isRequiredFileCreation = false;
    int opt;
    char* path = "1.bin";
    while ((opt = getopt(argc, argv, ":f:p")) != -1)
    {
        switch (opt)
        {
            case 'f':
                path = (char*) malloc((sizeof(char) + 1) * strlen(optarg));
                assert(path);
                strcpy(path, optarg);
                break;
            case 'p':
                isRequiredFileCreation = true;
                break;
            case ':':
                printf("option needs a value\n");
                break;
            case '?':
                printf("unknown option: %c\n", optopt);
                break;
        }
    }

    int fd = isRequiredFileCreation
             ? CreateFile(path, sizeof(Archipelago))
             : OpenOrCreateFile(path, sizeof(Archipelago));

    Archipelago archipelago;
    FillArchipelago(&archipelago, argv[optind], atoi(argv[optind + 1]),
                    atoi(argv[optind + 2]));

    AddRecord(fd, &archipelago);

    CloseFile(fd);
}

void FormatCommandExec(int argc, char** argv)
{
    bool isRequiredFileCreation = false;
    int opt;
    char* path = "1.bin";
    char* format = "%s %d %d";
    while ((opt = getopt(argc, argv, ":f:pF:")) != -1)
    {
        switch (opt)
        {
            case 'f':
                path = (char*) malloc((sizeof(char) + 1) * strlen(optarg));
                assert(path);
                strcpy(path, optarg);
                break;
            case 'p':
                isRequiredFileCreation = true;
                break;
            case 'F':
                format = (char*) malloc((sizeof(char) + 1) * strlen(optarg));
                assert(format);
                strcpy(format, optarg);
                break;
            case ':':
                printf("option needs a value\n");
                break;
            case '?':
                printf("unknown option: %c\n", optopt);
                break;
        }
    }

    int fd = isRequiredFileCreation
             ? CreateFile(path, sizeof(Archipelago))
             : OpenOrCreateFile(path, sizeof(Archipelago));

    Meta meta;
    ReadMeta(fd, &meta);
    for (int i = 0; i < meta.Count; i++)
    {
        Archipelago archipelago;
        ReadRecord(fd, &archipelago, i);
        printf(format, archipelago.Name, archipelago.CountIslands,
               archipelago.CountInhabitedIslands);
        printf("\n");
    }

    CloseFile(fd);
}