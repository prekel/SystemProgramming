cmake_minimum_required(VERSION 3.0)
project(Lab_04_Lib C)

set(CMAKE_C_STANDARD 11)

add_library(Lab_04_Lib
        Archipelago.c Archipelago.h
        RecordFile.c RecordFile.h
        Meta.c Meta.h
        ParseInt.c ParseInt.h
        IOWrapper.c IOWrapper.h
        ReturnCodesLib.h)

target_include_directories(Lab_04_Lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
