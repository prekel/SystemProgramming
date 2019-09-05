cmake_minimum_required(VERSION 3.10)
project(assert-demo C)
project(set C)
project(set1 C)

set(CMAKE_C_STANDARD 11)

add_executable(assert-demo assert-demo.c)
add_executable(set set.c)
add_executable(set1 set1.c)