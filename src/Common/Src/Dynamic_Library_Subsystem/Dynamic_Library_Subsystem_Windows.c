/*!
    Multiverse Engine Project 28/3/2014 Dynamic_Library_Subsystem Dynamic_Library_Subsystem_Windows.c

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
#include "Dynamic_Library_Subsystem_Syscall.h"
#include "../Error_Handler/Common_Error_Handler_Structures.h"
#include "../Error_Handler/Common_Error_Handler_Error_Codes.h"
#include "../Error_Handler/Windows_Error_Translation_Table.h"

/* External includes. */
#include <windows.h>

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
		HMODULE callResult = NULL;						/* The result of the call to LoadLibraryEx(). */
		DWORD retLLEX = 0;								/* Error code from LoadLibraryEx(). */

		/* Check for invalid arguments. */
		if ((pathToLibrary != NULL) && (pathToLibraryLength > 0) && (osSpecificPointerData != NULL))
		{
			/* Call LoadLibraryEx(). */
			callResult = LoadLibraryEx(pathToLibrary, NULL, 0);

			/* Check the callResult. */
			if (callResult == NULL)
			{
				/* Get the last error. */
				retLLEX = GetLastError();
				ret = Common_Translate_Windows_Error_Code_To_Common_Error_Code(retLLEX);
			}
			else
			{
				/* Cast the OS specific data structure pointer to void*.  */
				(*osSpecificPointerData) = ((void*)callResult);
				
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
		DWORD retFL = 0;								/* Error code from FreeLibrary(). */
		
		/* Check for invalid arguments. */
		if (osData != NULL)
		{
			/* Call FreeLibrary. */
			if (FreeLibrary((HMODULE)osData))
			{
				/* The library was unloaded successfully. */
				ret = COMMON_ERROR_SUCCESS;
			}
			else
			{
				/* Get the last error. */
				retFL = GetLastError();
				ret = Common_Translate_Windows_Error_Code_To_Common_Error_Code(retFL);
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

	int Common_Dynamic_Library_Subsystem_Get_Symbol_Syscall(void * osData, const char * symbolName, const size_t symbolNameLength, void ** retSym)
	{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */
		int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;	/* The result of calls to other engine functions. */
		DWORD retGPA = 0;								/* Error code from GetProcAddress(). */
		void * pSym = NULL;								/* The returned symbol pointer. */
		
		/* Check for invalid arguments. */
		if ((osData != NULL) && (symbolName != NULL) && (retSym != NULL))
		{
			/* Get the address. */
			pSym = (void*)GetProcAddress((HMODULE)osData, symbolName);
			if (pSym == NULL)
			{
				/* Get the last error. */
				retGPA = GetLastError();
				ret = Common_Translate_Windows_Error_Code_To_Common_Error_Code(retGPA);
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
		
		/* Exit function. */
		return ret;
	}
	
#ifdef __cplusplus
}		/* End of extern C. */
#endif	/* __cplusplus */

