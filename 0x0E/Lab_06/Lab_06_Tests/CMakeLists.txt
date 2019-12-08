cmake_minimum_required(VERSION 3.0)
project(Lab_06_Tests C)

set(CMAKE_C_STANDARD 99)

if (NOT WIN32 OR TARGET cunit)

    add_executable(Lab_06_Tests main.c
            MatrixTests.c MatrixTests.h
            Suite.c Suite.h)

    target_link_libraries(Lab_06_Tests PRIVATE Lab_06_C_Lib)

    target_link_libraries(Lab_06_Tests PRIVATE cunit)

endif (NOT WIN32 OR TARGET cunit)
