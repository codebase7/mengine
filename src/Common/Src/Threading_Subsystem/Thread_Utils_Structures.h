/*!
    Multiverse Engine Project 31/5/2013 Common Thread_Utils_Structures.h

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
#ifndef THREAD_UTILS_STRUCTURES_H
#define THREAD_UTILS_STRUCTURES_H

// Check for THREAD_UTILS_H.
#ifndef THREAD_UTILS_H
#error "This header is included by Thread_Utils.h, do not include it directly."
#endif

// Include Generic_Wrapper.
#include "../Generic_Wrapper.h"	// Defines LibraryID.

/*!
 * 	static int threadUtilsLastError
 * 
 * 	Holds the last error that a call to a Common::Thread_Utils function encountered.
 * 
 * 	Does NOT hold the last error encounted by a Common::Thread_Utils class object.
 * 	(For those errors, call their GetLastError() member function.)
 */
static int threadUtilsLastError = 0;

/*!
 * 	struct TU_Library_Support_Status
 * 
 * 	This structure is used to aid programs in determining what threading library to use.
 *
 * 	It contains varius info about what is supported by the current Thread_Utils.
 * 	Note To Library Maintainers: If support is added / removed for a given library you
 * 	must update it's Library_Support_Status structure.
 *
 * 	Also if you add support for a new threading library you must create it's
 * 	Library_Support_Status structure. (In the actual header files for that particular
 * 	library.)
 */
struct TU_Library_Support_Status
{
	// Library ID.
	const Common_LibraryID * lib;

	// Thread support status.
	bool bThreadsSupport;
	bool bJoinThreadSupport;
	bool bDetachThreadSupport;
	bool bLibraryRequiresSpecificFunctionSig;

	// Mutex support status.
	bool bMutexesSupport;
	bool bTryLockSupport;

	// Condition variable support status.
	bool bConditionVariableSupport;
	bool bConditionWaitTimeoutSupport;
};

// This is the LibraryID structure for the none / unsupported library.
const Common_LibraryID TU_LibID_none = {false, "None / Unsupported"};

// Below is a instance of the Library_Support_Status struct for the none / unsupported library.
const TU_Library_Support_Status TU_LibSupport_none =
{
	&TU_LibID_none, // idNum				(ID of the thread library that this struct is for.)
	false,          // bThreadsSupport                      (Do we support creating threads with this library.)
	false,          // bJoinThreadSupport                   (Do we support joining threads with this library.)
	false,          // bDetachThreadSupport                 (Do we support detaching threads with this library.)
	false,          // bLibraryRequiresSpecificFunctionSig  (Do we require that the user use a specific function signature when creating threads?)
	false,          // bMutexesSupport                      (Do we support creating mutexes with this library. Also basic lock and unlock support.)
	false,          // bTryLockSupport                      (Do we support trying to lock mutexes with this library.)
	false,          // bConditionVariableSupport            (Do we support condition variables with this library.)
	false           // bConditionWaitTimeoutSupport         (Do we support a timeout limit when waiting on a condition variable with this library.)
};

#endif

// End of Thread_Utils_Structures.h
