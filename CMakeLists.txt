# Basic flags. (Minimum required cmake version, project name.)
cmake_minimum_required(VERSION 2.6)
project(Multiverse_Engine_Project)

# Set the build type unless it's set for us.
if (NOT CMAKE_BUILD_TYPE)
message(STATUS "No build type selected, defaulting to Release mode.")
set(CMAKE_BUILD_TYPE Release)
endif()

# Set the output directory unless it's set for us.
if (NOT T_OUTPUT_DIR)
message(STATUS "Build output directories not set, defaulting to ./build")
set(T_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE} CACHE PATH "Build top level output directory")
set(B_OUTPUT_DIR ${T_OUTPUT_DIR} CACHE PATH "Build executable output directory")
set(L_OUTPUT_DIR ${T_OUTPUT_DIR}/lib CACHE PATH "Build library output directory")
set(O_OUTPUT_DIR ${T_OUTPUT_DIR}/obj CACHE PATH "Build object output directory")
endif()
add_subdirectory(src)
