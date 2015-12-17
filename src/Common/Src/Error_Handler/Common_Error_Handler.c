/*!
    Multiverse Engine Project 23/6/2014 Common Common_Error_Handler.c

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

/* Internal includes. */
#include "Common_Error_Handler.h"		/* Main header. */
#include "Common_Error_Handler_Internal.h"	/* Private internal header that defines the structure used for error logging. */

/* Only include the mutex header if needed by the fatal error handler. */
#ifdef MSYS_BUILD_FATAL_ERROR_SUPPORT
#ifdef _WIN32
#include "..\Mutexes\MSYS_Mutexes.h"		/* Internal mutex support. */
#else
#include "../Mutexes/MSYS_Mutexes.h"		/* Internal mutex support. */
#endif	/* _WIN32 */
#endif	/* MSYS_BUILD_FATAL_ERROR_SUPPORT */

/* Enable C linkage if needed. */
#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/*!
 * 	static int Common_commonLastErrorCode
 * 
 * 	Contains the last error code encountered by a Common namespace function.
 * 
 * 	Note: Calling Common_GetErrorMessage() or Common_GetErrorTableSize()
 * 	will NOT clear this variable.
 * 	Calling any other Common namespace function WILL clear this variable.
 */
static int Common_commonLastErrorCode = COMMON_ERROR_SUCCESS;

void Common_Set_Error_Log_Level(const unsigned int logLevel)
{
	/* Set the log level. */
	commonErrorLoggingData.errorLogLevel = logLevel;

	/* Exit function. */
	return;
}

unsigned int Common_Get_Error_Log_Level()
{
	/* Return the current log level. */
	return commonErrorLoggingData.errorLogLevel;
}

void Common_Register_Error_Log_Callback(void (*loggingFunction)(const unsigned int logLevel, const char * errorMsg))
{
	/* Check and see if the pointer is NULL. */
	if (loggingFunction == NULL)
	{
		/* Set the log level to ERROR_DISABLE. */
		commonErrorLoggingData.errorLogLevel = ERROR_DISABLE;
		commonErrorLoggingData.loggingFunct = NULL;
	}
	else
	{
		/* Set the pointer. */
		commonErrorLoggingData.loggingFunct = loggingFunction;
	}

	/* Exit function. */
	return;
}

/* Build the Fatal Error Handler if needed. */
#ifdef MSYS_BUILD_FATAL_ERROR_SUPPORT
/*!
 * 	static size_t registeredFatalErrorCallbackFunctionsSize
 *
 * 	This size_t is used to remember the allocated size of the registeredFatalErrorCallbackFunctions array.
 */
static size_t registeredFatalErrorCallbackFunctionsSize = 0;

/*
 * 	static Common_pErrorCallBackFunction * registeredFatalErrorCallbackFunctions
 *
 * 	This pointer to an array contains the callback functions (registered with Common::Register_Fatal_Error_Callback())
 * 	used to notify the engine's subsystems and the application that a fatal error has occured and the engine's
 * 	process is about to be terminated by the host system.
 */
static Common_pErrorCallBackFunction * registeredFatalErrorCallbackFunctions = NULL;

/*!
 * 	static MSYS_Mutex * fatalErrorHandlerMutex
 *
 * 	This pointer is to an MSYS_Mutex object that is used to control access to the registered fatal error handler
 * 	function pointer list and it's size value.
 */
static MSYS_Mutex * fatalErrorHandlerMutex = NULL;

