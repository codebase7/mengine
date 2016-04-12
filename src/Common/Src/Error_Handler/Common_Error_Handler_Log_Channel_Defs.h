/*!
    Multiverse Engine Project 12/2/2016 Common Common_Error_Handler_Log_Channel_Defs.h

    Copyright (C) 2016 Multiverse Engine Project

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
#ifndef COMMON_ERROR_HANDLER_LOG_CHANNEL_DEFS_H
#define COMMON_ERROR_HANDLER_LOG_CHANNEL_DEFS_H

/* Internal includes. */
#include "../../../DLL_PORT.h"

/* External includes. */
#include <stddef.h>

/* Define error log channels. */
#define MSYS_ERROR_LOG_CHANNEL_LIST_VER 0	/* Version ID of the channel list. If you change the channel IDs below change the version ID. */
#define MSYS_ERROR_LOG_CHANNEL_UNDEFINED 0
#define MSYS_ERROR_LOG_CHANNEL_USERDEFINED 1
#define MSYS_ERROR_LOG_CHANNEL_ERROR_HANDLER 2
#define MSYS_ERROR_LOG_CHANNEL_DYNLIB 3
#define MSYS_ERROR_LOG_CHANNEL_BYTEORDER 4
#define MSYS_ERROR_LOG_CHANNEL_FILEUTILLS 5
#define MSYS_ERROR_LOG_CHANNEL_THREADUTILS 6
#define MSYS_ERROR_LOG_CHANNEL_RENDERING_SUBSYS 7

/* Define the human readable error log channel name strings. */
#define MSYS_ERROR_LOG_CHANNEL_UNDEFINED_NAME "Undefined"
#define MSYS_ERROR_LOG_CHANNEL_USERDEFINED_NAME "User Defined"
#define MSYS_ERROR_LOG_CHANNEL_ERROR_HANDLER_NAME "Error Handler"
#define MSYS_ERROR_LOG_CHANNEL_DYNLIB_NAME "Dynamic Library Subsystem"
#define MSYS_ERROR_LOG_CHANNEL_BYTEORDER_NAME "Byte Order"
#define MSYS_ERROR_LOG_CHANNEL_FILEUTILLS_NAME "File Management Subsystem"
#define MSYS_ERROR_LOG_CHANNEL_THREADUTILS_NAME "Threading Subsystem"
#define MSYS_ERROR_LOG_CHANNEL_RENDERING_SUBSYS_NAME "Rendering Subsystem"

/* Check for a C++ Compiler. */
#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/*!
	int Common_Error_Get_Logging_Channel_ID_Number_By_Name(int * channelID, const char * name, const size_t nameLength)

	Takes the given human readable error log channel name (in C-String format) and length, and returns it's associated channel ID number.

	Note: This function will overwrite whatever value is stored by the given channel ID argument.
	If you need that value after this function returns, copy it elsewhere before calling this function.

	Returns COMMON_ERROR_SUCCESS if the channel ID was found. (The channel ID argument will be updated in this case.)
	Returns COMMON_ERROR_INVALID_ARGUMENT if the given channel name is invalid / not recognized, the given channel name
	length is less than or equal to zero, or a given pointer is NULL.

	No-alteration clause:
		- In case of error, this function will not modify it's arguments.
 */
MSYS_DLL_EXPORT int Common_Error_Get_Logging_Channel_ID_Number_By_Name(int * channelID, const char * name, const size_t nameLength);

/*!
	int Common_Error_Get_Logging_Channel_Name_By_ID_Number(const int channelID, const char ** name, size_t * nameLength)

	Takes the given error log channel ID number, and returns a pointer to a human readable name in C-String format, along with it's length.

	WARNING: DO NOT ATTEMPT TO DEALLOCATE OR ALTER THIS STRING. IT IS FOR REFERENCE ONLY.

	Note: This function will overwrite whatever values are stored by the given name pointer and length arguments.
	If you need those values after this function returns, copy them elsewhere before calling this function.

	Returns COMMON_ERROR_SUCCESS if the channel name was found. (The pointer and length arguments will be updated in this case.)
	Returns COMMON_ERROR_INVALID_ARGUMENT if the given channel ID is invalid / not recognized, or a given pointer is NULL.

	No-alteration clause:
		- In case of error, this function will not modify it's arguments.
 */
MSYS_DLL_EXPORT int Common_Error_Get_Logging_Channel_Name_By_ID_Number(const int channelID, const char ** name, size_t * nameLength);

/*!
	int Common_Error_Get_Logging_Channel_Status_By_ID_Number(const int channelID)

	Takes the given error log channel ID number, and returns whether or not the channel is enabled.
	(If a channel is enabled, it's messages will be sent to the registered error handler callback function.
	 If a channel is disabled, it's messages will be discarded.)

	Returns COMMON_ERROR_TRUE if the channel is enabled.
	Returns COMMON_ERROR_FALSE if the channel is disabled.
	Returns COMMON_ERROR_INVALID_ARGUMENT if the given channel ID is invalid / not recognized.
 */
MSYS_DLL_EXPORT int Common_Error_Get_Logging_Channel_Status_By_ID_Number(const int channelID);

/*!
	int Common_Error_Set_Logging_Channel_Status_By_ID_Number(const int channelID, const short enabled)

	Takes the given error log channel ID number, and sets whether or not the channel is enabled.
	(If a channel is enabled, it's messages will be sent to the registered error handler callback function.
	 If a channel is disabled, it's messages will be discarded.)

	Note: This function will return success if the given channel is already set to the given status.

	Pram enabled: If enabled is set to zero, the given channel will be disabled.
	If enabled is set to a non-zero value, the given channel will be enabled.

	Returns COMMON_ERROR_SUCCESS if setting the channel's status was successful.
	Returns COMMON_ERROR_INVALID_ARGUMENT if the given channel ID is invalid / not recognized.
 */
MSYS_DLL_EXPORT int Common_Error_Set_Logging_Channel_Status_By_ID_Number(const int channelID, const short enabled);

#ifdef __cplusplus
}	/* extern "C" */
#endif	/* __cplusplus */

#endif	/* COMMON_ERROR_HANDLER_LOG_CHANNEL_DEFS_H */

/* End of Common_Error_Handler_Log_Channel_Defs.h. */
