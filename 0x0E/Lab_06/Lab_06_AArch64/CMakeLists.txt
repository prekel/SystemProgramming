cmake_minimum_required(VERSION 3.0)
project(Lab_06_AArch64 ASM)

set(CMAKE_ASM_FLAGS "-target aarch64")

add_executable(Lab_06_AArch64 main.s)
