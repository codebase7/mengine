# Set output directories.
set(EXECUTABLE_OUTPUT_PATH ${B_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${O_OUTPUT_DIR})

# Define Unit Tests base includes.
set (UNIT_TESTS_INCLUDES_BASE Unit_Tests.cpp)

# We may make Core and Byte_Order an optional subsystem in the future.
set (UNIT_TESTS_INCLUDES ${UNIT_TESTS_INCLUDES_BASE} 
Test_Base_Header.cpp
Unit_Test_DataProcess.c
Unit_Test_Data_Object.cpp 
Unit_Test_Data_Object_Insert_Char.cpp
Unit_Test_Byte_Order.cpp)

# Only build the tests for the subsystems that are enabled.
if (BUILD_COMMON_ERROR_HANDLER)
		set (UNIT_TESTS_INCLUDES ${UNIT_TESTS_INCLUDES} Unit_Tests_Common_Error_Handler.cpp)
		set (UNIT_TESTS_DEFINES ${UNIT_TESTS_DEFINES} MSYS_HAVE_COMMON_ERROR_HANDLER)
endif (BUILD_COMMON_ERROR_HANDLER)

if (BUILD_FILE_MANAGEMENT_SUBSYSTEM)
		set (UNIT_TESTS_INCLUDES ${UNIT_TESTS_INCLUDES} Unit_Test_FileUtills_CopyPath.cpp)
		set (UNIT_TESTS_DEFINES ${UNIT_TESTS_DEFINES} MSYS_HAVE_FILEUTILLS)
endif (BUILD_FILE_MANAGEMENT_SUBSYSTEM)

if (BUILD_THREADING_SUBSYSTEM)
		set (UNIT_TESTS_INCLUDES ${UNIT_TESTS_INCLUDES} Unit_Test_Thread_Utils.cpp)
		set (UNIT_TESTS_DEFINES ${UNIT_TESTS_DEFINES} MSYS_HAVE_THREAD_UTILS)
endif (BUILD_THREADING_SUBSYSTEM)

# Add shared library executable.
add_executable(Unit_Tests ${UNIT_TESTS_INCLUDES})
target_link_libraries(Unit_Tests Common_Multiverse_Engine Core_Multiverse_Engine)
set_property (TARGET Unit_Tests APPEND PROPERTY COMPILE_DEFINITIONS ${UNIT_TESTS_DEFINES})

# Add static library executable.
add_executable(Unit_Tests_Static ${UNIT_TESTS_INCLUDES})
target_link_libraries(Unit_Tests_Static Common_Multiverse_Engine_Static Core_Multiverse_Engine_Static)
set_property (TARGET Unit_Tests_Static APPEND PROPERTY COMPILE_DEFINITIONS ${UNIT_TESTS_DEFINES})
