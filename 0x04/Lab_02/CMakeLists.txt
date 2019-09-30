cmake_minimum_required(VERSION 3.10)
project(Lab_02 C)

set(CMAKE_C_STANDARD 11)

add_executable(Lab_02 main.c Input.c Input.h Philosopher.c Philosopher.h Fork.c Fork.h Table.c Table.h Utils.c Utils.h)

target_link_libraries(Lab_02 PRIVATE pthread)
