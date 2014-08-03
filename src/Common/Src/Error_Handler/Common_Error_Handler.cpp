/*!
    Multiverse Engine Project 23/6/2014 Common Common_Error_Handler.cpp

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

#include "Common_Error_Handler.h"		// Main header.
#include "Common_Error_Handler_Internal.h"	// Private internal header that defines the structure used for error logging.

const unsigned int Common::Get_Error_Table_Size()
{
	return (sizeof(Common::commonErrorTable) / sizeof(Common_Error_Object));
}

const char * Common::Get_Error_Message(const int & errorCode)
{
	// Init vars.
	const char * result = Common::UNKNOWN_ERROR_MSG;		// Result of this function.
	const size_t errorTableSize = Common::Get_Error_Table_Size();	// Size of the Common error lookup table.

	// Begin lookup loop.
	for (size_t x = 0; ((x < errorTableSize) && (result == NULL)); x++)
	{
		// Check for the correct error code.
		if (Common::commonErrorTable[x].errorCode == errorCode)
		{
			// Found the correct error code.
			result = Common::commonErrorTable[x].error;
		}
	}

	// Return the result.
	return result;
}

void Common::Set_Error_Log_Level(const unsigned int & logLevel)
{
	// Set the log level.
	commonErrorLoggingData.errorLogLevel = logLevel;

	// Exit function.
	return;
}

unsigned int Common::Get_Error_Log_Level()
{
	// Return the current log level.
	return commonErrorLoggingData.errorLogLevel;
}

void Common::Register_Error_Log_Callback(void (*loggingFunction)(const unsigned int logLevel, const char * errorMsg))
{
	// Check and see if the pointer is NULL.
	if (loggingFunction == NULL)
	{
		// Set the log level to ERROR_DISABLE.
		commonErrorLoggingData.errorLogLevel = ERROR_DISABLE;
	}

	// Set the pointer.
	commonErrorLoggingData.loggingFunct = loggingFunction;

	// Exit function.
	return;
}

void COMMON_LOG_ERROR(const unsigned int loggingLevel, const char * errorMsg)
{
	/*
	 * 	Only do something if the log is enabled,
	 * 	the error is at or below our current log level,
	 * 	and the logging callback function is defined.
	 * 
	 * 	Note: The lower the log level, the higher severity of the error.
	 */
	if ((commonErrorLoggingData.errorLogLevel != ERROR_DISABLE) &&
	    (commonErrorLoggingData.loggingFunct != NULL) &&
	    (loggingLevel <= commonErrorLoggingData.errorLogLevel))
	{
		// Call the callback. (Hope it returns....)
		commonErrorLoggingData.loggingFunct(loggingLevel, errorMsg);
	}

	// Exit function.
	return;
}

void COMMON_LOG_CRITICAL(const char * errorMsg)
{
	COMMON_LOG_ERROR(ERROR_CRITICAL, errorMsg);
	return;
}

void COMMON_LOG_WARNING(const char * errorMsg)
{
	COMMON_LOG_ERROR(ERROR_WARNING, errorMsg);
	return;
}

void COMMON_LOG_INFO(const char * errorMsg)
{
	COMMON_LOG_ERROR(ERROR_INFO, errorMsg);
	return;
}

void COMMON_LOG_DEBUG(const char * errorMsg)
{
	COMMON_LOG_ERROR(ERROR_DEBUG, errorMsg);
	return;
}

void COMMON_LOG_VERBOSE(const char * errorMsg)
{
	COMMON_LOG_ERROR(ERROR_VERBOSE, errorMsg);
	return;
}
