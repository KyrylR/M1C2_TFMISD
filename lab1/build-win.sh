#!/bin/bash

# Define the project directory
PROJECT_DIR="/home/inastro/Desktop/University/Masters_2024_Sem_2/algs"

# Define the build directory
BUILD_DIR="$PROJECT_DIR/build"

# Check if the build directory exists
if [ -d "$BUILD_DIR" ]; then
    echo "Cleaning existing build directory..."
    rm -rf "$BUILD_DIR"
fi

# Create a new build directory
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# Run CMake to configure the project with the cross-compiler
cmake "$PROJECT_DIR" -DCMAKE_TOOLCHAIN_FILE="$PROJECT_DIR/mingw-toolchain.cmake"

# Build the project using Make
make

# Check if the build was successful
if [ $? -eq 0 ]; then
    echo "Build successful. Executable is located in $BUILD_DIR"
else
    echo "Build failed."
fi
