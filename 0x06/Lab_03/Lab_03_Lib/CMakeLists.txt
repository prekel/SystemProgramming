cmake_minimum_required(VERSION 3.0)
project(Lab_03_Lib C)

set(CMAKE_C_STANDARD 11)

add_library(Lab_03_Lib qwer.c LinkedList.h LinkedList.c ArchipelagoCollection.h Data.c Data.h ArchipelagoCollection.c LinkedListNode.c LinkedListNode.h LinkedListDeclarations.h)

target_include_directories(Lab_03_Lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
