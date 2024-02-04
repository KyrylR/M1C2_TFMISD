cmake_minimum_required(VERSION 3.28)
project(algs C)

set(CMAKE_C_STANDARD 11)

include_directories(include)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/mingw-toolchain.cmake)

add_executable(algs main.c
        include/addition.h
        include/utility.h
        src/addition.c
        src/utility.c
        include/multiplication.h
        src/multiplication.c
        include/cli.h
        src/cli.c
        src/image.c
        include/imag.h)
