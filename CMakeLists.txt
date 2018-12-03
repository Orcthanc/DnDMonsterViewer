cmake_minimum_required (VERSION 3.0)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

project (DnDMonsterViewer)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE DnDMonsterViewer_SOURCES "src/*.c")

add_executable (DnDMonsterViewer ${DnDMonsterViewer_SOURCES})

target_include_directories(DnDMonsterViewer PUBLIC "src" )
