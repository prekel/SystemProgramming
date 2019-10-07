cmake_minimum_required(VERSION 3.0)
project(Lab_02_Lib C)

set(CMAKE_C_STANDARD 11)

add_library(Lab_02_Lib
        Input.c Input.h
        Philosopher.c Philosopher.h
        Fork.c Fork.h
        Table.c Table.h
        Utils.c Utils.h
        PhilosopherEatingThread.c PhilosopherEatingThread.h
        PhilosophersSpawnerThread.c PhilosophersSpawnerThread.h
        Logger.c Logger.h
        PhilosophersWaiterThread.c PhilosophersWaiterThread.h)

target_link_libraries(Lab_02_Lib PRIVATE pthread)

target_link_libraries(Lab_02_Lib PRIVATE m)

target_include_directories(Lab_02_Lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
