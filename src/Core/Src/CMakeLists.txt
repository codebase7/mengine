# Set output directories.
set(LIBRARY_OUTPUT_PATH ${L_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${O_OUTPUT_DIR})

# Add libraries.
add_library(Panic_Handler_Multiverse_Engine SHARED Panic.cpp)
add_library(Panic_Handler_Multiverse_Engine_Static STATIC Panic.cpp)

add_library(Core_Multiverse_Engine SHARED DataProcess.cpp
DataProcess_Endianness_Check.cpp
FileStreams.cpp)
add_library(Core_Multiverse_Engine_Static STATIC DataProcess.cpp
DataProcess_Endianness_Check.cpp
FileStreams.cpp)
target_link_libraries(Core_Multiverse_Engine Panic_Handler_Multiverse_Engine)
target_link_libraries(Core_Multiverse_Engine_Static Panic_Handler_Multiverse_Engine_Static)
