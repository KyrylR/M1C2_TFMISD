cmake_minimum_required(VERSION 3.28)
project(lab3 C)

set(CMAKE_C_STANDARD 11)

include_directories(include)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/mingw-toolchain.cmake)

add_executable(lab3 main.c
        src/cli.c
        include/cli.h
        src/logical_eval.c
        include/logical_eval.h
        include/semantic_table.h
        src/semantic_table.c)
