# Set CMake minimum version
set(CMAKE_MINIMUM_REQUIRED_VERSION "3.20")

# Declare project
project(tinystl)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)

# Add include dirs
target_include_directories(tinystl PUBLIC include)
