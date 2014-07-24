# Set output directories.
set(LIBRARY_OUTPUT_PATH ${L_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${O_OUTPUT_DIR})

# Build the Dynamic_Library_Subsystem if needed.
if (BUILD_DYNAMIC_LIBRARY_SUBSYSTEM)

    # Create the Dynamic_Library_Subsystem library.
    # Figure out what OS to use...
    IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	# Building on windows.
	set(DYNAMIC_LIBRARY_SUBSYSTEM_INCLUDES Dynamic_Library_Subsystem_Data_Structures.c
	Dynamic_Library_Subsystem_Windows.c)
	unset(DYNAMIC_LIBRARY_SUBSYSTEM_LINK_LIBS)
	
	ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	    # Building on Linux.
	    set(DYNAMIC_LIBRARY_SUBSYSTEM_INCLUDES Dynamic_Library_Subsystem_Data_Structures.c
	    Dynamic_Library_Subsystem_POSIX.c)
	    set(DYNAMIC_LIBRARY_SUBSYSTEM_LINK_LIBS dl)

	ELSE(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	    # We don't have a match against a known system.
	    message(FATAL_ERROR "Attempting to build the Dynamic Library Subsystem with an unrecognized OS / System / Arch. Aborting build.")

    ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

    # Actually build it.
    add_library(Dynamic_Library_Subsystem_Multiverse_Engine SHARED ${DYNAMIC_LIBRARY_SUBSYSTEM_INCLUDES})
    target_link_libraries(Dynamic_Library_Subsystem_Multiverse_Engine ${DYNAMIC_LIBRARY_SUBSYSTEM_LINK_LIBS} 
    Common_Error_Handler_Multiverse_Engine)

endif(BUILD_DYNAMIC_LIBRARY_SUBSYSTEM)
