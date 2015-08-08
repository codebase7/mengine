# Set output directories.
set(LIBRARY_OUTPUT_PATH ${L_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${O_OUTPUT_DIR})

# Set default includes.
set(FILEUTILLS_INCLUDES FileUtills.cpp FileUtills_Private_API.cpp FileUtills_Private_API.c)

# Set system specific includes.
IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	# Building on windows.
	set(FILEUTILLS_INCLUDES ${FILEUTILLS_INCLUDES} FileUtills_Private_API_Windows_Syscall.cpp) 
	
	ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	    # Building on Linux.
	    set(FILEUTILLS_INCLUDES ${FILEUTILLS_INCLUDES} FileUtills_Private_API_Posix_Syscall.cpp)

	ELSE(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	    # We don't have a match against a known system.
	    message(FATAL_ERROR "Attempting to build the File Management Subsystem with an unrecognized OS / System / Arch. Aborting build.")

ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

add_library(File_Management_Multiverse_Engine SHARED ${FILEUTILLS_INCLUDES})
target_link_libraries(File_Management_Multiverse_Engine Common_Error_Handler_Multiverse_Engine)
