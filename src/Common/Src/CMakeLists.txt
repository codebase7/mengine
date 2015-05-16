# Set output directories.
set(LIBRARY_OUTPUT_PATH ${L_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${O_OUTPUT_DIR})

# Create the mutexes library.
add_subdirectory(Mutexes)

# Create the error handler.
add_subdirectory(Error_Handler)

# Create FileUtills.
add_subdirectory(File_Management_Subsystem)

# Create the Dynamic_Library_Subsystem.
add_subdirectory(Dynamic_Library_Subsystem)

# Create the Threading Subsystem.
add_subdirectory(Threading_Subsystem)

# Add library.
add_library(Common_Multiverse_Engine SHARED Generic_Wrapper.cpp)

target_link_libraries(Common_Multiverse_Engine Core_Multiverse_Engine
Panic_Handler_Multiverse_Engine
File_Management_Multiverse_Engine
Threading_Subsystem_Multiverse_Engine)