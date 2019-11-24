cmake_minimum_required(VERSION 3.0)
project(Lab_05_Lib C)

set(CMAKE_C_STANDARD 99)

add_library(Lab_05_Lib
        ParseInt.h ParseInt.c
        Input.c Input.h
        ReturnCodes.c ReturnCodes.h
        Socket.c Socket.h
        Request.c Request.h
        LastErrorMessage.c LastErrorMessage.h
        Args.h Args.c
        ArgsPrivate.h ArgsPrivate.c)

target_link_libraries(Lab_05_Lib PRIVATE Lab_05_MatrixLib)

target_include_directories(Lab_05_Lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
