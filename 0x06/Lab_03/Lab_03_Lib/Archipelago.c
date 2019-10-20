#include <assert.h>
#include <malloc.h>
#include <string.h>

#include "Archipelago.h"

Archipelago* ArchipelagoCreate(char* name,
                               int countIslands,
                               int countInhabitedIslands)
{
    Archipelago* pArchipelago = (Archipelago*) malloc(sizeof(Archipelago));
    assert(pArchipelago);

    pArchipelago->Name = (char*) malloc((strlen(name) + 1) * sizeof(char));
    assert(pArchipelago->Name);
    strcpy(pArchipelago->Name, name);

    pArchipelago->CountIslands = countIslands;
    pArchipelago->CountInhabitedIslands = countInhabitedIslands;

    return pArchipelago;
}

void ArchipelagoDestroy(Archipelago* pArchipelago)
{
    free(pArchipelago->Name);
    free(pArchipelago);
}

#define ARCHIPELAGO_TO_STRING_FORMAT "Архипелаг: %s; Кол-во островов: %d; Кол-во обитаемых островов: %d\n"

char* ArchipelagoToString(Archipelago* pArchipelago)
{
    int len = snprintf(NULL, 0, ARCHIPELAGO_TO_STRING_FORMAT,
                       pArchipelago->Name,
                       pArchipelago->CountIslands,
                       pArchipelago->CountInhabitedIslands);
    char* string = (char*) malloc((len + 1) * sizeof(char));
    snprintf(string, len + 1, ARCHIPELAGO_TO_STRING_FORMAT,
             pArchipelago->Name,
             pArchipelago->CountIslands,
             pArchipelago->CountInhabitedIslands);
    return string;
}