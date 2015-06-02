# Set output directories.
set(LIBRARY_OUTPUT_PATH ${L_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${O_OUTPUT_DIR})

# Create the error handler.
set (COMMON_ERROR_HANDLER_INCLUDES_BASE Common_Error_Handler.cpp)

# Build the posix error translation table if we are running under posix.
if (${CMAKE_SYSTEM_NAME} EQUAL "Linux")
	set (COMMON_ERROR_HANDLER_INCLUDES ${COMMON_ERROR_HANDLER_INCLUDES_BASE} 
			Posix_Error_Translation_Table.cpp)
else (${CMAKE_SYSTEM_NAME} EQUAL "Linux")
	set (COMMON_ERROR_HANDLER_INCLUDES ${COMMON_ERROR_HANDLER_INCLUDES_BASE})
endif (${CMAKE_SYSTEM_NAME} EQUAL "Linux")

add_library(Common_Error_Handler_Multiverse_Engine SHARED ${COMMON_ERROR_HANDLER_INCLUDES})
add_library(Common_Error_Handler_Multiverse_Engine_Static STATIC ${COMMON_ERROR_HANDLER_INCLUDES})
