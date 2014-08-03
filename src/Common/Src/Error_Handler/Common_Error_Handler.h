/*!
    Multiverse Engine Project 23/6/2014 Common Common_Error_Handler.h

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
#ifndef COMMON_ERROR_HANDLER_H
#define COMMON_ERROR_HANDLER_H

// External includes.
#include <stddef.h>		// Defines NULL.

// Project includes.
#ifdef __win32	// Needed for different path seperator in Windows.
#include "..\..\..\Core\Src\Panic_Error_Levels.h"	// Defines the log levels.
#else
#include "../../../Core/Src/Panic_Error_Levels.h"	// Defines the log levels.
#endif // __win32

#include "Common_Error_Handler_Structures.h"		// Defines the error codes, error lookup table error lookup table version number, and Common::commonLastErrorCode.
#include "Posix_Error_Translation_Table.h"		// Defines the POSIX errno to Common namespace error translation table and functions.

// Define namespaces.
namespace Common
{
	/*!
	 * 	const unsigned int Common::Get_Error_Table_Size()
	 * 
	 * 	Returns the size of the common error table.
	 */
	const unsigned int Get_Error_Table_Size();

	/*!
	 * 	const char * Common::Get_Error_Message(const int & errorCode)
	 * 
	 * 	This function takes the given error code and returns a pointer to a human
	 * 	readable string describing the meaning of the given error code.
	 * 
	 * 	Returns a valid pointer if the given error code is in the common error table.
	 * 	Returns the message for Common::COMMON_UNKNOWN_ERROR otherwise.
	 */
	const char * Get_Error_Message(const int & errorCode);

	/*!
	 * 	void Common::Set_Error_Log_Level(const unsigned int & logLevel)
	 * 
	 * 	Sets the error logging level for the Common namespace functions.
	 * 
	 * 	By default it sets the error logging level to ERROR_DISABLE.
	 * 	(Disables all logging. See Core/Src/Panic.h for a list of
	 * 	 valid logging levels.)
	 */
	void Set_Error_Log_Level(const unsigned int & logLevel = ERROR_DISABLE);

	/*!
	 * 	unsigned int Common::Get_Error_Log_Level()
	 * 
	 * 	Returns the current error logging level for the Common namespace functions.
	 * 
	 * 	See Core/Src/Panic.h for a list of valid logging levels.
	 */
	unsigned int Get_Error_Log_Level();

	/*!
	 * 	void Common::Register_Error_Log_Callback(void (*loggingFunction)(const unsigned int logLevel, const char * errorMsg))
	 * 
	 * 	WARNING: The callback function MUST return control back to
	 * 	the caller, as the caller will be blocked until the callback
	 * 	function returns.
	 * 
	 * 	Sets the logging function to call when an error is generated
	 * 	by a Common namespace function.
	 * 
	 * 	For example, this function can be used to send the generated
	 * 	errors to the console in a multi-threaded enviroment.
	 * 
	 * 	Passing a NULL pointer to this function (the default) will
	 * 	disable calling another function when an error is generated.
	 * 	In addition the logging level will be reset to ERROR_DISABLE.
	 */
	void Register_Error_Log_Callback(void (*loggingFunction)(const unsigned int logLevel, const char * errorMsg) = NULL);
};

#endif // COMMON_ERROR_HANDLER_H

// End of Common_Error_Handler.h
