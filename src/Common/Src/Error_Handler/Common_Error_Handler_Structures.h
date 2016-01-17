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
#include "Error_Struct.h"		/* Structure used to create error lookup table. */
#include "../../../DLL_PORT.h"	/* Defines MSYS_DLL_EXPORT. */

/* Define the Common unknown error message. (It has to be replicated in two places, once for the C code and once for the C++ bindings.) */
#define COMMON_UNKNOWN_ERROR_MSG_DEF "Unknown error code."

/* Error code table ABI version. */
#define COMMON_ERROR_TABLE_ABI_VER 2	/* Increment this if you alter the table. */

/* Enable C linkage if needed. */
#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/* ERROR CODES MOVED TO Common_Error_Handler_Error_Codes.h */

/*!
 * 	const unsigned int Common_Get_Error_Table_API_Version()
 *
 * 	Returns the API version number of the common error table.
 */
MSYS_DLL_EXPORT const unsigned int Common_Get_Error_Table_API_Version();

/*!
 * 	const unsigned int Common_Get_Error_Table_Size()
 *
 * 	Returns the size of the common error table.
 */
MSYS_DLL_EXPORT const unsigned int Common_Get_Error_Table_Size();

/*!
 * 	const char * Common_Get_Error_Message(const int & errorCode)
 * 
 * 	This function takes the given error code and returns a pointer to a human
 * 	readable string describing the meaning of the given error code.
 * 
 * 	Returns a valid pointer if the given error code is in the common error table.
 * 	Returns the message for Common_COMMON_UNKNOWN_ERROR otherwise.
 */
MSYS_DLL_EXPORT const char * Common_Get_Error_Message(const int errorCode);

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
	MSYS_DLL_EXPORT const unsigned int Get_Error_Table_API_Version();

	/*!
	 * 	const unsigned int Common::Get_Error_Table_Size()
	 *
	 * 	(C++ Binding)
	 *
	 * 	Returns the size of the common error table.
	 */
	MSYS_DLL_EXPORT const unsigned int Get_Error_Table_Size();

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
	MSYS_DLL_EXPORT const char * Get_Error_Message(const int & errorCode);
};
#endif	/* __cplusplus */

#endif	/* COMMON_ERROR_HANDLER_STRUCTURES_H */

/* End of Common_Error_Handler_Structures.h */
