# Set output directories.
set(LIBRARY_OUTPUT_PATH ${L_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${O_OUTPUT_DIR})

# Build the error handler if needed.
if (BUILD_COMMON_ERROR_HANDLER)
	# Check for internal mutex support as the error handler uses it.
	if (BUILD_FATAL_ERROR_NOTIFY_SUPPORT)
		if (BUILD_INTERNAL_MUTEX_SUPPORT)
			# Enable the needed flags.
			set (COMMON_ERROR_HANDLER_DEFINES MSYS_BUILD_FATAL_ERROR_SUPPORT)

			# Define the link libraries.
			set(COMMON_ERROR_HANDLER_LINK_LIBS Common_Mutexes_Multiverse_Engine)
		else(BUILD_INTERNAL_MUTEX_SUPPORT)
			# No internal mutex support, so skip building the error handler's fatal error notification support.
			message(SEND_ERROR "ERROR: Internal mutex support is disabled, and is REQUIRED to build the Common Error Handler's fatal error notification support. Skipping.")
		endif(BUILD_INTERNAL_MUTEX_SUPPORT)
	endif (BUILD_FATAL_ERROR_NOTIFY_SUPPORT)

	# Create the error handler. (Nasty hack to avoid a warning from GCC about invalid -std:gnu99 flag below....)
	set (COMMON_ERROR_HANDLER_C_INCLUDES Common_Error_Handler.c 
	Posix_Error_Translation_Table.c
	)
	set (COMMON_ERROR_HANDLER_CXX_INCLUDES Common_Error_Handler_Structures_CPP_Bindings.cpp
	Common_Error_Handler_CPP_Bindings.cpp
	Posix_Error_Translation_Table_CPP_Bindings.cpp
	)

	# Because we broke up the object code build from the shared library linking, we need to break up the flags and arguments too.
	set (COMMON_ERROR_HANDLER_COMPILER_FLAGS -fPIC)
	set (COMMON_ERROR_HANDLER_C_FLAGS ${COMMON_ERROR_HANDLER_COMPILER_FLAGS})
	set (COMMON_ERROR_HANDLER_CXX_FLAGS ${COMMON_ERROR_HANDLER_COMPILER_FLAGS})
	set (COMMON_ERROR_HANDLER_LINK_FLAGS -fPIC)

	# Check for gcc and enable gnu99 extensions if needed.
	if (${CMAKE_COMPILER_IS_GNUCC})
		message (STATUS "GCC compiler detected, enabling gnu99 extensions for Common Error Handler.")
		set (COMMON_ERROR_HANDLER_C_FLAGS ${COMMON_ERROR_HANDLER_C_FLAGS} -std=gnu99) 
	endif(${CMAKE_COMPILER_IS_GNUCC})

	# First add the static C object library...
	add_library(Common_Error_Handler_Multiverse_Engine_C OBJECT ${COMMON_ERROR_HANDLER_C_INCLUDES})
	set_property(TARGET Common_Error_Handler_Multiverse_Engine_C APPEND PROPERTY COMPILE_DEFINITIONS ${COMMON_ERROR_HANDLER_DEFINES})
	target_compile_options (Common_Error_Handler_Multiverse_Engine_C BEFORE PRIVATE ${COMMON_ERROR_HANDLER_C_FLAGS}) # Allows us to put the args to the compiler in the correct order.
	
	# Now add the C++ Bindings object library.
	add_library(Common_Error_Handler_Multiverse_Engine_CXX OBJECT ${COMMON_ERROR_HANDLER_CXX_INCLUDES})
	set_property(TARGET Common_Error_Handler_Multiverse_Engine_CXX APPEND PROPERTY COMPILE_DEFINITIONS ${COMMON_ERROR_HANDLER_DEFINES})
	target_compile_options (Common_Error_Handler_Multiverse_Engine_CXX BEFORE PRIVATE ${COMMON_ERROR_HANDLER_CXX_FLAGS})  # Allows us to put the args to the compiler in the correct order.
	
	# Now the final shared library. (What we really want.)
	add_library(Common_Error_Handler_Multiverse_Engine SHARED $<TARGET_OBJECTS:Common_Error_Handler_Multiverse_Engine_C> 
	$<TARGET_OBJECTS:Common_Error_Handler_Multiverse_Engine_CXX>
	)
	target_link_libraries(Common_Error_Handler_Multiverse_Engine ${COMMON_ERROR_HANDLER_LINK_LIBS})
	set_property(TARGET Common_Error_Handler_Multiverse_Engine APPEND PROPERTY COMPILE_DEFINITIONS ${COMMON_ERROR_HANDLER_DEFINES})
	set_property(TARGET Common_Error_Handler_Multiverse_Engine APPEND PROPERTY LINK_FLAGS ${COMMON_ERROR_HANDLER_LINK_FLAGS})

endif(BUILD_COMMON_ERROR_HANDLER)
