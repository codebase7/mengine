/*!
    Multiverse Engine Project 12/2/2016 Common Common_Error_Handler_Log_Channel_Defs.c

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

/* Include headers. */
#include "Common_Error_Handler_Log_Channel_Defs.h"
#include "Common_Error_Handler_Error_Codes.h"

/* External includes. */
#include <stddef.h>
#include <string.h>

/* Define Common_Error_Log_Channel_Status structure.

	Used internally for managing the states of each logging channel.
*/
typedef struct Common_Error_Log_Channel_Status {
	short disabled;					/* Whether or not this channel is disabled. (Messages for disabled channels are discarded.) */
	const int channelID;			/* Internal ID number of the channel. */
	const size_t channelNameLength;	/* Length of the human readable channel name. */
	const char * const channelName;	/* Human readable channel name. */
} Common_Error_Log_Channel_Status;

/* Define the internal array for storing the channel statuses.

	Contains a definition for each supported logging channel.
*/
static Common_Error_Log_Channel_Status commonErrorLoggingChannelStatuses[] = {
	{0, MSYS_ERROR_LOG_CHANNEL_UNDEFINED, sizeof(MSYS_ERROR_LOG_CHANNEL_UNDEFINED_NAME), MSYS_ERROR_LOG_CHANNEL_UNDEFINED_NAME},
	{0, MSYS_ERROR_LOG_CHANNEL_USERDEFINED, sizeof(MSYS_ERROR_LOG_CHANNEL_USERDEFINED_NAME), MSYS_ERROR_LOG_CHANNEL_USERDEFINED_NAME},
	{0, MSYS_ERROR_LOG_CHANNEL_ERROR_HANDLER, sizeof(MSYS_ERROR_LOG_CHANNEL_ERROR_HANDLER_NAME), MSYS_ERROR_LOG_CHANNEL_ERROR_HANDLER_NAME},
	{0, MSYS_ERROR_LOG_CHANNEL_DYNLIB, sizeof(MSYS_ERROR_LOG_CHANNEL_DYNLIB_NAME), MSYS_ERROR_LOG_CHANNEL_DYNLIB_NAME},
	{0, MSYS_ERROR_LOG_CHANNEL_BYTEORDER, sizeof(MSYS_ERROR_LOG_CHANNEL_BYTEORDER_NAME), MSYS_ERROR_LOG_CHANNEL_BYTEORDER_NAME},
	{0, MSYS_ERROR_LOG_CHANNEL_FILEUTILLS, sizeof(MSYS_ERROR_LOG_CHANNEL_FILEUTILLS_NAME), MSYS_ERROR_LOG_CHANNEL_FILEUTILLS_NAME},
	{0, MSYS_ERROR_LOG_CHANNEL_THREADUTILS, sizeof(MSYS_ERROR_LOG_CHANNEL_THREADUTILS_NAME), MSYS_ERROR_LOG_CHANNEL_THREADUTILS_NAME},
	{0, MSYS_ERROR_LOG_CHANNEL_RENDERING_SUBSYS, sizeof(MSYS_ERROR_LOG_CHANNEL_RENDERING_SUBSYS_NAME), MSYS_ERROR_LOG_CHANNEL_RENDERING_SUBSYS_NAME},
};

size_t Common_Error_Get_Length_Of_Internal_Status_Array()
{
	/* Internal function to return the length of the commonErrorLoggingChannelStatuses array.

		Should NOT be called outside of this file.
	*/
	return ((sizeof(Common_Error_Log_Channel_Status) / sizeof(commonErrorLoggingChannelStatuses)));
}

