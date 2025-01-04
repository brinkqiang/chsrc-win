cmake_minimum_required(VERSION 3.8)

PROJECT(chsrc C CXX)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cmake/ModuleImport.cmake)
INCLUDE(cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()
ModuleSetWinCompilerFlags()

set(CMAKE_C_STANDARD 99)

if (WIN32)
    add_definitions(/utf-8)
endif()

if (UNIX AND NOT APPLE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static")
endif()

include_directories(include)
add_executable(chsrc src/chsrc.c)

AddInstall(chsrc)