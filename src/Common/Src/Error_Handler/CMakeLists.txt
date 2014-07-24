# Set output directories.
set(LIBRARY_OUTPUT_PATH ${L_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${O_OUTPUT_DIR})

# Create the error handler.
set (COMMON_ERROR_HANDLER_INCLUDES Common_Error_Handler.cpp
Posix_Error_Translation_Table.cpp)

add_library(Common_Error_Handler_Multiverse_Engine SHARED ${COMMON_ERROR_HANDLER_INCLUDES})
