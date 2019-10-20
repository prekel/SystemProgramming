cmake_minimum_required(VERSION 3.0)
project(Lab_03_Lib C)

set(CMAKE_C_STANDARD 11)

add_library(Lab_03_Lib
        ArchipelagoCollection.h  ArchipelagoCollection.c
        ArchipelagoCollectionQuery.h  ArchipelagoCollectionQuery.c
        Archipelago.c Archipelago.h
        LinkedListDeclarations.h
        LinkedList.h LinkedList.c
        LinkedListNode.c LinkedListNode.h )

target_include_directories(Lab_03_Lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
