# Set CMake minimum version
cmake_minimum_required(VERSION 3.20)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)

# Convenient for LSPs
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Declare project
project(tinystl LANGUAGES CXX)

# Declare library
add_library(tinystl INTERFACE)

# Expose the include directory
target_include_directories(tinystl INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>  # for installs
)

project(dummy)

# Add dummy target only to generate compile_commands.json
add_executable(dummy EXCLUDE_FROM_ALL include/tinystl/internal/dummy.cpp)
