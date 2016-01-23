/*!
    Multiverse Engine Project 01/4/2014 Dynamic_Library_Subsystem Dynamic_Library_Subsystem_POSIX.c

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

/* Check for linux. */
#ifdef __linux__

/* Internal includes */
#include "Dynamic_Library_Subsystem_Syscall.h"
#include "../Error_Handler/Common_Error_Handler_Structures.h"

/* External includes. */
#include <dlfcn.h>	/* dlopen, dlclose, dlsym, dlerror. */

/* Check for C++ Compiler. */
#ifdef __cplusplus
/* Define extern C. */
extern "C" {
#endif	/* __cplusplus */
	int Common_Dynamic_Library_Subsystem_Load_Library_Syscall(const char * pathToLibrary, const size_t pathToLibraryLength, void ** osSpecificPointerData)
	{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */
		int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;	/* The result of calls to other engine functions. */
		void * callResult = NULL;						/* The result of the call to dlopen(). */
		char * hostErr = NULL;							/* The result returned from dlerror(). */

		/* Check for invalid arguments. */
		if ((pathToLibrary != NULL) && (pathToLibraryLength > 0) && (osSpecificPointerData != NULL))
		{
			/* Call dlopen(). */
			callResult = dlopen(pathToLibrary, RTLD_LAZY | RTLD_LOCAL);

			/* Check the callResult. */
			if (callResult == NULL)
			{
				/* An error occured.
					There is no clean way to check the error given here, as dlerror() returns a human-readable string.
					In addition, dlopen() does not have any defined error codes in the POSIX standard.
					As such we have no way of returning the specific error encountered to the caller,
					so we must return COMMON_ERROR_SYSTEM_SPECIFIC.
				 */
				ret = COMMON_ERROR_SYSTEM_SPECIFIC;

				/* Could not load the library. */
				hostErr = dlerror();
				COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Load_Library_Syscall(): Could not load <");
				COMMON_LOG_VERBOSE(pathToLibrary);
				COMMON_LOG_VERBOSE("> Host function returned: ");
				COMMON_LOG_VERBOSE(hostErr);
			}
			else
			{
				/* Cast the OS specific data structure pointer to void*. */
				(*osSpecificPointerData) = (void*)callResult;

				/* Success. */
				ret = COMMON_ERROR_SUCCESS;
			}
		}
		else
		{
			/* Invalid argument. */
			ret = COMMON_ERROR_INVALID_ARGUMENT;
		}

		/* Exit function. */
		return ret;
	}

	int Common_Dynamic_Library_Subsystem_Unload_Library_Syscall(void * osData)
	{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */
		int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;	/* The result of calls to other engine functions. */
		char * hostErr = NULL;							/* The result returned from dlerror(). */

		/* Check for invalid arguments. */
		if (osData != NULL)
		{
			/* Call dlclose(). */
			retFromCall = dlclose(osData);
			if (retFromCall == 0)
			{
				/* The library was unloaded successfully. */
				ret = COMMON_ERROR_SUCCESS;
			}
			else
			{
				/* An error occured.
					There is no clean way to check the error given here, as dlerror() returns a human-readable string.
					In addition, dlclose() does not have any defined error codes in the POSIX standard.
					As such we have no way of returning the specific error encountered to the caller,
					so we must return COMMON_ERROR_SYSTEM_SPECIFIC.
				 */
				ret = COMMON_ERROR_SYSTEM_SPECIFIC;

				/* Could not load the library. */
				hostErr = dlerror();
				COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Unload_Library_Syscall(): Could not unload given library.");
				COMMON_LOG_VERBOSE(" Host function returned: ");
				COMMON_LOG_VERBOSE(hostErr);
			}
		}
		else
		{
			/* Invalid argument. */
			ret = COMMON_ERROR_INVALID_ARGUMENT;
		}

		/* Return result. */
		return ret;
	}

	int Common_Dynamic_Library_Subsystem_Get_Symbol_Syscall(void * osData, const char * symbolName, const size_t symbolNameLength, void ** retSym)
	{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */
		int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;	/* The result of calls to other engine functions. */
		void * pSym = NULL;								/* The returned symbol pointer. */
		char * hostErr = NULL;							/* The result returned from dlerror(). */

		/* Check for invalid arguments. */
		if ((osData != NULL) && (symbolName != NULL) && (retSym != NULL))
		{
			/* Call dlerror to clear the error state. */
			dlerror();

			/* Call dlsym. */
			pSym = dlsym(osData, symbolName);
			
			/* Call dlerror again to check for an error. */
			hostErr = dlerror();
			if (hostErr != NULL)
			{
				/* An error occured.
					There is no clean way to check the error given here, as dlerror() returns a human-readable string.
					In addition, dlsym() does not have any defined error codes in the POSIX standard.
					As such we have no way of returning the specific error encountered to the caller,
					so we must return COMMON_ERROR_SYSTEM_SPECIFIC.
				 */
				ret = COMMON_ERROR_SYSTEM_SPECIFIC;
				
				/* An error occured fetching the symbol. */
				COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Get_Symbol_Syscall(): Could not fetch symbol.");
				COMMON_LOG_VERBOSE(" Host function returned: ");
				COMMON_LOG_VERBOSE(hostErr);
			}
			else
			{
				/* Copy pSym to retSym. */
				(*retSym) = pSym;

				/* Success. */
				ret = COMMON_ERROR_SUCCESS;
			}
		}
		else
		{
			/* Invalid argument. */
			ret = COMMON_ERROR_INVALID_ARGUMENT;
		}					

		/* Return result. */
		return ret;
	}

#ifdef __cplusplus
}		/* End of extern C. */
#endif	/* __cplusplus */
#endif	/* __linux__ */
