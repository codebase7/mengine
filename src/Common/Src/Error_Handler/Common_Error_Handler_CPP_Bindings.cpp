/*!
    Multiverse Engine Project 13/5/2015 Common Common_Error_Handler_CPP_Bindings.cpp

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

// Define C++ Bindings.
#ifdef __cplusplus

// Internal includes.
#include "Common_Error_Handler.h"		// Main header.
#include "Common_Error_Handler_Internal.h"	// Private internal header that defines the structure used for error logging.

// External includes.
#include <exception>

void Common::Set_Error_Log_Level(const unsigned int & logLevel)
{
	Common_Set_Error_Log_Level(logLevel);
}

unsigned int Common::Get_Error_Log_Level()
{
	return Common_Get_Error_Log_Level();
}

void Common::Register_Error_Log_Callback(void (*loggingFunction)(const unsigned int logLevel, const char * errorMsg))
{
	Common_Register_Error_Log_Callback(loggingFunction);
}

// Build the Fatal Error Handler if needed.
#ifdef MSYS_BUILD_FATAL_ERROR_SUPPORT

bool Common::Register_Fatal_Error_Callback(const Common_pErrorCallBackFunction fatalErrorNotifyFunction)
{
	// Init vars.
	bool ret = false;		// The result of this function.

	// Begin try block.
	try {
		// Call real function.
		ret = Common_Register_Fatal_Error_Callback(fatalErrorNotifyFunction);
	}
	catch (...)
	{
		/* 
		 * Great probably a memory allocation error, if so, we don't do anything as the original list is not modifyed
		 * unless the operations succeed.
		 *
		 * If not, well we just destroyed the list of functions we needed to call when a fatal error happened,
		 * so maybe we should call terminate() here?
		 */
		ret = false;
	}

	// Return the result.
	return ret;
}

bool Common::Unregister_Fatal_Error_Callback(const Common_pErrorCallBackFunction fatalErrorNotifyFunction)
{
	// Init vars.
	bool ret = false;		// The result of this function.

	// Begin try block.
	try {
		// Call real function.
		ret = Common_Unregister_Fatal_Error_Callback(fatalErrorNotifyFunction);
	}
	catch (...)
	{
		/* 
		 * Great probably a memory allocation error, if so, we don't do anything as the original list is not modifyed
		 * unless the operations succeed.
		 *
		 * If not, well we just destroyed the list of functions we needed to call when a fatal error happened,
		 * so maybe we should call terminate() here?
		 */
		ret = false;
	}

	// Return the result.
	return ret;
}

void Common::Fatal_Error_Notify()
{
	// Begin try block.
	try {
		// Call real function.
		Common_Fatal_Error_Notify();
	}
	catch (std::exception & ex)
	{
		// Well, not much to do here, we are terminating anyway.
		COMMON_LOG_CRITICAL("Common::Fatal_Error_Notify(): Exception occured while notifying engine subsystems / application that a fatal error occured.");
	}
}

#endif	// MSYS_BUILD_FATAL_ERROR_SUPPORT

#endif	// __cplusplus

