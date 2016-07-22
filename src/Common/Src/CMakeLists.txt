# Set output directories.
set(LIBRARY_OUTPUT_PATH ${L_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${O_OUTPUT_DIR})

# Create the Byte_Order library.
if (BUILD_BYTE_ORDER)
	add_subdirectory(Byte_Order)
	set (COMMON_BUILT_SHARED_LIBRARY_LIST ${COMMON_BUILT_SHARED_LIBRARY_LIST} Common_Byte_Order_Multiverse_Engine)
	set (COMMON_BUILT_STATIC_LIBRARY_LIST ${COMMON_BUILT_STATIC_LIBRARY_LIST} Common_Byte_Order_Multiverse_Engine_Static)
endif (BUILD_BYTE_ORDER)

# Create the mutexes library.
if (BUILD_INTERNAL_MUTEX_SUPPORT)
	add_subdirectory(Mutexes)
	set (COMMON_BUILT_SHARED_LIBRARY_LIST ${COMMON_BUILT_SHARED_LIBRARY_LIST} Common_Mutexes_Multiverse_Engine)
	set (COMMON_BUILT_STATIC_LIBRARY_LIST ${COMMON_BUILT_STATIC_LIBRARY_LIST} Common_Mutexes_Multiverse_Engine_Static)
endif(BUILD_INTERNAL_MUTEX_SUPPORT)


# Create the error handler.
if (BUILD_COMMON_ERROR_HANDLER)
	add_subdirectory(Error_Handler)
	set (COMMON_BUILT_SHARED_LIBRARY_LIST ${COMMON_BUILT_SHARED_LIBRARY_LIST} Common_Error_Handler_Multiverse_Engine)
	set (COMMON_BUILT_STATIC_LIBRARY_LIST ${COMMON_BUILT_STATIC_LIBRARY_LIST} Common_Error_Handler_Multiverse_Engine_Static)
endif(BUILD_COMMON_ERROR_HANDLER)


# Create FileUtills.
if (BUILD_FILE_MANAGEMENT_SUBSYSTEM)
	add_subdirectory(File_Management_Subsystem)
	set (COMMON_BUILT_SHARED_LIBRARY_LIST ${COMMON_BUILT_SHARED_LIBRARY_LIST} File_Management_Multiverse_Engine)
	set (COMMON_BUILT_STATIC_LIBRARY_LIST ${COMMON_BUILT_STATIC_LIBRARY_LIST} File_Management_Multiverse_Engine_Static)
endif (BUILD_FILE_MANAGEMENT_SUBSYSTEM)


# Create the Dynamic_Library_Subsystem.
if(BUILD_DYNAMIC_LIBRARY_SUBSYSTEM)
	add_subdirectory(Dynamic_Library_Subsystem)
	set (COMMON_BUILT_SHARED_LIBRARY_LIST ${COMMON_BUILT_SHARED_LIBRARY_LIST} Dynamic_Library_Subsystem_Multiverse_Engine)
	set (COMMON_BUILT_STATIC_LIBRARY_LIST ${COMMON_BUILT_STATIC_LIBRARY_LIST} Dynamic_Library_Subsystem_Multiverse_Engine_Static)
endif(BUILD_DYNAMIC_LIBRARY_SUBSYSTEM)


# Create the Threading Subsystem.
if (BUILD_THREADING_SUBSYSTEM)
	add_subdirectory(Threading_Subsystem)
	set (COMMON_BUILT_SHARED_LIBRARY_LIST ${COMMON_BUILT_SHARED_LIBRARY_LIST} Threading_Subsystem_Multiverse_Engine)
	set (COMMON_BUILT_STATIC_LIBRARY_LIST ${COMMON_BUILT_STATIC_LIBRARY_LIST} Threading_Subsystem_Multiverse_Engine_Static)
endif (BUILD_THREADING_SUBSYSTEM)


# Create the Rendering Subsystem.
if (BUILD_RENDERING_SUBSYSTEM)
	add_subdirectory(Rendering_Subsystem)
	set (COMMON_BUILT_SHARED_LIBRARY_LIST ${COMMON_BUILT_SHARED_LIBRARY_LIST} Rendering_Subsystem_Multiverse_Engine)
	set (COMMON_BUILT_STATIC_LIBRARY_LIST ${COMMON_BUILT_STATIC_LIBRARY_LIST} Rendering_Subsystem_Multiverse_Engine_Static)
endif (BUILD_RENDERING_SUBSYSTEM)


# Add static library.
add_library(Common_Multiverse_Engine_Static STATIC Generic_Wrapper.cpp)
target_link_libraries(Common_Multiverse_Engine_Static Core_Multiverse_Engine_Static
${COMMON_BUILT_STATIC_LIBRARY_LIST})

# Add shared library.
add_library(Common_Multiverse_Engine SHARED Generic_Wrapper.cpp)
target_link_libraries(Common_Multiverse_Engine Core_Multiverse_Engine
${COMMON_BUILT_SHARED_LIBRARY_LIST})
