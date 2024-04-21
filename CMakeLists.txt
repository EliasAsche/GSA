cmake_minimum_required(VERSION 3.10)
project(Fraud)  # Name your project

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# GLFW configuration options
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)  # Disable Wayland
set(GLFW_BUILD_X11 OFF CACHE BOOL "" FORCE)  # Disable X11

# Add the GLFW directory
add_subdirectory(external/glfw)

# Include directories
include_directories(external/glfw/include)

# Find packages
find_package(OpenGL REQUIRED)

# Specify the source files for the project
set(SOURCES src/main.cpp src/window.cpp)  # Adjust this to your source files
add_executable(Fraud ${SOURCES})

# Link against GLFW and OpenGL
target_link_libraries(Fraud glfw OpenGL::GL)
