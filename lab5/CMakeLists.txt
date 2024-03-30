cmake_minimum_required(VERSION 3.28)
project(lab3 C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

# Manually set the paths for GMP include directory and library
include_directories(/opt/homebrew/include)
link_directories(/opt/homebrew/lib)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/mingw-toolchain.cmake)

add_executable(lab4 main.c
        src/cli.c
        include/cli.h
)

target_link_libraries(lab4 gmp)
