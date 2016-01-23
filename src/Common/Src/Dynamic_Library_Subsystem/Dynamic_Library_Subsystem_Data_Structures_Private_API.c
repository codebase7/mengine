/*!
    Multiverse Engine Project 22/1/2016 Dynamic_Library_Subsystem Dynamic_Library_Subsystem_Data_Structures_Private_API.c

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

/* Internal includes */
#include "Dynamic_Library_Subsystem.h"
#include "Dynamic_Library_Subsystem_Data_Structures_Private_API.h"
#include "../../../Core/Src/DataProcess.h"
#include "../Error_Handler/Common_Error_Handler_Internal.h"
#include "../Error_Handler/Common_Error_Handler_Structures.h"

/* Check for C++ Compiler. */
#ifdef __cplusplus
/* Define extern C. */
extern "C" {
#endif	/* __cplusplus	 */
		int Common_Dynamic_Library_Subsystem_Create_Loaded_Dynamic_Library_Private(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private ** lib)
		{
			/* Init vars. */
			int ret = COMMON_ERROR_UNKNOWN_ERROR;
			int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;
			Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private * result = NULL;

			/* Check for valid arguments. */
			if (lib != NULL)
			{
				/* Create the referece. */
				retFromCall = DataProcess_Reallocate_C_String(((char**)(&result)), 0, sizeof(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private));

				/* Check for a valid result. */
				if ((retFromCall == COMMON_ERROR_SUCCESS) && (result != NULL))
				{
					/* Initilize the vars. */
					result->pathToLibrary = NULL;	/* Avoid potential non-NULL causing a memory deallocation attempt for a pointer that is not allocated. */
					Common_Dynamic_Library_Subsystem_Blank_Loaded_Dynamic_Library_Private(result);

					/* Copy the pointer to lib. */
					(*lib) = result;

					/* Success. */
					ret = COMMON_ERROR_SUCCESS;
				}
				else
				{
					/* Could not init structure. */
					ret = ((retFromCall != COMMON_ERROR_SUCCESS) ? (retFromCall) : (COMMON_ERROR_INTERNAL_ERROR));
					COMMON_LOG_DEBUG("Common_Dynamic_Library_Subsystem_Create_Loaded_Dynamic_Library_Private(): Memory allocation function returned: ");
					COMMON_LOG_DEBUG(Common_Get_Error_Message(retFromCall));
					COMMON_LOG_DEBUG(" Could not allocate memory for management structure.");
				}
			}
			else
			{
				/* Invalid lib pointer. */
				ret = COMMON_ERROR_INVALID_ARGUMENT;
			}

			/* Return result. */
			return ret;
		}

		void Common_Dynamic_Library_Subsystem_Destroy_Loaded_Dynamic_Library_Private(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private ** lib)
		{
			/* Check for valid pointer. */
			if ((lib != NULL) && ((*lib) != NULL))
			{
				/* Free the structure. */
				DataProcess_Deallocate_CString(((char **)(lib)));
			}

			/* Exit function. */
			return;
		}

		void Common_Dynamic_Library_Subsystem_Blank_Loaded_Dynamic_Library_Private(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private * lib)
		{
			/* Check for valid pointer. */
			if (lib != NULL)
			{
				/* Clear the data. */
				lib->bIsLoaded = false;
				lib->bLastCallEncounteredAnError = false;
				lib->osSpecificPointerData = NULL;

				/* Check for set pathToLibrary. */
				if (lib->pathToLibrary != NULL)
				{
					/* Deallocate memory for the pathToLibrary variable. */
					DataProcess_Deallocate_CString(&(lib->pathToLibrary));
				}
			}

			/* Exit function. */
			return;
		}

		int Common_Dynamic_Library_Subsystem_Get_IsLoaded_Loaded_Dynamic_Library_Private(const Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private * lib)
		{
			/* Init vars. */
			int ret = COMMON_ERROR_UNKNOWN_ERROR;

			/* Check for valid pointer. */
			if (lib != NULL)
			{
				/* Check bIsLoaded. */
				ret = ((lib->bIsLoaded) ? (COMMON_ERROR_TRUE) : (COMMON_ERROR_FALSE));
			}
			else
			{
				/* Invalid lib pointer. */
				ret = COMMON_ERROR_INVALID_ARGUMENT;
			}

			/* Exit function. */
			return ret;
		}

		int Common_Dynamic_Library_Subsystem_Set_IsLoaded_Loaded_Dynamic_Library_Private(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private * lib, const bool value)
		{
			/* Init vars. */
			int ret = COMMON_ERROR_UNKNOWN_ERROR;

			/* Check for valid pointer. */
			if (lib != NULL)
			{
				/* Set bIsLoaded. */
				lib->bIsLoaded = value;

				/* Success. */
				ret = COMMON_ERROR_SUCCESS;
			}
			else
			{
				/* Invalid lib pointer. */
				ret = COMMON_ERROR_INVALID_ARGUMENT;
			}

			/* Exit function. */
			return ret;
		}

		int Common_Dynamic_Library_Subsystem_Get_LastCallEncounteredError_Loaded_Dynamic_Library_Private(const Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private * lib)
		{
			/* Init vars. */
			int ret = COMMON_ERROR_UNKNOWN_ERROR;

			/* Check for valid pointer. */
			if (lib != NULL)
			{
				/* Check bLastCallEncounteredAnError. */
				ret = ((lib->bLastCallEncounteredAnError) ? (COMMON_ERROR_TRUE) : (COMMON_ERROR_FALSE));
			}
			else
			{
				/* Invalid lib pointer. */
				ret = COMMON_ERROR_INVALID_ARGUMENT;
			}

			/* Exit function. */
			return ret;
		}

		int Common_Dynamic_Library_Subsystem_Set_LastCallEncounteredError_Loaded_Dynamic_Library_Private(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private * lib, const bool value)
		{
			/* Init vars. */
			int ret = COMMON_ERROR_UNKNOWN_ERROR;

			/* Check for valid pointer. */
			if (lib != NULL)
			{
				/* Set bLastCallEncounteredAnError. */
				lib->bLastCallEncounteredAnError = value;

				/* Success. */
				ret = COMMON_ERROR_SUCCESS;
			}
			else
			{
				/* Invalid lib pointer. */
				ret = COMMON_ERROR_INVALID_ARGUMENT;
			}

			/* Exit function. */
			return ret;
		}

		int Common_Dynamic_Library_Subsystem_Get_OsSpecificPointerData_Loaded_Dynamic_Library_Private(const Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private * lib, void ** retVar)
		{
			/* Init vars. */
			int ret = COMMON_ERROR_UNKNOWN_ERROR;

			/* Check for valid pointer. */
			if ((lib != NULL) && (retVar != NULL))
			{
				/* Get the osSpecificPointerData and copy it to retVar. */
				(*retVar) = lib->osSpecificPointerData;

				/* Success. */
				ret = COMMON_ERROR_SUCCESS;
			}
			else
			{
				/* Invalid lib pointer. */
				ret = COMMON_ERROR_INVALID_ARGUMENT;
			}

			/* Exit function. */
			return ret;
		}

		int Common_Dynamic_Library_Subsystem_Set_OsSpecificPointerData_Loaded_Dynamic_Library_Private(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private * lib, void * value)
		{
			/* Init vars. */
			int ret = COMMON_ERROR_UNKNOWN_ERROR;

			/* Check for valid pointer. */
			if (lib != NULL)
			{
				/* Copy the pointer value to osSpecificPointerData. */
				lib->osSpecificPointerData = value;

				/* Success. */
				ret = COMMON_ERROR_SUCCESS;
			}
			else
			{
				/* Invalid lib pointer. */
				ret = COMMON_ERROR_INVALID_ARGUMENT;
			}

			/* Exit function. */
			return ret;
		}

		int Common_Dynamic_Library_Subsystem_Get_PathToLibrary_Loaded_Dynamic_Library_Private(const Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private * lib, const char ** retVar)
		{
			/* Init vars. */
			int ret = COMMON_ERROR_UNKNOWN_ERROR;

			/* Check for valid pointer. */
			if ((lib != NULL) && (retVar != NULL))
			{
				/* Get the pathToLibrary pointer and copy it to retVar. */
				(*retVar) = lib->pathToLibrary;

				/* Success. */
				ret = COMMON_ERROR_SUCCESS;
			}
			else
			{
				/* Invalid lib pointer. */
				ret = COMMON_ERROR_INVALID_ARGUMENT;
			}

			/* Exit function. */
			return ret;
		}

		int Common_Dynamic_Library_Subsystem_Set_PathToLibrary_Loaded_Dynamic_Library_Private(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private * lib, const char * value, const size_t valueLength)
		{
			/* Init vars. */
			int ret = COMMON_ERROR_UNKNOWN_ERROR;
			int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;
			char * tempPath = NULL;

			/* Check for valid pointer. */
			if ((lib != NULL) && (((value == NULL) && (valueLength == 0)) || ((value != NULL) && (valueLength > 0))))
			{
				/* OK, allocate memory. If needed. */
				if ((value != NULL) && (valueLength > 0))
				{
					/* Allocate memory. */
					retFromCall = DataProcess_Reallocate_C_String(&tempPath, 0, valueLength);
					if ((retFromCall == COMMON_ERROR_SUCCESS) && (tempPath != NULL))
					{
						/* Copy the path string. */
						memcpy(tempPath, value, valueLength);
					}
					else
					{
						/* Could not allocate memory for path string. */
						ret = ((retFromCall != COMMON_ERROR_SUCCESS) ? (retFromCall) : (COMMON_ERROR_INTERNAL_ERROR));
						COMMON_LOG_DEBUG("Common_Dynamic_Library_Subsystem_Set_PathToLibrary_Loaded_Dynamic_Library_Private(): Memory allocation function returned: ");
						COMMON_LOG_DEBUG(Common_Get_Error_Message(retFromCall));
						COMMON_LOG_DEBUG(" Could not allocate memory for library path.");
					}
				}

				/* Check for unknown error. */
				if (ret == COMMON_ERROR_UNKNOWN_ERROR)
				{
					/* Check for allocated pathToLibrary. */
					if (lib->pathToLibrary != NULL)
					{
						/* Deallocate the path string. */
						DataProcess_Deallocate_CString(&(lib->pathToLibrary));
					}

					/* Check and see if we need to copy the tempPath pointer. */
					if (tempPath != NULL)
					{
						/* Copy the tempPath pointer to the structure. */
						lib->pathToLibrary = tempPath;
					}

					/* Success. */
					ret = COMMON_ERROR_SUCCESS;
				}
			}
			else
			{
				/* Invalid lib pointer. */
				ret = COMMON_ERROR_INVALID_ARGUMENT;
			}

			/* Exit function. */
			return ret;
		}

#ifdef __cplusplus
}		/* End of extern C. */
#endif	/* __cplusplus	*/
