cmake_minimum_required(VERSION 3.10)

# Set the compiling mode flags
set(CMAKE_CXX_FLAGS_DEBUG "-g -o0 - DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-o3 -DNDEBUG -s")

# Set the project name
project(tangent)

# Incloude the current directory for header files
include_directories()

# Add the executable
add_executable(tangent
                src/tangent.c
                src/main.c)

target_link_libraries(tangent
                        m)