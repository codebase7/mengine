/*!
    Multiverse Engine Project 10/4/2015 Common MSYS_Mutexes_Thread_Utils_Support.h

    Copyright (C) 2015 Multiverse Engine Project

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
#ifndef MSYS_MUTEXES_THREAD_UTILS_SUPPORT_H
#define MSYS_MUTEXES_THREAD_UTILS_SUPPORT_H

// Internal includes.
#ifdef __win32__
#include "..\Threading_Subsystem\Thread_Utils.h"		// Defines Thread_Utils.
#include "..\LibraryID_Struct.h"				// Defines Common_LibraryID.
#include "..\Error_Handler\Common_Error_Handler.h"		// Pulls in the error code lookup function and error codes.
#include "..\Error_Handler\Common_Error_Handler_Internal.h"	// Defines the error logging functions.
#else
#include "../Threading_Subsystem/Thread_Utils.h"		// Defines Thread_Utils.
#include "../LibraryID_Struct.h"				// Defines Common_LibraryID.
#include "../Error_Handler/Common_Error_Handler.h"		// Pulls in the error code lookup function and error codes.
#include "../Error_Handler/Common_Error_Handler_Internal.h"	// Defines the error logging functions.
#endif	// __win32__
#include "MSYS_Mutexes.h"

// Define ID Text for Thread_Utils.
#define MSYS_INTERNAL_MUTEX_SUPPORT_ID_STR "MSYS Internal Mutex Support"

// Define Library ID structure for Thread_Utils.
// If we are building a plugin, we need to set the plugin flag to true.
#ifdef MSYS_PLUGIN_BUILD
		// Building a plugin, so set the plugin flag to true.
		const Common_LibraryID TU_LibID_MSYS_Mutex = Common_LibraryID(true, MSYS_INTERNAL_MUTEX_SUPPORT_ID_STR);

// Also need to include the plugin header file.
#ifdef __win32__
#include "..\Threading_Subsystem\Thread_Utils_Plugin.h"	// Defines needed function prototypes for Threading Subsystem plugins.
#else
#include "../Threading_Subsystem/Thread_Utils_Plugin.h"	// Defines needed function prototypes for Threading Subsystem plugins.
#endif	// __win32__
#else
		// Not a plugin, so set the plugin flag to false.
		const Common_LibraryID TU_LibID_MSYS_Mutex = Common_LibraryID(false, MSYS_INTERNAL_MUTEX_SUPPORT_ID_STR);
#endif	// MSYS_PLUGIN_BUILD

// MSYS Internal Mutex Support Library_Support_Status structure.
const TU_Library_Support_Status TU_LibSupport_MSYS_Mutex_Support =
{
	&TU_LibID_MSYS_Mutex,		// {false, "MSYS Internal Mutex Support"}  (ID of the thread library that this struct is for.)
	false,				// bThreadsSupport  (Do we support creating threads with this library.)
	false,				// bJoinThreadSupport   (Do we support joining threads with this library.)
	false,				// bDetachThreadSupport (Do we support detaching threads with this library.)
	false,				// bLibraryRequiresSpecificFunctionSig  (Do we require that the user use a specific function signature when creating threads?)
	true,				// bMutexesSupport  (Do we support creating mutexes with this library. Also basic lock and unlock support.)
	true,				// bTryLockSupport  (Do we support trying to lock mutexes with this library.)
	false,				// bConditionVariableSupport  (Do we support condition variables with this library.)
	false				// bConditionWaitTimeoutSupport  (Do we support a timeout limit when waiting on a condition variable with this library.)
};

class TU_Mutex_MSYS : public TU_Mutex, public Common_Generic_Wrapper
{
	private:
		bool mutex_init;	// Used to tell if the mutex object has been inited by the user.
		MSYS_Mutex * mu;	// The actual mutex.

	protected:

	public:
		TU_Mutex_MSYS()
		{
			lib = TU_LibID_MSYS_Mutex;
			mutex_init = false;
			mu = NULL;
			rc_from_prevOP = COMMON_ERROR_SUCCESS;
		}
		~TU_Mutex_MSYS()
		{
			Destroy_Mutex();
		  
			if (mu != NULL)
			{
				MSYS_Destroy_Mutex(&mu);
				mu = NULL;
				mutex_init = false;
			}
		}

		// Accessor function for the lib.
		/*!
			short TU_Mutex_MSYS::Init_Mutex()

			This function is the real wrapper function for creating mutexes using the MSYS Internal Mutex library.

			Returns COMMON_ERROR_SUCCESS on success.
			Returns COMMON_ERROR_INVALID_ARGUMENT if the mutex was already inited. (Use Destroy_Mutex() first.)
			Returns COMMON_ERROR_EXCEPTION_THROWN if an exception is thrown during the call to MSYS_Create_Mutex().
			Returns COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED if the function is not implimented.
		*/
		short Init_Mutex();

		/*!
			short TU_Mutex_MSYS::Destroy_Mutex()

			This function is the real wrapper function for destroying mutexes using the MSYS Internal Mutex library.

			Returns COMMON_ERROR_SUCCESS on success.
			Returns COMMON_ERROR_INVALID_ARGUMENT if the mutex was already destroyed. (Use Init_Mutex() first.)
			Returns COMMON_ERROR_INTERNAL_ERROR on error from library. (Return code will be stored in rc_from_prevOP.)
			Returns COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED if the function is not implimented.
		*/
		short Destroy_Mutex();

		/*!
			short TU_Mutex_MSYS::Lock_Mutex()

			This function is the real wrapper function for locking mutexes using the MSYS Internal Mutex library.

			Note: This function will block the calling thread, until the mutex is locked by it.

			Returns COMMON_ERROR_SUCCESS on success. (Or if the mutex is already held by the current thread. In this case Get_Return_Code() will return EDEADLK.)
			Returns COMMON_ERROR_INVALID_LIBRARY_ID if mutex object was created for a different library.
			Returns COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED if the function is not implimented.
			Returns COMMON_ERROR_SYSTEM_SPECIFIC on error from library. (Return code will be stored in rc_from_prevOP.)
		*/
		short Lock_Mutex();

		/*!
			short TU_Mutex_MSYS::Try_Lock_Mutex()

			This function is the real wrapper function for trying to lock a mutex using the MSYS Internal Mutex library.

			Note: This function will NOT block the calling thread, if the mutex is already locked it returns 1.

			Returns COMMON_ERROR_SUCCESS on success.
			Returns THREAD_UTILS_ERROR_MUTEX_ALREADY_LOCKED if the mutex is locked already.
			Returns COMMON_ERROR_INVALID_LIBRARY_ID if mutex object was created for a different library.
			Returns COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED if the function is not implimented.
			Returns COMMON_ERROR_SYSTEM_SPECIFIC on error from library. (Return code will be stored in rc_from_prevOP.)
		*/
		short Try_Lock_Mutex();

		/*!
			short TU_Mutex_MSYS::Unlock_Mutex()

			This function is the real wrapper function for unlocking mutexes using the MSYS Internal Mutex library.

			Returns COMMON_ERROR_SUCCESS on success.
			Returns COMMON_ERROR_INVALID_LIBRARY_ID if mutex object was created for a different library.
			Returns COMMON_ERROR_ACCESS_DENIED if unlocking fails due to the mutex not being held by the current thread.
			Returns COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED if the function is not implimented.
			Returns COMMON_ERROR_SYSTEM_SPECIFIC on error from library. (Return code will be stored in rc_from_prevOP.)
		*/
		short Unlock_Mutex();
};