bool Common_Register_Fatal_Error_Callback(const Common_pErrorCallBackFunction fatalErrorNotifyFunction)
{
	/* Init vars. */
	bool ret = false;										/* The result of this function. */
	size_t previousErrorListSize = registeredFatalErrorCallbackFunctionsSize;			/* The size of the previous error list. */
	size_t newErrorListSize = 0;									/* The size of the new error list we are creating. */
	size_t x = 0;											/* Counter used in for loops. */
	Common_pErrorCallBackFunction * previousErrorList = registeredFatalErrorCallbackFunctions;	/* The previous error list. */
	Common_pErrorCallBackFunction * newErrorList = NULL;						/* The new error list we are creating. */
	MSYS_Mutex * retFromLockMutex = NULL;								/* The result from the call to MSYS_Lock_Mutex(). */

	/* Check for a valid mutex. */
	if (fatalErrorHandlerMutex == NULL)
	{
		/* Allocate the mutex. */
		fatalErrorHandlerMutex = MSYS_Create_Mutex();
	}

	/* Lock the error handler mutex. */
	retFromLockMutex = MSYS_Lock_Mutex(fatalErrorHandlerMutex);
	if ((retFromLockMutex != NULL) && (retFromLockMutex == fatalErrorHandlerMutex))
	{
		/* Check for valid function pointer. */
		if (fatalErrorNotifyFunction != NULL)
		{
			/* Check for a error function list. */
			if ((previousErrorList != NULL) && (previousErrorListSize > 0))
			{
				/* Re-allocate the error list. */
				newErrorList = (Common_pErrorCallBackFunction *)malloc((sizeof(Common_pErrorCallBackFunction) * (previousErrorListSize + 1)));
				if (newErrorList != NULL)
				{
					/* Update the size info. */
					newErrorListSize = (previousErrorListSize + 1);

					/* Copy the data. */
					for (x = 0; x < previousErrorListSize; x++)
					{
						newErrorList[x] = previousErrorList[x];
					}
				}
			}
			else
			{
				/* Allocate the error list. */
				newErrorList = (Common_pErrorCallBackFunction *)malloc(sizeof(Common_pErrorCallBackFunction));
				if (newErrorList != NULL)
				{
					/* Update the size info. */
					newErrorListSize = 1;
				}
			}

			/* Check for a valid list. */
			if ((previousErrorListSize + 1) == newErrorListSize)
			{
				/* Register the function. */
				newErrorList[(previousErrorListSize)] = fatalErrorNotifyFunction;

				/* Copy the new list pointer, and size info. */
				registeredFatalErrorCallbackFunctions = newErrorList;
				registeredFatalErrorCallbackFunctionsSize = newErrorListSize;

				/* Check and see if we need to deallocate the previousErrorList. */
				if ((previousErrorList != NULL) && (previousErrorList != newErrorList) && (previousErrorListSize > 0))
				{
					/* Null out the old pointer list. */
					for (x = 0; x < previousErrorListSize; x++)
					{
						previousErrorList[x] = NULL;
					}

					/* Deallocate the old array. */
					free(previousErrorList);
					previousErrorList = NULL;
					previousErrorListSize = 0;
				}

				/* We are done. */
				ret = true;
			}
		}

		/* Release the error handler mutex. */
		MSYS_Unlock_Mutex(fatalErrorHandlerMutex);
	}

	/* Return the result. */
	return ret;
}

