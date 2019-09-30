cmake_minimum_required(VERSION 3.10)
project(Lab_02_Interactive C)

set(CMAKE_C_STANDARD 11)

if (UNIX)
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})
endif (UNIX)

add_executable(Lab_02_Interactive main.c)

if (UNIX)
    target_link_libraries(Lab_02_Interactive ${SDL2_LIBRARIES})
endif (UNIX)

#target_link_libraries(Lab_02_Interactive PRIVATE pthread)
