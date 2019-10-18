cmake_minimum_required(VERSION 3.0)
project(Lab_03_Lib C)

set(CMAKE_C_STANDARD 11)

add_library(Lab_03_Lib qwer.c LinkedList.h LinkedList.c DataLinkedList.h LinkedListFunctions.h Data.c Data.h DataLinkedList.c LinkedListNode.c LinkedListNode.h)

target_include_directories(Lab_03_Lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