bool Common_Unregister_Fatal_Error_Callback(const Common_pErrorCallBackFunction fatalErrorNotifyFunction)
{
	/* Init vars. */
	bool ret = false;										/* The result of this function. */
	size_t previousErrorListSize = registeredFatalErrorCallbackFunctionsSize;			/* The size of the previous error list. */
	size_t newErrorListSize = 0;									/* The size of the new error list we are creating. */
	size_t x = 0;													/* Counter used in top level for loops. */
	size_t y = 0;													/* Counter used in sub level 1 for loops. */
	Common_pErrorCallBackFunction * previousErrorList = registeredFatalErrorCallbackFunctions;	/* The previous error list. */
	Common_pErrorCallBackFunction * newErrorList = NULL;						/* The new error list we are creating. */
	MSYS_Mutex * retFromLockMutex = NULL;								/* The result from the call to MSYS_Lock_Mutex(). */

	/* Lock the error handler mutex. */
	retFromLockMutex = MSYS_Lock_Mutex(fatalErrorHandlerMutex);
	if ((retFromLockMutex != NULL) && (retFromLockMutex == fatalErrorHandlerMutex))
	{
		/* Check for valid function pointer. */
		if (fatalErrorNotifyFunction != NULL)
		{
			/* Check for a error function list. */
			if ((previousErrorList != NULL) && (previousErrorListSize > 0))
			{
				/* Check the existing list for that function. */
				for (x = 0; ((newErrorList == NULL) && (x < previousErrorListSize)); x++)
				{
					/* Check for the correct function, to see if the function was registered previously. */
					if (previousErrorList[x] == fatalErrorNotifyFunction)
					{
						/* Found the function, so re-allocate the error list so we can remove it. */
						newErrorList = (Common_pErrorCallBackFunction *)malloc((sizeof(Common_pErrorCallBackFunction) * (previousErrorListSize - 1)));
						if (newErrorList != NULL)
						{
							/* Update the size info. */
							newErrorListSize = (previousErrorListSize - 1);
						}
					}
				}

				/* Only continue if the list was reallocated due to us finding the function to remove. */
				if ((newErrorList != NULL) && (newErrorListSize == (previousErrorListSize - 1)))
				{
					/* Copy the data. */
					for (x = 0, y = 0; ((x < previousErrorListSize) && (y < newErrorListSize)); x++)
					{
						/* Make sure we don't copy the pointer we are removing. */
						if (previousErrorList[x] != fatalErrorNotifyFunction)
						{
							/* Copy the pointer, and increment y. (Yes, y can be different than x, because it will not contain every pointer.) */
							newErrorList[y] = previousErrorList[x];
							y++;
						}
					}

					/* Now that the data is copied, copy the pointers. */
					registeredFatalErrorCallbackFunctions = newErrorList;
					registeredFatalErrorCallbackFunctionsSize = newErrorListSize;

					/* Deallocate the old list. */
					if ((previousErrorList != NULL) && (previousErrorList != newErrorList) && (previousErrorListSize > 0))
					{
						/* Null out the old pointer list. */
						for (x = 0; x < previousErrorListSize; x++)
						{
							previousErrorList[x] = NULL;
						}

						free(previousErrorList);
						previousErrorList = NULL;
						previousErrorListSize = 0;
					}

					/* Done. */
					ret = true;
				}
			}
		}

		/* Release the error handler mutex. */
		MSYS_Unlock_Mutex(fatalErrorHandlerMutex);
	}

	/* Return the result. */
	return ret;
}

void Common_Fatal_Error_Notify()
{
	/* Init vars. */
	MSYS_Mutex * retFromLockMutex = NULL;						/* The result from the call to MSYS_Lock_Mutex(). */
	size_t x = 0;												/* Counter used in loops. */

	/* Lock the error handler mutex. */
	retFromLockMutex = MSYS_Lock_Mutex(fatalErrorHandlerMutex);
	if ((retFromLockMutex != NULL) && (retFromLockMutex == fatalErrorHandlerMutex))
	{
		/* Check for registered fatal error callbacks. */
		if (registeredFatalErrorCallbackFunctionsSize > 0)
		{
			/* Begin vector iteration loop. */
			for (x = 0; (x < registeredFatalErrorCallbackFunctionsSize); x++)
			{
				/* Trigger each function. */
				if (registeredFatalErrorCallbackFunctions[x] != NULL)
				{
					registeredFatalErrorCallbackFunctions[x]();
				}
			}
		}

		/* Release the error handler mutex. */
		MSYS_Unlock_Mutex(fatalErrorHandlerMutex);
	}

	/* Exit function. */
	return;
}

#endif	/* MSYS_BUILD_FATAL_ERROR_SUPPORT */

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
		/* Call the callback. (Hope it returns....) */
		commonErrorLoggingData.loggingFunct(loggingLevel, errorMsg);
	}

	/* Exit function. */
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

/* End C Linkage if needed. */
#ifdef __cplusplus
}
#endif	/* __cplusplus */
