cmake_minimum_required(VERSION 3.20)
project(MaineCoon)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE 0) 

if (WIN32)
    cmake_policy(SET CMP0091 NEW)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)
endif ()

add_definitions(-w) # disables warnings

add_subdirectory(maine-coon)
add_subdirectory(maine-coon-app)
