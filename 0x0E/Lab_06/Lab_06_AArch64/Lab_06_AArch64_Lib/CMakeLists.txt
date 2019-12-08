cmake_minimum_required(VERSION 3.0)
project(Lab_06_AArch64_Lib ASM)

set(CMAKE_ASM_COMPILER aarch64-linux-gnu-as)

set(CMAKE_ASM_COMPILE_OBJECT aarch64-linux-gnu-ld)


add_library(Lab_06_AArch64_Lib Matrix.s)

target_include_directories(Lab_06_AArch64_Lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../)
