# Set the system name to indicate the target environment
set(CMAKE_SYSTEM_NAME Windows)

# Specify the cross-compiler for 64-bit Windows applications
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)

# Additional flags for the C compiler.
# Note: '-mwindows' flag is for GUI applications, remove it if you are building a console application
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
