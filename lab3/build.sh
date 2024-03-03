#!/bin/bash

# Define the project directory
PROJECT_DIR="/Users/kirilrs/Desktop/University/Masters1Sem2/M1C2_TFMISD/lab3"

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
cmake "$PROJECT_DIR"

# Build the project using Make
make

# Check if the build was successful
if [ $? -eq 0 ]; then
    echo "Build successful. Executable is located in $BUILD_DIR"
else
    echo "Build failed."
fi
