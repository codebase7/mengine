# Set CMAKE_THREAD_PREFER_PTHREAD.
set(CMAKE_THREAD_PREFER_PTHREAD 1)

# Look for the pthreads library.
find_package(Threads REQUIRED)
if (Threads_FOUND)
    # Check for pthread.
    if (NOT CMAKE_USE_PTHREADS_INIT)
	  # We need the pthreads library abort.
	  message(FATAL_ERROR "No pthreads library found. We need the Posix Thread Library, not a win32, sparc, hp, etc. version. Aborting.")
    endif(NOT CMAKE_USE_PTHREADS_INIT)
endif(Threads_FOUND)
add_library(Common_Multiverse_Engine SHARED FileUtills.cpp Thread_Utils_Base.cpp Thread_Utils_Functions.cpp Thread_Utils_pthread.cpp)
target_link_libraries(Common_Multiverse_Engine Core_Multiverse_Engine Panic_Handler_Multiverse_Engine ${CMAKE_THREAD_LIBS_INIT})