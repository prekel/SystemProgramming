cmake_minimum_required(VERSION 3.0)
project(Lab_02_InteractiveLib C)

set(CMAKE_C_STANDARD 11)

add_library(Lab_02_InteractiveLib
        RendererThread.c RendererThread.h
        ProgramQuitThread.c ProgramQuitThread.h
        MainWindow.c MainWindow.h
        MainCycleThread.c MainCycleThread.h)

if (EMSCRIPTEN)
    #set(CMAKE_AR ${CMAKE_C_COMPILER})
    #set(CMAKE_STATIC_LIBRARY_SUFFIX ".bc")
    #set(CMAKE_C_CREATE_STATIC_LIBRARY "<CMAKE_AR> -o <TARGET> <LINK_FLAGS> <OBJECTS>")
    #set(CMAKE_CXX_CREATE_STATIC_LIBRARY "<CMAKE_AR> -o <TARGET> <LINK_FLAGS> <OBJECTS>")
    #target_link_options(Lab_02_InteractiveLib PUBLIC "SHELL: -s USE_SDL=2")
else (EMSCRIPTEN)
    if (UNIX)
        if (TARGET SDL2)
            target_link_libraries(Lab_02_InteractiveLib PRIVATE SDL2main SDL2)
        else (TARGET SDL2)
            find_package(SDL2 REQUIRED)
            target_include_directories(
                    Lab_02_InteractiveLib PRIVATE ${SDL2_INCLUDE_DIRS})
            target_link_libraries(Lab_02_InteractiveLib PRIVATE ${SDL2_LIBRARIES})
        endif (TARGET SDL2)
    endif (UNIX)

    if (MINGW)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mconsole -mwindows")
        target_link_libraries(Lab_02_InteractiveLib PRIVATE mingw32 SDL2main SDL2)
    endif (MINGW)
endif (EMSCRIPTEN)

target_link_libraries(Lab_02_InteractiveLib PRIVATE Lab_02_Lib)

target_include_directories(
        Lab_02_InteractiveLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
