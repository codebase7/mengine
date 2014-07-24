# Set output directories.
set(LIBRARY_OUTPUT_PATH ${L_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${O_OUTPUT_DIR})

set(FILEUTILLS_INCLUDES FileUtills.cpp)

add_library(File_Management_Multiverse_Engine SHARED ${FILEUTILLS_INCLUDES})
target_link_libraries(File_Management_Multiverse_Engine Common_Error_Handler_Multiverse_Engine)
