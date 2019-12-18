cmake_minimum_required(VERSION 3.0)

if (NOT WIN32 OR TARGET cunit)

project(Lab_06_Tests C)

set(CMAKE_C_STANDARD 99)

add_executable(Lab_06_Tests main.c
        MatrixTests.c MatrixTests.h
        Suite.c Suite.h
        ../Lab_06_C/Matrix.c
        ../Lab_06_C/MatrixIO.c)

target_link_libraries(Lab_06_Tests PRIVATE cunit)

target_include_directories(Lab_06_Tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

endif (NOT WIN32 OR TARGET cunit)
