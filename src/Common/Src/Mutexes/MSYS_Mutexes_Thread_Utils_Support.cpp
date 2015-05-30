/*!
    Multiverse Engine Project 10/4/2015 Common MSYS_Mutexes_Thread_Utils_Support.cpp

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

// Internal includes.
#include "MSYS_Mutexes_Thread_Utils_Support.h"

short TU_Mutex_MSYS::Init_Mutex()
{
	// Init vars.
	short ret = COMMON_ERROR_UNKNOWN_ERROR;		// The result of this function.

	// Check for a mutex from our library.
	if (this->lib == TU_LibID_MSYS_Mutex)
	{
		// Check for inited status.
		if (!(this->mutex_init))
		{
			// Check for allocated memory.
			if (this->mu != NULL)
			{
				// Destroy the mutex first.
				this->Destroy_Mutex();
			}

			// Begin try block.
			try {
				// Allocate the mutex.
				this->mu = MSYS_Create_Mutex();
				if (mu != NULL)
				{
					// Success.
					ret = COMMON_ERROR_SUCCESS;
					this->mutex_init = true;
				}
			}
			catch (std::exception & ex)
			{
				// Exception thrown.
				ret = COMMON_ERROR_EXCEPTION_THROWN;
				COMMON_LOG_VERBOSE("TU_Mutex_MSYS::Init_Mutex(): ");
				COMMON_LOG_VERBOSE(Common::Get_Error_Message(COMMON_ERROR_EXCEPTION_THROWN));
				COMMON_LOG_VERBOSE(" ");
				COMMON_LOG_VERBOSE(ex.what());
			}
		}
		else
		{
			// Already inited mutex.
			ret = COMMON_ERROR_INVALID_ARGUMENT;
		}
	}
	else
	{
		// Not an object from our library.
		ret = COMMON_ERROR_INVALID_LIBRARY_ID;
	}

	// Copy return code.
	this->rc_from_prevOP = ret;

	// Return result.
	return ret;
}

short TU_Mutex_MSYS::Destroy_Mutex()
{
	// Init vars.
	short ret = COMMON_ERROR_UNKNOWN_ERROR;	// The result of this function.

	// Check for a mutex from our library.
	if (this->lib == TU_LibID_MSYS_Mutex)
	{
		// Check for allocated memory.
		if (this->mu != NULL)
		{
			// Destroy the mutex first.
			MSYS_Destroy_Mutex(&(this->mu));
			if (this->mu == NULL)
			{
				// Success.
				this->mutex_init = false;
				ret = COMMON_ERROR_SUCCESS;
			}
			else
			{
				// Internal error.
				ret = COMMON_ERROR_INTERNAL_ERROR;
				COMMON_LOG_VERBOSE("TU_Mutex_MSYS::Destroy_Mutex(): ");
				COMMON_LOG_VERBOSE(Common::Get_Error_Message(COMMON_ERROR_INTERNAL_ERROR));
				COMMON_LOG_VERBOSE(" Unable to destroy mutex, MSYS_Destroy_Mutex() function failed.");
			}
		}
		else
		{
			// Already destroyed.
			ret = COMMON_ERROR_INVALID_ARGUMENT;
		}
	}
	else
	{
		// Not an object from our library.
		ret = COMMON_ERROR_INVALID_LIBRARY_ID;
	}

	// Copy return code.
	this->rc_from_prevOP = ret;

	// Return result.
	return ret;
}

short TU_Mutex_MSYS::Lock_Mutex()
{
	// Init vars.
	short ret = COMMON_ERROR_UNKNOWN_ERROR;	// The result of this function.
	MSYS_Mutex * retFromFunct = NULL;		// The result from MSYS_Lock_Mutex().

	// Check for a mutex from our library.
	if (this->lib == TU_LibID_MSYS_Mutex)
	{
		// Lock the mutex.
		retFromFunct = MSYS_Lock_Mutex(this->mu);
		if (retFromFunct == MSYS_MU_SUCCESS)
		{
			// Success.
			ret = COMMON_ERROR_SUCCESS;
		}
		else
		{
			// Null return, invalid mutex.
			ret = COMMON_ERROR_SYSTEM_SPECIFIC;
			COMMON_LOG_VERBOSE("TU_Mutex_MSYS::Lock_Mutex(): ");
			COMMON_LOG_VERBOSE(Common::Get_Error_Message(COMMON_ERROR_SYSTEM_SPECIFIC));
			COMMON_LOG_VERBOSE(" call to MSYS_Lock_Mutex() returned invalid pointer.");
		}
	}
	else
	{
		// Not an object from our library.
		ret = COMMON_ERROR_INVALID_LIBRARY_ID;
	}

	// Copy return code.
	this->rc_from_prevOP = ret;

	// Return result.
	return ret;
}

short TU_Mutex_MSYS::Try_Lock_Mutex()
{
	// Init vars.
	short ret = COMMON_ERROR_UNKNOWN_ERROR;		// The result of this function.
	short retFromFunct = MSYS_MU_UNKNOWN_ERROR;	// The result of the call to MSYS_Try_Lock_Mutex().

	// Check for a mutex from our library.
	if (this->lib == TU_LibID_MSYS_Mutex)
	{
		// Call try lock function.
		retFromFunct = MSYS_Try_Lock_Mutex(this->mu);
		if (retFromFunct == MSYS_MU_SUCCESS)
		{
			// Success.
			ret = COMMON_ERROR_SUCCESS;
		}
		else
		{
			if (retFromFunct == MSYS_MU_ALREADY_LOCKED)
			{
				// Lock already active.
				ret = THREAD_UTILS_ERROR_MUTEX_ALREADY_LOCKED;
			}
			else
			{
				// Internal error.
				ret = COMMON_ERROR_SYSTEM_SPECIFIC;
				COMMON_LOG_VERBOSE("TU_Mutex_MSYS::Try_Lock_Mutex(): ");
				COMMON_LOG_VERBOSE(Common::Get_Error_Message(COMMON_ERROR_SYSTEM_SPECIFIC));
				COMMON_LOG_VERBOSE(" call to MSYS_Try_Lock_Mutex() failed.");
			}
		}
	}
	else
	{
		// Not an object from our library.
		ret = COMMON_ERROR_INVALID_LIBRARY_ID;
	}

	// Copy return code.
	this->rc_from_prevOP = ret;

	// Return result.
	return ret;
}

short TU_Mutex_MSYS::Unlock_Mutex()
{
	// Init vars.
	short ret = COMMON_ERROR_UNKNOWN_ERROR;			// The result of this function.
	short retFromFunct = MSYS_MU_UNKNOWN_ERROR;		// The result from MSYS_Unlock_Mutex().

	// Check for a mutex from our library.
	if (this->lib == TU_LibID_MSYS_Mutex)
	{
		// Unlock the mutex.
		retFromFunct = MSYS_Unlock_Mutex(this->mu);
		if (retFromFunct == MSYS_MU_SUCCESS)
		{
			// Success.
			ret = COMMON_ERROR_SUCCESS;
		}
		else
		{
			// Check for ownership error.
			if (retFromFunct == MSYS_MU_ALREADY_LOCKED)
			{
				// The calling thread does not own the mutex.
				ret = COMMON_ERROR_ACCESS_DENIED;
			}
			else
			{
				// Null return, invalid mutex.
				ret = COMMON_ERROR_SYSTEM_SPECIFIC;
				COMMON_LOG_VERBOSE("TU_Mutex_MSYS::Unlock_Mutex(): ");
				COMMON_LOG_VERBOSE(Common::Get_Error_Message(COMMON_ERROR_SYSTEM_SPECIFIC));
				COMMON_LOG_VERBOSE(" call to MSYS_Unlock_Mutex() returned invalid pointer.");
			}
		}
	}
	else
	{
		// Not an object from our library.
		ret = COMMON_ERROR_INVALID_LIBRARY_ID;
	}

	// Copy return code.
	this->rc_from_prevOP = ret;

	// Return result.
	return ret;
}

TU_Mutex * TU_Create_MSYS_Mutex_Object()
{
	// Init vars.
	TU_Mutex * ret = NULL;		// The result of this function.

	// Begin try block.
	try {
		ret = new TU_Mutex_MSYS;
	}
	catch(std::exception & ex)
	{
		// Exception thrown.
		COMMON_LOG_VERBOSE("TU_Create_MSYS_Mutex_Object(): ");
		COMMON_LOG_VERBOSE(Common::Get_Error_Message(COMMON_ERROR_EXCEPTION_THROWN));
		COMMON_LOG_VERBOSE(" ");
		COMMON_LOG_VERBOSE(ex.what());
	}

	// Return the result.
	return ret;
}

void TU_Destroy_MSYS_Mutex_Object(TU_Mutex ** mu)
{
	// Check for valid pointer.
	if ((mu != NULL) && (*mu != NULL))
	{
		// Check for our library.
		if (((*mu)->Get_Thread_Library()) == TU_LibID_MSYS_Mutex)
		{
			delete *mu;
			*mu = NULL;
		}
	}

	// Exit function.
	return;
}

// End of MSYS_Mutexes_Thread_Utils_Support.cpp
