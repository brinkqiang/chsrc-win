cmake_minimum_required(VERSION 3.8)

PROJECT(chsrc)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cmake/ModuleImport.cmake)
INCLUDE(cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Iinclude")

if (WIN32)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Target x86_64-pc-windows-gnu")
endif()

if (UNIX AND NOT APPLE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static")
endif()

add_executable(chsrc src/chsrc.c)