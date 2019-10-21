#ifndef ARCHIPELAGO_H
#define ARCHIPELAGO_H

typedef struct
{
    char* Name;
    int CountIslands;
    int CountInhabitedIslands;
} Archipelago;

Archipelago* ArchipelagoCreate(char* name,
                               int countIslands,
                               int countInhabitedIslands);

void ArchipelagoDestroy(Archipelago* pArchipelago);

char* ArchipelagoToString(Archipelago* pArchipelago);

#endif //ARCHIPELAGO_H