# Set output directories.
set(LIBRARY_OUTPUT_PATH ${L_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${O_OUTPUT_DIR})

# Add libraries.
add_library(Core_Multiverse_Engine SHARED DataProcess.cpp FileStreams.cpp)
add_library(Panic_Handler_Multiverse_Engine SHARED Panic.cpp)

