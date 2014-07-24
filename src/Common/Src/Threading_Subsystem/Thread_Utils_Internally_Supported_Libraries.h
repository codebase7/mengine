/*!
    Multiverse Engine Project 04/7/2014 Common Thread_Utils_Internally_Supported_Libraries.h (INTERNAL ENGINE USE ONLY)

    Copyright (C) 2014 Multiverse Engine Project

    This program is free software;
    you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation;
    either version 2 of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
    without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
    See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with this program;
    if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

    Official source repository and project information can be found at
    https://github.com/codebase7/mengine
*/

// Include guard.
#ifndef THREAD_UTILS_INTERNALLY_SUPPORTED_LIBRARIES_H
#define THREAD_UTILS_INTERNALLY_SUPPORTED_LIBRARIES_H

// Check for THREAD_UTILS_H.
#ifndef THREAD_UTILS_H
#error "This header is not for public use, as it is a part of the engine's private internal API. DO NOT LINK TO THIS HEADER!"
#endif

/*!
 * 	const Common_LibraryID Thread_Utils_supportedThreadLibs
 *
 * 	Contains a list of internally supported threading libraries.
 *
 * 	The actual list used by the engine is generated at compile time.
 * 	Below is the entire list of supported libraries that could be avaiable.
 * 	Note: That some of the libraries below may not be avaiable to the engine
 * 	at run-time due to external reasons.
 * 	(Ex. The library is not supported on the given platform, was disabled at compile
 * 	time due to user override, etc.)
 *
 * 	The format for the structure defintions below is:
 *
 * 	{Library_Support_Status structure, Thread creation function pointer,
 * 	 Mutex creation function pointer, Condition variable creation pointer,
 * 	 Thread destruction function pointer, Mutex destruction function pointer,
 * 	 Condition variable destruction function pointer};
 *
 * 	Note: If you add support for a library, it must define creation and destruction
 * 	functions in addition to it's Library_Support_Status structure for any supported
 * 	object.
 *
 * 	(For example, If you add a library whose Library_Support_Status structure
 * 	says it supports Threads and mutexes but not condition variables, then you must
 * 	define a creation and a destruction function for thread objects, in addition to
 * 	defining a creation and a destruction function for mutex objects. The pointers
 * 	for creating and destroying a condition variable object should be NULL pointers.)
 */
const TU_Library TU_supportedThreadLibs[] =
{
	// Default None / Unsupported Dummy Library. (DO NOT REMOVE!)
	{TU_LibSupport_none, NULL, NULL, NULL, NULL, NULL, NULL},
	#ifdef TW_PTHREADS_SUPPORT
	{TU_LibSupport_pthreads, TU_Create_Pthread_Thread_Object, TU_Create_Pthread_Mutex_Object, TU_Create_Pthread_Condition_Object,
	 TU_Destroy_Pthread_Thread_Object, TU_Destroy_Pthread_Mutex_Object, TU_Destroy_Pthread_Condition_Object},
	#endif
};

#endif	// THREAD_UTILS_INTERNALLY_SUPPORTED_LIBRARIES_H

// End of Thread_Utils_Internally_Supported_Libraries.h