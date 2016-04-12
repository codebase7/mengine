
# Set source files.
set(Data_Object_Includes Data_Object.c)

# Create libraries.
add_library(Data_Object_Multiverse_Engine SHARED ${Data_Object_Includes})
add_library(Data_Object_Multiverse_Engine_Static STATIC ${Data_Object_Includes})

# Link libraries.
target_link_libraries(Data_Object_Multiverse_Engine DataProcess_Memory_Management_Multiverse_Engine)
target_link_libraries(Data_Object_Multiverse_Engine_Static DataProcess_Memory_Management_Multiverse_Engine_Static)
