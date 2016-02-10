# Set output directories.
set(LIBRARY_OUTPUT_PATH ${L_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${O_OUTPUT_DIR})

# Set the includes.
set(RENDERING_SUBSYS_INCLUDES Renderer_Data_Structures.cpp
Renderer_Data_Structures_Overlay_Base_Functions.cpp
Renderer_Basic_Functions.cpp
Renderer_Text_Console.cpp)

# Build Rendering_Subsystem library.
add_library(Rendering_Subsystem_Multiverse_Engine SHARED ${RENDERING_SUBSYS_INCLUDES})
target_link_libraries(Rendering_Subsystem_Multiverse_Engine Common_Error_Handler_Multiverse_Engine 
Core_Multiverse_Engine 
Panic_Handler_Multiverse_Engine)
