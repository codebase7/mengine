# Set output directories.
set(LIBRARY_OUTPUT_PATH ${L_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${O_OUTPUT_DIR})

# Set CMAKE_THREAD_PREFER_PTHREAD.
set(CMAKE_THREAD_PREFER_PTHREAD 1)

# Look for the pthreads library.
find_package(Threads REQUIRED)
if (Threads_FOUND)
    # Check for pthread.
    if (CMAKE_USE_PTHREADS_INIT)
		set (PTHREADS_ENABLED TRUE)
	else(CMAKE_USE_PTHREADS_INIT)
		set (PTHREADS_ENABLED FALSE)
	  # We need the pthreads library abort.
	  message(FATAL_ERROR "No pthreads library found. We need the Posix Thread Library, not a win32, sparc, hp, etc. version. Aborting.")
    endif(CMAKE_USE_PTHREADS_INIT)
endif(Threads_FOUND)

# Catch someone attempting to build plugin support without enabling the dynamic library subsystem.
if (ENABLE_THREADING_SUBSYSTEM_PLUGIN_SUPPORT)
	if (BUILD_DYNAMIC_LIBRARY_SUBSYSTEM)
		
		# Set the needed preprocessor defines for Thread_Utils plugin support if needed.
		set (THREAD_UTILS_DEFINES MSYS_PLUGIN_SUPPORT)

	else (BUILD_DYNAMIC_LIBRARY_SUBSYSTEM)
		message(SEND_ERROR "To use the threading subsystem's plugin support, the dynamic library subsystem must be built as well, as it is disabled in the build config, the build will now abort.")
	endif (BUILD_DYNAMIC_LIBRARY_SUBSYSTEM)
endif(ENABLE_THREADING_SUBSYSTEM_PLUGIN_SUPPORT)


# Figure out what OS to use...
IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	# Building on windows.
	# Create the Threading_Subsystem library.
	set(THREAD_UTILS_INCLUDES ../Generic_Wrapper.cpp 
	    Thread_Utils_Base.cpp 
	    Thread_Utils_Functions.cpp 
	    Posix_Threads/Thread_Utils_pthread.cpp)
	
	# Create the Pthreads Plugin.
	set(PTHREADS_PLUGIN_INCLUDES ../Generic_Wrapper.cpp 
	    Thread_Utils_Base.cpp 
	    Thread_Utils_pthread.cpp
	    Posix_Threads/Thread_Utils_pthread_Plugin.cpp)
	
	ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	    # Building on Linux.
	    # Create the Threading_Subsystem library.
	    set(THREAD_UTILS_INCLUDES ../Generic_Wrapper.cpp 
		Thread_Utils_Base.cpp 
		Thread_Utils_Functions.cpp 
		Posix_Threads/Thread_Utils_pthread.cpp)

	    # Create the Pthreads Plugin.
	    set(PTHREADS_PLUGIN_INCLUDES ../Generic_Wrapper.cpp 
		Thread_Utils_Base.cpp 
		Thread_Utils_pthread.cpp
		Posix_Threads/Thread_Utils_pthread_Plugin.cpp)

	ELSE(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	    # We don't have a match against a known system.
	    message(FATAL_ERROR "Attempting to build the Threading Subsystem with an unrecognized OS / System / Arch. Aborting build.")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")


# Build the Threading_Subsystem library.
add_library(Threading_Subsystem_Multiverse_Engine SHARED ${THREAD_UTILS_INCLUDES})

target_link_libraries(Threading_Subsystem_Multiverse_Engine Common_Error_Handler_Multiverse_Engine 
Dynamic_Library_Subsystem_Multiverse_Engine 
File_Management_Multiverse_Engine 
${CMAKE_THREAD_LIBS_INIT})

set_property(TARGET Threading_Subsystem_Multiverse_Engine APPEND PROPERTY COMPILE_DEFINITIONS ${THREAD_UTILS_DEFINES})


# Build the pthreads plugin if needed.
if (BUILD_THREAD_SUBSYS_PTHREADS_PLUGIN)
		# Set the needed preprocessor defines for the plugin build.
		set(PTHREADS_PLUGIN_DEFINES TW_PTHREADS_SUPPORT MSYS_PLUGIN_BUILD)

		# Build the PThreads Threading_Subsystem plugin.
		add_library(Pthreads_Plugin_Multiverse_Engine MODULE ${PTHREADS_PLUGIN_INCLUDES})

		# Set the compile definitons for plugins.
		set_property(TARGET Pthreads_Plugin_Multiverse_Engine APPEND PROPERTY COMPILE_DEFINITIONS ${PTHREADS_PLUGIN_DEFINES})

		# Set output directories for plugins.
		set_target_properties(Pthreads_Plugin_Multiverse_Engine PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PLUGIN_OUTPUT_DIR})
endif (BUILD_THREAD_SUBSYS_PTHREADS_PLUGIN)