// Define the factories and destructor functions.
/*!
 * 	TU_Mutex * TU_Create_MSYS_Mutex_Object()
 *
 * 	Factory function for creating TU_Mutex objects that use
 * 	MSYS_Mutex objects as a base.
 *
 * 	Returns a valid pointer if successful.
 *
 * 	Returns NULL otherwise.
 */
TU_Mutex * TU_Create_MSYS_Mutex_Object();

/*!
 * 	void TU_Destroy_MSYS_Mutex_Object(TU_Mutex ** mu)
 *
 * 	Destructor function for TU_Mutex objects created by
 * 	TU_Create_MSYS_Mutex_Object().
 *
 * 	The pointer to object given as a pointer to pointer
 * 	argument to this function will be NULL apon this
 * 	function's return if the call to this function is
 * 	successful.
 *
 * 	If an invalid (NULL) pointer is given no free attempt
 * 	will be made, and the pointer will remain unaltered.
 *
 * 	This function will check the Common_LibraryID reported
 * 	by the given TU_Mutex object. If an object not created
 * 	by this library is given to this function, then the
 * 	object and it's pointer will remain unaltered apon this
 * 	function's return.
 */
void TU_Destroy_MSYS_Mutex_Object(TU_Mutex ** mu);

#endif	// MSYS_MUTEXES_THREAD_UTILS_SUPPORT_H

// End of MSYS_Mutexes_Thread_Utils_Support.h
