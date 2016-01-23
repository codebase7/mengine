/*!
    Multiverse Engine Project 01/4/2014 Dynamic_Library_Subsystem Dynamic_Library_Subsystem_Data_Structures.c

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
		int Common_Dynamic_Library_Subsystem_Get_API_Version()
		{
			/* Return the API Version number. */
			return MSYS_DYNAMIC_LIBRARY_SUBSYSTEM_API_LEVEL;
		}

		int Common_Dynamic_Library_Subsystem_Create_Loaded_Dynamic_Library(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library ** lib)
		{
			/* Init vars. */
			int ret = COMMON_ERROR_UNKNOWN_ERROR;
			int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;
			Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library * result = NULL;

			/* Check for valid arguments. */
			if (lib != NULL)
			{
				/* Create the referece. */
				retFromCall = DataProcess_Reallocate_C_String(((char**)(&result)), 0, sizeof(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library));

				/* Check for a valid result. */
				if ((retFromCall == COMMON_ERROR_SUCCESS) && (result != NULL))
				{
					/* Set the pointer to NULL. */
					result->pointer = NULL;

					/* Call the real function. */
					ret = Common_Dynamic_Library_Subsystem_Create_Loaded_Dynamic_Library_Private(((Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private **)(&(result->pointer))));
				}
				else
				{
					/* Could not init structure. */
					ret = ((retFromCall != COMMON_ERROR_SUCCESS) ? (retFromCall) : (COMMON_ERROR_INTERNAL_ERROR));
					COMMON_LOG_DEBUG("Common_Dynamic_Library_Subsystem_Create_Loaded_Dynamic_Library(): Memory allocation function returned: ");
					COMMON_LOG_DEBUG(Common_Get_Error_Message(retFromCall));
					COMMON_LOG_DEBUG(" Could not allocate memory for management structure.");
				}
			}
			else
			{
				/* Invalid lib pointer. */
				ret = COMMON_ERROR_INVALID_ARGUMENT;
				COMMON_LOG_DEBUG("Common_Dynamic_Library_Subsystem_Create_Loaded_Dynamic_Library(): ");
				COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
			}

			/* Return result. */
			return ret;
		}

		void Common_Dynamic_Library_Subsystem_Destroy_Loaded_Dynamic_Library(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library ** lib)
		{
			/* Check for valid pointer. */
			if ((lib != NULL) && ((*lib) != NULL))
			{
				/* Check for allocated pointer. */
				if ((*lib)->pointer != NULL)
				{
					/* Deallocate the pointer. */
					Common_Dynamic_Library_Subsystem_Destroy_Loaded_Dynamic_Library_Private(((Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private **)(&((*lib)->pointer))));
				}

				/* Free the structure. */
				DataProcess_Deallocate_CString(((char **)(lib)));
			}

			/* Exit function. */
			return;
		}

		void Common_Dynamic_Library_Subsystem_Blank_Loaded_Dynamic_Library(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library * lib)
		{
			/* Check for valid pointers. */
			if ((lib != NULL) && (lib->pointer != NULL))
			{
				/* Call real function. */
				Common_Dynamic_Library_Subsystem_Blank_Loaded_Dynamic_Library_Private(((Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private *)(lib->pointer)));
			}

			/* Exit function. */
			return;
		}

		int Common_Dynamic_Library_Subsystem_Get_IsLoaded_Loaded_Dynamic_Library(const Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library * lib)
		{
			/* Init vars. */
			int ret = COMMON_ERROR_UNKNOWN_ERROR;

			/* Check for valid pointers. */
			if ((lib != NULL) && (lib->pointer != NULL))
			{
				/* Call real function. */
				ret = Common_Dynamic_Library_Subsystem_Get_IsLoaded_Loaded_Dynamic_Library_Private(((Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private *)(lib->pointer)));
				if (ret == COMMON_ERROR_INVALID_ARGUMENT)
				{
					/* That's an error, we didn't set up the private data structure correctly or it's been corrupted. */
					COMMON_LOG_DEBUG("Common_Dynamic_Library_Subsystem_Get_IsLoaded_Loaded_Dynamic_Library(): ");
					COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
					COMMON_LOG_DEBUG(" Private API data structure pointer is invalid.");
				}
			}
			else
			{
				/* Invalid lib pointer. */
				ret = COMMON_ERROR_INVALID_ARGUMENT;
				COMMON_LOG_DEBUG("Common_Dynamic_Library_Subsystem_Get_IsLoaded_Loaded_Dynamic_Library(): ");
				COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
			}

			/* Exit function. */
			return ret;
		}

		int Common_Dynamic_Library_Subsystem_Set_IsLoaded_Loaded_Dynamic_Library(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library * lib, const bool value)
		{
			/* Init vars. */
			int ret = COMMON_ERROR_UNKNOWN_ERROR;

			/* Check for valid pointers. */
			if ((lib != NULL) && (lib->pointer != NULL))
			{
				/* Call real function. */
				ret = Common_Dynamic_Library_Subsystem_Set_IsLoaded_Loaded_Dynamic_Library_Private(((Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private *)(lib->pointer)), value);
				if (ret == COMMON_ERROR_INVALID_ARGUMENT)
				{
					/* That's an error, we didn't set up the private data structure correctly or it's been corrupted. */
					COMMON_LOG_DEBUG("Common_Dynamic_Library_Subsystem_Set_IsLoaded_Loaded_Dynamic_Library(): ");
					COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
					COMMON_LOG_DEBUG(" Private API data structure pointer is invalid.");
				}
			}
			else
			{
				/* Invalid lib pointer. */
				ret = COMMON_ERROR_INVALID_ARGUMENT;
				COMMON_LOG_DEBUG("Common_Dynamic_Library_Subsystem_Set_IsLoaded_Loaded_Dynamic_Library(): ");
				COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
			}

			/* Exit function. */
			return ret;
		}

		int Common_Dynamic_Library_Subsystem_Get_LastCallEncounteredError_Loaded_Dynamic_Library(const Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library * lib)
		{
			/* Init vars. */
			int ret = COMMON_ERROR_UNKNOWN_ERROR;

			/* Check for valid pointers. */
			if ((lib != NULL) && (lib->pointer != NULL))
			{
				/* Call real function. */
				ret = Common_Dynamic_Library_Subsystem_Get_LastCallEncounteredError_Loaded_Dynamic_Library_Private(((Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private *)(lib->pointer)));
				if (ret == COMMON_ERROR_INVALID_ARGUMENT)
				{
					/* That's an error, we didn't set up the private data structure correctly or it's been corrupted. */
					COMMON_LOG_DEBUG("Common_Dynamic_Library_Subsystem_Get_LastCallEncounteredError_Loaded_Dynamic_Library(): ");
					COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
					COMMON_LOG_DEBUG(" Private API data structure pointer is invalid.");
				}
			}
			else
			{
				/* Invalid lib pointer. */
				ret = COMMON_ERROR_INVALID_ARGUMENT;
				COMMON_LOG_DEBUG("Common_Dynamic_Library_Subsystem_Get_LastCallEncounteredError_Loaded_Dynamic_Library(): ");
				COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
			}

			/* Exit function. */
			return ret;
		}

		int Common_Dynamic_Library_Subsystem_Set_LastCallEncounteredError_Loaded_Dynamic_Library(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library * lib, const bool value)
		{
			/* Init vars. */
			int ret = COMMON_ERROR_UNKNOWN_ERROR;

			/* Check for valid pointers. */
			if ((lib != NULL) && (lib->pointer != NULL))
			{
				/* Call real function. */
				ret = Common_Dynamic_Library_Subsystem_Set_LastCallEncounteredError_Loaded_Dynamic_Library_Private(((Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private *)(lib->pointer)), value);
				if (ret == COMMON_ERROR_INVALID_ARGUMENT)
				{
					/* That's an error, we didn't set up the private data structure correctly or it's been corrupted. */
					COMMON_LOG_DEBUG("Common_Dynamic_Library_Subsystem_Set_LastCallEncounteredError_Loaded_Dynamic_Library(): ");
					COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
					COMMON_LOG_DEBUG(" Private API data structure pointer is invalid.");
				}
			}
			else
			{
				/* Invalid lib pointer. */
				ret = COMMON_ERROR_INVALID_ARGUMENT;
				COMMON_LOG_DEBUG("Common_Dynamic_Library_Subsystem_Set_LastCallEncounteredError_Loaded_Dynamic_Library(): ");
				COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
			}

			/* Exit function. */
			return ret;
		}

		int Common_Dynamic_Library_Subsystem_Get_OsSpecificPointerData_Loaded_Dynamic_Library(const Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library * lib, void ** retVar)
		{
			/* Init vars. */
			int ret = COMMON_ERROR_UNKNOWN_ERROR;

			/* Check for valid pointers. */
			if ((lib != NULL) && (lib->pointer != NULL) && (retVar != NULL))
			{
				/* Call real function. */
				ret = Common_Dynamic_Library_Subsystem_Get_OsSpecificPointerData_Loaded_Dynamic_Library_Private(((Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private *)(lib->pointer)), retVar);
				if (ret == COMMON_ERROR_INVALID_ARGUMENT)
				{
					/* That's an error, we didn't set up the private data structure correctly or it's been corrupted. */
					COMMON_LOG_DEBUG("Common_Dynamic_Library_Subsystem_Get_OsSpecificPointerData_Loaded_Dynamic_Library(): ");
					COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
					COMMON_LOG_DEBUG(" Private API data structure pointer is invalid.");
				}
			}
			else
			{
				/* Invalid lib pointer. */
				ret = COMMON_ERROR_INVALID_ARGUMENT;
				COMMON_LOG_DEBUG("Common_Dynamic_Library_Subsystem_Get_OsSpecificPointerData_Loaded_Dynamic_Library(): ");
				COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
			}

			/* Exit function. */
			return ret;
		}

		int Common_Dynamic_Library_Subsystem_Set_OsSpecificPointerData_Loaded_Dynamic_Library(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library * lib, void * value)
		{
			/* Init vars. */
			int ret = COMMON_ERROR_UNKNOWN_ERROR;

			/* Check for valid pointers. */
			if ((lib != NULL) && (lib->pointer != NULL))
			{
				/* Call real function. */
				ret = Common_Dynamic_Library_Subsystem_Set_OsSpecificPointerData_Loaded_Dynamic_Library_Private(((Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private *)(lib->pointer)), value);
				if (ret == COMMON_ERROR_INVALID_ARGUMENT)
				{
					/* That's an error, we didn't set up the private data structure correctly or it's been corrupted. */
					COMMON_LOG_DEBUG("Common_Dynamic_Library_Subsystem_Set_OsSpecificPointerData_Loaded_Dynamic_Library(): ");
					COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
					COMMON_LOG_DEBUG(" Private API data structure pointer is invalid.");
				}
			}
			else
			{
				/* Invalid lib pointer. */
				ret = COMMON_ERROR_INVALID_ARGUMENT;
				COMMON_LOG_DEBUG("Common_Dynamic_Library_Subsystem_Set_OsSpecificPointerData_Loaded_Dynamic_Library(): ");
				COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
			}

			/* Exit function. */
			return ret;
		}

		int Common_Dynamic_Library_Subsystem_Get_PathToLibrary_Loaded_Dynamic_Library(const Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library * lib, const char ** retVar)
		{
			/* Init vars. */
			int ret = COMMON_ERROR_UNKNOWN_ERROR;

			/* Check for valid pointers. */
			if ((lib != NULL) && (lib->pointer != NULL) && (retVar != NULL))
			{
				/* Call real function. */
				ret = Common_Dynamic_Library_Subsystem_Get_PathToLibrary_Loaded_Dynamic_Library_Private(((Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private *)(lib->pointer)), retVar);
				if (ret == COMMON_ERROR_INVALID_ARGUMENT)
				{
					/* That's an error, we didn't set up the private data structure correctly or it's been corrupted. */
					COMMON_LOG_DEBUG("Common_Dynamic_Library_Subsystem_Get_PathToLibrary_Loaded_Dynamic_Library(): ");
					COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
					COMMON_LOG_DEBUG(" Private API data structure pointer is invalid.");
				}
			}
			else
			{
				/* Invalid lib pointer. */
				ret = COMMON_ERROR_INVALID_ARGUMENT;
				COMMON_LOG_DEBUG("Common_Dynamic_Library_Subsystem_Get_PathToLibrary_Loaded_Dynamic_Library(): ");
				COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
			}

			/* Exit function. */
			return ret;
		}

		int Common_Dynamic_Library_Subsystem_Set_PathToLibrary_Loaded_Dynamic_Library(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library * lib, const char * value, const size_t valueLength)
		{
			/* Init vars. */
			int ret = COMMON_ERROR_UNKNOWN_ERROR;
			int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;
			char * tempPath = NULL;

			/* Check for valid pointers. */
			if ((lib != NULL) && (lib->pointer != NULL) && (((value == NULL) && (valueLength == 0)) || ((value != NULL) && (valueLength > 0))))
			{
				/* Call real function. */
				ret = Common_Dynamic_Library_Subsystem_Set_PathToLibrary_Loaded_Dynamic_Library_Private(((Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private *)(lib->pointer)), value, valueLength);
				if (ret == COMMON_ERROR_INVALID_ARGUMENT)
				{
					/* That's an error, we didn't set up the private data structure correctly or it's been corrupted. */
					COMMON_LOG_DEBUG("Common_Dynamic_Library_Subsystem_Set_PathToLibrary_Loaded_Dynamic_Library(): ");
					COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
					COMMON_LOG_DEBUG(" Private API data structure pointer is invalid.");
				}
			}
			else
			{
				/* Invalid lib pointer. */
				ret = COMMON_ERROR_INVALID_ARGUMENT;
				COMMON_LOG_DEBUG("Common_Dynamic_Library_Subsystem_Set_PathToLibrary_Loaded_Dynamic_Library(): ");
				COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
			}

			/* Exit function. */
			return ret;
		}

#ifdef __cplusplus
}		/* End of extern C. */
#endif	/* __cplusplus	*/
