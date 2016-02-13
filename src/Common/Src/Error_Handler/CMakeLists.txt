# Set output directories.
set(LIBRARY_OUTPUT_PATH ${L_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${O_OUTPUT_DIR})

# Check for internal mutex support as the error handler uses it.
if (BUILD_FATAL_ERROR_NOTIFY_SUPPORT)
	if (BUILD_INTERNAL_MUTEX_SUPPORT)
		# Enable the needed flags.
		set (COMMON_ERROR_HANDLER_DEFINES MSYS_BUILD_FATAL_ERROR_SUPPORT)

		# Define the link libraries.
		set(COMMON_ERROR_HANDLER_LINK_LIBS Common_Mutexes_Multiverse_Engine)
		set(COMMON_ERROR_HANDLER_STATIC_LINK_LIBS Common_Mutexes_Multiverse_Engine_Static)
	else(BUILD_INTERNAL_MUTEX_SUPPORT)
		# No internal mutex support, so skip building the error handler's fatal error notification support.
		message(SEND_ERROR "ERROR: Internal mutex support is disabled, and is REQUIRED to build the Common Error Handler's fatal error notification support. Skipping.")
	endif(BUILD_INTERNAL_MUTEX_SUPPORT)
endif (BUILD_FATAL_ERROR_NOTIFY_SUPPORT)

# Create the error handler. (Nasty hack to avoid a warning from GCC about invalid -std:gnu99 flag below....)
set (COMMON_ERROR_HANDLER_C_INCLUDES_BASE Common_Error_Handler.c
		Common_Error_Handler_Log_Channel_Defs.c
		Common_Error_Handler_Structures.c)
set (COMMON_ERROR_HANDLER_CXX_INCLUDES_BASE Common_Error_Handler_Structures_CPP_Bindings.cpp
		Common_Error_Handler_CPP_Bindings.cpp)

# Build the posix error translation table if we are running under posix.
if (${CMAKE_SYSTEM_NAME} EQUAL "Linux")
	set (COMMON_ERROR_HANDLER_C_INCLUDES ${COMMON_ERROR_HANDLER_C_INCLUDES_BASE} 
			Posix_Error_Translation_Table.c)
	set (COMMON_ERROR_HANDLER_CXX_INCLUDES ${COMMON_ERROR_HANDLER_CXX_INCLUDES_BASE} 
			Posix_Error_Translation_Table_CPP_Bindings.cpp)
else (${CMAKE_SYSTEM_NAME} EQUAL "Windows")
	set (COMMON_ERROR_HANDLER_C_INCLUDES ${COMMON_ERROR_HANDLER_C_INCLUDES_BASE}
			Windows_Error_Translation_Table.c)
	set (COMMON_ERROR_HANDLER_CXX_INCLUDES ${COMMON_ERROR_HANDLER_CXX_INCLUDES_BASE}
			Windows_Error_Translation_Table_CPP_Bindings.cpp)
else (${CMAKE_SYSTEM_NAME} EQUAL "Linux")
	set (COMMON_ERROR_HANDLER_C_INCLUDES ${COMMON_ERROR_HANDLER_C_INCLUDES_BASE})
	set (COMMON_ERROR_HANDLER_CXX_INCLUDES ${COMMON_ERROR_HANDLER_CXX_INCLUDES_BASE})
endif (${CMAKE_SYSTEM_NAME} EQUAL "Linux")

# Check for gcc and enable gnu99 extensions if needed.
if (${CMAKE_COMPILER_IS_GNUCC})
	message (STATUS "GCC compiler detected, enabling gnu99 extensions for Common Error Handler.")
	set (COMMON_ERROR_HANDLER_C_FLAGS ${COMMON_ERROR_HANDLER_C_FLAGS} -std=gnu99)
endif(${CMAKE_COMPILER_IS_GNUCC})

# Create the static library.
add_library(Common_Error_Handler_Multiverse_Engine_Static STATIC ${COMMON_ERROR_HANDLER_C_INCLUDES} ${COMMON_ERROR_HANDLER_CXX_INCLUDES})
set_property(TARGET Common_Error_Handler_Multiverse_Engine_Static APPEND PROPERTY COMPILE_DEFINITIONS ${COMMON_ERROR_HANDLER_DEFINES})
target_link_libraries(Common_Error_Handler_Multiverse_Engine_Static ${COMMON_ERROR_HANDLER_STATIC_LINK_LIBS})

# Now the shared library.
add_library(Common_Error_Handler_Multiverse_Engine SHARED ${COMMON_ERROR_HANDLER_C_INCLUDES} ${COMMON_ERROR_HANDLER_CXX_INCLUDES})
set_property(TARGET Common_Error_Handler_Multiverse_Engine_Static APPEND PROPERTY COMPILE_DEFINITIONS ${COMMON_ERROR_HANDLER_DEFINES})
target_link_libraries(Common_Error_Handler_Multiverse_Engine ${COMMON_ERROR_HANDLER_LINK_LIBS})
