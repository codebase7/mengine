# Set output directories.
set(LIBRARY_OUTPUT_PATH ${L_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${O_OUTPUT_DIR})

# Build if needed.
if (BUILD_INTERNAL_MUTEX_SUPPORT)
	# Define the basic headers for the mutexes library used on all platforms.
	set (COMMON_MUTEXES_BASE_INCLUDES MSYS_Mutexes.c)

	# Figure out what system we are building on so we can include the correct headers.
	IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
		# Building on Linux.
		set(COMMON_MUTEXES_INCLUDES ${COMMON_MUTEXES_BASE_INCLUDES} Linux/MSYS_Mutexes_Linux.c)

	ELSEIF (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
		# Building on Windows.
		set(COMMON_MUTEXES_INCLUDES ${COMMON_MUTEXES_BASE_INCLUDES} Windows\MSYS_Mutexes_Windows.c)

	ELSE(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
		message(FATAL_ERROR "Internal Mutex Support is unsupported on this system. Please consider adding support! Aborting.")

	ENDIF (${CMAKE_SYSTEM_NAME} MATCHES "Linux")

	# Set the needed preprocessor defines for Thread_Utils plugin support if needed.
	set(MSYS_MUTEX_DEFINES MSYS_PLUGIN_SUPPORT)

	# Set the needed preprocessor defines for the plugin build.
	set(MSYS_MUTEX_PLUGIN_DEFINES MSYS_PLUGIN_BUILD)

	# Define the source files for the Threading subsystem wrapper.
	set (COMMON_MUTEXES_THREAD_SUBSYS_WRAPPER_INCLUDES MSYS_Mutexes_Thread_Utils_Support.cpp)

	# Define the source files for the Threading subsystem plugin.
	set (COMMON_MUTEXES_THREAD_SUBSYS_WRAPPER_PLUGIN_INCLUDES ${COMMON_MUTEXES_THREAD_SUBSYS_WRAPPER_INCLUDES} MSYS_Mutexes_Thread_Utils_Plugin_Support.cpp)

	# Define the link libraries for the threading subsystem wrapper and plugin.
	set (COMMON_MUTEXES_THREAD_SUBSYS_WRAPPER_LINK_LIBS Common_Mutexes_Multiverse_Engine)

	# Create the mutexes library.
	add_library(Common_Mutexes_Multiverse_Engine SHARED ${COMMON_MUTEXES_INCLUDES}) 

	# Build the Thread Utils wrapper if needed.
	if (BUILD_INTERNAL_MUTEX_THREAD_SUBSYS_WRAPPER)
		add_library(Common_Mutexes_Threading_Subsystem_Wrapper_Multiverse_Engine STATIC ${COMMON_MUTEXES_THREAD_SUBSYS_WRAPPER_INCLUDES})
		target_link_libraries(Common_Mutexes_Threading_Subsystem_Wrapper_Multiverse_Engine ${COMMON_MUTEXES_THREAD_SUBSYS_WRAPPER_LINK_LIBS})
		set_property(TARGET Common_Mutexes_Threading_Subsystem_Wrapper_Multiverse_Engine APPEND PROPERTY COMPILE_DEFINITIONS ${MSYS_MUTEX_PLUGIN_DEFINES})
	endif (BUILD_INTERNAL_MUTEX_THREAD_SUBSYS_WRAPPER)

	# Build the threading subsystem plugin if needed.
	if (BUILD_INTERNAL_MUTEX_THREAD_SUBSYS_WRAPPER_PLUGIN)
		add_library(Common_Mutexes_Threading_Subsystem_Plugin_Wrapper_Multiverse_Engine SHARED ${COMMON_MUTEXES_THREAD_SUBSYS_WRAPPER_PLUGIN_INCLUDES})
		target_link_libraries(Common_Mutexes_Threading_Subsystem_Plugin_Wrapper_Multiverse_Engine ${COMMON_MUTEXES_THREAD_SUBSYS_WRAPPER_LINK_LIBS})
		set_property(TARGET Common_Mutexes_Threading_Subsystem_Plugin_Wrapper_Multiverse_Engine APPEND PROPERTY COMPILE_DEFINITIONS ${MSYS_MUTEX_PLUGIN_DEFINES})
	endif (BUILD_INTERNAL_MUTEX_THREAD_SUBSYS_WRAPPER_PLUGIN)
endif(BUILD_INTERNAL_MUTEX_SUPPORT)