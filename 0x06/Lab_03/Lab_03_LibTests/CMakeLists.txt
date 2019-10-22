cmake_minimum_required(VERSION 3.0)
project(Lab_03_LibTests C)

set(CMAKE_C_STANDARD 11)

add_executable(Lab_03_LibTests main.c
        LinkedListTests.c LinkedListTests.h
        Suite.c Suite.h
        ArchipelagoCollectionTests.c ArchipelagoCollectionTests.h)

target_link_libraries(Lab_03_LibTests PRIVATE Lab_03_Lib)
target_link_libraries(Lab_03_LibTests PRIVATE cunit)
