/*!
    Multiverse Engine Project 23/6/2014 Common Common_Error_Handler_Structures.h

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

/* Include guard. */
#ifndef COMMON_ERROR_HANDLER_STRUCTURES_H
#define COMMON_ERROR_HANDLER_STRUCTURES_H

/* Internal Includes. */
#include "Error_Struct.h"	/* Structure used to create error lookup table. */

/* Define the Common unknown error message. (It has to be replicated in two places, once for the C code and once for the C++ bindings.) */
#define COMMON_UNKNOWN_ERROR_MSG_DEF "Unknown error code."

/* Error code table ABI version. */
#define COMMON_ERROR_TABLE_ABI_VER 2	/* Increment this if you alter the table. */

/* Enable C linkage if needed. */
#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/* Common namespace error code definitions. (Human-readable error message translation table is located in Common_Error_Handler_Structures.c) */
	enum {
		/* Generic error codes. */
		COMMON_ERROR_SYSTEM_SPECIFIC = 99,
		COMMON_ERROR_SUCCESS = 0,
		COMMON_ERROR_UNKNOWN_ERROR = -1,
		COMMON_ERROR_INVALID_ARGUMENT = -2,
		COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED = -3,
		COMMON_ERROR_ACCESS_DENIED = -4,
		COMMON_ERROR_EXCEPTION_THROWN = -5,
		COMMON_ERROR_INTERNAL_ERROR = -6,
		COMMON_ERROR_IO_ERROR = -7,
		COMMON_ERROR_RANGE_ERROR = -8,
		COMMON_ERROR_MEMORY_ERROR = -9,
		COMMON_ERROR_INVALID_LIBRARY_ID = -10,	/* Formerly THREAD_UTILS_INVALID_LIBRARY_ID. */
		COMMON_ERROR_PEBKAC_INVALID_OPERATION_ORDER = -11,
		COMMON_ERROR_CANNOT_GET_SYSTEM_TIME = -12,
		COMMON_ERROR_SUBSYSTEM_OBJECT_NOT_INITED = -13,
		COMMON_ERROR_SUBSYSTEM_OBJECT_ALREADY_INITED = -14,
		
		/* Rendering Subsystem error codes. */
		RENDERER_ERROR_UNABLE_TO_ALLOC_OI_BUF = -21,	/* Overlay image buffer. */
		RENDERER_ERROR_UNABLE_TO_ALLOC_TD_BUF = -22,	/* Transparency data buffer. */
		RENDERER_ERROR_MEM_BUF_ALLOC_EXCEPTION = -23, 
		RENDERER_ERROR_DUPE_OVERLAY_EXCEPTION = -24,
		RENDERER_ERROR_INVAL_OVERLAY_SELF_OVERWRITE = -25,
		RENDERER_ERROR_TRANSPARENCY_DISABLED = -26,
		/* Threading Subsystem error codes. */
		THREAD_UTILS_ERROR_EXCEPTION_THROWN = -31,
		THREAD_UTILS_ERROR_PLUGIN_LOAD_FAILURE = -32,
		THREAD_UTILS_ERROR_THREAD_COULD_NOT_START = -33,
		THREAD_UTILS_ERROR_THREAD_COULD_NOT_DETACH = -34,
		THREAD_UTILS_ERROR_THREAD_COULD_NOT_JOIN = -35,
		THREAD_UTILS_ERROR_MUTEX_ALREADY_LOCKED = -36,
		THREAD_UTILS_ERROR_CONDITION_CANNOT_LOCK_MUTEX = -37,
		THREAD_UTILS_ERROR_CONDITION_WAIT_TIMEOUT_REACHED = -38,
		/* FileUtills error codes. */
		FILEUTILLS_ERROR_EXISTANT = -60,
		FILEUTILLS_ERROR_NON_EXISTANT = -61,
		FILEUTILLS_ERROR_READ_ONLY = -62,
		FILEUTILLS_ERROR_PATH_LENGTH_INVALID = -63,
		FILEUTILLS_ERROR_PATH_FILE_AS_DIRECTORY = -64,
		FILEUTILLS_ERROR_PATH_IS_A_FILE = -65,
		FILEUTILLS_ERROR_PATH_IS_A_DIRECTORY = -66,
		FILEUTILLS_ERROR_FILESYSTEM_FULL = -67,
		FILEUTILLS_ERROR_FILESYSTEM_QUOTA_REACHED = -68,
		FILEUTILLS_ERROR_EMPTY_DIRECTORY = -69,
		FILEUTILLS_ERROR_NON_EMPTY_DIRECTORY = -70,
		/* UI Subsystem. */
		UI_SUBSYSTEM_ERROR_EXCEPTION_THROWN = -90,
	};

/*!
 * 	const unsigned int Common_Get_Error_Table_API_Version()
 *
 * 	Returns the API version number of the common error table.
 */
const unsigned int Common_Get_Error_Table_API_Version();

/*!
 * 	const unsigned int Common_Get_Error_Table_Size()
 *
 * 	Returns the size of the common error table.
 */
const unsigned int Common_Get_Error_Table_Size();

/*!
 * 	const char * Common_Get_Error_Message(const int & errorCode)
 * 
 * 	This function takes the given error code and returns a pointer to a human
 * 	readable string describing the meaning of the given error code.
 * 
 * 	Returns a valid pointer if the given error code is in the common error table.
 * 	Returns the message for Common_COMMON_UNKNOWN_ERROR otherwise.
 */
const char * Common_Get_Error_Message(const int errorCode);

/* End C Linkage if needed. */
#ifdef __cplusplus
}	/* extern C */
#endif	/* __cplusplus */

/* Define C++ Bindings. */
#ifdef __cplusplus
/* Define namespaces. */
namespace Common
{
	/*!
	 * 	const unsigned int Common::Get_Error_Table_API_Version()
	 *
	 * 	(C++ Binding)
	 *
	 * 	Returns the API version number of the common error table.
	 */
	const unsigned int Get_Error_Table_API_Version();

	/*!
	 * 	const unsigned int Common::Get_Error_Table_Size()
	 *
	 * 	(C++ Binding)
	 *
	 * 	Returns the size of the common error table.
	 */
	const unsigned int Get_Error_Table_Size();

	/*!
	 * 	const char * Common::Get_Error_Message(const int & errorCode)
	 * 
	 * 	(C++ Binding)
	 * 
	 * 	This function takes the given error code and returns a pointer to a human
	 * 	readable string describing the meaning of the given error code.
	 * 
	 * 	Returns a valid pointer if the given error code is in the common error table.
	 * 	Returns the message for Common_COMMON_UNKNOWN_ERROR otherwise.
	 */
	const char * Get_Error_Message(const int & errorCode);
};
#endif	/* __cplusplus */

#endif	/* COMMON_ERROR_HANDLER_STRUCTURES_H */

/* End of Common_Error_Handler_Structures.h */