int Common_Error_Get_Logging_Channel_ID_Number_By_Name(int * channelID, const char * name, const size_t nameLength)
{
	/* Init vars. */
	int ret = COMMON_ERROR_INVALID_ARGUMENT;	/* The result of this function. */
	size_t x = 0;								/* Counter used in the for loop. */

	/* Check for valid arguments. */
	if ((channelID != NULL) && (name != NULL) && (nameLength > 0))
	{
		/* Begin search loop. */
		for (x = 0; ((ret == COMMON_ERROR_INVALID_ARGUMENT) && (x < Common_Error_Get_Length_Of_Internal_Status_Array())); x++)
		{
			/* Check the current struct in the array for the given channel name length. */
			if (commonErrorLoggingChannelStatuses[x].channelNameLength == nameLength)
			{
				/* Check for a valid name pointer. */
				if (commonErrorLoggingChannelStatuses[x].channelName != NULL)
				{
					/* Check the current struct in the array for the given channel name. */
					if (memcmp(name, commonErrorLoggingChannelStatuses[x].channelName, nameLength) == 0)
					{
						/* Copy the channel ID value. */
						(*channelID) = commonErrorLoggingChannelStatuses[x].channelID;

						/* Done. */
						ret = COMMON_ERROR_SUCCESS;
					}
				}
			}
		}
	}

	/* Exit function. */
	return ret;
}

int Common_Error_Get_Logging_Channel_Name_By_ID_Number(const int channelID, const char ** name, size_t * nameLength)
{
	/* Init vars. */
	int ret = COMMON_ERROR_INVALID_ARGUMENT;	/* The result of this function. */
	size_t x = 0;								/* Counter used in the for loop. */

	/* Check for valid arguments. */
	if ((name != NULL) && (nameLength != NULL))
	{
		/* Begin search loop. */
		for (x = 0; ((ret == COMMON_ERROR_INVALID_ARGUMENT) && (x < Common_Error_Get_Length_Of_Internal_Status_Array())); x++)
		{
			/* Check the current struct in the array for the given ID number. */
			if (commonErrorLoggingChannelStatuses[x].channelID == channelID)
			{
				/* Copy the pointer for the name and the value for the length. */
				(*name) = commonErrorLoggingChannelStatuses[x].channelName;
				(*nameLength) = commonErrorLoggingChannelStatuses[x].channelNameLength;

				/* Done. */
				ret = COMMON_ERROR_SUCCESS;
			}
		}
	}

	/* Exit function. */
	return ret;
}

int Common_Error_Get_Logging_Channel_Status_By_ID_Number(const int channelID)
{
	/* Init vars. */
	int ret = COMMON_ERROR_INVALID_ARGUMENT;	/* The result of this function. */
	size_t x = 0;								/* Counter used in the for loop. */

	/* Begin search loop. */
	for (x = 0; ((ret == COMMON_ERROR_INVALID_ARGUMENT) && (x < Common_Error_Get_Length_Of_Internal_Status_Array())); x++)
	{
		/* Check the current struct in the array for the given ID number. */
		if (commonErrorLoggingChannelStatuses[x].channelID == channelID)
		{
			/* Check and see if the channel is enabled.
				Returns COMMON_ERROR_TRUE if the channel is enabled, or
				Returns COMMON_ERROR_FALSE if the channel is disabled.
			*/
			ret = ((commonErrorLoggingChannelStatuses[x].disabled) ? (COMMON_ERROR_FALSE) : (COMMON_ERROR_TRUE));
		}
	}

	/* Exit function. */
	return ret;
}

int Common_Error_Set_Logging_Channel_Status_By_ID_Number(const int channelID, const short enabled)
{
	/* Init vars. */
	int ret = COMMON_ERROR_INVALID_ARGUMENT;	/* The result of this function. */
	size_t x = 0;								/* Counter used in the for loop. */

	/* Begin search loop. */
	for (x = 0; ((ret == COMMON_ERROR_INVALID_ARGUMENT) && (x < Common_Error_Get_Length_Of_Internal_Status_Array())); x++)
	{
		/* Check the current struct in the array for the given ID number. */
		if (commonErrorLoggingChannelStatuses[x].channelID == channelID)
		{
			/* Set the channel status.
				Set commonErrorLoggingChannelStatuses[x].disabled to non-zero value if the channel should be disabled.
				Set commonErrorLoggingChannelStatuses[x].disabled to zero if the channel should be enabled.
			*/
			commonErrorLoggingChannelStatuses[x].disabled = ((enabled) ? (0) : (1));

			/* Done. */
			ret = COMMON_ERROR_SUCCESS;
		}
	}

	/* Exit function. */
	return ret;
}
