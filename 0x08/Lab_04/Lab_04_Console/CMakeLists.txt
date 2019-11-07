cmake_minimum_required(VERSION 3.0)
project(Lab_04_Console C)

set(CMAKE_C_STANDARD 11)

add_executable(Lab_04_Console main.c
        Commands.c Commands.h
        Args.c Args.h
        Print.c Print.h getopt.h)

target_link_libraries(Lab_04_Console PRIVATE Lab_04_Lib)
