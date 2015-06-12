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
set(PLUGIN_OUTPUT_DIR ${L_OUTPUT_DIR}/plugins CACHE PATH "Build plugin output directory")
set(O_OUTPUT_DIR ${T_OUTPUT_DIR}/obj CACHE PATH "Build object output directory")
endif()

# Option Defaults.
option (BUILD_DYNAMIC_LIBRARY_SUBSYSTEM "Whether or not to build the Dynamic Library Subsystem. (Defaults to yes.)" ON)
option (BUILD_COMMON_ERROR_HANDLER "Whether or not to build the Common Error Handler. (Defaults to yes.)" ON)
option (BUILD_FATAL_ERROR_NOTIFY_SUPPORT "Whether or not to build the Common Error Handler's fatal error notification support. (Defaults to yes.)" ON)
option (BUILD_INTERNAL_MUTEX_SUPPORT "Whether or not to build the internal mutex support library. (Defaults to yes.)" ON)
option (BUILD_COMMON_ERROR_HANDLER "Whether or not to build the common error handler. (Defaults to yes.)" ON)
option (BUILD_INTERNAL_MUTEX_THREAD_SUBSYS_WRAPPER "Whether or not the Threading Subsystem library will have Internal Mutex Support built in. (Defaults to yes, but is disabled currently due to changes to Thread_Utils that have not been commited yet.)" OFF)
option (BUILD_INTERNAL_MUTEX_THREAD_SUBSYS_WRAPPER_PLUGIN "Whether or not to build the Threading Subsystem plugin for Internal Mutex Support. (Defaults to yes, but is disabled currently due to changes to Thread_Utils that have not been commited yet.)" OFF)
option (BUILD_FILE_MANAGEMENT_SUBSYSTEM "Whether or not to build the file management subsystem. FileUtills. (Defaults to yes.)" ON)
option (BUILD_THREADING_SUBSYSTEM "Whether or not to build the threading subsystem. Thread_Utils. (Defaults to yes.)" ON)
option (ENABLE_THREADING_SUBSYSTEM_PLUGIN_SUPPORT "Whether or not to enable the threading subsystem's plugin support. (Defaults to yes.)" ON)
option (BUILD_THREAD_SUBSYS_PTHREADS_PLUGIN "Whether or not to build the threading subsystem's pthreads plugin. (Defaults to yes.)" ON)
option (BUILD_UNIT_TESTS "Whether or not to build the unit_test program. (Defaults to yes.)" ON)

# Include src sub directory.
add_subdirectory(src)
